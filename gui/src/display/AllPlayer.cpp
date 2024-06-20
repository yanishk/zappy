/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AllPlayers
*/

#include "Player.hpp"

void AllPlayers::loadModelAndAnim(std::pair<Model, float> modelPair, std::string path)
{
    _model = modelPair.first;
    float size = modelPair.second;
    _size = (Vector3){size, size, size};
    _anim = LoadModelAnimations(path.c_str(), &_animsCount);
    _incantationModel = LoadModel(INCANTATION_PATH);
    _expulsionModel = LoadModel(EXPULSION_PATH);
    _animsCount = 0;
}

void AllPlayers::moovePlayerToIsland(Vector3 position, int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.moovePlayerToIsland(position);
            break;
        }
    }
}

void AllPlayers::changePlayerOrientation(float direction, int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i._playerModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 0, DEG2RAD * (-direction * 90), DEG2RAD * 0});
            i._rotationAngle = direction * 90;
            i._playerOrientation = direction;
            break;
        }
    }
}

void AllPlayers::setPlayerTeam(std::string playerTeam, int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.setTeam(playerTeam);
            i.setPlayerColor(setPlayerColor(playerTeam));
            break;
        }
    }
}

void AllPlayers::addPlayerToIsland(Vector3 position, int playerID)
{
    Player tmpPlayer(position);

    tmpPlayer._playerModel = _model;
    tmpPlayer._playerAnimation = _anim;
    tmpPlayer._level = 1;
    tmpPlayer._playerID = playerID;
    tmpPlayer._animsCount = 0;
    tmpPlayer._animFrameCounter = 0;
    tmpPlayer._incantationModel = _incantationModel;
    tmpPlayer._expulsionModel = _expulsionModel;
    _allPlayer.push_back(tmpPlayer);
}

bool AllPlayers::removePlayerFromIsland(int playerID)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer[i]._playerID == playerID) {
            _allPlayer[i].isAlive = false;
            _allPlayer.erase(_allPlayer.begin() + i);
            return true;
        }
    }
    return false;
}

Vector3 AllPlayers::getPlayerRealPos(int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            return i._realPos;
        }
    }
    return {};
}

Vector3 AllPlayers::getSize(void)
{
    return _size;
}

void AllPlayers::drawPlayer(bool isAnimated)
{
    for (auto &i: _allPlayer) {
        if (!isAnimated) {
            DrawModel(i._playerModel , i.getPosition(), 1, WHITE);
            continue;
        }
        i._animFrameCounter++;
        if (i._animFrameCounter >= i._playerAnimation[0].frameCount)
            i._animFrameCounter = 0;
        UpdateModelAnimation(i._playerModel, i._playerAnimation[0], i._animFrameCounter);
        DrawModelEx(i._playerModel , i.getPosition(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, getSize(), WHITE);
    }
}

void AllPlayers::setPlayerLevel(int playerID, int level)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i._level = level;
        }
    }
}

int AllPlayers::getPlayerLevel(int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            return i._level;
        }
    }
    return -1;
}

bool AllPlayers::isPlayerAlive(int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            return i.isAlive;
        }
    }
    return false;
}

void AllPlayers::displayMorePlayerInfo(int playerID, int screenWidth, std::vector<Item> &_allItem)
{
    int playerInfoBoxWidth = 400;
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            DrawRectangle(screenWidth - playerInfoBoxWidth - 5, 5, playerInfoBoxWidth,
                (TEXT_SIZE * TEXT_LINE_SPACING_RATIO) * PLAYER_INFO_NBR_LINE, Fade(GRAY, 0.5f));
            i.displayInfo2D(screenWidth - playerInfoBoxWidth - 5, 5, _allItem);
        }
    }
}

void AllPlayers::addItem(int playerID, int itemType)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.addItem(itemType);
        }
    }
}

void AllPlayers::removeItem(int playerID, int itemType)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.removeItem(itemType);
        }
    }
}

void AllPlayers::resetInventory(int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.resetInventory();
        }
    }
}

std::vector<int> AllPlayers::getInventory(int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            return i.getInventory();
        }
    }
    return {};
}

void AllPlayers::setInventory(int playerID, std::vector<int> newInv)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.setInventory(newInv);
        }
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

void AllPlayers::drawMessage(int playerID, std::string msg, Vector3 camPosition)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.drawMessage(msg, camPosition);
        }
    }
}

void AllPlayers::enableIncantationMode(int playerID, Vector2 pos)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.enableIncantationMode(pos);
        }
    }
}

void AllPlayers::disableIncantationMode(Vector2 pos)
{
    for (auto &i: _allPlayer) {
        Vector2 incantPos = i.getIncantationPos();
        if (incantPos.x == pos.x && incantPos.y == pos.y) {
            i.disableIncantationMode();
        }
    }
}

void AllPlayers::playerExpulsion(int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.playerExpulsion();
        }
    }
}
