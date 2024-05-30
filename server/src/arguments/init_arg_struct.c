/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

struct flag_occurence flags[] = {
    {"-n", 0},
    {"-p", 0},
    {"-x", 0},
    {"-y", 0},
    {"-c", 0},
    {"-f", 0},
};

int (*flag_func[])(const char **av, int i,
    bool *is_a_team_name, arguments_t *arg) = {
    &team_name_flag,
    &port_flag,
    &width_flag,
    &height_flag,
    &nb_clients_flag,
    &frequency_flag
};

static void increment_flag_occurence(const char *team_name_flagame)
{
    for (size_t i = 0; i != NB_FLAGS; i++) {
        if (strcmp(flags[i].name, team_name_flagame) == 0)
            flags[i].occurence++;
    }
}

static int check_flags_occurences(arguments_t *arg)
{
    for (size_t i = 0; i != NB_FLAGS; i++) {
        if (flags[i].occurence < 1 && strcmp(flags[i].name, "-f") != 0) {
            fprintf(stderr, "%s not specified\n", flags[i].name);
            return EXIT_WITH_ERROR;
        }
        if (flags[i].occurence > 1) {
            fprintf(stderr, "%s must be specified once\n", flags[i].name);
            return EXIT_WITH_ERROR;
        }
        if (flags[i].occurence == 1 && strcmp(flags[i].name, "-f") == 0
            && arg->freq == 0) {
            fprintf(stderr, "%s must be followed by a value\n", flags[i].name);
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}

static void fill_team_name(const char *team_name, const bool is_a_team_name,
    arguments_t *arg)
{
    team_t *team;

    if (is_a_team_name && strcmp(team_name, "-n") != 0) {
        team = malloc(sizeof(team_t));
        TAILQ_INSERT_TAIL(&arg->team_head, team, team_entries);
        team->team_name = strdup(team_name);
    }
}

static int check_arg_values(arguments_t *arg)
{
    if (arg->port == 0 ||
        arg->width == 0 ||
        arg->height == 0 ||
        arg->nb_clients == 0) {
        fprintf(stderr, UNSPECIFIED_ARG_VALUE);
        return EXIT_WITH_ERROR;
    }
    if (arg->freq == 0)
        arg->freq = 100;
    if (TAILQ_EMPTY(&arg->team_head)) {
        fprintf(stderr, "no team provided\n");
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

int call_flag(const char **av, int i, bool *is_a_team_name, arguments_t *arg)
{
    for (size_t y = 0; y < NB_FLAGS; y++) {
        if (flag_func[y](av, i, is_a_team_name, arg) == EXIT_WITH_ERROR)
            return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

int init_arg_struct(int ac, const char **av, arguments_t *arg)
{
    bool is_a_team_name = false;
    unsigned int status = 0;

    TAILQ_INIT(&arg->team_head);
    for (int i = 1; i != ac; i++) {
        increment_flag_occurence(av[i]);
        if (i < ac - 1)
            status = call_flag(av, i, &is_a_team_name, arg);
        if (status == EXIT_WITH_ERROR)
            return status;
        fill_team_name(av[i], is_a_team_name, arg);
    }
    if (check_flags_occurences(arg) == EXIT_WITH_ERROR ||
        check_arg_values(arg) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}

void print_arg_struct(const arguments_t arg)
{
    team_t *team;

    printf("teams:\n");
    TAILQ_FOREACH(team, &arg.team_head, team_entries)
        printf("team %s\n", team->team_name);
    printf("\n");
    printf("port:%d\n", arg.port);
    printf("width:%d\n", arg.width);
    printf("height:%d\n", arg.height);
    printf("nb_clients:%d\n", arg.nb_clients);
    printf("freq:%d\n", arg.freq);
}
