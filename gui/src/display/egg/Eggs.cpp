/*
** EPITECH PROJECT, 2024
** Eggs file
** File description:
** Eggs
*/

#include <unordered_map>

#include "Eggs.hpp"

Vector3 Egg::get3DEggPos()
{
    return _egg3DPosition;
}

void Egg::render()
{
    DrawModel(_eggModel, get3DEggPos(), _eggSize, WHITE);
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
    static const std::unordered_map<std::string,
        std::function<void(std::vector<std::string> &)>> commandHandlers = {

        { SMG_CMD, [this, &model](std::vector<std::string>& cmd) {
            Egg newEgg;
            newEgg.fillModel(model);
            newEgg.setEggPosAndID((Vector2){std::stof(cmd[2]),
                std::stof(cmd[3])}, std::atoi(cmd[1].c_str()));
            _allEggs.push_back(newEgg);
        }},

        { ENW_CMD, [this, &model](std::vector<std::string>& cmd) {
            Egg newEgg;
            newEgg.fillModel(model);
            newEgg.setEggPosAndID((Vector2){std::stof(cmd[2]),
                std::stof(cmd[3])}, std::atoi(cmd[0].c_str()));
            _allEggs.push_back(newEgg);
        }},

        { EBO_CMD, [this](std::vector<std::string>& cmd) {
            removeEgg(std::stoi(cmd[0]));
        }},

        { EDI_CMD, [this](std::vector<std::string>& cmd) {
            removeEgg(std::stoi(cmd[0]));
        }}
    };

    for (const auto& [cmdType, handler] : commandHandlers) {
        if (!_cmd.getCommandAt(cmdType, 0).empty()) {
            std::vector<std::string> cmd = _cmd.getCommandAt(cmdType, 0);
            handler(cmd);
            _cmd.eraseFirstCmdInMap(cmdType);
            break;
        }
    }
}

void AllEggs::renderAll(void)
{
    for (auto &t : _allEggs) {
        t.render();
    }
}