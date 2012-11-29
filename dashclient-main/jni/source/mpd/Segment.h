/*
 * Segment.h
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

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "../http/Chunk.h"
#include "../mpd/BaseUrl.h"

#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

namespace dash
{
    namespace mpd
    {
        class Segment
        {
            public:
                Segment             ();
                virtual ~Segment    ();

                const std::string&  getDependencyId () const;
                bool                hasDependency   () const;
                const std::string&  getSourceUrl    () const;
                int                 getStartByte    () const;
                int                 getEndByte      () const;
                long                getBitrate      () const;
                
                void                setDependencyId (const std::string &depId);
                void                setDependency   (bool value);
                void                setSourceUrl    (const std::string &url);
                bool                useByteRange    ();
                void                setUseByteRange (bool useByteRange);
                void                setStartByte    (int startByte);
                void                setEndByte      (int endByte);
                void                setBitrate      (long bitrate);
                void                setByteRange    (int start, int end);
                dash::http::Chunk*  toChunk         ();

                void                            addBaseUrl      (BaseUrl *url);
                const std::vector<BaseUrl *>&   getBaseUrls     () const;

            private:
                std::string url;
                bool        hasByteRange;
                int         startByte;
                int         endByte;
                long        bitrate;
                bool        isDependent;
                std::string depId;

                std::vector<BaseUrl *>  baseUrls;
        };
    }
}

#endif /* SEGMENT_H_ */
