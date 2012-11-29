/*
 * PersistentHTTPConnection.h
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
#ifndef PERSISTENTHTTPCONNECTION_H_
#define PERSISTENTHTTPCONNECTION_H_

#include "HTTPConnection.h"
#include <queue>

#define RETRY 5

namespace dash
{
    namespace http
    {
        class PersistentHTTPConnection : public HTTPConnection
        {
            public:
                PersistentHTTPConnection            ();
                virtual ~PersistentHTTPConnection   ();

                virtual int         read        (void *p_buffer, unsigned int len);
                virtual bool        init        (Chunk *chunk);
                bool                addChunk    (Chunk *chunk);
                const std::string&  getHostname ();
                bool                isConnected ();

            private:
                std::queue<Chunk *> chunkQueue;
                bool                isInit;
                std::string         hostname;

            protected:
                virtual std::string prepareRequest  (Chunk *chunk);
                bool                initChunk       (Chunk *chunk);
                bool                reconnect       (Chunk *chunk);
        };
    }
}

#endif /* PERSISTENTHTTPCONNECTION_H_ */