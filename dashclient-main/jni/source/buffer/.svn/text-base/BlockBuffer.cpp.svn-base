/*
 * BlockBuffer.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2011 Klagenfurt University
 *
 * Created on: Aug 10, 2010
 * Authors: Christopher Mueller <christopher.mueller@itec.uni-klu.ac.at>
 *          Christian Timmerer  <christian.timmerer@itec.uni-klu.ac.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "../buffer/BlockBuffer.h"

using namespace dash;
using namespace dash::buffer;

BlockBuffer::BlockBuffer        (size_t capacityMilliSec) :
             sizeMilliSec       (0),
             sizeBytes          (0),
             isEOF              (false),
             capacityMilliSec   (capacityMilliSec)

{
    if(this->capacityMilliSec <= 0)
        this->capacityMilliSec = DEFAULTBUFFERLENGTH;

    InitializeConditionVariable (&this->empty);
    InitializeConditionVariable (&this->full);
    InitializeCriticalSection   (&this->monitorMutex);
}
BlockBuffer::~BlockBuffer       ()
{
    DMSG("Delete buffer queue length: " << this->blockQueue.size() << " Bytes: " << this->sizeBytes)

    while(this->blockQueue.size())
    {
        DeleteBlock(this->blockQueue.front());
        this->blockQueue.pop();
    }
    DeleteConditionVariable(&this->empty);
    DeleteConditionVariable(&this->full);
    DeleteCriticalSection(&this->monitorMutex);
}

int     BlockBuffer::peek                 (uint8_t *p_data, size_t len)
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->sizeBytes == 0 && !this->isEOF)
        SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->sizeBytes == 0)
    {
        WakeAllConditionVariable(&this->empty);
        LeaveCriticalSection(&this->monitorMutex);
        return 0;
    }

    int ret = len > this->sizeBytes ? this->sizeBytes : len;

    DMSG("Peek Bytes: " << ret << " from buffer length: ")

    memcpy(p_data, this->blockQueue.front()->p_buffer, ret);

    DMSG("Buffer length Sec: " << this->sizeMilliSec << " Bytes: ")
    LeaveCriticalSection(&this->monitorMutex);
    return ret;
}
int     BlockBuffer::get                  (uint8_t *p_data, size_t len)
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->sizeBytes == 0 && !this->isEOF)
        SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->sizeBytes == 0)
    {
        WakeAllConditionVariable(&this->empty);
        LeaveCriticalSection(&this->monitorMutex);
        return 0;
    }

    int ret = len > this->sizeBytes ? this->sizeBytes : len;

    DMSG("Get Bytes: " << ret << " from buffer length: " << this->sizeBytes)

    this->blockQueueGetBytes(p_data, ret);

    DMSG("Buffer lengthMilliSec: " << this->sizeMilliSec << " Bytes: " << this->sizeBytes << " QueueLength: " << this->blockQueue.size())

    this->notify();
    WakeAllConditionVariable(&this->empty);
    LeaveCriticalSection(&this->monitorMutex);
    return ret;
}
void    BlockBuffer::put                  (block_t *block)
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->sizeMilliSec >= this->capacityMilliSec && !this->isEOF)
        SleepConditionVariableCS(&this->empty, &this->monitorMutex, INFINITE);

    if(this->isEOF)
    {
        WakeAllConditionVariable(&this->full);
        LeaveCriticalSection(&this->monitorMutex);
        return;
    }

    DMSG("Put MilliSec: " << block->i_millisec << " Bytes: " << block->i_buffer << " into buffer")
    this->sizeMilliSec   += block->i_millisec;
    this->sizeBytes += block->i_buffer;

    this->blockQueue.push(block);

    DMSG("Buffer lengthMilliSec: " << this->sizeMilliSec << " Bytes: " << this->sizeBytes << " QueueLength: " << this->blockQueue.size())

    this->notify();
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
void    BlockBuffer::setEOF               (bool value)
{
    EnterCriticalSection(&this->monitorMutex);
    this->isEOF = value;
    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
bool    BlockBuffer::getEOF               ()
{
    EnterCriticalSection(&this->monitorMutex);
    bool ret = this->isEOF;
    LeaveCriticalSection(&this->monitorMutex);
    return ret;
}
void    BlockBuffer::attach               (IBufferObserver *observer)
{
    this->bufferObservers.push_back(observer);
}
void    BlockBuffer::notify               ()
{
    size_t percent = (size_t) (((float)this->sizeMilliSec / (float)this->capacityMilliSec) * 100);
    for(size_t i = 0; i < this->bufferObservers.size(); i++)
        this->bufferObservers.at(i)->bufferLevelChanged(this->sizeMilliSec, this->sizeBytes, percent);
}
void    BlockBuffer::blockQueueGetBytes   (uint8_t *p_data, size_t bytes)
{
    size_t pos = 0;
    float sec = 0;

    block_t *block = this->blockQueue.front();

    if(bytes < (block->i_buffer - block->i_offset))
    {
        memcpy(p_data + pos, block->p_buffer + block->i_offset, bytes);
        block->i_offset += bytes;

        pos = bytes;
        //sec = ((float)block->i_millisec / (float)block->i_buffer) * bytes;
    }
    else
    {
        memcpy(p_data + pos, block->p_buffer + block->i_offset, block->i_buffer - block->i_offset);
        pos = block->i_buffer - block->i_offset;
        //sec = ((float)block->i_millisec / (float)block->i_buffer) * (block->i_buffer - block->i_offset);
        sec = block->i_millisec;

        DeleteBlock(block);
        this->blockQueue.pop();
    }

    while(pos < bytes)
    {
        block = this->blockQueue.front();
        if((bytes - pos) < (block->i_buffer - block->i_offset))
        {
            memcpy(p_data + pos, block->p_buffer + block->i_offset, bytes - pos);
            block->i_offset += bytes - pos;
            pos = bytes;
            //sec += ((float)block->i_millisec / (float)block->i_buffer) * (bytes - pos);
        }
        else
        {
            memcpy(p_data + pos, block->p_buffer + block->i_offset, block->i_buffer - block->i_offset);
            pos += block->i_buffer;
            sec += block->i_millisec;

            DeleteBlock(block);
            this->blockQueue.pop();
        }
    }

    this->sizeMilliSec  -= sec;
    this->sizeBytes     -= bytes;

    if(this->sizeMilliSec < 0)
        this->sizeMilliSec = 0;

    if(this->sizeBytes == 0)
        this->sizeMilliSec = 0;
}
float   BlockBuffer::getSizeMilliSec      ()
{
    EnterCriticalSection(&this->monitorMutex);
    float ret = this->sizeMilliSec;
    LeaveCriticalSection(&this->monitorMutex);

    return ret;
}