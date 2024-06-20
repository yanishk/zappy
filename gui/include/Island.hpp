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

    #include "Render.hpp"
    #include "Commands.hpp"

class Island : public LoadAndRender {

    public:

        void render() override;
        void fillModel(std::pair<Model, float> model) override;
        void setIslandPos(Vector3 pos);

    private:

        Model _islandModel;
        Vector3 _islandPosition;
        float _islandSize;
};

class AllIsland {

    public:

        AllIsland(CommandManager &cmd);

        void getIsland();
        void setAllIsland(std::pair<Model, float> model,
            std::pair<int, int> mapSize);

    private:

        CommandManager &_cmd;
        std::vector<Island> _allIsland;

};

#endif /* !ISLAND_HPP_ */
