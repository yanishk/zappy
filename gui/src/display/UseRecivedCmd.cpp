/*
** EPITECH PROJECT, 2024
** my_branch_with_timo
** File description:
** UseRecivedCmd
*/

#include "UseRecivedCmd.hpp"

UseRecivedCmd::UseRecivedCmd(CommandManager &cmd, AllPlayers &player) : _cmd(cmd), _player(player)
{
}

void UseRecivedCmd::getPnw(void)
{
    while (_cmd.getCommandAt("pnw", _newPlayerIndex).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pnw", _newPlayerIndex);
        _player.addPlayerToIsland((Vector3){std::stof(cmd.at(1).c_str()), 1.8, std::stof(cmd.at(2).c_str())}, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation((std::atoi(cmd.at(3).c_str()) - 1) * 90, std::atoi(cmd.at(0).c_str()));
        _player.setPlayerTeam(cmd.at(5), std::atoi(cmd.at(0).c_str()));
        _newPlayerIndex++;
    }
}

void UseRecivedCmd::getPpo(void)
{
    for (int i = 0; _cmd.getCommandAt("ppo", i).size() > 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ppo", i);
        Vector3 newPos = (Vector3){std::stof(cmd.at(1).c_str()), 1.8, std::stof(cmd.at(2).c_str())};

        if (!Utils::Vec3Comp(newPos, _player.getPlayerRealPos(std::atoi(cmd.at(0).c_str()))))
            _player.moovePlayerToIsland(newPos, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation((std::atoi(cmd.at(3).c_str()) - 1) * 90, std::atoi(cmd.at(0).c_str()));
    }
}

void UseRecivedCmd::getPlv(void)
{
    for (int i = 0; _cmd.getCommandAt("plv", i).size() > 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("plv", i);
        int playerID = std::atoi(cmd.at(0).c_str());
        int playerLevel = std::atoi(cmd.at(1).c_str());
        if (_player.getPlayerLevel(playerID) != playerLevel)
            _player.setPlayerLevel(playerID, playerLevel);
    }
}

void UseRecivedCmd::getPin(void)
{
    // for (int i = 0; _cmd.getCommandAt("pin", _inventoryIndex).size() >= 1; i++) {
    //     std::vector<std::string> cmd = _cmd.getCommandAt("pin", _inventoryIndex);
    //     _player.addItem(std::atoi(cmd.at(0).c_str()), std::atoi(cmd.at(1).c_str()));
    //     _inventoryIndex += 1;
    // }
}

void UseRecivedCmd::getPex(void)
{

}

void UseRecivedCmd::getPbc(void)
{

}

void UseRecivedCmd::getPic(void)
{

}

void UseRecivedCmd::getPie(void)
{

}

void UseRecivedCmd::getPdr(void)
{
    for (int i = 0; _cmd.getCommandAt("pdr", _droppingItemIndex).size() >= 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pdr", _droppingItemIndex);
        _player.removeItem(std::atoi(cmd.at(0).c_str()), std::atoi(cmd.at(1).c_str()));
        _droppingItemIndex += 1;
    }
}

void UseRecivedCmd::getPgt(void)
{
    for (int i = 0; _cmd.getCommandAt("pgt", _collectingItemIndex).size() >= 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pgt", _collectingItemIndex);
        int playerID = std::atoi(cmd.at(0).c_str());
        int itemType = std::atoi(cmd.at(1).c_str());
        _player.addItem(playerID, itemType);
        _collectingItemIndex += 1;
    }
}

void UseRecivedCmd::getPdi(void)
{
    for (int i = 0; _cmd.getCommandAt("pdi", _playerLevelIndex).size() >= 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pdi", _playerLevelIndex);
        _player.removePlayerFromIsland(std::atoi(cmd.at(0).c_str()));
        _playerLevelIndex += 1;
    }
}

void UseRecivedCmd::getEnw(void)
{

}

void UseRecivedCmd::getEbo(void)
{
    for (int i = 0; _cmd.getCommandAt("ebo", _playerEboIndex).size() >= 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ebo", _playerEboIndex);
        std::cout << "There is " << cmd.at(0) << " Egg(s) !" << std::endl;
        _playerEboIndex += 1;
    }
}

void UseRecivedCmd::getEdi(void)
{

}

void UseRecivedCmd::getSgt(void)
{

}

void UseRecivedCmd::getSst(void)
{

}

void UseRecivedCmd::getSeg(void)
{

}

