/*
 * DOMParser.cpp
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

#include "DOMParser.h"
#include <android/log.h>
#include <errno.h>

using namespace dash::xml;
using namespace dash::http;
using namespace dash::mpd;

DOMParser::DOMParser    (std::string url) :
           url          (url)
{
    this->init();
}
DOMParser::~DOMParser   ()
{
    xmlCleanupParser();
}

Node*   DOMParser::getRootNode              () const
{
    return this->root;
}
bool    DOMParser::parse                    ()
{
    this->reader = xmlReaderForFile(this->url.c_str(), NULL, 0);
    if(this->reader == NULL)
        return false;

    if(xmlTextReaderRead(this->reader))
        this->root = this->processNode();

    xmlFreeTextReader(this->reader);

    return true;
}
Node*   DOMParser::processNode              ()
{
    int type = xmlTextReaderNodeType(this->reader);

    if(type != WhiteSpace && type != Text)
    {
        Node *node = new Node();
        node->setType(type);

        std::string name    = (const char *) xmlTextReaderConstName(this->reader);
        int         isEmpty = xmlTextReaderIsEmptyElement(this->reader);

        node->setName(name);

        this->addAttributesToNode(node);

        if(isEmpty)
            return node;

        Node    *subnode    = NULL;
        int     ret         = xmlTextReaderRead(this->reader);

        while(ret == 1)
        {
            if(!strcmp(name.c_str(), (const char *) xmlTextReaderConstName(this->reader)))
            {
                xmlTextReaderRead(this->reader);
                return node;
            }

            subnode = this->processNode();

            if(subnode != NULL)
                node->addSubNode(subnode);

            ret = xmlTextReaderRead(this->reader);
        }

        return node;
    } else if (type == Text)
    {
       const char* text = (const char *) xmlTextReaderReadString(this->reader);

       if(text != NULL)
       {
           Node *node = new Node();
           node->setType(type);
           node->setText(text);
           return node;
       }
    }
    return NULL;
}
void    DOMParser::addAttributesToNode      (Node *node)
{
    if(xmlTextReaderHasAttributes(this->reader))
    {
        while(xmlTextReaderMoveToNextAttribute(this->reader))
        {
            std::string key      = (const char *) xmlTextReaderConstName(this->reader);
            std::string value    = (const char *) xmlTextReaderConstValue(this->reader);
            node->addAttribute(key, value);
        }
    }
}
void    DOMParser::print                    (Node *node, int offset)
{
    std::stringstream ss;
    for(int i = 0; i < offset; i++)
        ss << " ";
    ss << node->getName();

    DMSG(ss.str())

    std::vector<std::string> keys = node->getAttributeKeys();

    ss.clear();
    for(unsigned int i = 0; i < keys.size(); i++)
    {
        ss << " " << keys.at(i) << "=" << node->getAttributeValue(keys.at(i));
    }

    DMSG(ss.str())

    offset++;

    for(unsigned int i = 0; i < node->getSubNodes().size(); i++)
    {
        this->print(node->getSubNodes().at(i), offset);
    }
}
void    DOMParser::init                     ()
{
    this->root      = NULL;
    this->reader    = NULL;
}
void    DOMParser::print                    ()
{
    this->print(this->root, 0);
}
Profile DOMParser::getProfile               (dash::xml::Node *node) const
{
    if(this->root == NULL)
        return dash::mpd::NotValid;

    const std::string profile = this->root->getAttributeValue("profiles");

    if(!profile.compare("urn:mpeg:mpegB:profile:dash:isoff-basic-on-demand:cm"))
        return dash::mpd::BasicCM;

    if(!profile.compare("urn:mpeg:dash:profile:isoff-main:2011"))
        return dash::mpd::IsoffMain;

    return dash::mpd::NotValid;
}
bool    DOMParser::isDash                   (uint8_t *p_peek, size_t len)
{
    const char* psz_namespaceDIS = "urn:mpeg:mpegB:schema:DASH:MPD:DIS2011";
    const char* psz_namespaceIS  = "urn:mpeg:DASH:schema:MPD:2011";

    if (len < (int)strlen(psz_namespaceDIS))
        return false;

    std::string header((const char*)p_peek, len);
    return (header.find(psz_namespaceDIS) != std::string::npos) || (header.find(psz_namespaceIS) != std::string::npos);
}
