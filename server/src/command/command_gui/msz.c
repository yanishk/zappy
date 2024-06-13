/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** msz
*/

#include "command_gui.h"

int msz_func(server_t *, zappy_t *, arguments_t *arg, client_t *client)
{
    dprintf(client->client_fd, "msz %d %d \n", arg->width, arg->height);
    return EXIT_WITH_SUCCESS;
}
