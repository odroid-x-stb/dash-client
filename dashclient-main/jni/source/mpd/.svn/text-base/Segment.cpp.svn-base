/*
 * Segment.cpp
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

#include "Segment.h"

using namespace dash::mpd;
using namespace dash::http;

Segment::Segment        () :
         hasByteRange   (false),
         startByte      (-1),
         endByte        (-1),
         bitrate        (-1),
         isDependent    (false)
{
}
Segment::~Segment       ()
{
}

const std::string&              Segment::getSourceUrl       () const
{
    return this->url;
}
void                            Segment::setSourceUrl       (const std::string &url)
{
    this->url = url;
}
bool                            Segment::useByteRange       ()
{
    return this->hasByteRange;
}
void                            Segment::setUseByteRange    (bool useByteRange)
{
    this->hasByteRange = useByteRange;
}
int                             Segment::getStartByte       () const
{
    return this->startByte;
}
void                            Segment::setStartByte       (int startByte)
{
    this->startByte = startByte;
}
int                             Segment::getEndByte         () const
{
    return this->endByte;
}
void                            Segment::setEndByte         (int endByte)
{
    this->endByte = endByte;
}
long                            Segment::getBitrate         ()const 
{
    return this->bitrate;
}
void                            Segment::setBitrate         (long bitrate)
{
    this->bitrate = bitrate;
}
dash::http::Chunk*              Segment::toChunk            ()
{
    Chunk *chunk = new Chunk();

    if(this->startByte != -1 && this->endByte != -1)
    {
        chunk->setUseByteRange(true);
        chunk->setStartByte(this->startByte);
        chunk->setEndByte(this->endByte);
    }

    if(this->baseUrls.size() > 0)
    {
        std::stringstream ss;
        ss << this->baseUrls.at(0)->getUrl() << this->url;
        chunk->setUrl(ss.str());
        ss.clear();

        for(size_t i = 1; i < this->baseUrls.size(); i++)
        {
            ss << this->baseUrls.at(i)->getUrl() << this->url;
            chunk->addOptionalUrl(ss.str());
            ss.clear();
        }
    }
    else
    {
        chunk->setUrl(this->url);
    }

    chunk->setBitrate(this->bitrate);
    return chunk;
}
void                            Segment::setByteRange       (int start, int end)
{
    this->startByte = start;
    this->endByte   = end;
}
void                            Segment::addBaseUrl         (BaseUrl *url)
{
    this->baseUrls.push_back(url);
}
const std::vector<BaseUrl *>&   Segment::getBaseUrls        () const
{
    return this->baseUrls;
}
bool                            Segment::hasDependency      () const
{
    return this->isDependent;
}
void                            Segment::setDependency      (bool value)
{
    this->isDependent = value;
}
const std::string&              Segment::getDependencyId    () const
{
    return this->depId;
}
void                            Segment::setDependencyId    (const std::string &depId)
{
    this->depId = depId;
}