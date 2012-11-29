/*
 * Group.cpp
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

#include "Group.h"

using namespace dash::mpd;

Group::Group    () :
       width    (0),
       height   (0)
{
}
Group::~Group   ()
{
    for(unsigned int i = 0; i < this->representations.size(); i++)
        delete(this->representations.at(i));
}

int     Group::getWidth     ()
{
    return this->width;
}
void    Group::setWidth     (int width)
{
    this->width = width;
}
int     Group::getHeight    ()
{
    return this->height;
}
void    Group::setHeight    (int height)
{
    this->height = height;
}
std::vector<Representation*>    Group::getRepresentations       ()
{
    return this->representations;
}
void                            Group::addRepresentation        (Representation *rep)
{
    this->representations.push_back(rep);
}