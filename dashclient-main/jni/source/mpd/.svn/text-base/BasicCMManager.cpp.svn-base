/*
 * BasicCMManager.cpp
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

#include "BasicCMManager.h"

using namespace dash::mpd;

BasicCMManager::BasicCMManager  (MPD *mpd) :
                mpd             (mpd)
{
}
BasicCMManager::~BasicCMManager ()
{
}

std::vector<Segment*>           BasicCMManager::getSegments             (Representation *rep) const
{
    std::vector<Segment *> retSegments;

    SegmentInfo *info = rep->getSegmentInfo();
    Segment     *init = info->getInitSegment();

    retSegments.push_back(init);

    std::vector<Segment *> segments = info->getSegments();

    for(unsigned int i = 0; i < segments.size(); i++)
        retSegments.push_back(segments.at(i));

    return retSegments;
}
const std::vector<Period*>&     BasicCMManager::getPeriods              () const
{
    return this->mpd->getPeriods();
}
Representation*                 BasicCMManager::getBestRepresentation   (Period *period) const
{
    std::vector<Group *> groups = period->getGroups();

    long            bitrate  = 0;
    Representation  *best    = NULL;

    for(unsigned int i = 0; i < groups.size(); i++)
    {
        std::vector<Representation *> reps = groups.at(i)->getRepresentations();
        for(unsigned int j = 0; j < reps.size(); j++)
        {

            long currentBitrate = reps.at(j)->getBitrate();
            if(currentBitrate > bitrate)
            {
                bitrate = currentBitrate;
                best    = reps.at(j);
            }
        }
    }

    return best;
}
Period*                         BasicCMManager::getFirstPeriod          () const
{
    std::vector<Period *> periods = this->mpd->getPeriods();

    if(periods.size() == 0)
        return NULL;

    return periods.at(0);
}
Representation*                 BasicCMManager::getRepresentation       (Period *period, int64_t bitrate) const
{
    std::vector<Group *> groups = period->getGroups();

    Representation  *best       = NULL;
    int64_t            bestDif  = -1;

    for(unsigned int i = 0; i < groups.size(); i++)
    {
        std::vector<Representation *> reps = groups.at(i)->getRepresentations();
        for(unsigned int j = 0; j < reps.size(); j++)
        {
            int64_t currentBitrate = reps.at(j)->getBitrate();
            int64_t dif = bitrate - currentBitrate;

            if(bestDif == -1)
            {
                bestDif = dif;
                best = reps.at(j);
            }
            else
            {
                if(dif >= 0 && dif < bestDif)
                {
                    bestDif = dif;
                    best = reps.at(j);
                }
            }
        }
    }

    return best;
}
Period*                         BasicCMManager::getNextPeriod           (Period *period) const
{
    std::vector<Period *> periods = this->mpd->getPeriods();

    for(unsigned int i = 0; i < periods.size(); i++)
    {
        if(periods.at(i) == period && (i + 1) < periods.size())
            return periods.at(i + 1);
    }

    return NULL;
}
Segment*                        BasicCMManager::getSegment              (int number, int64_t bitrate) const
{
    Period          *current = this->getFirstPeriod();
    Representation  *rep;

    int count = 0;
    do
    {
        rep      = this->getRepresentation(current, bitrate);
        count   += this->getSegments(rep).size();
        current  = this->getNextPeriod(current);
    }while(count < number && current != NULL);

    if(current == NULL && count <= number)
        return NULL;

    return this->getSegments(rep).at(number - count + this->getSegments(rep).size());
}
Segment*                        BasicCMManager::getSegment              (int number, std::string repId) const
{
    return NULL;
}