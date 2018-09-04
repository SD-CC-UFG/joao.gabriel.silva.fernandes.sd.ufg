#include "Server.h"


class SubServer;

class SubServer: public Server{

    void atenderCliente(int connectionfd, sockaddr_in6 clientAddr, socklen_t addrLen);

  public:
    SubServer(int porta);
    void Start();
    void Accept();
};
