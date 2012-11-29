/*
 * IDASHManager.h
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

#ifndef IDASHMANAGER_H_
#define IDASHMANAGER_H_

#include <stdint.h>
#include "../source/http/Chunk.h"


namespace dash
{
    class IDASHManager
    {
        public:
            virtual bool    open                (char *path)                    = 0;
            virtual bool    start               ()                              = 0;
            virtual int     read                (uint8_t *p_data, size_t len)   = 0;
            virtual int     peek                (uint8_t *p_data, size_t len)   = 0;
            virtual void    setBufferLength     (size_t seconds)                = 0;
            virtual void    destroy             ()                              = 0;
    };
}

#endif /* IDASHMANAGER_H_ */