/*
 * DASHManager.cpp
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

#include "DASHManager.h"
#include <android/log.h>

using namespace dash;
using namespace dash::http;
using namespace dash::xml;
using namespace dash::logic;
using namespace dash::mpd;
using namespace dash::buffer;

DASHManager::DASHManager        ()  :
             conManager         (NULL),
             node               (NULL),
             logicType          (IAdaptationLogic::Default),
             profile            (mpd::NotValid),
             mpdManager         (NULL),
             adaptationLogic    (NULL),
             buffer             (NULL),
             downloader         (NULL),
             bufferLength       (0)
{
}
DASHManager::~DASHManager       ()
{
    this->deleteAll();
}

bool    DASHManager::open               (char *path)
{
	__android_log_print(ANDROID_LOG_ERROR, "DEBUG", "Media: %s", path);
    DOMParser parser(path);

    if(!parser.parse())
        return false;

    this->node      = parser.getRootNode();
    this->profile   = parser.getProfile(this->node);

    return true;
}
bool    DASHManager::start              ()
{
    if(this->node == NULL)
        return false;

    this->mpdManager = MPDManagerFactory::create(this->profile, this->node);

    if(this->mpdManager == NULL)
    {
        this->deleteAll();
        return false;
    }

    this->buffer            = new BlockBuffer(this->bufferLength * 1000);
    this->logicType         = IAdaptationLogic::RateBased;
    this->adaptationLogic   = AdaptationLogicFactory::create(this->logicType, this->mpdManager);
    this->conManager        = new HTTPConnectionManager(this->adaptationLogic);
    this->downloader        = new DASHDownloader(this->conManager, this->buffer);

    this->conManager->attach(this->adaptationLogic);
    this->conManager->attach(&this->statisticsManager);
    this->buffer->attach(this->adaptationLogic);
    this->buffer->attach(&this->statisticsManager);

    if(!this->downloader->start())
    {
        this->deleteAll();
        return false;
    }

    return true;
}
int     DASHManager::read               (uint8_t *p_data, size_t len)
{
    return this->buffer->get(p_data, len);
}
int     DASHManager::peek               (uint8_t *p_data, size_t len)
{
    return this->buffer->peek(p_data, len);
}
void    DASHManager::destroy            ()
{
    delete this;
}
void    DASHManager::setBufferLength    (size_t seconds)
{
    this->bufferLength = seconds;
}
void    DASHManager::deleteAll          ()
{
    delete(this->downloader);
    delete(this->adaptationLogic);
    delete(this->mpdManager);
    delete(this->conManager);
    delete(this->buffer);
}
