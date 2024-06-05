/*
** EPITECH PROJECT, 2024
** ai
** File description:
** TestsRessources
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Ressources.hpp"

Test(Ressources, Ressources)
{
    Zappy::Ressources ressources;

    cr_assert_eq(ressources.getRessource(FOOD), FOOD_START_VALUE);
    cr_assert_eq(ressources.getRessource(LINEMATE), 0);
    cr_assert_eq(ressources.getRessource(DERAUMERE), 0);
    cr_assert_eq(ressources.getRessource(SIBUR), 0);
    cr_assert_eq(ressources.getRessource(MENDIANE), 0);
    cr_assert_eq(ressources.getRessource(PHIRAS), 0);
    cr_assert_eq(ressources.getRessource(THYSTAME), 0);
}

Test(Ressources, addRessources)
{
    Zappy::Ressources ressources;

    cr_assert_eq(ressources.getRessource(FOOD), FOOD_START_VALUE);

    ressources.addRessources(FOOD, 10);
    ressources.addRessources(LINEMATE, 5);

    cr_assert_eq(ressources.getRessource(FOOD), 10 + FOOD_START_VALUE);
    cr_assert_eq(ressources.getRessource(LINEMATE), 5);

    ressources.addRessources(FOOD, 5);

    cr_assert_eq(ressources.getRessource(FOOD), 15 + FOOD_START_VALUE);
}

Test(Ressources, removeRessources)
{
    Zappy::Ressources ressources;

    ressources.removeRessources(FOOD, FOOD_START_VALUE);

    cr_assert_eq(ressources.getRessource(FOOD), 0);

    ressources.addRessources(FOOD, FOOD_START_VALUE);
    ressources.removeRessources(FOOD, 6);

    cr_assert_eq(ressources.getRessource(FOOD), FOOD_START_VALUE - 6);
}
