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

class Egg : public ILoadAndRender {

    public:

        void render() override;
        void fillModel(std::pair<Model, float> model) override;
        void setEggPosAndID(Vector2 pos, int eggId);

        int getEggId();
        Vector2 getEggRealPos();
        Vector3 get3DEggPos();

    private:

        Vector2 _eggRealPos;
        Vector3 _egg3DPosition;
        Model _eggModel;

        float _eggHight;
        float _eggSize;

        int _eggID;
};

class AllEggs {

    public:

        AllEggs(CommandManager &cmd);

        void setAllEggs(std::pair<Model, float> model);
        void removeEgg(int Id);
        void renderAll(void);

    private:

        CommandManager &_cmd;
        std::vector<Egg> _allEggs;
};

#endif /* !EGGS_HPP_ */
