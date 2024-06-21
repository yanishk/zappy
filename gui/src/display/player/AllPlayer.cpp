/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AllPlayers
*/

#include "Player.hpp"

AllPlayers::AllPlayers(CommandManager &cmd, bool isAnimated) : _cmd(cmd)
{
    _isAnimated = isAnimated;
    _anim = LoadModelAnimations(PLAYER_ANIM, &_animsCount);
    _incantationModel = LoadModel(INCANTATION_PATH);
    _expulsionModel = LoadModel(EXPULSION_PATH);
    _animsCount = 0;
}

void AllPlayers::renderAll(Vector3 camPosition)
{
    for (auto &player : _allPlayer) {
        player.render();
        player.displayPlayerInfo(camPosition);
        player.drawMessage(player.getMessage(), camPosition);
    }
}

void AllPlayers::renderAll2D(std::pair<bool, std::size_t> moreInfo, std::unique_ptr<AllItem> &_allItem)
{
    int playerInfoBoxWidth = 400;
    if (moreInfo.first) {
        DrawRectangle(SCREEN_WIDTH - playerInfoBoxWidth - 5, 5, playerInfoBoxWidth, (TEXT_SIZE * TEXT_LINE_SPACING_RATIO) * PLAYER_INFO_NBR_LINE, Fade(GRAY, 0.5f));
        getPlayerByID(moreInfo.second).displayInfo2D(SCREEN_WIDTH - playerInfoBoxWidth - 5, 5, _allItem);
    }
}

void AllPlayers::setAllPlayer(std::vector<std::pair<Model, float>> model)
{
    getAllTeam();
    addPlayer(model);
    moovePlayer();
    setPlayerLevel();
    setInventory();
    collectOrDropItem();
    incantation();
    ejection();
    broadcast();
    playerDied();
}

std::pair<bool, std::size_t> AllPlayers::isPlayerSelected(Vector3 target, Vector3 position)
{
    std::pair<bool, std::size_t> selectedPlayer;
    for (auto &player: _allPlayer) {
        Vector3 direction = Vector3Subtract(target, position);
        direction = Vector3Normalize(direction);
        Ray ray = {position, direction};

        BoundingBox playerBox = GetMeshBoundingBox(player.getPlayerModel().meshes[0]);
        if (player.isPlayerSelected(playerBox, ray)) {
            selectedPlayer.first = true;
            selectedPlayer.second = player.getPlayerID();
        }
    }
    return selectedPlayer;
}

// Private Function

Player &AllPlayers::getPlayerByID(int PlayerID)
{
    for (auto &player : _allPlayer) {
        if (player.getPlayerID() == PlayerID) {
            return player;
        }
    }
    return _allPlayer[0];
}

void AllPlayers::addPlayer(std::vector<std::pair<Model, float>> model)
{
    if (!_cmd.getCommandAt(PNW_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PNW_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        Vector2 pos = {std::stof(cmd[1].c_str()), std::stof(cmd[2].c_str())};
        int orientation = std::atoi(cmd[3].c_str());
        std::string team = cmd[5];
        int level = std::atoi(cmd[4].c_str());
        Player player(pos, _isAnimated);
        player.setPlayerID(playerID);
        player.setPlayerDirection(orientation);
        player.setLevel(level);
        player.setTeam(team);
        player.fillModel(model.front());
        player.setEjectModel(_expulsionModel);
        player.setIncantModel(_incantationModel);
        player.setPlayerAnimation(_anim);
        player.setPlayerColor(setPlayerColor(team));
        _allPlayer.push_back(player);
        _cmd.eraseFirstCmdInMap(PNW_CMD);
    }
}

Color AllPlayers::setPlayerColor(std::string teamName)
{
    float teamIndex = 0;
    while (teamName != _allTeamName[teamIndex] && (std::size_t)teamIndex < _allTeamName.size()) {
        teamIndex++;
    }
    Color color;
    color.r = (3 / teamIndex) * 255;
    color.g = (2 / teamIndex) * 255;
    color.b = (1 / teamIndex) * 255;
    color.a = 255;
    return color;
}

void AllPlayers::moovePlayer(void)
{
    if (!_cmd.getCommandAt(PPO_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PPO_CMD, 0);
        Vector2 newPos = (Vector2){std::stof(cmd[1].c_str()), std::stof(cmd[2].c_str())};
        int playerID = std::atoi(cmd.front().c_str());
        int direction = std::atoi(cmd[3].c_str()) - 1;
        getPlayerByID(playerID).setPlayerPos(newPos);
        getPlayerByID(playerID).setPlayerDirection(direction);
        _cmd.eraseFirstCmdInMap(PPO_CMD);
    }
}

void AllPlayers::setPlayerLevel(void)
{
    if (!_cmd.getCommandAt(PLV_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PLV_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        int playerLevel = std::atoi(cmd[1].c_str());
        getPlayerByID(playerID).setLevel(playerLevel);
        _cmd.eraseFirstCmdInMap(PLV_CMD);
    }
}

void AllPlayers::collectOrDropItem(void)
{
    std::string command = PDR_CMD;
    bool addOrRemoveItem = REMOVE_ITEM;
    for (int i = 0; i < 2; i++) {
        if (!_cmd.getCommandAt(command, 0).empty()) {
            std::vector<std::string> cmd = _cmd.getCommandAt(command, 0);
            int playerID = std::atoi(cmd.front().c_str());
            int itemType = std::atoi(cmd[1].c_str());
            getPlayerByID(playerID).addOrRemoveItem(itemType, addOrRemoveItem);
            _cmd.eraseFirstCmdInMap(command);
        }
        command = PGT_CMD;
        addOrRemoveItem = ADD_ITEM;
    }
}

void AllPlayers::setInventory(void)
{
    while (!_cmd.getCommandAt(PIN_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PIN_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        std::vector<int> newInv;
        for (std::size_t i = 0; i < NBR_ITEM; i++) {
            newInv.push_back(std::atoi(cmd[i + 3].c_str()));
        }
        getPlayerByID(playerID).setInventory(newInv);
        _cmd.eraseFirstCmdInMap(PIN_CMD);
    }
}

void AllPlayers::incantation(void)
{
    while (!_cmd.getCommandAt(PIC_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PIC_CMD, 0);
        Vector2 pos = (Vector2){std::stof(cmd[0].c_str()), std::stof(cmd[1].c_str())};
        for (std::size_t i = 3; i < cmd.size(); i++) {
            startIncantation(std::atoi(cmd[i].c_str()), pos);
        }
        _cmd.eraseFirstCmdInMap(PIC_CMD);
    }

    while (!_cmd.getCommandAt(PIE_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PIE_CMD, 0);
        Vector2 pos = (Vector2){std::stof(cmd[0].c_str()), std::stof(cmd[1].c_str())};
        endOfIncantation(pos);
        _cmd.eraseFirstCmdInMap(PIE_CMD);
    }
}

void AllPlayers::startIncantation(int playerID, Vector2 pos)
{
    for (auto &player : _allPlayer) {
        if (player.getPlayerID() == playerID) {
            player.enableIncantationMode(pos);
        }
    }
}

void AllPlayers::endOfIncantation(Vector2 pos)
{
    for (auto &player : _allPlayer) {
        if (Utils::Vec2Comp(player.getRealPos(), pos)) {
            player.disableIncantationMode();
        }
    }
}

void AllPlayers::ejection(void)
{
    while (!_cmd.getCommandAt(PEX_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PEX_CMD, 0);
        int playerID = std::atoi(cmd[0].c_str());
        getPlayerByID(playerID).playerExpulsion();
        _cmd.eraseFirstCmdInMap(PEX_CMD);
    }
}

void AllPlayers::playerDied(void)
{
    while (!_cmd.getCommandAt(PDI_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PDI_CMD, 0);
        if (removePlayerFromIsland(std::atoi(cmd.front().c_str()))) {
            _cmd.eraseFirstCmdInMap(PDI_CMD);
        } else {
            break;
        }
    }
}

bool AllPlayers::removePlayerFromIsland(int playerID)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer[i].getPlayerID() == playerID) {
            _allPlayer.erase(_allPlayer.begin() + i);
            return true;
        }
    }
    return false;
}

void AllPlayers::getAllTeam(void)
{
    while (_cmd.getCommandAt(TNA_CMD, 0).size() == 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(TNA_CMD, 0);
        if (_allTeamName.size() == 0) {
            _allTeamName.push_back(cmd.front());
            continue;
        }
        bool isUnique = true;
        for (auto &i: _allTeamName) {
            if (i == cmd.front())
                isUnique = false;
        }
        if (isUnique) {
            _allTeamName.push_back(cmd.front());
        }
        _cmd.eraseFirstCmdInMap(TNA_CMD);
    }
}

void AllPlayers::broadcast(void)
{
    if (!_cmd.getCommandAt(PBC_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(PBC_CMD, 0);
        int playerID = std::atoi(cmd.front().c_str());
        getPlayerByID(playerID).setMessage(cmd[1]);
        _cmd.eraseFirstCmdInMap(PBC_CMD);
    }
}
