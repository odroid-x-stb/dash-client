/*
 * DASHManager.h
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

#ifndef DASHMANAGER_H_
#define DASHMANAGER_H_

#include "../http/HTTPConnectionManager.h"
#include "../xml/Node.h"
#include "../xml/DOMParser.h"
#include "../adaptationlogic/IAdaptationLogic.h"
#include "../adaptationlogic/AdaptationLogicFactory.h"
#include "../mpd/IMPDManager.h"
#include "../mpd/MPDManagerFactory.h"
#include "../buffer/BlockBuffer.h"
#include "DASHDownloader.h"
#include "../../include/IDASHManager.h"
#include "../statistics/StatisticsManager.h"

namespace dash
{
    class DASHManager : public IDASHManager
    {
        public:
            DASHManager             ();
            virtual ~DASHManager    ();

            bool    open                (char *path);
            bool    start               ();
            int     read                (uint8_t *p_data, size_t len);
            int     peek                (uint8_t *p_data, size_t len);
            void    setBufferLength     (size_t seconds);
            void    destroy             ();

        private:
            http::HTTPConnectionManager         *conManager;
            logic::IAdaptationLogic             *adaptationLogic;
            logic::IAdaptationLogic::LogicType  logicType;
            mpd::Profile                        profile;
            xml::Node                           *node;
            mpd::IMPDManager                    *mpdManager;
            buffer::BlockBuffer                 *buffer;
            DASHDownloader                      *downloader;
            statistics::StatisticsManager       statisticsManager;
            size_t                              bufferLength;

            void    deleteAll();
    };
}

#endif /* DASHMANAGER_H_ */
