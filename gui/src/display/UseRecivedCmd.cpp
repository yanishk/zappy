/*
** EPITECH PROJECT, 2024
** my_branch_with_timo
** File description:
** UseRecivedCmd
*/

#include "UseRecivedCmd.hpp"

UseRecivedCmd::UseRecivedCmd(CommandManager &cmd, AllPlayers &player, AllEggs &egg,
    std::vector<Item> &allItem, std::vector<Item> &allItemModel, asio::ip::tcp::socket &socket) : _cmd(cmd), _player(player), _egg(egg) , _allItem(allItem), _allItemModel(allItemModel), _socket(socket)
{
}

void UseRecivedCmd::callAllFunctions(Vector3 camPosition)
{
    getBct();
    getTna();
    getPnw();
    getPpo();
    getPlv();
    getPdi();
    getEbo();
    getPgt();
    getPdr();
    getPin();
    getEnw();
    getSmg();
    getPbc(camPosition);
    getSgt();
    getSst();
    getEdi();
    getPic();
    getPie();
    getSeg();
    getPex();
}

void UseRecivedCmd::getBct(void)
{
    while (_cmd.getCommandAt(BCT_CMD, 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(BCT_CMD, 0);
        float x = std::stof(cmd.front().c_str());
        float z = std::stof(cmd[1].c_str());
        Vector3 itemPosition = (Vector3){x, 1.8, z};
        for (std::size_t j = 2; j < cmd.size(); j++) {
            int nbItem = std::atoi(cmd[j].c_str());
            int nbItemOnIsland = getNbrItemTypeOnIsland(itemPosition, j - 2);
            while (nbItemOnIsland > 0) {
                removeItemFromIsland(itemPosition, j - 2);
                nbItemOnIsland--;
            }
            for (int k = 0; k < nbItem; k++) {
                addItemToIsland(itemPosition, j - 2);
            }
        }
        _cmd.eraseFirstCmdInMap(BCT_CMD);
    }
}

void UseRecivedCmd::getTna(void)
{
    while (_cmd.getCommandAt(TNA_CMD, 0).size() == 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(TNA_CMD, 0);
        if (_player._allTeamName.size() == 0) {
            _player._allTeamName.push_back(cmd.front());
            continue;
        }
        bool isUnique = true;
        for (auto &i: _player._allTeamName) {
            if (i == cmd.front())
                isUnique = false;
        }
        if (isUnique) {
            _player._allTeamName.push_back(cmd.front());
        }
        _cmd.eraseFirstCmdInMap(TNA_CMD);
    }
}

void UseRecivedCmd::getPnw(void)
{
    if (!_cmd.getCommandAt(PNW_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PNW_CMD, 0);
        _player.addPlayerToIsland((Vector3){std::stof(cmd[1].c_str()), 1.8, std::stof(cmd[2].c_str())}, std::atoi(cmd.front().c_str()));
        _player.changePlayerOrientation((std::atoi(cmd[3].c_str()) - 1), std::atoi(cmd.front().c_str()));
        _player.setPlayerTeam(cmd[5], std::atoi(cmd.front().c_str()));
        _cmd.eraseFirstCmdInMap(PNW_CMD);
    }
}

void UseRecivedCmd::getPpo(void)
{
    if (!_cmd.getCommandAt(PPO_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PPO_CMD, 0);
        Vector3 newPos = (Vector3){std::stof(cmd[1].c_str()), 1.8, std::stof(cmd[2].c_str())};

        if (!Utils::Vec3Comp(newPos, _player.getPlayerRealPos(std::atoi(cmd.front().c_str()))))
            _player.moovePlayerToIsland(newPos, std::atoi(cmd.front().c_str()));
        _player.changePlayerOrientation((std::atoi(cmd[3].c_str()) - 1), std::atoi(cmd.front().c_str()));
        _cmd.eraseFirstCmdInMap(PPO_CMD);
    }
}

void UseRecivedCmd::getPlv(void)
{
    if (!_cmd.getCommandAt(PLV_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PLV_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int playerLevel = std::atoi(cmd[1].c_str());
        _player.setPlayerLevel(playerID, playerLevel);
        _cmd.eraseFirstCmdInMap(PLV_CMD);
    }
}

void UseRecivedCmd::getPin(void)
{
    while (!_cmd.getCommandAt(PIN_CMD, 0).empty()) {
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
    while (!_cmd.getCommandAt(PEX_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PEX_CMD, 0);
        int playerID = std::atoi(cmd[0].c_str());
        _player.playerExpulsion(playerID);
        _cmd.eraseFirstCmdInMap(PEX_CMD);
    }
}

void UseRecivedCmd::getPbc(Vector3 camPosition)
{
    if (!_cmd.getCommandAt(PBC_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PBC_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        _player.drawMessage(playerID, cmd[1], camPosition);
        _cmd.eraseFirstCmdInMap(PBC_CMD);
    }
}

void UseRecivedCmd::getPic(void)
{
    while (!_cmd.getCommandAt(PIC_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PIC_CMD, 0);
        Vector2 pos = (Vector2){std::stof(cmd[0].c_str()), std::stof(cmd[1].c_str())};
        for (std::size_t i = 3; i < cmd.size(); i++) {
            int playerID = std::atoi(cmd[i].c_str());
            _player.enableIncantationMode(playerID, pos);
        }
        _cmd.eraseFirstCmdInMap(PIC_CMD);
    }
}

void UseRecivedCmd::getPie(void)
{
    while (!_cmd.getCommandAt(PIE_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PIE_CMD, 0);
        Vector2 pos = (Vector2){std::stof(cmd[0].c_str()), std::stof(cmd[1].c_str())};
        _player.disableIncantationMode(pos);
        _cmd.eraseFirstCmdInMap(PIE_CMD);
    }
}

void UseRecivedCmd::getPdr(void)
{
    if (!_cmd.getCommandAt(PDR_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PDR_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int itemType = std::atoi(cmd[1].c_str());
        _player.removeItem(playerID, itemType);
        _cmd.eraseFirstCmdInMap(PDR_CMD);
    }
}

void UseRecivedCmd::getPgt(void)
{
    if (!_cmd.getCommandAt(PGT_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PGT_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int itemType = std::atoi(cmd[1].c_str());
        _player.addItem(playerID, itemType);
        _cmd.eraseFirstCmdInMap(PGT_CMD);
    }
}

void UseRecivedCmd::getPdi(void)
{
    while (!_cmd.getCommandAt(PDI_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PDI_CMD, 0);
        if (_player.removePlayerFromIsland(std::atoi(cmd.front().c_str()))) {
            _cmd.eraseFirstCmdInMap(PDI_CMD);
        } else {
            break;
        }
    }
}

void UseRecivedCmd::getEnw(void)
{
    while (!_cmd.getCommandAt(ENW_CMD, 0).empty()) {
        std::vector<std::string> tmpCmd = _cmd.getCommandAt(ENW_CMD, 0);
        _egg.addEggToIsland((Vector3){std::stof(tmpCmd[2].c_str()), 1.0,
            std::stof(tmpCmd[3].c_str())}, std::stoi(tmpCmd[0]));
        _cmd.eraseFirstCmdInMap(ENW_CMD);
    }
}

void UseRecivedCmd::getEbo(void)
{
    while (!_cmd.getCommandAt(EBO_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(EBO_CMD, 0);
        _egg.removeEggFromIsland(std::stoi(cmd[0]));
        _cmd.eraseFirstCmdInMap(EBO_CMD);
    }
}

void UseRecivedCmd::getSmg(void)
{
    while (!_cmd.getCommandAt(SMG_CMD, 0).empty()) {
        std::vector<std::string> tmpCmd = _cmd.getCommandAt(SMG_CMD, 0);
        _egg.addEggToIsland((Vector3){std::stof(tmpCmd[2].c_str()), 1.0,
            std::stof(tmpCmd[3].c_str())}, std::stoi(tmpCmd[1]));
        _cmd.eraseFirstCmdInMap(SMG_CMD);
    }
}

void UseRecivedCmd::getEdi(void)
{
    while (!_cmd.getCommandAt(EDI_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(EDI_CMD, 0);
        _egg.removeEggFromIsland(std::stoi(cmd[0]));
        _cmd.eraseFirstCmdInMap(EDI_CMD);
    }
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

bool UseRecivedCmd::getGameStatus()
{
    return _isFinished;
}

void UseRecivedCmd::getSeg(void)
{
    if (!_cmd.getCommandAt(SEG_CMD, 0).empty()) {
        _isFinished = true;
    }
}

int UseRecivedCmd::getNbrItemTypeOnIsland(Vector3 pos, int type)
{
    int nbr = 0;
    for (auto &i: _allItem) {
        if (Utils::Vec3Comp(i._realPos, pos) && i._itemType == type)
            nbr++;
    }
    return nbr;
}

void UseRecivedCmd::removeItemFromIsland(Vector3 position, int type)
{
    for (std::size_t i = 0; i < _allItem.size(); i++) {
        if (Utils::Vec3Comp(_allItem[i]._realPos, position) && _allItem[i]._itemType == type) {
            _allItem.erase(_allItem.begin() + i);
            break;
        }
    }
}

void UseRecivedCmd::addItemToIsland(Vector3 position, int type)
{
    _allItem.push_back(_allItemModel[type]);
    _allItem.back()._itemPosition = (Vector3){(position.x + 1) * spaceBetwenIsland, 1.8, position.z * spaceBetwenIsland};
    _allItem.back()._itemPosition.x += -3 + (rand() % 6);
    _allItem.back()._itemPosition.z += -3 + (rand() % 6);
    _allItem.back()._realPos = position;
    _allItem.back()._itemType = type;
}
