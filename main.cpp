#include <pthread.h> //for threading , link with lpthread
#include "tcp_socket_server.h"

int main(int argc, char* argv[]) {
	pthread_t thread_id;
    int ret = 0;
    ret = pthread_create(&thread_id, NULL, socket_server_func, NULL);
    if (ret) {
        ERROR("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_id, NULL);
    exit(EXIT_SUCCESS);
}
