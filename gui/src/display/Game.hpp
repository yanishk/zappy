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
    #include "Sky.hpp"
    #include "Sea.hpp"

    #define WINDOW_NAME "Zappy_gui"
    #define ERROR_NO_MODEL "No or bad path to model"
    #define ERROR_NO_PLAYER_MODEL "No player model"
    #define ERROR_NOT_ENOUTH_ITEM_MODEL "Not enough item model"

    #define SKY_MODEL_PATH "./gui/assets/models/unreal-engine-4-sky/source/ue4sky.obj"
    #define SKY_TEXTURE_PATH "./gui/assets/models/unreal-engine-4-sky/textures/T_Sky_Blue.png"
    #define WATER_SHADER "./gui/assets/shaders/water.fs"
    #define WATER_TEXTURE "./gui/assets/image/water_texture.png"

    #define FOV 70
    #define FPS 60
    #define SST_CHANGE 25

    #define CROSSBAR_SIZE 8

    #define SKY_SIZE 10
    #define EGG_MODEL_SIZE 0.3

    #define START_POS_COEF_Y 7
    #define START_POS_COEF_Z 5

    #define MARGIN_LEFT 10
    #define MARGIN_TOP 10
    #define WIGHT 370
    #define HIGHT 180
    #define FONT_SIZE 20
    #define BACKSLASH_N 25
    #define START_POS 15
    #define FPS_MARGIN 80

    #define CAMERA_MOVEMENT_SPEED 0.4
    #define CAM_POS "- Position: (%06.3f, %06.3f, %06.3f)"
    #define CAM_TARGET "- Target: (%06.3f, %06.3f, %06.3f)"
    #define TIME_UNIT "- Time unit: %d"
    #define NBR_ITEM_MAP "- Nbr item on the map: %d"
    #define NBR_PLAYER_MAP "- Nbr player on the map: %d"
    #define NBR_ISLAND_MAP "- Nbr island on the map: %d"
    #define NBR_EGGS_MAP "- Nbr egg on the map: %d"

using ZappyModel = std::vector<std::pair<std::pair<std::string, float>, int>>;
namespace Zappy {

    class Game {

        public:

            Game(int screenWidth, int screenHeight, CommandManager &cmd,
                asio::ip::tcp::socket &socket, bool animation);
            void updateCamera(void);

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
                PlayerType = 3,
                Egg = 4,
                SkyM = 5
            };

            CommandManager &_cmd;
            Camera _camera;
            asio::ip::tcp::socket &_socket;

            int _screenWidth;
            int _screenHeight;
            int _cameraMode;
            int _sgtValue;

            bool _displayGameInfo;

            std::pair<int, int> _mapSize;
            std::pair<bool, std::size_t> _selectedPlayer;

            std::vector<std::pair<Model, float>> _allItemModel;
            std::vector<std::pair<Model, float>> _islandModel;
            std::vector<std::pair<Model, float>> _playerModel;
            std::vector<std::pair<Model, float>> _eggModel;
            std::pair<Model, float> _skyModel;
            std::pair<Model, float> _seaModel;

            std::unique_ptr<AllIsland> _allIsland;
            std::unique_ptr<AllItem> _allItem;
            std::unique_ptr<AllEggs> _allEggs;
            std::unique_ptr<AllPlayers> _allPlayer;
            std::unique_ptr<Sky> _sky;
            std::unique_ptr<Sea> _sea;

            void display3D(void);
            void display2D(void);
            void setCameraToCoord(Vector3 position, Vector3 target);
            void cameraPositionStart(void);
            void unloadAllModel(void);
    };
}

#endif /* !Game_HPP_ */
