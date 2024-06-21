/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** Game
*/

#ifndef Game_HPP_
    #define Game_HPP_

    #include <string>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include <stdlib.h>
    #include <ctime>
    #include "Commands.hpp"
    #include "Client.hpp"
    #include "AllPlayer.hpp"
    #include "AllItem.hpp"
    #include "AllEggs.hpp"
    #include "AllIsland.hpp"

    #define WINDOW_NAME "Zappy_gui"
    #define ERROR_NO_MODEL "No or bad path to model"
    #define ERROR_NO_PLAYER_MODEL "No player model"
    #define ERROR_NOT_ENOUTH_ITEM_MODEL "Not enough item model"

    #define SKY_MODEL_PATH "./gui/assets/models/unreal-engine-4-sky/source/ue4sky.obj"
    #define SKY_TEXTURE_PATH "./gui/assets/models/unreal-engine-4-sky/textures/T_Sky_Blue.png"
    #define WATER_SHADER "./gui/assets/shaders/water.fs"
    #define WATER_TEXTURE "./gui/assets/image/water_texture.png"

    #define FOV 60
    #define FPS 60

    #define SKY_SIZE 10
    #define CROSSBAR_SIZE 8

    #define CAMERA_MOVEMENT_SPEED 0.4
    #define EGG_MODEL_SIZE 0.3
    #define WATER_SIZE 1000
    #define WATER_RESXZ 2

    #define START_POS_COEF_Y 7
    #define START_POS_COEF_Z 5

    #define WATER_ALTITUDE -2
    #define SUB_WATER_ALTITUDE -2.3

    #define SHADER_FORMAT 330
    #define SHADER_SECONDS "seconds"
    #define SHADER_FREQX "freqX"
    #define SHADER_FREQY "freqY"
    #define SHADER_AMPX "ampX"
    #define SHADER_AMPY "ampY"
    #define SHADER_SPEEDX "speedX"
    #define SHADER_SPEEDY "speedY"
    #define SHADER_SIZE "size"

    #define VALUE_SHADER_FREQX 25.0
    #define VALUE_SHADER_FREQY 25.0
    #define VALUE_SHADER_AMPX 5.0
    #define VALUE_SHADER_AMPY 5.0
    #define VALUE_SHADER_SPEEDX 8.0
    #define VALUE_SHADER_SPEEDY 8.0

using ZappyModel = std::vector<std::pair<std::pair<std::string, float>, int>>;

class Game {
    public:
        Game(int screenWidth, int screenHeight, CommandManager &cmd, asio::ip::tcp::socket &socket, bool animation);
        ~Game();
        void updateCamera(void);
        Vector3 setVector3(float x, float y, float z);
        int getSgt(void);

        void launchGame(void);
        void fillAllModel(ZappyModel);
        void getSgtCmd(void);
        void requestChangingTimeUnit(void);

    private:
        enum ModelType
        {
            ErrorType = 0,
            ItemType = 1,
            IslandType = 2,
            PlayerType = 3
        };

        CommandManager &_cmd;
        Camera _camera;
        Shader _waterShader;
        Model _WaterModel;
        Model _sky;
        asio::ip::tcp::socket &_socket;

        int _screenWidth;
        int _screenHeight;
        int _cameraMode;
        int _secondLoc;
        int _sgtValue;

        std::pair<int, int> _mapSize;
        std::pair<bool, std::size_t> _selectedPlayer;

        std::vector<std::pair<Model, float>> _allItemModel;
        std::vector<std::pair<Model, float>> _islandModel;
        std::vector<std::pair<Model, float>> _playerModel;
        std::pair<Model, float> _eggModel;

        std::unique_ptr<AllIsland> _allIsland;
        std::unique_ptr<AllItem> _allItem;
        std::unique_ptr<AllEggs> _allEggs;
        std::unique_ptr<AllPlayers> _allPlayer;

        void initWaterShader(void);
        void display3D(void);
        void display2D(void);
        void setCameraToCoord(Vector3 position, Vector3 target);
        void cameraPositionStart(void);
};

#endif /* !Game_HPP_ */
