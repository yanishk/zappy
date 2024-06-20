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
    #define NB_FLAGS 7

    #define DEFAULT_FREQUENCE_VALUE 100

    #define PORT "port"
    #define WIDTH "width"
    #define HEIGHT "height"
    #define NB_CLIENTS "nb of clients"
    #define FREQUENCY "frequency"
    #define IMMORTAL "immortal"

    #define NO_TEAM_PROVIDED "no team provided\n"
    #define INVALID_FLAG_ARGUMENT(flag) "invalid %s argument\n", flag
    #define ARG_MUST_BE_A_NUMBER(flag) "%s must be a number > 0\n", flag
    #define UNRECOGNIZED_FLAG(flag) "unrecognized flag %s\n", flag
    #define SPECIFY_FLAG_ONCE(flag) "flag %s must be specified once\n", flag
    #define FLAG_NOT_SPECIFIED(flag) "flag %s not specified\n", flag

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
    bool immortal;
    TAILQ_HEAD(, team_s) team_head;
} arguments_t;

struct flag_occurence {
    char *name;
    int occurence;
    int (*func)(int, const char **, int *, arguments_t *);
};

extern struct flag_occurence flags[NB_FLAGS];

int team_name_flag(int, const char **, int *, arguments_t *);
int port_flag(int, const char **, int *, arguments_t *);
int width_flag(int, const char **, int *, arguments_t *);
int height_flag(int, const char **, int *, arguments_t *);
int nb_clients_flag(int, const char **, int *, arguments_t *);
int frequency_flag(int, const char **, int *, arguments_t *);
int immortal_flag(int, const char **, int *, arguments_t *);

int fill_arg_struct(int, const char **, arguments_t *);

#endif
