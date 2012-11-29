/*
 * BlockBuffer.h
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

#ifndef BLOCKBUFFER_H_
#define BLOCKBUFFER_H_

#include "../Debug.h"
#include "../buffer/IBufferObserver.h"
#include "../Block.h"
#include "../portable/MultiThreading.h"
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <queue>

#define DEFAULTBUFFERLENGTH 30000

namespace dash
{
    namespace buffer
    {
        class BlockBuffer
        {
            public:
                BlockBuffer           (size_t capacityMilliSec);
                virtual ~BlockBuffer  ();

                void    put             (block_t *block);
                int     get             (uint8_t *p_data, size_t len);
                int     peek            (uint8_t *p_data, size_t len);
                void    setEOF          (bool value);
                bool    getEOF          ();
                void    attach          (IBufferObserver *observer);
                void    notify          ();
                float   getSizeMilliSec ();

            private:
                size_t                          capacityMilliSec;
                float                           sizeMilliSec;
                size_t                          sizeBytes;
                CRITICAL_SECTION                monitorMutex;
                CONDITION_VARIABLE              empty;
                CONDITION_VARIABLE              full;
                bool                            isEOF;
                std::queue<dash::block_t *>     blockQueue;
                std::vector<IBufferObserver *>  bufferObservers;

                void blockQueueGetBytes(uint8_t *p_data, size_t bytes);
        };
    }
}

#endif /* BLOCKBUFFER_H_ */
