/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** arguments
*/


#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

    #include <stdio.h>
    #include <stdbool.h>
    #include <sys/queue.h>

    #define MIN_ARGS 11
    #define NB_FLAGS 6

    #define INVALID_PORT "port must be a number > 0\n"
    #define INVALID_WIDTH "width must be a number > 0\n"
    #define INVALID_HEIGHT "height must be a number > 0\n"
    #define INVALID_NB_CLIENTS "nb of clients must be a number > 0\n"
    #define INVALID_FREQUENCY "frequency must be a number > 0\n"
    #define UNSPECIFIED_ARG_VALUE "all flags must be followed by a value\n"

struct flag_occurence {
    char *name;
    int occurence;
};

typedef struct team_s {
    char *team_name;
    TAILQ_ENTRY(team_s) team_entries;
} team_t;

typedef struct arguments_s {
    int port;
    int width;
    int height;
    int freq;
    int nb_clients;
    int nb_teams;
    TAILQ_HEAD(, team_s) team_head;
} arguments_t;

int team_name_flag(const char **, int, bool *, arguments_t *);
int port_flag(const char **, int, bool *, arguments_t *);
int width_flag(const char **, int, bool *, arguments_t *);
int height_flag(const char **, int, bool *, arguments_t *);
int nb_clients_flag(const char **, int, bool *, arguments_t *);
int frequency_flag(const char **, int, bool *, arguments_t *);

int fill_arg_struct(int, const char **, arguments_t *);
void print_arg_struct(const arguments_t);

#endif
