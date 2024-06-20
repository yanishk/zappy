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
    #include <time.h>
    #include <string.h>
    #include "game.h"

    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0
    #define ERROR_RETURN -1
    #define UNKNOWN_COMMAND 1
    #define COMMAND_SUCCESS 2
    #define INTERRUPTED_SYSCALL 4

    #define MAX_BUFFER_SIZE 1024
    #define MAX_QUEUE_COMMANDS 10

    #define WIN_LEVEL 8
    #define REQUIRED_WINNER 6

typedef struct client_s {
    struct sockaddr_in sock_addr;
    int client_fd;
    bool has_been_closed;
    bool is_graphic;
    TAILQ_HEAD(, command_ia_s) command_head;
} client_t;

typedef struct server_s {
    struct sockaddr_in sock_addr;
    int port;
    int server_fd;
    int *fd_array;
    size_t max_clients;
    size_t fd_array_size;
    fd_set readfds;
    client_t **clients;
    char **cmd_arg_array;
} server_t;

int server(int, const char **);
server_t *init_server_struct(const arguments_t);
int initialize_server(server_t *);
void init_client(client_t *);
int run_server(server_t *, zappy_t *, arguments_t *);
client_t *get_client_in_struct(server_t *, const int);
client_t *insert_client_in_struct(server_t *, const int);
void get_user_input(server_t *, zappy_t *, arguments_t *, client_t *);
bool connect_graphical_client(server_t *, zappy_t *, arguments_t *,
    client_t *);
void answer_client(const int, const unsigned int);
void close_client_socket(server_t *, zappy_t *, client_t *);

void check_players_food(server_t *, zappy_t *, arguments_t);
int insert_game_command_in_queue(server_t *, arguments_t, client_t *);
void insert_other_command_in_queue(server_t *, client_t *);
void check_command_queue(server_t *, zappy_t *, arguments_t *, client_t *);

void free_program(server_t *, zappy_t *, arguments_t *);
void free_client_commands(client_t *);
void free_player(zappy_t *, player_t *);
void free_link_by_client_fd(zappy_t *, const unsigned int);
void free_egg(zappy_t *, egg_t *);
void free_game(zappy_t *, const arguments_t *);
void free_arg_teams(arguments_t *);

bool is_positive_number(const char *);
size_t array_size(char **);
void free_array(char **);
char **word_array(char const *, char *);
int get_next_id(int *id);
bool has_backslash(const char *);
player_t *get_player_by_fd(const zappy_t *, const unsigned int);
player_t *get_player_by_id(const zappy_t *, const int);
int get_client_fd(const zappy_t *, const unsigned int);
link_t *get_link_by_client_fd(const zappy_t *, const unsigned int);
link_t *get_link_by_player_id(const zappy_t *, const unsigned int);
egg_t *get_random_team_egg(zappy_t *, char *);
unsigned int count_team_eggs(const zappy_t *, const char *);
unsigned int count_team_players(const zappy_t *, const char *);
unsigned int count_team_slots(const zappy_t *, const char *);
int get_player_direction(const player_t *);
client_t *get_graphical_client(server_t *);
bool is_command_queue_full(client_t *);
bool time_is_up(clock_t, double);
bool player_on_same_tile(const player_t *, const player_t *);
bool egg_on_same_tile(const player_t *, const egg_t *);
int get_resources(const resource_t *, const char *);
void set_resources(resource_t *, const char *, int);
bool is_a_resource(const char *);
int get_tile_index(const char *, const int);
double calculate_freq(int, double);
void refill_map(zappy_t *, const arguments_t, server_t *, clock_t *);
char *win_condition(server_t *, zappy_t *, arguments_t *);

#endif /* !SERVER_H_ */
