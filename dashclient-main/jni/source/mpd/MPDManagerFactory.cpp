/*
 * MPDManagerFactory.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2011 Klagenfurt University
 *
 * Created on: Apr 20, 2011
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

#include "../mpd/MPDManagerFactory.h"

using namespace dash::mpd;
using namespace dash::xml;

IMPDManager* MPDManagerFactory::create                  (Profile profile, Node *root)
{
    switch(profile)
    {
        case mpd::Basic:        return NULL;
        case mpd::BasicCM:      return MPDManagerFactory::createBasicCMManager(root);
        case mpd::Full2011:     return NULL;
        case mpd::NotValid:     return NULL;
        case mpd::IsoffMain:    return MPDManagerFactory::createIsoffMainManager(root);

        default:                return NULL;
    }
}
IMPDManager* MPDManagerFactory::createBasicCMManager    (Node *root)
{
    BasicCMParser parser(root);

    if(!parser.parse())
        return NULL;

    return new BasicCMManager(parser.getMPD());
}
IMPDManager* MPDManagerFactory::createIsoffMainManager  (Node *root)
{
    IsoffMainParser parser(root);

    if(!parser.parse())
        return NULL;

    return new IsoffMainManager(parser.getMPD());
}