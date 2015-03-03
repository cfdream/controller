#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdint.h>
#include <set>

using namespace std;

//switch number
int switch_num = 4;

//socket information
int server_port = 8888;
char server_ip[20] = "10.1.0.254";


//if the socket server finished receiving data from one client, insert the client ip into the set
set<uint32_t> g_received_client_set;

#endif
