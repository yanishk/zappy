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
    #include <chrono>
    #include "Utils.hpp"
    #include "Item.hpp"

    #define MAX_RGB 255
    #define PLAYER_INFO_NBR_LINE 11
    #define TEXT_SIZE 20
    #define TEXT_LINE_SPACING_RATIO 1.30
    #define NBR_ITEM 7
    #define TEXT_TEAM "\nTeam : "
    #define TEXT_LEVEL "Level : "
    #define INCANTATION_PATH "./gui/assets/models/subatomic_particle_fx.glb"
    #define EXPULSION_PATH "./gui/assets/models/sun.glb"

    static const std::map<int, std::string> PLAYER_ORIENTATION {
        {0, "North"},
        {1, "East"},
        {2, "South"},
        {3, "West"}
    };

class Player {
    public:
        Player(Vector3 position);
        void moovePlayerToIsland(Vector3 position);
        void displayPlayerInfo(Vector3 camPosition);
        void setTeam(std::string team);
        bool isPlayerSelected(BoundingBox playerBox, Ray ray);
        void displayInfo2D(int x, int y, std::vector<Item> &_allItem);
        void setPlayerColor(Color color);
        void addItem(int itemType);
        void removeItem(int itemType);
        void resetInventory(void);
        void setInventory(std::vector<int> newInv);
        void drawMessage(std::string msg, Vector3 camPosition);
        void enableIncantationMode(Vector2 pos);
        void drawIncantation(void);
        void disableIncantationMode(void);
        Vector2 getIncantationPos(void);
        Vector3 getPosition();
        std::vector<int> getInventory(void);
        void playerExpulsion(void);
        void drawExpulsion(void);

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
        Model _incantationModel;
        Model _expulsionModel;
        std::string _team;
        int _playerOrientation;
    private:
        void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, Color tint);
        void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float scale, Color tint);
        BoundingBox UpdateBoundingBox(BoundingBox box, Vector3 position);
        Vector3 RotatePointAroundY(Vector3 point);
        Color getNegativeColor(Color color);

        Color _playerColor = WHITE;
        Model _infoBackground;
        Model _broadcastBackground;
        Vector3 _incantAngle;
        Vector3 _playerPosition;
        Vector3 _destPosition;
        Vector2 _incantPos;
        float _distanceBetweenPos;
        float _playerHight;
        float _speedX;
        float _speedY;
        float _speedZ;
        std::string _broadcastMsg;
        std::vector<int> _inventory;
        std::chrono::time_point<std::chrono::system_clock> _startTime;
        bool _isMooving;
        bool _isIncantation;
        bool _isTimerStart;
        float _incantationSize = 0.1;
        float _incantationOpacity = 0.5;
        bool _isIncantationExpload = false;

        float _expulsionSize = 0.1;
        float _expulsionOrientation = 0;
        bool _isExpulsion = false;
};

class AllPlayers {

    public:

        std::vector<Player> _allPlayer;
        std::vector<std::string> _allTeamName;

        void loadModelAndAnim(std::pair<Model, float>, std::string path);
        void addPlayerToIsland(Vector3 position, int playerID);
        void moovePlayerToIsland(Vector3 position, int playerID);
        void changePlayerOrientation(float direction, int playerID);
        bool removePlayerFromIsland(int playerID);
        void setPlayerTeam(std::string playerTeam, int playerID);
        void drawPlayer(bool isAnimated);
        Vector3 getPlayerRealPos(int playerID);
        Vector3 getSize(void);
        void setPlayerLevel(int playerID, int level);
        int getPlayerLevel(int playerID);
        bool isPlayerAlive(int playerID);
        void displayMorePlayerInfo(int playerID, int screenWidth, std::vector<Item> &_allItem);
        void addItem(int playerID, int itemType);
        void removeItem(int playerID, int itemType);
        void resetInventory(int playerID);
        std::vector<int> getInventory(int playerID);
        void setInventory(int playerID, std::vector<int> newInv);
        void drawMessage(int playerID, std::string msg, Vector3 camPosition);
        void disableIncantationMode(Vector2 pos);
        void enableIncantationMode(int playerID, Vector2 pos);
        void playerExpulsion(int playerID);
    private:
        Model _model;
        Model _incantationModel;
        Model _expulsionModel;
        Vector3 _size;
        ModelAnimation *_anim;
        int _animsCount;
        std::vector<std::vector<int>> _bct;
        Color setPlayerColor(std::string teamName);
};

#endif /* !PLAYER_HPP_ */
