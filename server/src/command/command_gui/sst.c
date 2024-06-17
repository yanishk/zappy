/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** sst
*/

#include "command_gui.h"

int sst_func(server_t *server, zappy_t *, arguments_t *arg, client_t *)
{
    client_t *graphical = get_graphical_client(server);
    int new_freq = atoi(server->cmd_arg_array[1]);

    if (graphical == NULL)
        return EXIT_WITH_ERROR;
    if (!is_positive_number(server->cmd_arg_array[1]) || new_freq == 0)
        return EXIT_WITH_ERROR;
    arg->freq = new_freq;
    dprintf(graphical->client_fd, "sst %d\n", arg->freq);
    return EXIT_WITH_SUCCESS;
}
