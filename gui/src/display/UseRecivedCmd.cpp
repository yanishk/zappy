/*
** EPITECH PROJECT, 2024
** my_branch_with_timo
** File description:
** UseRecivedCmd
*/

#include "UseRecivedCmd.hpp"

UseRecivedCmd::UseRecivedCmd(CommandManager &cmd, AllPlayers &player, asio::ip::tcp::socket &socket) : _cmd(cmd), _player(player), _socket(socket)
{
}

void UseRecivedCmd::getPnw(void)
{
    if (_cmd.getCommandAt("pnw", _newPlayerIndex).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pnw", _newPlayerIndex);
        _player.addPlayerToIsland((Vector3){std::stof(cmd.at(1).c_str()), 1.8, std::stof(cmd.at(2).c_str())}, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation((std::atoi(cmd.at(3).c_str()) - 1) * 90, std::atoi(cmd.at(0).c_str()));
        _player.setPlayerTeam(cmd.at(5), std::atoi(cmd.at(0).c_str()));
        _cmd.eraseFirstCmdInMap("pnw");
    }
}

void UseRecivedCmd::getPpo(void)
{
    if (_cmd.getCommandAt("ppo", 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ppo", 0);
        Vector3 newPos = (Vector3){std::stof(cmd.at(1).c_str()), 1.8, std::stof(cmd.at(2).c_str())};

        if (!Utils::Vec3Comp(newPos, _player.getPlayerRealPos(std::atoi(cmd.at(0).c_str()))))
            _player.moovePlayerToIsland(newPos, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation((std::atoi(cmd.at(3).c_str()) - 1) * 90, std::atoi(cmd.at(0).c_str()));
        _cmd.eraseFirstCmdInMap("ppo");
    }
}

void UseRecivedCmd::getPlv(void)
{
    if (_cmd.getCommandAt("plv", 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("plv", 0);
        int playerID = std::atoi(cmd.at(0).c_str());
        int playerLevel = std::atoi(cmd.at(1).c_str());
        _player.setPlayerLevel(playerID, playerLevel);
        _cmd.eraseFirstCmdInMap("plv");
    }
}

void UseRecivedCmd::getPin(void)
{
    if (_cmd.getCommandAt("pin", 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pin", 0);
        int playerID = std::atoi(cmd.at(0).c_str());
        std::vector<int> actualInv = _player.getInventory(playerID);
        std::vector<int> newInv;
        for (std::size_t i = 0; i < actualInv.size(); i++) {
            newInv.push_back(std::atoi(cmd.at(i + 3).c_str()));
        }
        if (newInv == actualInv)
            return;
        _player.setInventory(playerID, newInv);
        _cmd.eraseFirstCmdInMap("pin");
    }
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
    if (_cmd.getCommandAt("pdr", 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pdr", 0);
        int playerID = std::atoi(cmd.at(0).c_str());
        int itemType = std::atoi(cmd.at(1).c_str());
        _player.removeItem(playerID, itemType);
        Vector3 playerPos = _player.getPlayerRealPos(playerID);
        std::string buf = "pin " + std::to_string(playerID) + "\n";
        asio::write(_socket, asio::buffer(buf));
        std::string buf2 = "pdr : bct " + std::to_string((int)playerPos.x) + " " + std::to_string((int)playerPos.z) + "\n";
        std::cout << "Je send : [" << buf2 << "]" << std::endl;
        asio::write(_socket, asio::buffer(buf2));
        _cmd.eraseFirstCmdInMap("pdr");
    }
}

void UseRecivedCmd::getPgt(void)
{
    if (_cmd.getCommandAt("pgt", 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pgt", 0);
        int playerID = std::atoi(cmd.at(0).c_str());
        int itemType = std::atoi(cmd.at(1).c_str());
        _player.addItem(playerID, itemType);
        _cmd.eraseFirstCmdInMap("pgt");
    }
}

void UseRecivedCmd::getPdi(void)
{
    while (_cmd.getCommandAt("pdi", 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pdi", 0);
        _player.removePlayerFromIsland(std::atoi(cmd.at(0).c_str()));
        _cmd.eraseFirstCmdInMap("pdi");
    }
}

void UseRecivedCmd::getEnw(void)
{

}

void UseRecivedCmd::getEbo(void)
{
    while (_cmd.getCommandAt("ebo", 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ebo", 0);
        std::cout << "There is " << cmd.at(0) << " Egg(s) !" << std::endl;
        _cmd.eraseFirstCmdInMap("ebo");
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
