/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** main
*/

#include "server.h"

static void display_help(void)
{
    dprintf(2, "USAGE: ./zappy_server -p port -x width -y height -n name1");
    dprintf(2, " name2 ... -c clientsNb -f freq --immortal isImmortal\n");
    dprintf(2, "\t\tport\t\tis the port number\n");
    dprintf(2, "\t\twidth\t\tis the width of the world\n");
    dprintf(2, "\t\theight\t\tis the height of the world\n");
    dprintf(2, "\t\tnameX\t\tis the name of the team X\n");
    dprintf(2, "\t\tclientsNb\tis the number of authorized clients per ");
    dprintf(2, "team\n");
    dprintf(2, "\t\tfreq\t\tis the reciprocal of time unit for execution");
    dprintf(2, " of actions (optional, set to 100 by default)\n");
    dprintf(2, "\t\tisImmortal\tis the state of immortality for the players ");
    dprintf(2, "(optional, set to false by default)\n");
}

int main(int ac, const char **av)
{
    if (ac == 2) {
        if (strcmp(av[1], "-help") == 0) {
            display_help();
            return EXIT_WITH_SUCCESS;
        }
    }
    if (ac < MIN_ARGS) {
        display_help();
        return EXIT_WITH_ERROR;
    }
    return server(ac, av);
}
