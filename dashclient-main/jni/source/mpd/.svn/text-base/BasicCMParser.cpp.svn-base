/*
 * BasicCMParser.cpp
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

#include "BasicCMParser.h"

using namespace dash::mpd;
using namespace dash::xml;

BasicCMParser::BasicCMParser    (Node *root) :
               root             (root),
               currentRep       (NULL)
{
}
BasicCMParser::~BasicCMParser   ()
{
}

bool    BasicCMParser::parse                ()
{
    this->setMPD();
    return true;
}
void    BasicCMParser::setMPD               ()
{
    this->mpd = new MPD();
    this->setMPDBaseUrl(this->root);
    this->setPeriods(this->root);
}
void    BasicCMParser::setMPDBaseUrl        (Node *root)
{
    std::vector<Node *> baseUrls = DOMHelper::getChildElementByTagName(root, "BaseURL");

    for(unsigned int i = 0; i < baseUrls.size(); i++)
    {
        BaseUrl *url = new BaseUrl(baseUrls.at(i)->getText());
        this->mpd->addBaseUrl(url);
    }
}
void    BasicCMParser::setPeriods           (Node *root)
{
    std::vector<Node *> periods = DOMHelper::getElementByTagName(root, "Period", false);

    for(unsigned int i = 0; i < periods.size(); i++)
    {
        Period *period = new Period();
        this->setGroups(periods.at(i), period);
        this->mpd->addPeriod(period);
    }
}
void    BasicCMParser::setGroups            (Node *root, Period *period)
{
    std::vector<Node *> groups = DOMHelper::getElementByTagName(root, "Group", false);

    for(unsigned int i = 0; i < groups.size(); i++)
    {
        Group *group = new Group();
        this->setRepresentations(groups.at(i), group);
        period->addGroup(group);
    }
}
void    BasicCMParser::setRepresentations   (Node *root, Group *group)
{
    std::vector<Node *> representations = DOMHelper::getElementByTagName(root, "Representation", false);

    for(unsigned int i = 0; i < representations.size(); i++)
    {
        this->currentRep = new Representation();

        if(representations.at(i)->hasAttribute("bandwidth"))
            this->currentRep->setBitrate(atoi(representations.at(i)->getAttributeValue("bandwidth").c_str()));

        this->setSegmentInfo(representations.at(i), this->currentRep);
        group->addRepresentation(this->currentRep);
    }
}
void    BasicCMParser::setSegmentInfo       (Node *root, Representation *rep)
{
    std::vector<Node *> segmentInfo = DOMHelper::getChildElementByTagName(root, "SegmentInfo");

    for(unsigned int i = 0; i < segmentInfo.size(); i++)
    {
        SegmentInfo *info = new SegmentInfo();
        this->setInitSegment(segmentInfo.at(i), info);
        this->setSegments(segmentInfo.at(i), info);
        rep->setSegmentInfo(info);
        return;
    }
}
void    BasicCMParser::setInitSegment       (Node *root, SegmentInfo *info)
{
    std::vector<Node *> initSeg = DOMHelper::getChildElementByTagName(root, "InitialisationSegmentURL");

    for(unsigned int i = 0; i < initSeg.size(); i++)
    {
        Segment *seg = new Segment();
        seg->setBitrate(this->currentRep->getBitrate());

        if(initSeg.at(i)->hasAttribute("sourceURL"))
            seg->setSourceUrl(initSeg.at(i)->getAttributeValue("sourceURL"));

        seg->setBitrate(this->currentRep->getBitrate());

        info->setInitSegment(seg);
        return;
    }
}
void    BasicCMParser::setSegments          (Node *root, SegmentInfo *info)
{
    std::vector<Node *> segments = DOMHelper::getElementByTagName(root, "Url", false);

    for(unsigned int i = 0; i < segments.size(); i++)
    {
        Segment *seg = new Segment();
        seg->setBitrate(this->currentRep->getBitrate());

        if(segments.at(i)->hasAttribute("sourceURL"))
            seg->setSourceUrl(segments.at(i)->getAttributeValue("sourceURL"));

        seg->setBitrate(this->currentRep->getBitrate());

        info->addSegment(seg);
    }
}
MPD*    BasicCMParser::getMPD               ()
{
    return this->mpd;
}
