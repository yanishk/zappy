/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** arguments
*/

#include <stdio.h>
#include <stdbool.h>
#include <sys/queue.h>

#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

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
    int nb_clients;
    int freq;
    TAILQ_HEAD(, team_s) team_head;
} arguments_t;

int flag_n(const char **, int, bool *, arguments_t *);
int flag_p(const char **, int, bool *, arguments_t *);
int flag_x(const char **, int, bool *, arguments_t *);
int flag_y(const char **, int, bool *, arguments_t *);
int flag_c(const char **, int, bool *, arguments_t *);
int flag_f(const char **, int, bool *, arguments_t *);

int init_arg_struct(int ac, const char **av, arguments_t *arguments);
void print_arg_struct(const arguments_t arguments);

#endif
