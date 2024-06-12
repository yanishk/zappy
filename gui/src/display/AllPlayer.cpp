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
            i._playerModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 0, DEG2RAD * direction, DEG2RAD * 0});
            i._rotationAngle = direction;
            break;
        }
    }
}

void AllPlayers::setPlayerTeam(std::string playerTeam, int playerID)
{
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            i.setTeam(playerTeam);
            i.setPlayerColor();
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
    _allPlayer.push_back(tmpPlayer);
}

void AllPlayers::removePlayerFromIsland(int playerID)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer.at(i)._playerID == playerID) {
            _allPlayer.at(i).isAlive = false;
            _allPlayer.erase(_allPlayer.begin() + i);
            break;
        }
    }
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

void AllPlayers::drawPlayer(Vector3 cameraPosition, bool isAnimated)
{
    for (auto &i: _allPlayer) {
        if (!isAnimated) {
            DrawModel(i._playerModel , i.getPosition(), 1, WHITE);
            i.displayPlayerInfo(cameraPosition);
            continue;
        }
        i._animFrameCounter++;
        if (i._animFrameCounter >= i._playerAnimation[0].frameCount)
            i._animFrameCounter = 0;
        UpdateModelAnimation(i._playerModel, i._playerAnimation[0], i._animFrameCounter);
        DrawModelEx(i._playerModel , i.getPosition(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, getSize(), WHITE);
        i.displayPlayerInfo(cameraPosition);
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

void AllPlayers::displayMorePlayerInfo(int playerID, int screenWidth)
{
    int playerInfoBoxWidth = 400;
    int playerInfoBoxHeight = 110;
    for (auto &i: _allPlayer) {
        if (i._playerID == playerID) {
            DrawRectangle(screenWidth - playerInfoBoxWidth - 5, 5, playerInfoBoxWidth, playerInfoBoxHeight, Fade(GRAY, 0.5f));
            i.displayInfo2D(screenWidth - playerInfoBoxWidth - 5, 5);
        }
    }
}
