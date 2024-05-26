/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** main
*/

#include <stdio.h>
#include "server.h"

static void display_help(void)
{
    dprintf(2, "USAGE: ./zappy_server -p port -x width -y height -n name1");
    dprintf(2, " name2 ... -c clientsNb -f freq\n");
    dprintf(2, "\t\tport\t\tis the port number\n");
    dprintf(2, "\t\twidth\t\tis the width of the world\n");
    dprintf(2, "\t\theight\t\tis the height of the world\n");
    dprintf(2, "\t\tnameX\t\tis the name of the team X\n");
    dprintf(2, "\t\tclientsNb\tis the number of authorized clients per ");
    dprintf(2, "team\n");
    dprintf(2, "\t\tfreq\t\tis the reciprocal of time unit for execution");
    dprintf(2, " of actions\n");
}

int main(int ac, __attribute__((__unused__)) char **av)
{
    if (ac < MIN_ARGS) {
        display_help();
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}
