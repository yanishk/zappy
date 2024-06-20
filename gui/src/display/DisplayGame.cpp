/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** DisplayGame
*/

#include "DisplayGame.hpp"

DisplayGame::DisplayGame(int screenWidth, int screenHeight, CommandManager &cmd, asio::ip::tcp::socket &socket, bool animation) : _cmd(cmd), _socket(socket)
{
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;
    InitWindow(screenWidth, screenHeight, WINDOW_NAME);
    _camera.position = setVector3(70.0, 40.0, -50.0);
    _camera.target = setVector3(70.0, 18.0, -0.0);
    _camera.up = setVector3(0.0, 1.0, 0.0);
    _camera.fovy = 60;
    _camera.projection = CAMERA_PERSPECTIVE;
    initWaterShader();
    _selectedPlayer.first = false;
    _mapSize.first = 0;
    _mapSize.second = 0;
    _isAnimated = animation;

    _allIsland = std::make_unique<AllIsland>(_cmd);
}

DisplayGame::~DisplayGame()
{
    CloseWindow();
    for (auto &i: _allItemModel)
        UnloadModel(i._itemModel);
}

Vector3 DisplayGame::setVector3(float x, float y, float z)
{
    return (Vector3){x, y, z};
}

void DisplayGame::updateCamera(void)
{
    float alltitude = 0.0;
    float speed = 0.4;

    if (IsKeyDown(KEY_SPACE))
        alltitude += speed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        alltitude -= speed;
    if (IsKeyDown(KEY_LEFT_CONTROL))
        speed += 0.2;
    Vector3 movement = setVector3(IsKeyDown(KEY_W) * speed - IsKeyDown(KEY_S) * speed, IsKeyDown(KEY_D) * speed - IsKeyDown(KEY_A) * speed, alltitude);
    Vector3 rotation = setVector3(GetMouseDelta().x * 0.05f, GetMouseDelta().y * 0.05f, 0);

    UpdateCameraPro(&_camera, movement, rotation, GetMouseWheelMove() * 2.0f);
}

void DisplayGame::fillAllModel(ZappyModel allPath)
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
                _islandModel = tmpPair;
                break;
            case ItemType: {
                tmpModel.push_back(tmpPair);
                Item tmpItem;
                _allItemModel.push_back(tmpItem);
                _allItemModel.back()._itemModel = tmpModel.back().first;
                _allItemModel.back()._itemSize = tmpModel.back().second;
                break;
            }
            case PlayerType: {
                _player.loadModelAndAnim(tmpPair, i.first.first);
                hasPlayer = true;
                break;
            }
        }
    }
    std::pair<Model, float> eggPair;
    eggPair.first = LoadModel(EGG_MOD_PATH);
    eggPair.second = 0.3;
    _allEggs.loadEggModel(eggPair);

    _sky = LoadModel("./gui/assets/models/unreal-engine-4-sky/source/ue4sky.obj");
    Texture2D texture = LoadTexture("./gui/assets/models/unreal-engine-4-sky/textures/T_Sky_Blue.png");
    _sky.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    if (!hasPlayer)
        throw ErrorHandling(ERROR_NO_PLAYER_MODEL);
    if (_allItemModel.size() < 7)
        throw ErrorHandling(ERROR_NOT_ENOUTH_ITEM_MODEL);
}

void DisplayGame::mooveCameraToCoord(Vector3 position, Vector3 target)
{
    _camera.position = position;
    _camera.target = target;
}

void DisplayGame::initWaterShader(void)
{
    _waterShader = LoadShader(0, TextFormat("./gui/assets/shaders/water.fs", 330));

    _secondLoc = GetShaderLocation(_waterShader, "seconds");
    int freqXLoc = GetShaderLocation(_waterShader, "freqX");
    int freqYLoc = GetShaderLocation(_waterShader, "freqY");
    int ampXLoc = GetShaderLocation(_waterShader, "ampX");
    int ampYLoc = GetShaderLocation(_waterShader, "ampY");
    int speedXLoc = GetShaderLocation(_waterShader, "speedX");
    int speedYLoc = GetShaderLocation(_waterShader, "speedY");

    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(_waterShader, GetShaderLocation(_waterShader, "size"), &screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(_waterShader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_waterShader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    Texture2D texture = LoadTexture("./gui/assets/image/water_texture.png");
    _WaterModel = LoadModelFromMesh(GenMeshPlane(1000, 1000, 2, 2));
    _WaterModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _WaterModel.materials[0].shader = _waterShader;
}

void DisplayGame::displayMorePlayerInfo(void)
{
    for (auto &i: _player._allPlayer) {
        Vector3 direction = Vector3Subtract(_camera.target, _camera.position);
        direction = Vector3Normalize(direction);
        Ray ray = {_camera.position, direction};

        BoundingBox playerBox = GetMeshBoundingBox(i._playerModel.meshes[0]);
        if (i.isPlayerSelected(playerBox, ray)) {
            _selectedPlayer.first = true;
            _selectedPlayer.second = i._playerID;
        }
    }
}

void DisplayGame::useServerInfo(UseRecivedCmd &recivedCmd)
{
    recivedCmd.callAllFunctions(_camera.position);
}

void DisplayGame::display3D(void)
{
    BeginMode3D(_camera);

    DrawModel(_sky, setVector3(_camera.position.x, 0, _camera.position.z), 10, WHITE);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        displayMorePlayerInfo();
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        _selectedPlayer.first = false;
    }

    BeginShaderMode(_waterShader);
        DrawModel(_WaterModel, setVector3(_camera.position.x, -2.3, _camera.position.z), 1, WHITE);
        DrawModel(_WaterModel, setVector3((_mapSize.first * spaceBetwenIsland) / 2, -2, (_mapSize.second * spaceBetwenIsland) / 2), 1, WHITE);
    EndShaderMode();


    _allIsland.get()->renderAll();
    _allEggs.drawEgg();

    for (auto &i: _allItem) {
        i.changeItemAnim();
        i.drawItem();
    }
    _player.drawPlayer(_isAnimated);

    for (auto &i: _player._allPlayer) {
        i.displayPlayerInfo(_camera.position);
        i.drawIncantation();
        i.drawExpulsion();
    }

    EndMode3D();
}

void DisplayGame::display2D(void)
{
    if (_selectedPlayer.first) {
        _player.displayMorePlayerInfo(_selectedPlayer.second, _screenWidth, _allItem);
    }

    int size = 8;
    DrawCircleLines(1920 / 2, 1080 / 2, size, RED);
    size += 4;
    DrawLine(1920 / 2 - size / 2, 1080 / 2 - size / 2, 1920 / 2 + size / 2, 1080 / 2 + size / 2, RED);
    DrawLine(1920 / 2 + size / 2, 1080 / 2 - size / 2, 1920 / 2 - size / 2, 1080 / 2 + size / 2, RED);

    DrawRectangle(5, 5, 330, 75, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(5, 5, 330, 75, BLUE);

    DrawText("camera controls:", 15, 15, 10, BLACK);
    DrawText("- Move keys: Z, Q, S, D, Space, Left-Ctrl, Left-Shift", 15, 30, 10, BLACK);
    DrawText("- Look around: mouse", 15, 45, 10, BLACK);
    DrawText("- Zoom keys: mouse scroll", 15, 60, 10, BLACK);

    DrawRectangle(350, 5, 195, 60, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(350, 5, 195, 60, BLUE);

    DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", _camera.position.x, _camera.position.y, _camera.position.z), 355, 15, 10, BLACK);
    DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", _camera.target.x, _camera.target.y, _camera.target.z), 355, 30, 10, BLACK);
    DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", _camera.up.x, _camera.up.y, _camera.up.z), 355, 45, 10, BLACK);
}

void DisplayGame::launchGame(void)
{
    DisableCursor();
    UseRecivedCmd recivedCmd(_cmd, _player, _allEggs, _allItem, _allItemModel, _socket);

    SetTargetFPS(60);
    float seconds = 0.0f;

    while (!WindowShouldClose()) {
        _allIsland.get()->setAllIsland(_islandModel);
        useServerInfo(recivedCmd);
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
