/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** check_incantation
*/

#include "command_ia.h"

static resource_t const elevations_resources[NB_ELEVATIONS] = {
    {1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0},
    {2, 0, 1, 0, 2, 0, 0},
    {1, 1, 2, 0, 1, 0, 0},
    {1, 2, 1, 3, 0, 0, 0},
    {1, 2, 3, 0, 1, 0, 0},
    {2, 2, 2, 2, 2, 1, 0}
};

static incantation_t const elevations[NB_ELEVATIONS] = {
    {2, 1, &elevations_resources[0]},
    {3, 2, &elevations_resources[1]},
    {4, 2, &elevations_resources[2]},
    {5, 4, &elevations_resources[3]},
    {6, 4, &elevations_resources[4]},
    {7, 6, &elevations_resources[5]},
    {8, 6, &elevations_resources[6]},
};

#define ELEVATION elevations[player->level -1]
#define REQUIRED_RESOURCE ELEVATION.required_resources
#define REQUIRED_LEVEL ELEVATION.elevation_level
#define REQUIRED_PLAYER ELEVATION.required_players

static int check_required_resources(zappy_t *zappy, player_t *player)
{
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    for (size_t i = 0; i < NB_RESOURCES; i++) {
        if (get_resources(&TILE_RESOURCE, resource_list[i])
            < get_resources(REQUIRED_RESOURCE, resource_list[i])) {
                return EXIT_WITH_ERROR;
            }
    }
    return EXIT_WITH_SUCCESS;
}

static int *fill_required_player(zappy_t *zappy, player_t *player)
{
    player_t *player_on_tile = NULL;
    unsigned int player_allowed = 1;
    int *id_array = malloc(sizeof(int));

    id_array[0] = player->id;
    TAILQ_FOREACH(player_on_tile, &zappy->player_head, player_entries) {
        if (player_on_same_tile(player, player_on_tile) && player_on_tile->level == player->level) {
            player_allowed++;
            id_array = realloc(id_array, sizeof(int) * player_allowed + 1);
            id_array[player_allowed - 1] = player_on_tile->id;
        }
    }
    if (player_allowed < REQUIRED_LEVEL)
        return NULL;
    return id_array;
}

static int check_required_player(zappy_t *zappy, player_t *player)
{
    int *id_array = fill_required_player(zappy, player);

    if (id_array == NULL)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}

static void send_incantation_to_player(server_t *server, zappy_t *zappy,
    int player_id, char **array)
{
    command_ia_t *command = malloc(sizeof(command_ia_t));
    unsigned int client_fd = get_client_fd(zappy, player_id);
    client_t *client = get_client_in_struct(server, client_fd);

    if (client == NULL || command == NULL)
        return;
    TAILQ_INSERT_HEAD(&client->command_head, command,
        command_ia_entries);
    command->array = array;
    command->time_unit =  cmd_list_ia[NB_IA_CMD - 1].time_unit;
    command->index = NB_IA_CMD - 1;
    command->clock_begin = clock();
}

static void send_incantation_to_players(server_t *server, zappy_t *zappy,
    int required_players, int *player_id_array)
{
    char **array = word_array("Remove stones\n", "\n");

    if (array == NULL)
        return;
    for (int i = 0; i < required_players; i++) {
        if (i == 0)
            send_incantation_to_player(server, zappy, player_id_array[i], array);
        else
            send_incantation_to_player(server, zappy, player_id_array[i], NULL);
    }
}

int check_incantation(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    int player_id_array[] = {0, 1};

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (check_required_resources(zappy, player) == EXIT_WITH_ERROR ||
        check_required_player(zappy, player) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    send_incantation_to_players(server, zappy, REQUIRED_PLAYER,
        player_id_array);
    return COMMAND_SUCCESS;
}

void remove_stones_from_tile(resource_t *resource, player_t *player)
{
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};
    int resources_to_remove = 0;

    for (size_t i = 0; i < NB_RESOURCES; i++) {
        resources_to_remove = get_resources(REQUIRED_RESOURCE, resource_list[i]);
        set_resources(resource, resource_list[i], -resources_to_remove);
    }
}

int do_incantation(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
  if (check_required_resources(zappy, player) == EXIT_WITH_ERROR ||
        check_required_player(zappy, player) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    if (server->cmd_arg_array != NULL) {
        if (strcmp(server->cmd_arg_array[0], "Remove stones") == 0) {
            remove_stones_from_tile(&TILE_RESOURCE, player);
        }
    }
    player->level++;
    dprintf(client->client_fd, "Current level:%d\n", player->level);
    return COMMAND_SUCCESS;
}
