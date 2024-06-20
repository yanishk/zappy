/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** resource
*/

#ifndef RESOURCE_H_
    #define RESOURCE_H_

    #include <stdlib.h>

    #define FOOD_TIME_UNIT 126
    #define REFILL_MAP_TIME_UNIT 20

    #define NB_RESOURCES 7

    #define FOOD "food"
    #define LINEMATE "linemate"
    #define DERAUMERE "deraumere"
    #define SIBUR "sibur"
    #define MENDIANE "mendiane"
    #define PHIRAS "phiras"
    #define THYSTAME "thystame"

    #define FOOD_DEN 0.5
    #define LINEMATE_DEN 0.3
    #define DERAUMERE_DEN 0.15
    #define SIBUR_DEN 0.1
    #define MENDIANE_DEN 0.1
    #define PHIRAS_DEN 0.08
    #define THYSTAME_DEN 0.05

typedef struct resource_s {
    size_t food;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
} resource_t;

typedef struct associate_resource_nb_s {
    char *name;
    int code_resource;
} associate_resource_nb_t;

struct repartion_resource {
    char *name;
    double density;
};

extern struct repartion_resource const repartion_unit[NB_RESOURCES];

void print_tile_resources(const unsigned int, int, int, const resource_t);

#endif /* !RESOURCE_H_ */
