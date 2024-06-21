/*
** EPITECH PROJECT, 2024
** AllEggs file
** File description:
** Zappy proj
*/

#include "AllEggs.hpp"

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
            newEgg.setModel(model);
            newEgg.setEggPosAndID((Vector2){std::stof(cmd[2]),
                std::stof(cmd[3])}, std::atoi(cmd[1].c_str()));
            _allEggs.push_back(newEgg);
        }},

        { ENW_CMD, [this, &model](std::vector<std::string>& cmd) {
            Egg newEgg;
            newEgg.setModel(model);
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