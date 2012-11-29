/*
 * DOMParser.h
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

#ifndef DOMPARSER_H_
#define DOMPARSER_H_

#include "../Debug.h"
#include "../xml/Node.h"
#include "../http/IHTTPConnection.h"
#include "../mpd/IMPDManager.h"
#include <libxml/xmlreader.h>
#include <sstream>
#include <stdint.h>
#include <string.h>

namespace dash
{
    namespace xml
    {
        enum NodeType
        {
            Start           = 1,
            End             = 15,
            WhiteSpace      = 14,
            Text            = 3,
        };

        class DOMParser
        {
            public:
                DOMParser           (std::string url);
                virtual ~DOMParser  ();

                bool                parse       ();
                Node*               getRootNode () const;
                void                print       ();
                dash::mpd::Profile  getProfile  (dash::xml::Node *node) const;
                bool                isDash      (uint8_t *p_peek, size_t len);

            private:
                xmlTextReaderPtr    reader;
                Node                *root;
                std::string         url;

                void    init                    ();
                Node*   processNode             ();
                void    addAttributesToNode     (Node *node);
                void    print                   (Node *node, int offset);
        };
    }
}
#endif /* DOMPARSER_H_ */