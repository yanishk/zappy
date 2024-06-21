/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** DisplayGame
*/

#ifndef DISPLAYGAME_HPP_
    #define DISPLAYGAME_HPP_

    #include <string>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include <stdlib.h>
    #include <ctime>
    #include "Player.hpp"
    #include "Commands.hpp"
    #include "Client.hpp"
    #include "Item.hpp"
    #include "Island.hpp"
    #include "UseRecivedCmd.hpp"
    #include "Eggs.hpp"

    #define WINDOW_NAME "Zappy_gui"
    #define ERROR_NO_MODEL "No or bad path to model"
    #define ERROR_NO_PLAYER_MODEL "No player model"
    #define ERROR_NOT_ENOUTH_ITEM_MODEL "Not enough item model"

using ZappyModel = std::vector<std::pair<std::pair<std::string, float>, int>>;

class DisplayGame {
    public:
        DisplayGame(int screenWidth, int screenHeight, CommandManager &cmd, asio::ip::tcp::socket &socket, bool animation);
        ~DisplayGame();
        void updateCamera(void);
        Vector3 setVector3(float x, float y, float z);
        void launchGame(void);
        void fillAllModel(ZappyModel);

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
        int _screenWidth = 1920;
        int _screenHeight = 1080;
        int _cameraMode = CAMERA_FREE;
        int _secondLoc;
        std::pair<int, int> _mapSize;
        std::pair<bool, std::size_t> _selectedPlayer;
        asio::ip::tcp::socket &_socket;

        std::vector<std::pair<Model, float>> _allItemModel;
        std::vector<std::pair<Model, float>> _islandModel;
        std::vector<std::pair<Model, float>> _playerModel;
        std::pair<Model, float> _eggModel;

        std::unique_ptr<AllIsland> _allIsland;
        std::unique_ptr<AllItem> _allItem;
        std::unique_ptr<AllEggs> _allEggs;
        std::unique_ptr<AllPlayers> _allPlayer;

        void initWaterShader(void);
        void useServerInfo(UseRecivedCmd &recivedCmd);
        void display3D(void);
        void display2D(void);
        void mooveCameraToCoord(Vector3 position, Vector3 target);
};

#endif /* !DISPLAYGAME_HPP_ */
