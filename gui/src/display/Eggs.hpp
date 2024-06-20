/*
** EPITECH PROJECT, 2024
** Eggs Class
** File description:
** zappy proj
*/

#ifndef EGGS_HPP_
    #define EGGS_HPP_
    #include <string>
    #include <vector>
    #include <iostream>
    #include <iomanip>
    #include <map>
    #include "Utils.hpp"

class Egg {

    public:

        Egg(Vector3 position);
        Vector3 getPosition();

        Model _eggModel;
        int _eggID;
        int RngRotate;

        Vector3 _realPos;

    private:

        Vector3 _eggPosition;
        float _eggHight;
};

class AllEggs {

    public:

        std::vector<Egg> _allEggs;

        void loadEggModel(std::pair<Model, float>);
        void addEggToIsland(Vector3 position, int playerID);
        void removeEggFromIsland(int playerID);
        void drawEgg();
        Vector3 getEggRealPos(int playerID);

    private:

        Model _model;
        float _size;

};

#endif /* !EGGS_HPP_ */
