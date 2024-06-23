/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** Game
*/

#include "Game.hpp"
#include "Factory.hpp"

Zappy::Game::Game(int screenWidth, int screenHeight, CommandManager &cmd,
    asio::ip::tcp::socket &socket, bool anim) : _cmd(cmd),
                                                    _socket(socket),
                                                    _displayGameInfo(true)
{
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;
    SetTraceLogLevel(TraceLogLevel::LOG_FATAL);
    InitWindow(screenWidth, screenHeight, WINDOW_NAME);
    _camera.up = Utils::Vec3(0.0, 1.0, 0.0);
    _camera.fovy = FOV;
    _camera.projection = CAMERA_PERSPECTIVE;
    _cameraMode = CAMERA_FREE;
    _selectedPlayer.first = false;

    _sky = std::get<std::unique_ptr<Sky>>(Factory::newObject(objType::SkyType));
    _sea = std::get<std::unique_ptr<Sea>>(Factory::newObject(objType::SeaType));
    _allIsland = std::get<std::unique_ptr<AllIsland>>(Factory::newObjects(objType::IslandType, cmd, anim));
    _allItem = std::get<std::unique_ptr<AllItem>>(Factory::newObjects(objType::ItemType, cmd, anim));
    _allEggs = std::get<std::unique_ptr<AllEggs>>(Factory::newObjects(objType::EggType, cmd, anim));
    _allPlayer = std::get<std::unique_ptr<AllPlayers>>(Factory::newObjects(objType::PlayerType, cmd, anim));
}

void Zappy::Game::updateCamera(void)
{
    float alltitude = 0.0;
    float speed = CAMERA_MOVEMENT_SPEED;

    if (IsKeyDown(KEY_SPACE))
        alltitude += speed;

    if (IsKeyDown(KEY_LEFT_SHIFT))
        alltitude -= speed;

    if (IsKeyDown(KEY_LEFT_CONTROL))
        speed += CAMERA_MOVEMENT_SPEED / 2;

    Vector3 movement = Utils::Vec3(
        IsKeyDown(KEY_W) * speed - IsKeyDown(KEY_S) * speed,
        IsKeyDown(KEY_D) * speed - IsKeyDown(KEY_A) * speed, alltitude);
    Vector3 rotation = Utils::Vec3(GetMouseDelta().x * 0.05f, GetMouseDelta().y * 0.05f, 0);

    UpdateCameraPro(&_camera, movement, rotation, GetMouseWheelMove());
}

void Zappy::Game::fillAllModel(ZappyModel allPath)
{
    std::vector<std::pair<Model, float>> tmpModel;
    std::pair<Model, float> tmpEggModel;

    bool hasPlayer = false;

    if (allPath.size() == 0) {
        throw ErrorHandling(ERROR_NO_MODEL);
    }
    for (auto &i: allPath) {
        std::pair<Model, float> tmpPair;
        tmpPair.first = LoadModel(i.first.first.c_str());
        tmpPair.second = i.first.second;
        switch (i.second) {
            case IslandType:
                _islandModel.push_back(tmpPair);
                break;
            case ItemType: {
                _allItemModel.push_back(tmpPair);
                break;
            }
            case PlayerType: {
                _playerModel.push_back(tmpPair);
                hasPlayer = true;
                break;
            }
            case Egg: {
                _eggModel.push_back(tmpPair);
                break;
            }
            case SkyM: {
                _skyModel.first = LoadModel(SKY_MODEL_PATH);
                _skyModel.first.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
                LoadTexture(SKY_TEXTURE_PATH);
                _skyModel.second = 10;
            }
        }
    }

    if (!hasPlayer)
        throw ErrorHandling(ERROR_NO_PLAYER_MODEL);
    if (_allItemModel.size() < NBR_ITEM)
        throw ErrorHandling(ERROR_NOT_ENOUTH_ITEM_MODEL);
}

void Zappy::Game::setCameraToCoord(Vector3 position, Vector3 target)
{
    _camera.position = position;
    _camera.target = target;
}

void Zappy::Game::display3D(void)
{
    BeginMode3D(_camera);

    _sky.get()->setSkyPos(_camera.position);
    _sky.get()->render();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        std::pair<bool, int> tmpSelectedPlayer =
            _allPlayer.get()->isPlayerSelected(_camera.target, _camera.position);
        if (tmpSelectedPlayer.second != -1) {
            _selectedPlayer = tmpSelectedPlayer;
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        _selectedPlayer.first = false;
    }

    _sea.get()->setSeaPos(_camera.position, _mapSize);
    _sea.get()->render();
    _allIsland.get()->renderAllElements();
    _allItem.get()->renderAllElements();
    _allEggs.get()->renderAllElements();
    _allPlayer.get()->renderAllElements(_camera.position);

    EndMode3D();
}

void Zappy::Game::display2D(void)
{
    _allPlayer.get()->renderAll2D(_selectedPlayer, _allItem);

    int position = START_POS;
    int size = CROSSBAR_SIZE;

    DrawCircleLines(_screenWidth / 2, _screenHeight / 2, size, RED);
    size += CROSSBAR_SIZE / 2;

    DrawLine(_screenWidth / 2 - size / 2, _screenHeight / 2 - size /
        2, _screenWidth / 2 + size / 2, _screenHeight / 2 + size / 2, RED);
    DrawLine(_screenWidth / 2 + size / 2, _screenHeight / 2 - size /
        2, _screenWidth / 2 - size / 2, _screenHeight / 2 + size / 2, RED);

    if (IsKeyPressed(KEY_F3)) {
        _displayGameInfo = !_displayGameInfo;
    }

    if (!_displayGameInfo) {
        return;
    }

    DrawRectangle(MARGIN_LEFT, MARGIN_TOP, WIGHT, HIGHT, Fade(SKYBLUE, 0.5f));
    DrawFPS(_screenWidth - FPS_MARGIN, MARGIN_TOP);

    DrawText(TextFormat(CAM_POS, _camera.position.x, _camera.position.y,
        _camera.position.z), MARGIN_LEFT * 2, position, FONT_SIZE, BLACK);

    position += BACKSLASH_N;
    DrawText(TextFormat(CAM_TARGET, _camera.target.x, _camera.target.y,
        _camera.target.z), MARGIN_LEFT * 2, position, FONT_SIZE, BLACK);

    position += BACKSLASH_N;
    DrawText(TextFormat(TIME_UNIT, _sgtValue), MARGIN_LEFT * 2,
        position, FONT_SIZE, BLACK);

    position += BACKSLASH_N;
    DrawText(TextFormat(NBR_ITEM_MAP, _allItem.get()->getTotalNbrElements()),
        MARGIN_LEFT * 2, position, FONT_SIZE, BLACK);

    position += BACKSLASH_N;
    DrawText(TextFormat(NBR_PLAYER_MAP, _allPlayer.get()->getTotalNbrElements()),
        MARGIN_LEFT * 2, position, FONT_SIZE, BLACK);

    position += BACKSLASH_N;
    DrawText(TextFormat(NBR_ISLAND_MAP, _allIsland.get()->getTotalNbrElements()),
        MARGIN_LEFT * 2, position, FONT_SIZE, BLACK);

    position += BACKSLASH_N;
    DrawText(TextFormat(NBR_EGGS_MAP, _allEggs.get()->getTotalNbrElements()),
        MARGIN_LEFT * 2, position, FONT_SIZE, BLACK);
}

void Zappy::Game::cameraPositionStart(void)
{
    if (!_cmd.getCommandAt(MSZ_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(MSZ_CMD, 0);
        std::pair<float, float> mapSize;
        mapSize.first = std::stof(cmd.front().c_str());
        mapSize.second = std::stof(cmd[1].c_str());
        std::pair<float, float> middleMap;
        middleMap.first = ((mapSize.first * spaceBetwenIsland) / 2) +
            (spaceBetwenIsland / 2);
        middleMap.second = (((mapSize.second - 1) * spaceBetwenIsland) / 2);
        Vector3 target =   Utils::Vec3(middleMap.first, 0, middleMap.second);

        Vector3 position = Utils::Vec3(middleMap.first,
            mapSize.first * START_POS_COEF_Y,
            -(mapSize.second * spaceBetwenIsland) / START_POS_COEF_Z - spaceBetwenIsland);
        setCameraToCoord(position, target);
    }
}

void Zappy::Game::getSgtCmd(void)
{
    if (!_cmd.getCommandAt(SGT_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(SGT_CMD, 0);
        _sgtValue = std::stoi(cmd[0]);
        _cmd.eraseFirstCmdInMap(SGT_CMD);
    }
}

void Zappy::Game::requestChangingTimeUnit(void)
{
    if (IsKeyPressed(KEY_UP)) {
        _sgtValue += SST_CHANGE;
        std::string value = std::to_string(_sgtValue);
        std::string sstCmd = SST_CMD;
        sstCmd += SPACE_C;
        sstCmd += value;
        sstCmd += NEW_L;
        asio::write(_socket, asio::buffer(sstCmd));
    } else if (IsKeyPressed(KEY_DOWN)) {
        _sgtValue -= SST_CHANGE;
        std::string value = std::to_string(_sgtValue);
        std::string sstCmd = SST_CMD;
        sstCmd += SPACE_C;
        sstCmd += value;
        sstCmd += NEW_L;
        asio::write(_socket, asio::buffer(sstCmd));
    }
}

void Zappy::Game::unloadAllModel(void)
{
    for (auto &i: _allItemModel)
        UnloadModel(i.first);
    for (auto &i : _islandModel)
        UnloadModel(i.first);
    for (auto &i : _playerModel)
        UnloadModel(i.first);
    for (auto &i : _eggModel)
        UnloadModel(i.first);
    CloseWindow();
}

void Zappy::Game::launchGame(void)
{
    DisableCursor();
    cameraPositionStart();
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {

        _allIsland.get()->setAllElements(_islandModel);
        _allItem.get()->setAllElements(_allItemModel);
        _allEggs.get()->setAllElements(_eggModel);
        _allPlayer.get()->setAllElements(_playerModel);
        _sky.get()->setModel(_skyModel);

        requestChangingTimeUnit();
        updateCamera();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        display3D();
        display2D();
        EndDrawing();
    }
    unloadAllModel();
}
