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
    #include "Render.hpp"
    #include "Commands.hpp"

class Egg : public LoadAndRender {

    public:

        Egg(Vector3 position, int eggId);

        void render() override;
        void fillModel(std::pair<Model, float> model) override;

        int getEggId();
        int getRngRotate();
        Vector3 getEggRealPos();
        Vector3 get3DEggPos();

        Vector3 _eggRealPos;
        Vector3 _egg3DPosition;
    private:

        Model _eggModel;

        float _eggHight;
        float _eggSize;

        int _eggID;
        int _rngRotate;

};

class AllEggs {

    public:

        AllEggs(CommandManager &cmd);

        void setAllEggs(std::pair<Model, float> model);
        void renderAll(void);

    private:

        CommandManager &_cmd;
        std::vector<Egg> _allEggs;

};

#endif /* !EGGS_HPP_ */
