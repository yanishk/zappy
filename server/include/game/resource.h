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
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
    size_t food;
} resource_t;

struct repartion_resource {
    char *name;
    double density;
};

#endif /* !RESOURCE_H_ */
