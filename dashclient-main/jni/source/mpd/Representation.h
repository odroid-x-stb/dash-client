/*
 * Representation.h
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

#ifndef REPRESENTATION_H_
#define REPRESENTATION_H_

#include <string>
#include <vector>
#include <map>

#include "../mpd/SegmentInfo.h"
#include "../mpd/SegmentBase.h"
#include "../mpd/SegmentList.h"

namespace dash
{
    namespace mpd
    {
        class Representation
        {
            public:
                Representation          ();
                virtual ~Representation ();

                void                setDependency   (bool value);
                bool                hasDependency   () const;
                void                setId           (const std::string &id);
                const std::string&  getId           () const;
                void                setDependencyId (const std::string &depId);
                const std::string&  getDependencyId () const;
                long                getBitrate      () const;
                void                setBitrate      (long bitrate);
                void                setSegmentInfo  (SegmentInfo *info);
                SegmentInfo*        getSegmentInfo  () const;
                void                setWidth        (int width);
                int                 getWidth        () const;
                void                setHeight       (int height);
                int                 getHeight       () const;
                SegmentList*        getSegmentList  () const;
                void                setSegmentList  (SegmentList *list);
                SegmentBase*        getSegmentBase  () const;
                void                setSegmentBase  (SegmentBase *base);

            private:
                SegmentInfo     *segmentInfo;
                long            bitrate;
                int             width;
                int             height;
                SegmentBase     *segmentBase;
                SegmentList     *segmentList;
                std::string     id;
                std::string     depId;
                bool            isDependent;
        };
    }
}

#endif /* REPRESENTATION_H_ */
