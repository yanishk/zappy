/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(int screenWidth, int screenHeight, CommandManager &cmd, asio::ip::tcp::socket &socket, bool animation) : _cmd(cmd), _socket(socket)
{
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;
    SetTraceLogLevel(TraceLogLevel::LOG_ERROR);
    InitWindow(screenWidth, screenHeight, WINDOW_NAME);
    _camera.up = setVector3(0.0, 1.0, 0.0);
    _camera.fovy = FOV;
    _camera.projection = CAMERA_PERSPECTIVE;
    initWaterShader();
    _selectedPlayer.first = false;

    _allIsland = std::make_unique<AllIsland>(_cmd);
    _allItem = std::make_unique<AllItem>(_cmd);
    _allEggs = std::make_unique<AllEggs>(_cmd);
    _allPlayer = std::make_unique<AllPlayers>(_cmd, animation);
}

Game::~Game()
{
    CloseWindow();
    for (auto &i: _allItemModel)
        UnloadModel(i.first);
}

Vector3 Game::setVector3(float x, float y, float z)
{
    return (Vector3){x, y, z};
}

void Game::updateCamera(void)
{
    float alltitude = 0.0;
    float speed = CAMERA_MOVEMENT_SPEED;

    if (IsKeyDown(KEY_SPACE))
        alltitude += speed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        alltitude -= speed;
    if (IsKeyDown(KEY_LEFT_CONTROL))
        speed += CAMERA_MOVEMENT_SPEED / 2;
    Vector3 movement = setVector3(
        IsKeyDown(KEY_W) * speed - IsKeyDown(KEY_S) * speed,
        IsKeyDown(KEY_D) * speed - IsKeyDown(KEY_A) * speed, alltitude);
    Vector3 rotation = setVector3(GetMouseDelta().x * 0.05f, GetMouseDelta().y * 0.05f, 0);

    UpdateCameraPro(&_camera, movement, rotation, GetMouseWheelMove());
}

void Game::fillAllModel(ZappyModel allPath)
{
    std::vector<std::pair<Model, float>> tmpModel;
    bool hasPlayer = false;

    if (allPath.size() == 0)
        throw ErrorHandling(ERROR_NO_MODEL);
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
        }
    }
    _eggModel.first = LoadModel(EGG_MOD_PATH);
    _eggModel.second = EGG_MODEL_SIZE;

    _sky = LoadModel(SKY_MODEL_PATH);
    Texture2D texture = LoadTexture(SKY_TEXTURE_PATH);
    _sky.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    if (!hasPlayer)
        throw ErrorHandling(ERROR_NO_PLAYER_MODEL);
    if (_allItemModel.size() < NBR_ITEM)
        throw ErrorHandling(ERROR_NOT_ENOUTH_ITEM_MODEL);
}

void Game::setCameraToCoord(Vector3 position, Vector3 target)
{
    _camera.position = position;
    _camera.target = target;
}

void Game::initWaterShader(void)
{
    _waterShader = LoadShader(0, TextFormat(WATER_SHADER, SHADER_FORMAT));

    _secondLoc = GetShaderLocation(_waterShader, SHADER_SECONDS);
    int freqXLoc = GetShaderLocation(_waterShader, SHADER_FREQX);
    int freqYLoc = GetShaderLocation(_waterShader, SHADER_FREQY);
    int ampXLoc = GetShaderLocation(_waterShader, SHADER_AMPX);
    int ampYLoc = GetShaderLocation(_waterShader, SHADER_AMPY);
    int speedXLoc = GetShaderLocation(_waterShader, SHADER_SPEEDX);
    int speedYLoc = GetShaderLocation(_waterShader, SHADER_SPEEDY);

    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(_waterShader, GetShaderLocation(_waterShader, SHADER_SIZE), &screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(_waterShader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    Texture2D texture = LoadTexture(WATER_TEXTURE);
    _WaterModel = LoadModelFromMesh(GenMeshPlane(WATER_SIZE, WATER_SIZE, WATER_RESXZ, WATER_RESXZ));
    _WaterModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _WaterModel.materials[0].shader = _waterShader;
}

void Game::display3D(void)
{
    BeginMode3D(_camera);

    DrawModel(_sky, setVector3(_camera.position.x, 0, _camera.position.z), SKY_SIZE, WHITE);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        std::pair<bool, int> tmpSelectedPlayer = _allPlayer.get()->isPlayerSelected(_camera.target, _camera.position);
        if (tmpSelectedPlayer.second != -1)
            _selectedPlayer = tmpSelectedPlayer;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        _selectedPlayer.first = false;
    }

    BeginShaderMode(_waterShader);
        DrawModel(_WaterModel, setVector3(_camera.position.x, SUB_WATER_ALTITUDE, _camera.position.z), 1, WHITE);
        DrawModel(_WaterModel, setVector3((_mapSize.first * spaceBetwenIsland) / 2, WATER_ALTITUDE, (_mapSize.second * spaceBetwenIsland) / 2), 1, WHITE);
    EndShaderMode();

    _allIsland.get()->renderAll();
    _allItem.get()->renderAll();
    _allEggs.get()->renderAll();
    _allPlayer.get()->renderAll(_camera.position);

    EndMode3D();
}

void Game::display2D(void)
{
    _allPlayer.get()->renderAll2D(_selectedPlayer, _allItem);

    int size = CROSSBAR_SIZE;
    DrawCircleLines(_screenWidth / 2, _screenHeight / 2, size, RED);
    size += CROSSBAR_SIZE / 2;
    DrawLine(_screenWidth / 2 - size / 2, _screenHeight / 2 - size / 2, _screenWidth / 2 + size / 2, _screenHeight / 2 + size / 2, RED);
    DrawLine(_screenWidth / 2 + size / 2, _screenHeight / 2 - size / 2, _screenWidth / 2 - size / 2, _screenHeight / 2 + size / 2, RED);
}

void Game::cameraPositionStart(void)
{
    if (!_cmd.getCommandAt(MSZ_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(MSZ_CMD, 0);

        std::pair<float, float> mapSize;
        mapSize.first = std::stof(cmd.front().c_str());
        mapSize.second = std::stof(cmd[1].c_str());
        std::pair<float, float> middleMap;
        middleMap.first = ((mapSize.first * spaceBetwenIsland) / 2) + (spaceBetwenIsland / 2);
        middleMap.second = (((mapSize.second - 1) * spaceBetwenIsland) / 2);
        Vector3 target =   setVector3(middleMap.first, 0, middleMap.second);

        Vector3 position = setVector3(middleMap.first,
            mapSize.first * START_POS_COEF_Y,
            -(mapSize.second * spaceBetwenIsland) / START_POS_COEF_Z - spaceBetwenIsland);
        setCameraToCoord(position, target);
    }
}


int Game::getSgt(void)
{
    return _sgtValue;
}

void Game::getSgtCmd(void)
{
    if (!_cmd.getCommandAt(SGT_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(SGT_CMD, 0);
        _sgtValue = std::stoi(cmd[0]);
        _cmd.eraseFirstCmdInMap(SGT_CMD);
    }
}

void Game::requestChangingTimeUnit(void)
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

void Game::launchGame(void)
{
    DisableCursor();
    cameraPositionStart();

    SetTargetFPS(FPS);
    float seconds = 0.0f;

    while (!WindowShouldClose()) {
        _allIsland.get()->setAllIsland(_islandModel);
        _allItem.get()->setAllItem(_allItemModel);
        _allEggs.get()->setAllEggs(_eggModel);
        _allPlayer.get()->setAllPlayer(_playerModel);

        requestChangingTimeUnit();
        seconds += (GetFrameTime() / 2);

        SetShaderValue(_waterShader, _secondLoc, &seconds, SHADER_UNIFORM_FLOAT);
        updateCamera();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        display3D();
        display2D();
        EndDrawing();
    }
}
