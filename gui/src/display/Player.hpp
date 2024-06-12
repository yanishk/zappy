/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <string>
    #include <vector>
    #include <iostream>
    #include <iomanip>
    #include <map>
    #include "Utils.hpp"

    #define MAX_RGB 255
    #define PLAYER_INFO_NBR_LINE 5
    #define TEXT_SIZE 20
    #define TEXT_LINE_SPACING_RATIO 1.30
    #define NBR_ITEM 7

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
        void addItem(int itemType);
        void removeItem(int itemType);
        void resetInventory(void);
        std::vector<int> getInventory(void);
        void setInventory(std::vector<int> newInv);

        Model _playerModel;
        ModelAnimation *_playerAnimation;
        int _playerID;
        int _animsCount;
        int _animFrameCounter;
        int _level;
        std::string getTeam(void);
        Vector3 _realPos;
        float _rotationAngle;
        bool isAlive = true;
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
        std::vector<int> _inventory;
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
        void drawPlayer(Vector3 cameraPosition, bool isAnimated);
        Vector3 getPlayerRealPos(int playerID);
        Vector3 getSize(void);
        void setPlayerLevel(int playerID, int level);
        int getPlayerLevel(int playerID);
        bool isPlayerAlive(int playerID);
        void displayMorePlayerInfo(int playerID, int screenWidth);
        void addItem(int playerID, int itemType);
        void removeItem(int playerID, int itemType);
        void resetInventory(int playerID);
        std::vector<int> getInventory(int playerID);
        void setInventory(int playerID, std::vector<int> newInv);
    private:
        Model _model;
        Vector3 _size;
        ModelAnimation *_anim;
        int _animsCount;
        std::vector<std::vector<int>> _bct;
};

#endif /* !PLAYER_HPP_ */
