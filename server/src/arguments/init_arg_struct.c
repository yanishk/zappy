/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** init_arg_struct
*/

#include "server.h"

static struct flag_occurence flags[] = {
    {"-n", 0, &team_name_flag},
    {"-p", 0, &port_flag},
    {"-x", 0, &width_flag},
    {"-y", 0, &height_flag},
    {"-c", 0, &nb_clients_flag},
    {"-f", 0, &frequency_flag}
};

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
    team_t *team = NULL;

    if (is_a_team_name) {
        team = malloc(sizeof(team_t));
        TAILQ_INSERT_TAIL(&arg->team_head, team, team_entries);
        team->team_name = strdup(team_name);
        (*arg).nb_teams++;
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

static int call_flag(const char **av, int *i,
    bool *is_a_team_name, arguments_t *arg)
{
    unsigned int status = EXIT_WITH_SUCCESS;

    for (size_t j = 0; j < NB_FLAGS; j++) {
        if (strcmp(flags[j].name, av[*i]) == 0) {
            status = flags[j].func(av, i, is_a_team_name, arg);
            flags[j].occurence++;
        }
        if (status == EXIT_WITH_ERROR)
            return status;
    }
    return EXIT_WITH_SUCCESS;
}

static void init_arg_struct(arguments_t *arg)
{
    TAILQ_INIT(&arg->team_head);
    arg->port = 0;
    arg->width = 0;
    arg->height = 0;
    arg->freq = 0;
    arg->nb_clients = 0;
    arg->nb_teams = 0;
}

int fill_arg_struct(int ac, const char **av, arguments_t *arg)
{
    bool is_a_team_name = false;
    unsigned int status = EXIT_WITH_SUCCESS;

    init_arg_struct(arg);
    for (int i = 1; i != ac; i++) {
        if (i < (ac - 1))
            status = call_flag(av, &i, &is_a_team_name, arg);
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
    team_t *team = NULL;

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
