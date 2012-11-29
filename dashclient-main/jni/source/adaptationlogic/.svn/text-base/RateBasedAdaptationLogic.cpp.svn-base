/*
 * RateBasedAdaptationLogic.cpp
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


#include "RateBasedAdaptationLogic.h"

using namespace dash::logic;
using namespace dash::xml;
using namespace dash::http;
using namespace dash::mpd;

RateBasedAdaptationLogic::RateBasedAdaptationLogic  (IMPDManager *mpdManager) : 
                          AbstractAdaptationLogic   (mpdManager),
                          mpdManager                (mpdManager),
                          count                     (0),
                          rebuffer                  (true)
{
}
RateBasedAdaptationLogic::~RateBasedAdaptationLogic ()
{
}

Chunk*  RateBasedAdaptationLogic::getNextChunk ()
{
    if(this->getBufferPercent() > 80)
        this->rebuffer = false;

    if(this->rebuffer)
        return this->getNextChunk(this->count++, 0);

    if(this->getBufferPercent() < 20)
    {
        this->rebuffer = true;
        return this->getNextChunk(this->count++, 0);
    }

    if(this->segStack.size() != 0)
    {
        Chunk *chunk = this->segStack.top()->toChunk();
        this->segStack.pop();
        chunk->print();
        return chunk;
    }

    return this->getNextChunk(this->count++, this->getBpsAvg());
}
Chunk*  RateBasedAdaptationLogic::getNextChunk (int count, int64_t bitrate)
{
    this->clearStack();
    Segment *seg = this->mpdManager->getSegment(count, bitrate);

    if(seg == NULL)
        return NULL;

    while(seg->hasDependency())
    {
        this->segStack.push(seg);
        seg = this->mpdManager->getSegment(count, seg->getDependencyId());
    }

    Chunk *chunk = seg->toChunk();

    return chunk;
}
void    RateBasedAdaptationLogic::clearStack    ()
{
    while(this->segStack.size() > 0)
    {
        delete(this->segStack.top());
        this->segStack.pop();
    }
}