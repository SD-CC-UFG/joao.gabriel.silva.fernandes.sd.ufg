# joao.gabriel.silva.fernandes.sd.ufg

Componenetes - classes:
* Cliente
* Servidor multithread

Esse repostorio consiste na estrutura de um programa em C++, que possui um servidor onde fica ouvindo requisições de conexão de clientes, e então passa tais conexões para alguma de suas threads (pré alocadas, para prevenir overhead de pré alocação)

a pasta Many-servers consiste numa arquitetura onde um servidor principal recebe as requisições de conexão e envia as mensagens para sub servidores ( que são mutithreads ), onde irão tratar do processamento do pedido.
