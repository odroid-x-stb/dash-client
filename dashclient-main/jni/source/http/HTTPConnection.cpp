/*
 * HTTPConnection.cpp
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

#include "HTTPConnection.h"

using namespace dash::http;

HTTPConnection::HTTPConnection  () :
                peekBufferLen   (0),
                contentLength   (0)
{
    this->peekBuffer = new uint8_t[PEEKBUFFER];
}
HTTPConnection::~HTTPConnection ()
{
    delete[] this->peekBuffer;
    this->closeSocket();
}

int             HTTPConnection::read            (void *p_buffer, unsigned int len)
{
    if(this->peekBufferLen == 0)
    {
        int size = recv(this->httpSocket, (char *)p_buffer, len, 0);

        if(size <= 0)
            return 0;

        return size;
    }

    memcpy(p_buffer, this->peekBuffer, this->peekBufferLen);
    int ret = this->peekBufferLen;
    this->peekBufferLen = 0;
    return ret;
}
int             HTTPConnection::peek            (const uint8_t **pp_peek, size_t i_peek)
{
    if(this->peekBufferLen == 0)
        this->peekBufferLen = this->read(this->peekBuffer, PEEKBUFFER);

    int size = i_peek > this->peekBufferLen ? this->peekBufferLen : i_peek;

    uint8_t *peek = new uint8_t [size];
    memcpy(peek, this->peekBuffer, size);
    *pp_peek = peek;
    return size;
}
std::string     HTTPConnection::prepareRequest  (Chunk *chunk)
{
    std::string request;
    if(!chunk->useByteRange())
    {
        request = "GET "      + chunk->getPath()     + " HTTP/1.1" + "\r\n" +
                  "Host: "    + chunk->getHostname() + "\r\n" +
                  "Connection: close\r\n\r\n";
    }
    else
    {
        std::stringstream req;
        req << "GET " << chunk->getPath() << " HTTP/1.1\r\n" <<
               "Host: " << chunk->getHostname() << "\r\n" <<
               "Range: bytes=" << chunk->getStartByte() << "-" << chunk->getEndByte() << "\r\n" <<
               "Connection: close\r\n\r\n";

        request = req.str();
    }

    return request;
}
bool            HTTPConnection::init            (Chunk *chunk)
{
    if(!chunk->hasHostname())
        return false;

    if(!this->connectToHost(chunk->getHostname(), 80))
        return false;

    if(this->sendData(this->prepareRequest(chunk)))
        return this->parseHeader();

    return false;
}
bool            HTTPConnection::parseHeader     ()
{
    std::string line = this->readLine();
    
    if(line.size() == 0)
        return false;

    while(line.compare("\r\n"))
    {
        if(!line.compare(0, 14, "Content-Length"))
            this->contentLength = atoi(line.substr(15,line.size()).c_str());

        line = this->readLine();

        if(line.size() == 0)
            return false;
    }

    return true;
}
std::string     HTTPConnection::readLine        ()
{
    std::stringstream ss;
    char c[1];
    int size = recv(this->httpSocket, c, 1, 0);

    while(size > 0)
    {
        ss << c[0];
        if(c[0] == '\n')
            break;

        size = recv(this->httpSocket, c, 1, 0);
    }

    if(size > 0)
        return ss.str();

    return "";
}
bool            HTTPConnection::sendData        (std::string data)
{
  int size = send(this->httpSocket, data.c_str(), data.size(), 0);
  if (size == -1)
  {
    return false;
  }
  if (size != data.length())
  {
    this->sendData(data.substr(size, data.size()));
  }

  return true;
}
void            HTTPConnection::closeSocket     ()
{
    closesocket(this->httpSocket);
    WSACleanup();
}
bool            HTTPConnection::connectToHost   (std::string host, int port)
{
    WSADATA info;

    if(WSAStartup(MAKEWORD(2,0), &info))
      return false;

    this->httpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&this->addr, 0, sizeof(this->addr));

    this->hostent           = gethostbyname(host.c_str());
    this->addr.sin_family   = AF_INET;
    this->addr.sin_port     = htons(port);
    int result              = 0;
    char **p                = this->hostent->h_addr_list;
    do
    {
        if(*p == NULL)
            return false;

        addr.sin_addr.s_addr    = *reinterpret_cast<unsigned long*>(*p);
        result                  = connect(this->httpSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    }while(result == 1);

    return true;
}