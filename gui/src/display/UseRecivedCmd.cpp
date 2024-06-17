/*
** EPITECH PROJECT, 2024
** my_branch_with_timo
** File description:
** UseRecivedCmd
*/

#include "UseRecivedCmd.hpp"

UseRecivedCmd::UseRecivedCmd(CommandManager &cmd, AllPlayers &player, AllEggs &egg,
    asio::ip::tcp::socket &socket) : _cmd(cmd), _player(player), _egg(egg) , _socket(socket)
{
}

void UseRecivedCmd::getPnw(void)
{
    if (_cmd.getCommandAt(PNW_CMD, 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PNW_CMD, 0);
        _player.addPlayerToIsland((Vector3){std::stof(cmd[1].c_str()), 1.8, std::stof(cmd[2].c_str())}, std::atoi(cmd.front().c_str()));
        _player.changePlayerOrientation((std::atoi(cmd[3].c_str()) - 1) * 90, std::atoi(cmd.front().c_str()));
        _player.setPlayerTeam(cmd[5], std::atoi(cmd.front().c_str()));
        _cmd.eraseFirstCmdInMap(PNW_CMD);
    }
}

void UseRecivedCmd::getPpo(void)
{
    if (_cmd.getCommandAt(PPO_CMD, 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PPO_CMD, 0);
        Vector3 newPos = (Vector3){std::stof(cmd[1].c_str()), 1.8, std::stof(cmd[2].c_str())};

        if (!Utils::Vec3Comp(newPos, _player.getPlayerRealPos(std::atoi(cmd.front().c_str()))))
            _player.moovePlayerToIsland(newPos, std::atoi(cmd.front().c_str()));
        _player.changePlayerOrientation((std::atoi(cmd[3].c_str()) - 1) * 90, std::atoi(cmd.front().c_str()));
        _cmd.eraseFirstCmdInMap(PPO_CMD);
    }
}

void UseRecivedCmd::getPlv(void)
{
    if (_cmd.getCommandAt(PLV_CMD, 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PLV_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int playerLevel = std::atoi(cmd[1].c_str());
        _player.setPlayerLevel(playerID, playerLevel);
        _cmd.eraseFirstCmdInMap(PLV_CMD);
    }
}

void UseRecivedCmd::getPin(void)
{
    while (_cmd.getCommandAt(PIN_CMD, 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PIN_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        std::vector<int> actualInv = _player.getInventory(playerID);
        std::vector<int> newInv;
        for (std::size_t i = 0; i < actualInv.size(); i++) {
            newInv.push_back(std::atoi(cmd[i + 3].c_str()));
        }
        _player.setInventory(playerID, newInv);
        _cmd.eraseFirstCmdInMap(PIN_CMD);
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
    if (_cmd.getCommandAt(PDR_CMD, 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PDR_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int itemType = std::atoi(cmd[1].c_str());
        _player.removeItem(playerID, itemType);
        _cmd.eraseFirstCmdInMap(PDR_CMD);
    }
}

void UseRecivedCmd::getPgt(void)
{
    if (_cmd.getCommandAt(PGT_CMD, 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PGT_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int itemType = std::atoi(cmd[1].c_str());
        _player.addItem(playerID, itemType);
        _cmd.eraseFirstCmdInMap(PGT_CMD);
    }
}

void UseRecivedCmd::getPdi(void)
{
    while (_cmd.getCommandAt(PDI_CMD, 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PDI_CMD, 0);
        _player.removePlayerFromIsland(std::atoi(cmd.front().c_str()));
        _cmd.eraseFirstCmdInMap(PDI_CMD);
    }
}

void UseRecivedCmd::getEnw(void)
{
    while (_cmd.getCommandAt(ENW_CMD, 0).size() >= 1) {
        std::vector<std::string> tmpCmd = _cmd.getCommandAt(ENW_CMD, 0);
        _egg.addEggToIsland((Vector3){std::stof(tmpCmd[2].c_str()), 1.0,
            std::stof(tmpCmd[3].c_str())}, std::stoi(tmpCmd[0]));
        _cmd.eraseFirstCmdInMap(ENW_CMD);
    }
}

void UseRecivedCmd::getEbo(void)
{
    while (_cmd.getCommandAt(EBO_CMD, 0).size() >= 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(EBO_CMD, 0);
        _egg.removeEggFromIsland(std::stoi(cmd[0]));
        _cmd.eraseFirstCmdInMap(EBO_CMD);
    }
}

void UseRecivedCmd::getSmg(void)
{
    while (_cmd.getCommandAt(SMG_CMD, 0).size() >= 1) {
        std::vector<std::string> tmpCmd = _cmd.getCommandAt(SMG_CMD, 0);
        _egg.addEggToIsland((Vector3){std::stof(tmpCmd[2].c_str()), 1.0,
            std::stof(tmpCmd[3].c_str())}, std::stoi(tmpCmd[1]));
        _cmd.eraseFirstCmdInMap(SMG_CMD);
    }
}

void UseRecivedCmd::getEdi(void)
{

}

void UseRecivedCmd::getSgt(void)
{
    if (!_cmd.getCommandAt(SGT_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(SGT_CMD, 0);
        _sgtValue = std::stoi(cmd[0]);
        _cmd.eraseFirstCmdInMap(SGT_CMD);
    }
}

void UseRecivedCmd::getSst(void)
{
    if (IsKeyPressed(KEY_UP)) {
        _sgtValue += SST_CHANGE;
        std::string value = std::to_string(_sgtValue);
        std::string sstCmd = SST_CMD;
        sstCmd += SPACE_C;
        sstCmd += value;
        sstCmd += NEW_L;
        asio::write(_socket, asio::buffer(sstCmd));
    } else if (IsKeyPressed(KEY_DOWN)) {
        _sgtValue -= SST_CHANGE;
        std::string value = std::to_string(_sgtValue);
        std::string sstCmd = SST_CMD;
        sstCmd += SPACE_C;
        sstCmd += value;
        sstCmd += NEW_L;
        asio::write(_socket, asio::buffer(sstCmd));
    }
}

void UseRecivedCmd::getSeg(void)
{

}
