/*
 * Block.h
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Feb 2, 2012
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

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdint.h>
#include <stdlib.h>

namespace dash
{
    struct block_t
    {
        uint8_t *p_buffer;
        size_t  i_buffer;
        float   i_millisec;
        size_t  i_offset;
    };

    static block_t*   AllocBlock  (int len)
    {
        block_t *block      = (block_t *)malloc(sizeof(block_t));
        block->p_buffer     = new uint8_t[len];
        block->i_buffer     = len;
        block->i_millisec   = 0;
        block->i_offset     = 0;
      
        return block;
    }
    static void       DeleteBlock (block_t *block)
    {
        if(block)
        {
            delete [] block->p_buffer;
            free(block);
            block = NULL;
        }
    }
}

#endif