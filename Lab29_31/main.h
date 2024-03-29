//
// Created by Daniel on 27.12.2020.
//

#ifndef LAB31_MAIN_H
#define LAB31_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <connection/client/clientConnectionList.h>
#include "services/queue/queueService.h"
#include "services/threadpool/threadPool.h"
#include "argschecker/argsChecker.h"
#include "services/cache/cache.h"
#include "services/net/serverSockerService.h"
#include "config.h"

#define MAX_CONNECTIONS 100
#define MAX_CACHE_SIZE 3*1024
#define BUFFER_SIZE 16 * 1024
#define MAX_NUM_TRANSLATION_CONNECTIONS 100

int getNewClientSocket(int *localConnectionsCount, int threadId);

void handleGetException(int result, NodeClientConnection **list, ClientConnection *clientConnection, int threadId,
                        int *localConnectCount);

int updatePoll(struct pollfd *fds, NodeClientConnection *clients, NodeServerConnection *servers);

void *work(void *param);

void signalHandler(int sig);

void checkArgs(int argcc, const char *argv[]);

void updateServers(NodeServerConnection **listServerConnections, int threadId, int *localConnectCount);

void
updateClients(NodeClientConnection **listClientsConnections, NodeServerConnection **listServerConnection, int threadId,
              int *localConnectionsCount);

void
handleSendingFromCacheException(int result, NodeClientConnection **list, ClientConnection *clientConnection,
                                int threadId, int *localConnectCount);

void
handleCachingException(int result, NodeServerConnection **listServers, ServerConnection *serverConnection, int threadId,
                       int *localConnects);


#endif //LAB31_MAIN_H
