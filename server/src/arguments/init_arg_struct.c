/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** init_arg_struct
*/

#include "server.h"

struct flag_occurence flags[NB_FLAGS] = {
    {"-n", 0, &team_name_flag},
    {"-p", 0, &port_flag},
    {"-x", 0, &width_flag},
    {"-y", 0, &height_flag},
    {"-c", 0, &nb_clients_flag},
    {"-f", 0, &frequency_flag},
    {"--immortal", 0, &immortal_flag}
};

static int check_flags_occurences(void)
{
    for (size_t i = 0; i < NB_FLAGS; i++) {
        if (flags[i].occurence < 1 && strcmp(flags[i].name, "-f") != 0
        && strcmp(flags[i].name, "--immortal") != 0) {
            fprintf(stderr, FLAG_NOT_SPECIFIED(flags[i].name));
            return EXIT_WITH_ERROR;
        }
        if (flags[i].occurence > 1) {
            fprintf(stderr, SPECIFY_FLAG_ONCE(flags[i].name));
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}

static int check_arg_values(arguments_t *arg)
{
    if (TAILQ_EMPTY(&arg->team_head)) {
        fprintf(stderr, NO_TEAM_PROVIDED);
        return EXIT_WITH_ERROR;
    }
    if (arg->freq == 0)
        arg->freq = DEFAULT_FREQUENCE_VALUE;
    return EXIT_WITH_SUCCESS;
}

static int call_flag(int ac, const char **av, int *i, arguments_t *arg)
{
    unsigned int status = EXIT_WITH_SUCCESS;

    for (size_t j = 0; j < NB_FLAGS; j++) {
        if (strcmp(flags[j].name, av[*i]) == 0) {
            status = flags[j].func(ac, av, i, arg);
            flags[j].occurence++;
            return status;
        }
    }
    fprintf(stderr, UNRECOGNIZED_FLAG(av[*i]));
    return EXIT_WITH_ERROR;
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
    arg->immortal = false;
}

int fill_arg_struct(int ac, const char **av, arguments_t *arg)
{
    unsigned int status = EXIT_WITH_SUCCESS;

    init_arg_struct(arg);
    for (int i = 1; i < ac; i++) {
        if (i < (ac - 1)) {
            status = call_flag(ac, av, &i, arg);
        } else {
            return EXIT_WITH_ERROR;
        }
        if (status == EXIT_WITH_ERROR) {
            return EXIT_WITH_ERROR;
        }
    }
    if (check_flags_occurences() == EXIT_WITH_ERROR ||
        check_arg_values(arg) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
