/*
 * HTTPConnection.h
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

#ifndef HTTPCONNECTION_H_
#define HTTPCONNECTION_H_

#include "../Debug.h"
#include "../http/IHTTPConnection.h"
#include "../http/Chunk.h"
#include "../portable/Networking.h"

#include <sstream>
#include <stdint.h>

#define PEEKBUFFER 4096

namespace dash
{
    namespace http
    {
        class HTTPConnection : public IHTTPConnection
        {
            public:
                HTTPConnection          ();
                virtual ~HTTPConnection ();

                virtual bool    init        (Chunk *chunk);
                void            closeSocket ();
                virtual int     read        (void *p_buffer, unsigned int len);
                virtual int     peek        (const uint8_t **pp_peek, size_t i_peek);

            protected:
                int                 httpSocket;
                struct sockaddr_in  addr;
                struct hostent      *hostent;
                uint8_t             *peekBuffer;
                size_t              peekBufferLen;
                int                 contentLength;

                virtual std::string     prepareRequest  (Chunk *chunk);
                bool                    sendData        (std::string data);
                bool                    parseHeader     ();
                std::string             readLine        ();
                bool                    connectToHost   (std::string host, int port);
        };
    }
}

#endif /* HTTPCONNECTION_H_ */
