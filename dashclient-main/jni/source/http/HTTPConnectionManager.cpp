/*
 * HTTPConnectionManager.cpp
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

#include "HTTPConnectionManager.h"

using namespace dash::http;
using namespace dash::logic;

HTTPConnectionManager::HTTPConnectionManager    (IAdaptationLogic *adaptationLogic) :
                       adaptationLogic          (adaptationLogic),
                       chunkCount               (0),
                       bpsAvg                   (0),
                       bpsLastChunk             (0),
                       bpsCurrentChunk          (0),
                       bytesReadSession         (0),
                       bytesReadChunk           (0),
                       timeSession              (0),
                       timeChunk                (0)
{
    for(size_t i = 0; i < CONNECTIONS; i++)
        this->connectionPool.push_back(new PersistentHTTPConnection());
}
HTTPConnectionManager::~HTTPConnectionManager   ()
{
    this->closeAllConnections();
}

bool                                        HTTPConnectionManager::closeAllConnections      ()
{
    for(size_t i = 0; i < this->connectionPool.size(); i++)
    {
        this->connectionPool.at(i)->closeSocket();
        delete(this->connectionPool.at(i));
    }

    return true;
}
void                                        HTTPConnectionManager::attach                   (IDownloadRateObserver *observer)
{
    this->rateObservers.push_back(observer);
}
void                                        HTTPConnectionManager::notify                   ()
{
    for(unsigned int i = 0; i < this->rateObservers.size(); i++)
        this->rateObservers.at(i)->downloadRateChanged(this->bpsAvg, this->bpsLastChunk, this->bpsCurrentChunk, this->downloadQueue.front());
}
bool                                        HTTPConnectionManager::addChunk                 (Chunk *chunk)
{
    if(chunk == NULL)
        return false;

    this->downloadQueue.push(chunk);

    std::vector<PersistentHTTPConnection *> cons = this->getConnectionsForHost(chunk->getHostname());

    if(cons.size() == 0)
    {
        PersistentHTTPConnection *con = new PersistentHTTPConnection();
        this->connectionPool.push_back(con);
        cons.push_back(con);
    }

    size_t pos = this->chunkCount % cons.size();

    cons.at(pos)->addChunk(chunk);

    chunk->setConnection(cons.at(pos));

    this->chunkCount++;

    return true;
}
int                                         HTTPConnectionManager::read                     (void *p_buffer, unsigned int len, int64_t *bitrate)
{
    if(this->downloadQueue.size() == 0)
        if(!this->addChunk(this->adaptationLogic->getNextChunk()))
            return 0;

    if(this->downloadQueue.front()->getPercentDownloaded() > PIPELINE &&
       this->downloadQueue.size() < PIPELINELENGTH)
        this->addChunk(this->adaptationLogic->getNextChunk());

    int ret = 0;

    clock_t start = clock();
    ret = this->downloadQueue.front()->getConnection()->read(p_buffer, len);
    clock_t end = clock();

    double time = ((double)(end - start)) / CLOCKS_PER_SEC;

    if(ret <= 0)
    {
        this->bpsLastChunk   = this->bpsCurrentChunk;
        this->bytesReadChunk = 0;
        this->timeChunk      = 0;

        delete(this->downloadQueue.front());
        this->downloadQueue.pop();

        return this->read(p_buffer, len, bitrate);
    }
    else
    {
        this->updateStatistics(ret, time);
    }
    *bitrate = this->downloadQueue.front()->getBitrate();
    return ret;
}
std::vector<PersistentHTTPConnection *>     HTTPConnectionManager::getConnectionsForHost    (const std::string &hostname)
{
    std::vector<PersistentHTTPConnection *> cons;

    for(size_t i = 0; i < this->connectionPool.size(); i++)
        if(!this->connectionPool.at(i)->getHostname().compare(hostname) || !this->connectionPool.at(i)->isConnected())
            cons.push_back(this->connectionPool.at(i));

    return cons;
}
void                                        HTTPConnectionManager::updateStatistics         (int bytes, double time)
{
    this->bytesReadSession  += bytes;
    this->bytesReadChunk    += bytes;
    this->timeSession       += time;
    this->timeChunk         += time;

    this->bpsAvg            = (int64_t) ((this->bytesReadSession * 8) / this->timeSession);
    this->bpsCurrentChunk   = (int64_t) ((this->bytesReadChunk * 8) / this->timeChunk);

    if(this->bpsAvg < 0)
        this->bpsAvg = 0;

    if(this->bpsCurrentChunk < 0)
        this->bpsCurrentChunk = 0;

    this->notify();
}