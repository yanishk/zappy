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
    #define INTERRUPTED_SYSCALL 4
    #define UNKNOWN_COMMAND 1
    #define NB_CMD 7
    #define MAX_USER 1024
    #define MAX_BUFFER_SIZE 1024
    #define MAX_QUEUE_COMMANDS 10
    #define COMMAND_KO "ko\n"
    #define COMMAND_OK "ok\n"

    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <stdbool.h>
    #include <string.h>
    #include <time.h>
    #include "map.h"

typedef struct command_infos {
    char *name;
    double time_unit;
} command_infos_t;

typedef struct command_s {
    char **tab;
    double time_unit;
    size_t index;
    time_t time_begin;
    TAILQ_ENTRY(command_s) command_entries;
} command_t;

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
    size_t size;
    fd_set readfds;
    client_t **clients;
    char **cmd_arg_array;
} server_t;

extern int (*cmd_func[NB_CMD])(server_t *, zappy_t *, const arguments_t,
    client_t *);
extern command_infos_t cmd_list[NB_CMD];

int server(int, const char **);
server_t *init_server_struct(const arguments_t);
int initialize_server(server_t *);
int run_server(server_t *, zappy_t *, const arguments_t);
client_t *get_client_in_struct(server_t *, const int);
client_t *insert_client_in_struct(server_t *, const int);
void check_command_queue(server_t *, zappy_t *, const arguments_t, const int);
void close_client_socket(server_t *, client_t *);
void get_user_input(server_t *, zappy_t *, client_t *);
void answer_client(const int, const unsigned int);
void free_program(server_t *, zappy_t *, arguments_t *);

int exit_func(server_t *, zappy_t *, const arguments_t, client_t *);
int inventory_command(server_t *, zappy_t *, const arguments_t, client_t *);
int take_command(server_t *, zappy_t *, const arguments_t, client_t *);
int set_object(server_t *, zappy_t *, const arguments_t, client_t *);
int move_forward(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_left(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_right(server_t *, zappy_t *, const arguments_t, client_t *);

bool is_player_connected(const zappy_t *, const unsigned int);
int connect_player(server_t *, zappy_t *, const arguments_t,
    const unsigned int);

size_t array_size(char **);
void free_array(char **);
char **word_array(char const *, char *);
player_t *get_player(zappy_t *, const unsigned int);
bool is_command_queue_full(client_t *);
bool time_is_up(time_t, double);

#endif /* !SERVER_H_ */
