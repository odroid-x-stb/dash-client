/*
 * PersistentHTTPConnection.cpp
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

#include "PersistentHTTPConnection.h"

using namespace dash::http;


PersistentHTTPConnection::PersistentHTTPConnection() : HTTPConnection(), isInit(false)
{
}

PersistentHTTPConnection::~PersistentHTTPConnection()
{
}

int PersistentHTTPConnection::read(void *p_buffer, unsigned int len)
{
  Chunk *readChunk = this->chunkQueue.front();

  if(readChunk == NULL)
    return -1;

  if(readChunk->getBytesRead() == 0)
    {
      if(!this->initChunk(readChunk))
        {
	  this->chunkQueue.pop();
	  return -1;
        }
    }

  if(readChunk->getBytesToRead() == 0)
    {
      this->chunkQueue.pop();
      return 0;
    }

  int ret = 0;
  if(len > readChunk->getBytesToRead())
    ret = HTTPConnection::read(p_buffer, readChunk->getBytesToRead());
  else
    ret = HTTPConnection::read(p_buffer, len);

  if(ret <= 0)
    {
      readChunk->setStartByte(readChunk->getStartByte() + readChunk->getBytesRead());
      readChunk->setBytesRead(0);
      if(!this->reconnect(readChunk))
        {
	  this->chunkQueue.pop();
	  return -1;
        }

      return this->read(p_buffer, len);
    }

  readChunk->setBytesRead(readChunk->getBytesRead() + ret);

  DMSG("Persistent Conncection Read: " << ret 
       << " Length: " << readChunk->getLength()
       << " Downloaded: " << readChunk->getBytesRead())

    return ret;
}

std::string PersistentHTTPConnection::prepareRequest(Chunk *chunk)
{
  std::string request;
  if(!chunk->useByteRange())
    {
      request = "GET "    + chunk->getPath()     + " HTTP/1.1" + "\r\n" +
	"Host: "  + chunk->getHostname() + "\r\n\r\n";
    }
  else
    {
      std::stringstream req;
      req << "GET " << chunk->getPath() << " HTTP/1.1\r\n" <<
	"Host: " << chunk->getHostname() << "\r\n" <<
	"Range: bytes=" << chunk->getStartByte() << "-" << chunk->getEndByte() << "\r\n\r\n";

      request = req.str();
    }
  return request;
}

bool PersistentHTTPConnection::init(Chunk *chunk)
{
  if(this->isInit)
    return true;

  if(!chunk->hasHostname())
    return false;

  if(!this->connectToHost(chunk->getHostname(), 80))
    return false;

  if(this->sendData(this->prepareRequest(chunk)))
    this->isInit = true;

  this->chunkQueue.push(chunk);
  this->hostname = chunk->getHostname();

  return this->isInit;
}

bool PersistentHTTPConnection::addChunk(Chunk *chunk)
{
  if(!this->isInit)
    return this->init(chunk);

  if(!chunk->hasHostname() || chunk->getHostname().compare(this->hostname))
    return false;

  if(this->sendData(this->prepareRequest(chunk)))
    {
      this->chunkQueue.push(chunk);
      return true;
    }

  return false;
}

bool PersistentHTTPConnection::initChunk(Chunk *chunk)
{
  if(this->parseHeader())
    {
      chunk->setLength(this->contentLength);
      return true;
    }

  if(!this->reconnect(chunk))
    return false;

  if(this->parseHeader())
    {
      chunk->setLength(this->contentLength);
      return true;
    }

  return false;
}

bool PersistentHTTPConnection::reconnect(Chunk *chunk)
{
  int retry = 0;
  std::string request = this->prepareRequest(chunk);

  while(retry < RETRY)
    {
      if(this->connectToHost(chunk->getHostname(), 80))
	if(this->sendData(request))
	  return true;

      retry++;
    }

  return false;
}

const std::string& PersistentHTTPConnection::getHostname()
{
  return this->hostname;
}

bool PersistentHTTPConnection::isConnected()
{
  return this->isInit;
}
