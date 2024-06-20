/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/

#include "server.h"

int server(int ac, const char **av)
{
    server_t *server = NULL;
    arguments_t arg;
    zappy_t zappy;

    srand(time(NULL));
    if (fill_arg_struct(ac, av, &arg) == EXIT_WITH_ERROR) {
        free_arg_teams(&arg);
        return EXIT_WITH_ERROR;
    }
    server = init_server_struct(arg);
    initialize_game(arg, &zappy);
    if (server == NULL)
        return EXIT_WITH_ERROR;
    if (initialize_server(server) == EXIT_WITH_ERROR ||
        run_server(server, &zappy, &arg) == EXIT_WITH_ERROR) {
        free_program(server, &zappy, &arg);
        return EXIT_WITH_ERROR;
    }
    free_program(server, &zappy, &arg);
    return EXIT_WITH_SUCCESS;
}
