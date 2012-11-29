/*
 * StatisticsManager.h
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

#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include "../buffer/IBufferObserver.h"
#include "../adaptationlogic/IDownloadRateObserver.h"

#include <iostream>
#include <fstream>

namespace dash
{
    namespace statistics
    {
        class StatisticsManager : public buffer::IBufferObserver, public logic::IDownloadRateObserver
        {
            public:
                StatisticsManager             ();
                virtual ~StatisticsManager    ();

                void bufferLevelChanged     (float bufferedMilliSeconds, size_t bufferedBytes, size_t bufferedPercent);
                void downloadRateChanged    (int64_t bpsAvg, int64_t bpsLastChunk, int64_t bpsCurrentChunk, http::Chunk *currentChunk);
                void print                  ();

            private:
                float           bufferedMilliSec;
                size_t          bufferedBytes;
                size_t          bufferedPercent;
                int64_t         bpsAvg;
                int64_t         bpsLastChunk;
                int64_t         bpsCurrentChunk;
                int64_t         representation;
                std::ofstream   file;
        };
    }
}

#endif /* STATISTICSMANAGER_H_ */
