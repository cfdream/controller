#include <pthread.h> //for threading , link with lpthread
#include "tcp_socket_server.h"

int main(int argc, char* argv[]) {
	pthread_t thread_id;
    pthread_create(&thread_id, NULL, socket_server_func, NULL);
}
