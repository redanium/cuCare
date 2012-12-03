#ifndef SERVERNETWORKCONNECTION_H
#define SERVERNETWORKCONNECTION_H

#include <QtNetwork>
#include "ServerNetworkTranslator.h"

class ServerNetworkConnection
{
public:
    ServerNetworkConnection(QTcpSocket *connectedSocketParam);
    ~ServerNetworkConnection();

    void handleRequest();

private:
    QTcpSocket *connectedSocket;
};

#endif // SERVERNETWORKCONNECTION_H
