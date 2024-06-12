/*
** EPITECH PROJECT, 2024
** zappy_gui_try2
** File description:
** Island
*/

#ifndef ISLAND_HPP_
    #define ISLAND_HPP_

    #include <string>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include <stdlib.h>
    #include <ctime>
    #include "raylib.h"
    #include "raymath.h"
    #include "rlgl.h"

class Island {
    public:
        Model _islandModel;
        Vector3 _islandPosition;
        float _islandSize;
};

#endif /* !ISLAND_HPP_ */
