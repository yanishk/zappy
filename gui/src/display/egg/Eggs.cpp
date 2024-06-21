/*
** EPITECH PROJECT, 2024
** Eggs file
** File description:
** Eggs
*/

#include "Eggs.hpp"

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
    float rngRotate = std::rand() % (210 - 159 + 1) + 159;
    float tiltAngle = (std::rand() % 40) + 80;
    _eggModel.transform = MatrixRotateXYZ((Vector3){DEG2RAD * tiltAngle, DEG2RAD * rngRotate, DEG2RAD * 0});
}

void Egg::setEggPosAndID(Vector2 pos, int eggId)
{
    _eggID = eggId;
    _eggRealPos = pos;
    _egg3DPosition = (Vector3){(pos.x + 1) * spaceBetwenIsland, 1.0, pos.y * spaceBetwenIsland};
    _egg3DPosition.x += -2 + (std::rand() % 4);
    _egg3DPosition.z += -2 + (std::rand() % 4);
}

Vector2 Egg::getEggRealPos()
{
    return _eggRealPos;
}

int Egg::getEggId()
{
    return _eggID;
}

AllEggs::AllEggs(CommandManager &cmd) : _cmd(cmd)
{

}

void AllEggs::removeEgg(int Id)
{
    for (auto it = _allEggs.begin(); it != _allEggs.end(); ++it) {
        if (it->getEggId() == Id) {
            _allEggs.erase(it);
            break;
        }
    }
}

void AllEggs::setAllEggs(std::pair<Model, float> model)
{
    if (!_cmd.getCommandAt(SMG_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(SMG_CMD, 0);
        Egg newEgg;

        newEgg.fillModel(model);
        newEgg.setEggPosAndID((Vector2){std::stof(cmd[2].c_str()), std::stof(cmd[3].c_str())}, std::atoi(cmd[1].c_str()));
        _allEggs.push_back(newEgg);
        _cmd.eraseFirstCmdInMap(SMG_CMD);
    } else if (!_cmd.getCommandAt(ENW_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(ENW_CMD, 0);
        Egg newEgg;

        newEgg.fillModel(model);
        newEgg.setEggPosAndID((Vector2){std::stof(cmd[2].c_str()), std::stof(cmd[3].c_str())}, std::atoi(cmd[0].c_str()));
        _allEggs.push_back(newEgg);
        _cmd.eraseFirstCmdInMap(ENW_CMD);
    } else if (!_cmd.getCommandAt(EBO_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(EBO_CMD, 0);
        removeEgg(std::stoi(cmd[0]));
        _cmd.eraseFirstCmdInMap(EBO_CMD);
    } else if (!_cmd.getCommandAt(EDI_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(EDI_CMD, 0);
        removeEgg(std::stoi(cmd[0]));
        _cmd.eraseFirstCmdInMap(EDI_CMD);
    }

}

void AllEggs::renderAll(void)
{
    for (auto &t : _allEggs) {
        t.render();
    }
}