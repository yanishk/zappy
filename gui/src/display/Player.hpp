/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "raylib.h"
    #include "raymath.h"
    #include "rlgl.h"
    #include "string"
    #include <vector>
    #include "Utils.hpp"
    #include <iostream>
    #include <iomanip>
    #include <map>

class Player {
    public:
        Player(Vector3 position);
        Vector3 getPosition();
        void moovePlayerToIsland(Vector3 position);
        void displayPlayerInfo(Vector3 camPosition);
        void setTeam(std::string team);
        bool isPlayerSelected(BoundingBox playerBox, Ray ray);
        void displayInfo2D(int x, int y);
        void setPlayerColor(void);

        Model _playerModel;
        ModelAnimation *_playerAnimation;
        int _playerID;
        int _animsCount;
        int _animFrameCounter;
        int _level;
        std::string getTeam(void);
        Vector3 _realPos;
        float _rotationAngle;
    private:
        Color _playerColor = WHITE;
        bool _isMooving;
        Vector3 _playerPosition;
        Vector3 _destPosition;
        float _distanceBetweenPos;
        float _playerHight;
        std::string _team;
        void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, Color tint);
        void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float scale, Color tint);
        BoundingBox UpdateBoundingBox(BoundingBox box, Vector3 position);
        Vector3 RotatePointAroundY(Vector3 point);
};

class AllPlayers {
    public:
        std::vector<Player> _allPlayer;

        void loadModelAndAnim(std::pair<Model, float>, std::string path);
        void addPlayerToIsland(Vector3 position, int playerID);
        void moovePlayerToIsland(Vector3 position, int playerID);
        void changePlayerOrientation(float direction, int playerID);
        void removePlayerFromIsland(int playerID);
        void setPlayerTeam(std::string playerTeam, int playerID);
        void drawPlayer(Vector3 cameraPosition);
        Vector3 getPlayerRealPos(int playerID);
        Vector3 getSize(void);
    private:
        Model _model;
        Vector3 _size;
        ModelAnimation *_anim;
        int _animsCount;
        std::vector<std::vector<int>> _bct;
};

#endif /* !PLAYER_HPP_ */
