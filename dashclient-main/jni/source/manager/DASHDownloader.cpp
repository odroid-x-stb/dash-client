/*
 * DASHDownloader.h
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

#include "DASHDownloader.h"

using namespace dash;
using namespace dash::http;
using namespace dash::logic;
using namespace dash::buffer;

DASHDownloader::DASHDownloader  (HTTPConnectionManager *conManager, BlockBuffer *buffer)
{
    this->t_sys                     = (thread_sys_t *) malloc(sizeof(thread_sys_t));
    this->t_sys->conManager         = conManager;
    this->t_sys->buffer             = buffer;
}
DASHDownloader::~DASHDownloader ()
{
    free(this->t_sys);
    DestroyThreadPortable(this->dlThread);
}

bool DASHDownloader::start      ()
{
    this->dlThread = CreateThreadPortable (DASHDownloader::download, this->t_sys);

    if(this->dlThread == NULL)
        return false;

    return true;
}
void* DASHDownloader::download  (void *thread_sys)
{
    thread_sys_t            *t_sys              = (thread_sys_t *) thread_sys;
    HTTPConnectionManager   *conManager         = t_sys->conManager;
    BlockBuffer             *buffer             = t_sys->buffer;
    block_t                 *block              = AllocBlock(BLOCKSIZE);
    int                     ret                 = 0;
    int64_t                 bitrate             = 0;

    do
    {
        ret = conManager->read(block->p_buffer, block->i_buffer, &bitrate);
        if(ret > 0)
        {
            block_t *bufBlock = AllocBlock(ret);
            memcpy(bufBlock->p_buffer, block->p_buffer, ret);
            bufBlock->i_millisec = (ret * 8) / ((float)bitrate / 1000);
            buffer->put(bufBlock);
        }
    }while(ret);

    DMSG("Download Thread End")
    DeleteBlock(block);
    buffer->setEOF(true);

    return NULL;
}