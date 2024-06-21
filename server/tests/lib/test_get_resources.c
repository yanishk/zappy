/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_resources
*/

#include <criterion/criterion.h>
#include "server.h"

Test(get_resources, get_other)
{
    resource_t resource;
    int res = 0;

    resource.food = 1;
    res = get_resources(&resource, "other");
    cr_assert_eq(ERROR_RETURN, res);
}

Test(get_resources, get_food)
{
    resource_t resource;
    int res = 0;

    resource.food = 2;
    res = get_resources(&resource, FOOD);
    cr_assert_eq(resource.food, res);
}

Test(get_resources, get_linemate)
{
    resource_t resource;
    int res = 0;

    resource.linemate = 3;
    res = get_resources(&resource, LINEMATE);
    cr_assert_eq(resource.linemate, res);
}

Test(get_resources, get_deraumere)
{
    resource_t resource;
    int res = 0;

    resource.deraumere = 4;
    res = get_resources(&resource, DERAUMERE);
    cr_assert_eq(resource.deraumere, res);
}

Test(get_resources, get_sibur)
{
    resource_t resource;
    int res = 0;

    resource.sibur = 5;
    res = get_resources(&resource, SIBUR);
    cr_assert_eq(resource.sibur, res);
}

Test(get_resources, get_mendiane)
{
    resource_t resource;
    int res = 0;

    resource.mendiane = 6;
    res = get_resources(&resource, MENDIANE);
    cr_assert_eq(resource.mendiane, res);
}

Test(get_resources, get_phiras)
{
    resource_t resource;
    int res = 0;

    resource.phiras = 7;
    res = get_resources(&resource, PHIRAS);
    cr_assert_eq(resource.phiras, res);
}

Test(get_resources, get_thystame)
{
    resource_t resource;
    int res = 0;

    resource.thystame = 8;
    res = get_resources(&resource, THYSTAME);
    cr_assert_eq(resource.thystame, res);
}
