/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** choose_random_egg
*/

#include "server.h"

static egg_t **get_team_eggs(zappy_t *zappy,
    size_t *nb_eggs, char *team_name)
{
    egg_t *egg = NULL;
    egg_t **egg_array = NULL;

    for ((egg) = ((&zappy->egg_head)->tqh_first); (egg);
        (egg) = ((egg)->egg_entries.tqe_next)) {
        if (strcmp(team_name, egg->team_name) == 0) {
            *nb_eggs += 1;
            egg_array = realloc(egg_array, sizeof(egg_t *) * (*nb_eggs));
            egg_array[(*nb_eggs) - 1] = egg;
        }
    }
    return egg_array;
}

egg_t *get_random_team_egg(zappy_t *zappy, char *team_name)
{
    egg_t **egg_array = NULL;
    egg_t *random_egg = NULL;
    size_t nb_eggs = 0;

    egg_array = get_team_eggs(zappy, &nb_eggs, team_name);
    if (egg_array == NULL || nb_eggs == 0)
        return NULL;
    random_egg = egg_array[rand() % nb_eggs];
    free(egg_array);
    return random_egg;
}
