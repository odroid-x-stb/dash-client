/*
 * IsoffMainManager.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Jan 27, 2010
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

#include "../mpd/IsoffMainManager.h"

using namespace dash::mpd;

IsoffMainManager::IsoffMainManager  (MPD *mpd)
{
    this->mpd = mpd;
}
IsoffMainManager::~IsoffMainManager ()
{
    delete this->mpd;
}

std::vector<Segment*>       IsoffMainManager::getSegments           (Representation *rep) const
{
    std::vector<Segment *>  retSegments;
    SegmentList*            list= rep->getSegmentList();
    Segment*                initSegment = rep->getSegmentBase()->getInitSegment();

    if(initSegment)
        retSegments.push_back(initSegment);

    retSegments.insert(retSegments.end(), list->getSegments().begin(), list->getSegments().end());
    return retSegments;
}
const std::vector<Period*>& IsoffMainManager::getPeriods            () const
{
    return this->mpd->getPeriods();
}
Representation*             IsoffMainManager::getBestRepresentation (Period *period) const
{
    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();

    int             bitrate  = 0;
    Representation  *best    = NULL;

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for(size_t j = 0; j < reps.size(); j++)
        {
            int currentBitrate = reps.at(j)->getBitrate();

            if(currentBitrate > bitrate)
            {
                bitrate = currentBitrate;
                best    = reps.at(j);
            }
        }
    }
    return best;
}
Period*                     IsoffMainManager::getFirstPeriod        () const
{
    std::vector<Period *> periods = this->mpd->getPeriods();

    if(periods.size() == 0)
        return NULL;

    return periods.at(0);
}
Representation*             IsoffMainManager::getRepresentation     (Period *period, int64_t bitrate) const
{
    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();

    Representation  *best = NULL;
    DMSG("Searching for best representation with bitrate: " << bitrate)

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for( size_t j = 0; j < reps.size(); j++ )
        {
            int currentBitrate = reps.at(j)->getBitrate();

            if(best == NULL || (currentBitrate > best->getBitrate() && currentBitrate < bitrate))
            {
                DMSG("Found a better Representation bandwidth=" << reps.at(j)->getBitrate() << " in adaptationSet #" << i)
                best = reps.at( j );
            }
        }
    }
    return best;
}
Period*                     IsoffMainManager::getNextPeriod         (Period *period) const
{
    std::vector<Period *> periods = this->mpd->getPeriods();

    for(size_t i = 0; i < periods.size(); i++)
    {
        if(periods.at(i) == period && (i + 1) < periods.size())
            return periods.at(i + 1);
    }

    return NULL;
}
Representation*             IsoffMainManager::getRepresentation     (Period *period, int64_t bitrate, int width, int height) const
{
    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();

    DMSG("Searching for best representation with bitrate: " << bitrate << " and resolution: " << width << "x" << height)

    std::vector<Representation *> resMatchReps;

    int lowerWidth  = 0;
    int lowerHeight = 0;

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for( size_t j = 0; j < reps.size(); j++ )
        {
            if(reps.at(j)->getWidth() == width && reps.at(j)->getHeight() == height)
                resMatchReps.push_back(reps.at(j));

            if(reps.at(j)->getHeight() < height)
            {
                lowerWidth  = reps.at(j)->getWidth();
                lowerHeight = reps.at(j)->getHeight();
            }
        }
    }

    if(resMatchReps.size() == 0)
        return this->getRepresentation(period, bitrate, lowerWidth, lowerHeight);

    Representation  *best = NULL;
    for( size_t j = 0; j < resMatchReps.size(); j++ )
    {
        int currentBitrate = resMatchReps.at(j)->getBitrate();

        if(best == NULL || (currentBitrate > best->getBitrate() && currentBitrate < bitrate))
        {
            DMSG("Found a better Representation bandwidth=" << resMatchReps.at(j)->getBitrate()
                      << " and resolution: " << resMatchReps.at(j)->getWidth() << "x" << resMatchReps.at(j)->getHeight())
            best = resMatchReps.at(j);
        }
    }

    return best;
}
Segment*                    IsoffMainManager::getSegment            (int number, int64_t bitrate) const
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
Segment*                    IsoffMainManager::getSegment            (int number, std::string repId) const
{
    Period          *current = this->getFirstPeriod();
    Representation  *rep;

    int count = 0;
    do
    {
        rep      = this->getRepresentation(current, repId);
        count   += this->getSegments(rep).size();
        current  = this->getNextPeriod(current);
    }while(count < number && current != NULL);

    if(current == NULL && count <= number)
        return NULL;

    return this->getSegments(rep).at(number - count + this->getSegments(rep).size());
}
Representation*             IsoffMainManager::getRepresentation     (Period *period, const std::string &id) const
{
    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for(size_t j = 0; j < reps.size(); j++)
        {
            if(!reps.at(j)->getId().compare(id))
                return reps.at(j);
        }
    }
    return NULL;
}