/*
 * Chunk.h
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

#ifndef CHUNK_H_
#define CHUNK_H_

#include <string.h>
#include <vector>
#include <iostream>
#include "IHTTPConnection.h"

namespace dash
{
    namespace http
    {
        class Chunk
        {
            public:
                Chunk           ();
                virtual ~Chunk  ();

                int                 getEndByte              () const;
                int                 getStartByte            () const;
                const std::string&  getUrl                  () const;
                int64_t             getBitrate              () const;
                bool                useByteRange            () const;
                std::string         getName                 () const;
                bool                hasHostname             () const;
                const std::string&  getHostname             () const;
                const std::string&  getPath                 () const;
                IHTTPConnection*    getConnection           () const;
                size_t              getLength               () const;
                size_t              getBytesRead            () const;
                size_t              getBytesToRead          () const;
                size_t              getPercentDownloaded    () const;
                size_t              getSegmentIndex         () const;

                void                setSegmentIndex (size_t index);
                void                setBytesRead    (size_t bytes);
                void                setLength       (size_t length);
                void                setConnection   (IHTTPConnection *connection);
                void                setUseByteRange (bool value);
                void                setBitrate      (int64_t bitrate);
                void                setEndByte      (int endByte);
                void                setStartByte    (int startByte);
                void                setUrl          (std::string url);
                void                addOptionalUrl  (const std::string& url);
                void                print           ();

            private:
                std::string                 url;
                std::string                 hostname;
                std::string                 path;
                std::vector<std::string>    optionalUrls;
                int                         startByte;
                int                         endByte;
                int64_t                     bitrate;
                bool                        isByteRangeSet;
                bool                        isHostname;
                IHTTPConnection             *connection;
                size_t                      length;
                size_t                      bytesRead;
                size_t                      segmentindex;
        };
    }
}

#endif /* CHUNK_H_ */
