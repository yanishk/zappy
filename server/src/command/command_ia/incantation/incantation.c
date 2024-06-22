/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include "command_ia.h"
#include "command_gui.h"

static int check_required_resources(zappy_t *zappy, player_t *player)
{
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    for (size_t i = 0; i < NB_RESOURCES; i++) {
        if (get_resources(&TILE_RESOURCE, resource_list[i]) <
            get_resources(REQUIRED_RESOURCES, resource_list[i])) {
                return EXIT_WITH_ERROR;
            }
    }
    return EXIT_WITH_SUCCESS;
}

static int *check_required_players(zappy_t *zappy, player_t *player)
{
    player_t *player_on_tile = NULL;
    unsigned int player_allowed = 1;
    int *id_array = malloc(sizeof(int));

    if (id_array == NULL)
        return NULL;
    id_array[0] = player->id;
    for ((player_on_tile) = ((&zappy->player_head)->tqh_first);
        (player_on_tile); (player_on_tile) =
        ((player_on_tile)->player_entries.tqe_next)) {
        if (player_on_same_tile(player, player_on_tile) &&
            player_on_tile->level == player->level) {
            player_allowed++;
            id_array = realloc(id_array, sizeof(int) * player_allowed + 1);
            id_array[player_allowed - 1] = player_on_tile->id;
        }
    }
    if (player_allowed < REQUIRED_PLAYERS)
        return NULL;
    return id_array;
}

static void invite_player_to_ritual(server_t *server, zappy_t *zappy,
    arguments_t *arg, int player_id)
{
    command_ia_t *command = malloc(sizeof(command_ia_t));
    int client_fd = get_client_fd(zappy, player_id);
    client_t *client = get_client_in_struct(server, client_fd);

    if (command == NULL || client == NULL || client_fd == ERROR_RETURN)
        return;
    dprintf(client->client_fd, "Elevation underway\n");
    TAILQ_INSERT_HEAD(&client->command_head, command,
        command_ia_entries);
    command->array = NULL;
    command->time_unit = calculate_freq(arg->freq,
        cmd_list_ia[NB_IA_CMD - 1].time_unit);
    command->index = NB_IA_CMD - 1;
    command->clock_begin = clock();
}

static void invite_players_to_ritual(server_t *server, zappy_t *zappy,
    arguments_t *arg, int *id_array)
{
    player_t *player = get_player_by_id(zappy, id_array[0]);

    if (player == NULL)
        return;
    for (unsigned int i = 0; i < REQUIRED_PLAYERS; i++) {
        invite_player_to_ritual(server, zappy, arg, id_array[i]);
    }
}

int start_incantation(server_t *server, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    int *id_array = NULL;

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (check_required_resources(zappy, player) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    id_array = check_required_players(zappy, player);
    if (id_array == NULL)
        return EXIT_WITH_ERROR;
    invite_players_to_ritual(server, zappy, arg,
        id_array);
    pic_func(server, player, id_array);
    return COMMAND_SUCCESS;
}

static void remove_stones_from_tile(resource_t *resource, player_t *player)
{
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};
    int nb_resources = 0;

    for (size_t i = 0; i < NB_RESOURCES; i++) {
        nb_resources = get_resources(REQUIRED_RESOURCES, resource_list[i]);
        set_resources(resource, resource_list[i], -nb_resources);
    }
}

static bool ritual_succeed(zappy_t *zappy, player_t *player,
    bool *incantation_failed)
{
    *incantation_failed = false;
    if (check_required_players(zappy, player) == NULL) {
        *incantation_failed = true;
        return false;
    }
    if (check_required_resources(zappy, player) == EXIT_WITH_ERROR) {
        *incantation_failed = true;
        return false;
    }
    remove_stones_from_tile(&TILE_RESOURCE, player);
    return true;
}

int end_incantation(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    static bool incantation_failed = false;
    static unsigned int count_players = 0;
    bool is_success = false;

    if (player == NULL || incantation_failed)
        return EXIT_WITH_ERROR;
    if (count_players == 0) {
        is_success = ritual_succeed(zappy, player, &incantation_failed);
        if (!is_success)
            return EXIT_WITH_ERROR;
        pie_func(server, player, is_success);
    }
    count_players++;
    if (count_players == REQUIRED_PLAYERS)
        count_players = 0;
    player->level++;
    plv(server, zappy, player->id);
    dprintf(client->client_fd, "Current level:%d\n", player->level);
    return COMMAND_SUCCESS;
}
