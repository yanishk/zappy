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
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer.at(i)._playerID == playerID) {
            _allPlayer.at(i).moovePlayerToIsland(position);
            break;
        }
    }
}

void AllPlayers::changePlayerOrientation(float direction, int playerID)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer.at(i)._playerID == playerID) {
            _allPlayer.at(i)._playerModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0, DEG2RAD*direction, DEG2RAD*0});
            _allPlayer.at(i)._rotationAngle = direction;
            break;
        }
    }
}

void AllPlayers::setPlayerTeam(std::string playerTeam, int playerID)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer.at(i)._playerID == playerID) {
            _allPlayer.at(i).setTeam(playerTeam);
            _allPlayer.at(i).setPlayerColor();
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
            _allPlayer.erase(_allPlayer.begin() + i);
            break;
        }
    }
}

Vector3 AllPlayers::getPlayerRealPos(int playerID)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        if (_allPlayer.at(i)._playerID == playerID) {
            return _allPlayer.at(i)._realPos;
        }
    }
    return {};
}

Vector3 AllPlayers::getSize(void)
{
    return _size;
}

void AllPlayers::drawPlayer(Vector3 cameraPosition)
{
    for (std::size_t i = 0; i < _allPlayer.size(); i++) {
        _allPlayer.at(i)._animFrameCounter++;
        if (_allPlayer.at(i)._animFrameCounter >= _allPlayer.at(i)._playerAnimation[0].frameCount)
            _allPlayer.at(i)._animFrameCounter = 0;
        UpdateModelAnimation(_allPlayer.at(i)._playerModel, _allPlayer.at(i)._playerAnimation[0], _allPlayer.at(i)._animFrameCounter);
        DrawModelEx(_allPlayer.at(i)._playerModel , _allPlayer.at(i).getPosition(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, getSize(), WHITE);
        _allPlayer.at(i).displayPlayerInfo(cameraPosition);
    }
}
