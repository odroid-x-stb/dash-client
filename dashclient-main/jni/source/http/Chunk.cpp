/*
 * Chunk.cpp
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

#include "Chunk.h"

using namespace dash::http;

Chunk::Chunk            () :
       bitrate          (-1),
       isByteRangeSet   (false),
       startByte        (-1),
       endByte          (-1),
       isHostname       (false),
       connection       (NULL),
       length           (0),
       bytesRead        (0)
{
}
Chunk::~Chunk           ()
{
}

int                 Chunk::getEndByte           () const
{
    return endByte;
}
int                 Chunk::getStartByte         () const
{
    return startByte;
}
const std::string&  Chunk::getUrl               () const
{
    return url;
}
void                Chunk::setEndByte           (int endByte)
{
    this->endByte = endByte;
}
void                Chunk::setStartByte         (int startByte)
{
    this->startByte = startByte;
}
void                Chunk::setUrl               (std::string url)
{
    this->url      = url;
    this->hostname = url;
    this->hostname.erase(0, 7);
    this->path = this->hostname;

    size_t pos = this->hostname.find("/");

    this->hostname  = this->hostname.substr(0, pos);
    this->path      = this->path.substr(pos, this->path.size());
    this->isHostname = true;
}
const std::string&  Chunk::getPath              () const
{
    return this->path;
}
int64_t             Chunk::getBitrate           () const
{
    return this->bitrate;
}
void                Chunk::setBitrate           (int64_t bitrate)
{
    this->bitrate = bitrate;
}
bool                Chunk::useByteRange         () const
{
    return this->isByteRangeSet;
}
std::string         Chunk::getName              () const
{
    size_t pos = this->url.find_last_of("/") + 1;

    return this->url.substr(pos, this->url.size());
}
void                Chunk::addOptionalUrl       (const std::string& url)
{
    this->optionalUrls.push_back(url);
}
void                Chunk::setUseByteRange      (bool value)
{
    this->isByteRangeSet = value;
}
void                Chunk::print                ()
{
    std::cout << "=== Chunk Info Start ==="   << std::endl;
    std::cout << "Url: "        << this->url << std::endl;

    if(this->isByteRangeSet)
    {
        std::cout << "StartByte: " << this->startByte << std::endl;
        std::cout << "EndByte: " << this->endByte << std::endl;
    }

    std::cout << "Bitrate: "    << this->bitrate << std::endl;
    std::cout << "=== Chunk Info End ==="   << std::endl;
}
bool                Chunk::hasHostname          () const
{
    return this->isHostname;
}
const std::string&  Chunk::getHostname          () const
{
    return this->hostname;
}
IHTTPConnection*    Chunk::getConnection        () const
{
    return this->connection;
}
void                Chunk::setConnection        (IHTTPConnection *connection)
{
    this->connection = connection;
}
size_t              Chunk::getLength            () const
{
    return this->length;
}
void                Chunk::setLength            (size_t length)
{
    this->length = length;
}
size_t              Chunk::getBytesRead         () const
{
    return this->bytesRead;
}
void                Chunk::setBytesRead         (size_t bytes)
{
    this->bytesRead = bytes;
}
size_t              Chunk::getBytesToRead       () const
{
    return this->length - this->bytesRead;
}
size_t              Chunk::getPercentDownloaded () const
{
    return (size_t)(((float)this->bytesRead / this->length) * 100);
}
size_t              Chunk::getSegmentIndex         () const
{
    return this->segmentindex;
}
void                Chunk::setSegmentIndex (size_t index)
{
    this->segmentindex = index;
}