#ifndef SERVERNETWORKINTERFACE_H
#define SERVERNETWORKINTERFACE_H

#include "ServerNetworkListener.h"

class ServerNetworkInterface
{
public:
    ServerNetworkInterface(quint16 port);

private:
    ServerNetworkListener *listener;
};

#endif // SERVERNETWORKINTERFACE_H
