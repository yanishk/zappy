/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <stdbool.h>
    #include <string.h>
    #include <time.h>
    #include "map.h"

    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0
    #define ERROR_RETURN -1
    #define UNKNOWN_COMMAND 1
    #define COMMAND_SUCCESS 2
    #define INTERRUPTED_SYSCALL 4

    #define COMMAND_KO "ko\n"
    #define COMMAND_OK "ok\n"

    #define NB_CMD 10

    #define MAX_BUFFER_SIZE 1024
    #define MAX_QUEUE_COMMANDS 10

    #define TO_MILLI 1000

typedef struct client_s {
    struct sockaddr_in sock_addr;
    int client_fd;
    bool has_been_closed;
    TAILQ_HEAD(, command_s) command_head;
} client_t;

typedef struct server_s {
    struct sockaddr_in sock_addr;
    int port;
    int server_fd;
    int *fd_array;
    size_t max_user;
    size_t size;
    fd_set readfds;
    client_t **clients;
    char **cmd_arg_array;
} server_t;

int server(int, const char **);
server_t *init_server_struct(const arguments_t);
int initialize_server(server_t *);
void init_client(client_t *);
int run_server(server_t *, zappy_t *, const arguments_t);
client_t *get_client_in_struct(server_t *, const int);
client_t *insert_client_in_struct(server_t *, const int);
int insert_game_command_in_queue(server_t *, client_t *);
void insert_other_command_in_queue(server_t *, client_t *);
void check_command_queue(server_t *, zappy_t *, const arguments_t, client_t *);
void close_client_socket(server_t *, zappy_t *, client_t *);
void get_user_input(server_t *, zappy_t *, client_t *);
void check_players_food(server_t *, zappy_t *, const arguments_t);
void answer_client(const int, const unsigned int);
void free_client_commands(client_t *);
void free_program(server_t *, zappy_t *, arguments_t *);

size_t array_size(char **);
void free_array(char **);
char **word_array(char const *, char *);
player_t *get_player(zappy_t *, const unsigned int);
bool is_command_queue_full(client_t *);
bool time_is_up(clock_t, double);
int get_resources(resource_t *, const char *);
void set_resources(resource_t *, const char *, int);
bool is_a_resource(const char *);

#endif /* !SERVER_H_ */
