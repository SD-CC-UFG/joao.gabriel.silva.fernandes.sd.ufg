#include "SubServer.h"
using namespace std;


SubServer::SubServer(int porta):Server(porta){}

void SubServer::Start()
{
    //"amarra"/seta o socket
    int bind_result = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (bind_result < 0){
        perror(RED("bind() falhou"));
        return;
    }
}

void SubServer::Accept()
{
    //accept an incoming connection request, bloqueia o processo esperando pela conexão
    if ((connectionfd = accept(sockfd, NULL, NULL)) < 0)
    {
        perror(RED("accept() falhou"));
        return;
    }
    cout << BOLD(GRN("Cliente conectado")) << endl;

    //while(true)
        this->atenderCliente(connectionfd, clientAddr, addrLen);
}

void SubServer::atenderCliente(int connectionfd, sockaddr_in6 clientAddr, socklen_t addrLen){
    char addr_str[INET6_ADDRSTRLEN];
    getpeername(connectionfd, (struct sockaddr *)&clientAddr, &addrLen); //obtem o endereço do cliente conectado

    //converte o endereçoe porta de rede em string
    if (inet_ntop(AF_INET6, &clientAddr.sin6_addr, addr_str, INET6_ADDRSTRLEN) != NULL){
        cout << "\tEndereço do SuperServidor: " << addr_str << endl;
        cout << "\tPorta da conexão: " << ntohs(clientAddr.sin6_port) << endl;
    }

    bool continuar = true;
    while(continuar){
        char buffer[2056] = {0};
        char *msg;
        int totalBytes = recv(connectionfd, buffer, sizeof(buffer), 0);
        msg = buffer+sizeof(int);

        switch (totalBytes){
            case -1:
                perror(RED("erro ao receber mensagem do SuperServidor"));
                break;
            case 0:
                perror(YEL("o SuperServidor fechou a conexão antes que todos os dados fossem encaminhados"));
                continuar = false;
            default:
                cout << totalBytes << " Bytes recebidos --> ";
                printf("\"%s\"\n", msg);
        }

        /********trata do processamento da requisição********/


        /*******terminar de tratar requisição***************/

        totalBytes = send(connectionfd, buffer, strlen(msg) + 1 + sizeof(int), MSG_NOSIGNAL);
        if (totalBytes == -1)
            cout << YEL("Falhou ao responder, SuperServidor fechou a conexão") << endl;
        else
            cout << CYN("resposta enviada") << endl;
        
    }
    //shutdown(connectionfd, SHUT_RDWR); //fecha socket para receber e enviar dados
    printf(BOLD(YEL("Fim da conexão\n")));
}

//para matar processo de uma porta: fuser -n tcp -k 9000

int main(int argc, char *argv[]){

    if (argc < 2){
        cout << YEL("informe a porta do socket ( ex: ./prog_name <porta>)\n");
        exit(1);
    }


    try {
        //criando objeto servidor
        class SubServer subServidor(atoi(argv[1]));


        /***************Iniciando servidor*********************/
        subServidor.Start();
        subServidor.Listen();

        subServidor.Accept();
    }
    catch (exception ex) {
        cout << "Erro ao construir objeto" << endl;
    }
}