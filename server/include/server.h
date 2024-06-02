/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/


#ifndef SERVER_H_
    #define SERVER_H_

    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0
    #define INTERRUPT_SYSCALL 4
    #define UNKNOWN_COMMAND 1
    #define NB_CMD 7
    #define MAX_USER 1024
    #define BUFFER_MAX_SIZE 1024
    #define COMMAND_KO "ko\n"
    #define COMMAND_OK "ok\n"

    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <stdbool.h>
    #include <string.h>
    #include "map.h"

static char *const cmd_lst[NB_CMD] = {
    "Exit",
    "Inventory",
    "Take",
    "Forward",
    "Left",
    "Right",
    "Set"
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
    int user_index;
    fd_set readfds;
    clients_t **clients;
    cmd_t cmd_arg;
} server_t;

int server(int ac, const char **av);
server_t *init_server_struct(const int port);
int initialize_server(server_t *server);
int run_server(server_t *server, zappy_t *zappy, const arguments_t arg);
int insert_client_in_struct(server_t *server, const int client_fd);
void close_client_socket(server_t *);
void get_user_input(server_t *server, zappy_t *zappy, const arguments_t arg);
void free_program(server_t *server, zappy_t *zappy, arguments_t *arg);

bool is_player_connected(const zappy_t *zappy, const unsigned int client_fd);
int connect_player(server_t *server, zappy_t *zappy, const arguments_t arg,
    const unsigned int client_fd);

int exit_func(server_t *, zappy_t *, const arguments_t, const unsigned int);
int inventory_command(server_t *, zappy_t *, const arguments_t,
    const unsigned int);
int take_command(server_t *, zappy_t *, const arguments_t, const unsigned int);
int set_object(server_t *server, zappy_t *zappy, const arguments_t,
    const unsigned int client_fd);
int move_forward(server_t *, zappy_t *, const arguments_t, const unsigned int);
int turn_left(server_t *, zappy_t *, const arguments_t, const unsigned int);
int turn_right(server_t *, zappy_t *, const arguments_t, const unsigned int);

size_t array_size(char **array);
void free_array(char **array);
char **word_array(char const *str, char *delim);
player_t *get_player(zappy_t *zappy, const unsigned int client_fd);

#endif /* !SERVER_H_ */
