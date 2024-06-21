/*
** EPITECH PROJECT, 2024
** Eggs file
** File description:
** Eggs
*/

#include "Eggs.hpp"

Egg::Egg(Vector3 position, int eggId) : LoadAndRender()
{
    _eggHight = 1.2;
    _eggRealPos = position;
    _eggID = eggId;
}

Vector3 Egg::get3DEggPos()
{
    return _egg3DPosition;
}

void Egg::render()
{
    DrawModel(_eggModel, get3DEggPos(), 0.3, WHITE);
}

void Egg::fillModel(std::pair<Model, float> model)
{
    _eggModel = model.first;
    _eggSize = model.second;
}

Vector3 Egg::getEggRealPos()
{
    return _eggRealPos;
}

int Egg::getEggId()
{
    return _eggID;
}

int Egg::getRngRotate()
{
    return _rngRotate;
}

AllEggs::AllEggs(CommandManager &cmd) : _cmd(cmd)
{

}

void AllEggs::setAllEggs(std::pair<Model, float> model)
{
     while (!_cmd.getCommandAt(SMG_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(SMG_CMD, 0);
        _allEggs.clear();

        Egg tmpEgg((Vector3){std::stof(cmd[2].c_str()), 1.0,
            std::stof(cmd[3].c_str())}, std::stoi(cmd[1]));

        int rngRotate = std::rand() % (210 - 159 + 1) + 159;
        float tiltAngle = (std::rand() % 40) + 80;

        model.first.transform = MatrixRotateXYZ((Vector3){DEG2RAD * tiltAngle,
            DEG2RAD * rngRotate, DEG2RAD * 0});
        tmpEgg.fillModel(model);
       tmpEgg._egg3DPosition = (Vector3){std::stof(cmd[2].c_str()), 1.0,
            std::stof(cmd[3].c_str()) + spaceBetwenIsland};
        tmpEgg._egg3DPosition.x += -2 + (std::rand() % 4);
        tmpEgg._egg3DPosition.z += -2 + (std::rand() % 4);
        _allEggs.push_back(tmpEgg);

        _cmd.eraseFirstCmdInMap(SMG_CMD);
    }
}

void AllEggs::renderAll(void)
{
    for (auto &t : _allEggs) {
        t.render();
    }
}