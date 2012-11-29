/*
 * StatisticsManager.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Feb 29, 2012
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

#include "StatisticsManager.h"

using namespace dash::statistics;
using namespace dash::http;

StatisticsManager::StatisticsManager    () :
                   bufferedMilliSec     (0),
                   bufferedBytes        (0),
                   bufferedPercent      (0),
                   bpsAvg               (0),
                   bpsLastChunk         (0),
                   bpsCurrentChunk      (0),
                   representation       (0)
{
    this->file.open("log.txt");
}
StatisticsManager::~StatisticsManager   ()
{
    this->file.close();
}

void StatisticsManager::bufferLevelChanged  (float bufferedMilliSeconds, size_t bufferedBytes, size_t bufferedPercent)
{
    this->bufferedMilliSec = bufferedMilliSeconds;
    this->bufferedBytes    = bufferedBytes;
    this->bufferedPercent  = bufferedPercent;
    this->print();
}
void StatisticsManager::downloadRateChanged (int64_t bpsAvg, int64_t bpsLastChunk, int64_t bpsCurrentChunk, Chunk *currentChunk)
{
    this->bpsAvg            = bpsAvg;
    this->bpsLastChunk      = bpsLastChunk;
    this->bpsCurrentChunk   = bpsCurrentChunk;
    this->representation    = currentChunk->getBitrate();
    this->print();
}
void StatisticsManager::print               ()
{
    this->file << "Buffer[Sec:" << (int)this->bufferedMilliSec / 1000 << " KB:" << this->bufferedBytes / 1024 << " Percent:" << this->bufferedPercent <<"]"
        << " Rep (kbit): " << this->representation / 1024
        << " Bandwidth (kbit):" << this->bpsAvg / 1024 << std::endl;
}