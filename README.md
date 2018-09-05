# joao.gabriel.silva.fernandes.sd.ufg



Esse repostorio consiste em diversos sistemas distribuidos.

A pasta _Mutithread-Server_, é  um programa em C++, que possui um servidor onde fica ouvindo requisições de conexão de clientes, e então passa tais conexões para alguma de suas threads (pré alocadas, para prevenir overhead de pré alocação)

Componenetes - classes:
* Cliente
* Servidor multithread


A pasta Many-servers consiste numa arquitetura onde um servidor principal recebe as requisições de conexão e envia as mensagens para sub servidores ( que são mutithread ), onde irão tratar do processamento do pedido.

Ambos SuperServidor e Subservidor são multiThread.

Componenetes - classes:
* "Cliente" ->nao está na pasta, mas basta usar o mesmo _Cliente_ da pasta  _Mutithread-Server_;
* SuperServidor
* SubServidor(es)
