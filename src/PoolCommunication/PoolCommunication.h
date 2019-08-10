// Copyright (c) 2019, Zpalmtree
//
// Please see the included LICENSE file for more information.

#pragma once

#include <vector>

#include "SocketWrapper/SocketWrapper.h"
#include "Types/Pool.h"
#include "Types/PoolMessage.h"

class PoolCommunication
{
  public:
    PoolCommunication(const std::vector<Pool> pools);

    void login();

    Job getJob();

    void submitShare(
        const std::vector<uint8_t> &hash,
        const std::string jobID,
        const uint32_t nonce);

    /* Triggers us to start listening for messages and handling them */
    void handleMessages();

    /* Register a function to call when a new job is discovered */
    void onNewJob(const std::function<void(const Job &job)>);

    /* Register a function to call when a share is accepted */
    void onHashAccepted(const std::function<void(const std::string &shareID)>);

    /* Prints the currently connected pool for formatting purposes */
    void printPool();

  private:
    /* The current pool we are connected to */
    Pool m_currentPool;

    /* All the pools available to connect to */
    const std::vector<Pool> m_allPools;

    /* The socket instance for the pool we are talking to */
    std::shared_ptr<sockwrapper::SocketWrapper> m_socket;

    /* Are we currently mining on the preferred pool? If we aren't, we will
       try reconnecting to more preferred pools periodically */
    bool m_preferredPool;

    /* The current job to be working on */
    Job m_currentJob;

    /* We call this callback every time a new job is given to us */
    std::function<void(const Job &job)> m_onNewJob;

    /* We call this callback every time the pool accepts one of our shares */
    std::function<void(const std::string &shareID)> m_onHashAccepted;
};