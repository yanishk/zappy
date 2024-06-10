/*
** EPITECH PROJECT, 2024
** zappy_gui_try2
** File description:
** Island
*/

#ifndef ISLAND_HPP_
    #define ISLAND_HPP_

    #include "raylib.h"
    #include "raymath.h"
    #include "rlgl.h"
    #include "string"
    #include "iostream"
    #include <tuple>
    #include <vector>
    #include <stdlib.h>
    #include <ctime>

class Island {
    public:
        Model _islandModel;
        Vector3 _islandPosition;
        float _islandSize;

    protected:
    private:
};

class Item {
    public:
        Model _itemModel;
        Vector3 _itemPosition;
        float _itemSize;
        float _rotation;
        float _upValue;
        int _itemType;
        Vector3 _realPos;

    protected:
    private:
};

#endif /* !ISLAND_HPP_ */
