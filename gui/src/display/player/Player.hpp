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
    #define PLAYER_ANIM "./gui/assets/models/dilophosaurus-cross-x-men/source/dilophosaurus_sf_bone.glb"
    #define PLAYER_HIGHT 1.1
    #define ADD_ITEM true
    #define REMOVE_ITEM false
    #define SCREEN_WIDTH 1920

    static const std::map<int, std::string> PLAYER_ORIENTATION {
        {0, "North"},
        {1, "East"},
        {2, "South"},
        {3, "West"}
    };

class Player : public LoadAndRender {
    public:
        Player(Vector2 position, bool isAnimated);

        void render() override;
        void fillModel(std::pair<Model, float> model) override;
        void setPlayerAnimation(ModelAnimation *_playerAnimation);
        void setIncantModel(Model incantModel);
        void setEjectModel(Model ejectModel);
        void setPlayerID(int ID);
        int getPlayerID(void);
        void setPlayerPos(Vector2 pos);
        void setPlayerDirection(int direction);
        Vector3 getPosition(void);
        Vector2 getRealPos(void);
        void setLevel(int level);
        int getLevel(void);
        void setTeam(std::string team);
        std::string getTeam(void);
        void setPlayerColor(Color color);
        void drawMessage(std::string msg, Vector3 camPosition);
        void displayInfo2D(int x, int y, std::unique_ptr<AllItem> &_allItem);
        void displayPlayerInfo(Vector3 camPosition);
        bool isPlayerSelected(BoundingBox playerBox, Ray ray);
        void addOrRemoveItem(int itemType, bool addOrRemove);
        void setInventory(std::vector<int> newInv);
        std::vector<int> getInventory(void);
        void enableIncantationMode(Vector2 pos);
        void disableIncantationMode(void);
        Vector2 getIncantationPos(void);
        void drawIncantation(void);
        void playerExpulsion(void);
        void drawExpulsion(void);
        void setMessage(std::string msg);
        std::string getMessage(void);
        Model getPlayerModel(void);

    private:
        void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, Color tint);
        void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float scale, Color tint);
        BoundingBox UpdateBoundingBox(BoundingBox box, Vector3 position);
        Vector3 RotatePointAroundY(Vector3 point);
        Color getNegativeColor(Color color);

        Model _playerModel;
        ModelAnimation *_playerAnimation;
        int _playerID;
        int _animFrameCounter;
        int _level;
        Vector2 _realPos;
        float _rotationAngle;
        Model _incantationModel;
        Model _expulsionModel;
        std::string _team;
        int _playerOrientation;
        Color _playerColor = WHITE;
        Model _infoBackground;
        Model _broadcastBackground;
        Vector3 _incantAngle;
        Vector3 _playerPosition;
        Vector3 _destPosition;
        Vector2 _incantPos;
        float _distanceBetweenPos;
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
        float _playerSize;
        bool _isAnimated = false;
        std::string _msg;
};

class AllPlayers {

    public:
        AllPlayers(CommandManager &cmd, bool isAnimated);
        void renderAll(Vector3 camPosition);
        void renderAll2D(std::pair<bool, std::size_t> moreInfo, std::unique_ptr<AllItem> &_allItem);
        void setAllPlayer(std::vector<std::pair<Model, float>> model);
        std::pair<bool, std::size_t> isPlayerSelected(Vector3 target, Vector3 position);

    private:
        CommandManager &_cmd;
        std::vector<Player> _allPlayer;
        bool _isAnimated = false;

        Player &getPlayerByID(int PlayerID);
        void addPlayer(std::vector<std::pair<Model, float>> model);
        void moovePlayer(void);
        void setPlayerLevel(void);
        void collectOrDropItem(void);
        void setInventory(void);
        void incantation(void);
        void startIncantation(int playerID, Vector2 pos);
        void endOfIncantation(Vector2 pos);
        void ejection(void);
        void playerDied(void);
        bool removePlayerFromIsland(int playerID);
        void getAllTeam(void);
        void broadcast(void);


        Model _model;
        Model _incantationModel;
        Model _expulsionModel;
        Vector3 _size;
        ModelAnimation *_anim;
        int _animsCount;
        std::vector<std::vector<int>> _bct;
        std::vector<std::string> _allTeamName;
        Color setPlayerColor(std::string teamName);
};

#endif /* !PLAYER_HPP_ */
