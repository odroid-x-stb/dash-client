/*
 * Representation.cpp
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

#include "Representation.h"

using namespace dash::mpd;

Representation::Representation  () :
                segmentInfo     (NULL),
                segmentBase     (NULL),
                segmentList     (NULL),
                width           (0),
                height          (0),
                bitrate         (0),
                isDependent     (false)
{
}
Representation::~Representation ()
{
    delete(this->segmentInfo);
}

long                Representation::getBitrate      () const
{
    return this->bitrate;
}
void                Representation::setBitrate      (long bitrate)
{
    this->bitrate = bitrate;
}
SegmentInfo*        Representation::getSegmentInfo  () const
{
    return this->segmentInfo;
}
void                Representation::setSegmentInfo  (SegmentInfo *info)
{
    this->segmentInfo = info;
}
void                Representation::setWidth        (int width)
{
    this->width = width;
}
int                 Representation::getWidth        () const
{
    return this->width;
}
void                Representation::setHeight       (int height)
{
    this->height = height;
}
int                 Representation::getHeight       () const
{
    return this->height;
}
SegmentList*        Representation::getSegmentList  () const
{
    return this->segmentList;
}
void                Representation::setSegmentList  (SegmentList *list)
{
    this->segmentList = list;
}
SegmentBase*        Representation::getSegmentBase  () const
{
    return this->segmentBase;
}
void                Representation::setSegmentBase  (SegmentBase *base)
{
    this->segmentBase = base;
}
void                Representation::setId           (const std::string &id)
{
    this->id = id;
}
const std::string&  Representation::getId           () const
{
    return this->id;
}
void                Representation::setDependencyId (const std::string &depId)
{
    this->depId = depId;
}
const std::string&  Representation::getDependencyId () const
{
    return this->depId;
}
void                Representation::setDependency   (bool value)
{
    this->isDependent = value;
}
bool                Representation::hasDependency   () const
{
    return this->isDependent;
}