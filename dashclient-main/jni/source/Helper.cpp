/*
 * Helper.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Feb 20, 2012
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
#include "Helper.h"

using namespace dash;

std::string                 Helper::combinePaths        (const std::string &path1, const std::string &path2)
{
    char path1Last  = path1.at(path1.size() - 1);
    char path2First = path2.at(0);

    if(path1Last == '/' && path2First == '/')
        return path1 + path2.substr(1, path2.size());

    if(path1Last != '/' && path2First != '/')
        return path1 + "/" + path2;

    return path1 + path2;
}
std::string                 Helper::getDirectoryPath    (const std::string &path)
{
    int pos = path.find_last_of('/');

    return path.substr(0, pos);
}
std::vector<std::string>    Helper::split               (const std::string &s, char delim)
{
    std::stringstream           ss(s);
    std::string                 item;
    std::vector<std::string>    ret;

    while(std::getline(ss, item, delim)) 
        ret.push_back(item);

    return ret;
}