/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** DisplayGame
*/

#include "DisplayGame.hpp"

DisplayGame::DisplayGame(int screenWidth, int screenHeight, CommandManager &cmd) : _cmd(cmd)
{
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;
    InitWindow(screenWidth, screenHeight, "Zappy_gui");
    _camera.position = setVector3(70.0, 40.0, -50.0);
    _camera.target = setVector3(70.0, 18.0, -0.0);
    _camera.up = setVector3(0.0, 1.0, 0.0);
    _camera.fovy = 60;
    _camera.projection = CAMERA_PERSPECTIVE;
    initWaterShader();
    _selectedPlayer.first = false;

    // std::thread reader(&Client::readServ, this);
    // writeToServ();
    // reader.join();
}

DisplayGame::~DisplayGame()
{
    CloseWindow();
    for (std::size_t i = 0; i < _allItemModel.size(); i++) {
        UnloadModel(_allItemModel.at(i)._itemModel);
    }
}

Vector3 DisplayGame::setVector3(float x, float y, float z)
{
    Vector3 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void DisplayGame::updateCamera(void)
{
    float alltitude = 0.0;
    float speed = 0.4;

    if (IsKeyDown(KEY_SPACE)) {
        alltitude += speed;
    }
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        alltitude -= speed;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        speed += 0.2;
    }
    Vector3 movement = setVector3(IsKeyDown(KEY_W) * speed - IsKeyDown(KEY_S) * speed, IsKeyDown(KEY_D) * speed - IsKeyDown(KEY_A) * speed, alltitude);
    Vector3 rotation = setVector3(GetMouseDelta().x * 0.05f, GetMouseDelta().y * 0.05f, 0);

    UpdateCameraPro(&_camera, movement, rotation, GetMouseWheelMove() * 2.0f);
}

void DisplayGame::fillAllModel(std::vector<std::pair<std::pair<std::string, float>, int>> allPath)
{
    std::vector<std::pair<Model, float>> tmpIslandModel;
    std::vector<std::pair<Model, float>> tmpModel;

    for (std::size_t i = 0; i < allPath.size(); i++) {
        std::pair<Model, float> tmpPair;
        tmpPair.first = LoadModel(allPath.at(i).first.first.c_str());
        tmpPair.second = allPath.at(i).first.second;
        if (allPath.at(i).second == IslandType) {
            _islandModel.push_back(tmpPair);
        }
        if (allPath.at(i).second == ItemType) {
            tmpModel.push_back(tmpPair);

            Item tmpItem;
            _allItemModel.push_back(tmpItem);
            _allItemModel.back()._itemModel = tmpModel.back().first;
            _allItemModel.back()._itemSize = tmpModel.back().second;
        }
        if (allPath.at(i).second == PlayerType) {
            _player.loadModelAndAnim(tmpPair, allPath.at(i).first.first);
        }
    }
}

void DisplayGame::placeIsland(int x, int y)
{
    _mapSize.first = x;
    _mapSize.second = y;
    float posX = 0;
    _allIsland.clear();
    for (int i = 0; i < x; i++) {
        float posY = 0;
        posX += spaceBetwenIsland;
        for (int j = 0; j < y; j++) {
            std::size_t islandIndex = rand() % _islandModel.size();
            Island tmpIsland;
            _allIsland.push_back(tmpIsland);
            _islandModel.at(islandIndex).first.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0, DEG2RAD*(std::rand() % 360), DEG2RAD*0});
            _allIsland.back()._islandModel = _islandModel.at(islandIndex).first;
            _allIsland.back()._islandPosition = setVector3(posX, -4, posY);
            _allIsland.back()._islandSize = _islandModel.at(islandIndex).second;
            posY += spaceBetwenIsland;
        }
    }
}

void DisplayGame::initWaterShader(void)
{
    _waterShader = LoadShader(0, TextFormat("./assets/shaders/water.fs", 330));

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

    Texture2D texture = LoadTexture("./assets/image/water_texture.png");
    Texture2D texture2 = LoadTexture("./assets/image/rose_des_vents.png");
    _RoseModel = LoadModelFromMesh(GenMeshPlane(1000, 1000, 2, 2));
    _RoseModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture2;
    _WaterModel = LoadModelFromMesh(GenMeshPlane(1000, 1000, 2, 2));
    _WaterModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _WaterModel.materials[0].shader = _waterShader;
}

void DisplayGame::addItemToIsland(Vector3 position, int type)
{
    _allItem.push_back(_allItemModel.at(type));
    _allItem.back()._itemPosition = setVector3((position.x + 1) * spaceBetwenIsland, 1.8, position.z * spaceBetwenIsland);
    _allItem.back()._itemPosition.x += -3 + (rand() % 6);
    _allItem.back()._itemPosition.z += -3 + (rand() % 6);
    _allItem.back()._rotation = 0;
    _allItem.back()._upValue = -0.005;
    _allItem.back()._realPos = position;
    _allItem.back()._itemType = type;
}

void DisplayGame::removeItemFromIsland(Vector3 position, int type)
{
    for (std::size_t i = 0; i < _allItem.size(); i++) {
        if (Utils::Vec3Comp(_allItem.at(i)._realPos, position) && _allItem.at(i)._itemType == type) {
            _allItem.erase(_allItem.begin() + i);
            break;
        }
    }
}

void DisplayGame::displayMorePlayerInfo(void)
{
    for (std::size_t i = 0; i < _player._allPlayer.size(); i++) {
        Vector3 direction = Vector3Subtract(_camera.target, _camera.position);
        direction = Vector3Normalize(direction);
        Ray ray = {_camera.position, direction};

        BoundingBox playerBox = GetMeshBoundingBox(_player._allPlayer.at(i)._playerModel.meshes[0]);
        if (_player._allPlayer.at(i).isPlayerSelected(playerBox, ray)) {
            _selectedPlayer.first = true;
            _selectedPlayer.second = i;
        }
    }
}

void DisplayGame::useServerInfo(void)
{
    if (_cmd.getCommandAt("pnw", _newPlayerIndex).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pnw", _newPlayerIndex);
        _player.addPlayerToIsland((Vector3){std::atoi(cmd.at(1).c_str()), 1.8, std::atoi(cmd.at(2).c_str())}, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation(std::atoi(cmd.at(3).c_str()) * 90, std::atoi(cmd.at(0).c_str()));
        _player.setPlayerTeam(cmd.at(5), std::atoi(cmd.at(0).c_str()));
        _newPlayerIndex++;
    }
    for (int i = 0; _cmd.getCommandAt("ppo", i).size() > 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ppo", i);

        _player.moovePlayerToIsland((Vector3){std::atoi(cmd.at(1).c_str()), 1.8, std::atoi(cmd.at(2).c_str())}, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation(std::atoi(cmd.at(3).c_str()) * 90, std::atoi(cmd.at(0).c_str()));
    }
}

void DisplayGame::tmpLaunch(void)
{
    DisableCursor();

    SetTargetFPS(60);
    Model sky = LoadModel("./assets/models/unreal-engine-4-sky/source/ue4sky.obj");
    Texture2D texture = LoadTexture("./assets/models/unreal-engine-4-sky/textures/T_Sky_Blue.png");
    sky.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    float seconds = 0.0f;
    while (!WindowShouldClose()) {
        useServerInfo();
        seconds += (GetFrameTime() / 2);

        SetShaderValue(_waterShader, _secondLoc, &seconds, SHADER_UNIFORM_FLOAT);
        updateCamera();

        BeginDrawing();

        ClearBackground(BLANK);

        BeginMode3D(_camera);
        DrawModel(sky, setVector3(_camera.position.x, 0, _camera.position.z), 10, WHITE);

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
        DrawModel(_RoseModel, setVector3(_camera.position.x, -1.5, _camera.position.z), 1, WHITE);

        for (std::size_t i = 0; i < _allItem.size(); i++) {
            _allItem.at(i)._rotation += 1;
            if (_allItem.at(i)._rotation > 360)
                _allItem.at(i)._rotation = 0;
            _allItem.at(i)._itemPosition.y += _allItem.at(i)._upValue;
            if (_allItem.at(i)._itemPosition.y <= 1.5 || _allItem.at(i)._itemPosition.y >= 2)
                _allItem.at(i)._upValue *= -1;
            _allItem.at(i)._itemModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0, DEG2RAD*_allItem.at(i)._rotation, DEG2RAD*0});
            DrawModel(_allItem.at(i)._itemModel , _allItem.at(i)._itemPosition, _allItem.at(i)._itemSize, WHITE);
        }
        for (std::size_t i = 0; i < _player._allPlayer.size(); i++) {
            _player._allPlayer.at(i)._animFrameCounter++;
            if (_player._allPlayer.at(i)._animFrameCounter >= _player._allPlayer.at(i)._playerAnimation[0].frameCount)
                _player._allPlayer.at(i)._animFrameCounter = 0;
            UpdateModelAnimation(_player._allPlayer.at(i)._playerModel, _player._allPlayer.at(i)._playerAnimation[0], _player._allPlayer.at(i)._animFrameCounter);
            DrawModelEx(_player._allPlayer.at(i)._playerModel , _player._allPlayer.at(i).getPosition(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, _player.getSize(), WHITE);
            _player._allPlayer.at(i).displayPlayerInfo(_camera.position);
        }

        for (std::size_t i = 0; i < _allIsland.size(); i++) {
            DrawModel(_allIsland.at(i)._islandModel , _allIsland.at(i)._islandPosition, _allIsland.at(i)._islandSize, WHITE);
        }

        EndMode3D();

        if (_selectedPlayer.first) {
            int playerInfoBoxWidth = 400;
            int playerInfoBoxHeight = 110;
            DrawRectangle(_screenWidth - playerInfoBoxWidth - 5, 5, playerInfoBoxWidth, playerInfoBoxHeight, Fade(GRAY, 0.5f));
            _player._allPlayer.at(_selectedPlayer.second).displayInfo2D(_screenWidth - playerInfoBoxWidth - 5, 5);
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

        EndDrawing();
    }
}
