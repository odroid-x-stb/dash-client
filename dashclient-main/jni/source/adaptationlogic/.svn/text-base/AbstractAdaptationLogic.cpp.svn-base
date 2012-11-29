/*
 * AbstractAdaptationLogic.cpp
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

#include "AbstractAdaptationLogic.h"

using namespace dash::logic;
using namespace dash::xml;
using namespace dash::mpd;
using namespace dash::http;

AbstractAdaptationLogic::AbstractAdaptationLogic    (IMPDManager *mpdManager) :
                         bpsAvg                     (0),
                         bpsLastChunk               (0),
                         bufferedMilliSec           (0),
                         bufferedPercent            (0),
                         mpdManager                 (mpdManager)
{
}
AbstractAdaptationLogic::~AbstractAdaptationLogic   ()
{
}

void    AbstractAdaptationLogic::downloadRateChanged    (int64_t bpsAvg, int64_t bpsLastChunk, int64_t bpsCurrentChunk, Chunk *currentChunk)
{
    this->bpsAvg        = bpsAvg;
    this->bpsLastChunk  = bpsLastChunk;
}
void    AbstractAdaptationLogic::bufferLevelChanged     (float bufferedMilliSeconds, size_t bufferedBytes, size_t bufferedPercent)
{
    this->bufferedMilliSec  = bufferedMilliSeconds;
    this->bufferedPercent   = bufferedPercent;
}
int64_t AbstractAdaptationLogic::getBpsAvg              ()
{
    return this->bpsAvg;
}
int64_t AbstractAdaptationLogic::getBpsLastChunk        ()
{
    return this->bpsLastChunk;
}
size_t  AbstractAdaptationLogic::getBufferPercent       ()
{
    return this->bufferedPercent;
}
float   AbstractAdaptationLogic::getBufferedMilliSec    ()
{
    return this->bufferedMilliSec;
}