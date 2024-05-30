/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #define MIN_ARGS 13
    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0
    #define MAX_USER 1024
    #define NB_CMD 1
    #define BUFFER_MAX_SIZE 1024

    #include <sys/queue.h>
    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <stdbool.h>

static char *const cmd_lst[NB_CMD] = {
    "/exit"
};

typedef struct clients_s {
    struct sockaddr_in sock_addr;
    int client_fd;
    bool has_been_closed;
} clients_t;

typedef struct cmd_s {
    char **tab;
    size_t len;
} cmd_t;

typedef struct server_s {
    struct sockaddr_in sock_addr;
    int port;
    int server_fd;
    int *fd_array;
    size_t size;
    unsigned int max_fd_set;
    int user_index;
    fd_set readfds;
    clients_t **clients;
    cmd_t cmd_arg;
} server_t;

int server(const char *port_number);
server_t *init_server_struct(const char *port_number);
int initialize_server(server_t *server);
int run_server(server_t *server);
int insert_client_in_struct(server_t *server, const int client_fd);
void close_client_socket(server_t *);
void get_user_input(server_t *server, const int client_fd);

size_t array_size(char **array);
char **word_array(char const *str, char *delim);

int exit_func(void);

#endif /* !SERVER_H_ */
