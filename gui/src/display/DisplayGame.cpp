/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** DisplayGame
*/

#include "DisplayGame.hpp"

DisplayGame::DisplayGame(int screenWidth, int screenHeight, CommandManager &cmd, asio::ip::tcp::socket &socket) : _cmd(cmd), _socket(socket)
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
    _mapSize.first = 0;
    _mapSize.second = 0;
}

DisplayGame::~DisplayGame()
{
    CloseWindow();
    for (auto &i: _allItemModel) {
        UnloadModel(i._itemModel);
    }
}

Vector3 DisplayGame::setVector3(float x, float y, float z)
{
    return (Vector3){x, y, z};
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

void DisplayGame::fillAllModel(ZappyModel allPath)
{
    std::vector<std::pair<Model, float>> tmpIslandModel;
    std::vector<std::pair<Model, float>> tmpModel;
    bool hasPlayer = false;
    if (allPath.size() == 0)
        throw ErrorHandling("No or bad path to model");
    for (auto &i: allPath) {
        std::pair<Model, float> tmpPair;
        tmpPair.first = LoadModel(i.first.first.c_str());
        tmpPair.second = i.first.second;
        switch (i.second) {
            case IslandType:
                _islandModel.push_back(tmpPair);
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
    _sky = LoadModel("./gui/assets/models/unreal-engine-4-sky/source/ue4sky.obj");
    Texture2D texture = LoadTexture("./gui/assets/models/unreal-engine-4-sky/textures/T_Sky_Blue.png");
    _sky.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    if (!hasPlayer)
        throw ErrorHandling("No player model");
    if (_allItemModel.size() < 7)
        throw ErrorHandling("Not enough item model");
}

void DisplayGame::placeIsland(int x, int y)
{
    float posX = 0;
    float posY = 0;
    _mapSize.first = x;
    _mapSize.second = y;
    _allIsland.clear();
    for (int i = 0; i < x; i++) {
        posY = 0;
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

void DisplayGame::addItemToIsland(Vector3 position, int type)
{
    _allItem.push_back(_allItemModel.at(type));
    _allItem.back()._itemPosition = setVector3((position.x + 1) * spaceBetwenIsland, 1.8, position.z * spaceBetwenIsland);
    _allItem.back()._itemPosition.x += -3 + (rand() % 6);
    _allItem.back()._itemPosition.z += -3 + (rand() % 6);
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
    int index = 0;
    for (auto &i: _player._allPlayer) {
        Vector3 direction = Vector3Subtract(_camera.target, _camera.position);
        direction = Vector3Normalize(direction);
        Ray ray = {_camera.position, direction};
        index++;

        BoundingBox playerBox = GetMeshBoundingBox(i._playerModel.meshes[0]);
        if (i.isPlayerSelected(playerBox, ray)) {
            _selectedPlayer.first = true;
            _selectedPlayer.second = index;
        }
    }
}

int DisplayGame::getNbrItemTypeOnIsland(Vector3 pos, int type)
{
    int nbr = 0;
    for (auto &i: _allItem) {
        if (Utils::Vec3Comp(i._realPos, pos) && i._itemType == type)
            nbr++;
    }
    return nbr;
}

void DisplayGame::useServerInfo(void)
{
    if (_cmd.getCommandAt("pnw", _newPlayerIndex).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pnw", _newPlayerIndex);
        _player.addPlayerToIsland((Vector3){std::stof(cmd.at(1).c_str()), 1.8, std::stof(cmd.at(2).c_str())}, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation((std::atoi(cmd.at(3).c_str()) - 1) * 90, std::atoi(cmd.at(0).c_str()));
        _player.setPlayerTeam(cmd.at(5), std::atoi(cmd.at(0).c_str()));
        _newPlayerIndex++;
    }
    for (int i = 0; _cmd.getCommandAt("ppo", i).size() > 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ppo", i);
        Vector3 newPos = (Vector3){std::stof(cmd.at(1).c_str()), 1.8, std::stof(cmd.at(2).c_str())};

        if (!Utils::Vec3Comp(newPos, _player.getPlayerRealPos(std::atoi(cmd.at(0).c_str()))))
            _player.moovePlayerToIsland(newPos, std::atoi(cmd.at(0).c_str()));
        _player.changePlayerOrientation((std::atoi(cmd.at(3).c_str()) - 1) * 90, std::atoi(cmd.at(0).c_str()));
    }
    if (!_cmd.getCommandAt("msz", 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt("msz", 0);

        std::pair<int, int> mapSize;
        mapSize.first = std::atoi(cmd.at(0).c_str());
        mapSize.second = std::atoi(cmd.at(1).c_str());
        if (mapSize.first != _mapSize.first || mapSize.second != _mapSize.second)
            placeIsland(mapSize.first, mapSize.second);
    }
    for (int i = 0; _cmd.getCommandAt("bct", i).size() > 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("bct", i);
        float x = std::stof(cmd.at(0).c_str());
        float z = std::stof(cmd.at(1).c_str());
        Vector3 itemPosition = (Vector3){x, 1.8, z};
        for (std::size_t j = 2; j < cmd.size(); j++) {
            int nbItem = std::atoi(cmd.at(j).c_str());
            if (nbItem == getNbrItemTypeOnIsland(itemPosition, j - 2))
                continue;
            for (int k = 0; k < nbItem; k++) {
                addItemToIsland(itemPosition, j - 2);
            }
        }
    }
    for (int i = 0; _cmd.getCommandAt("pdi", _playerLevelIndex).size() >= 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("pdi", _playerLevelIndex);
        std::cout << "Player " << cmd.at(0) << " is dead !" << std::endl;
        _playerLevelIndex += 1;
    }
    for (int i = 0; _cmd.getCommandAt("ebo", _playerEboIndex).size() >= 1; i++) {
        std::vector<std::string> cmd = _cmd.getCommandAt("ebo", _playerEboIndex);
        std::cout << "There is " << cmd.at(0) << " Egg(s) !" << std::endl;
        _playerEboIndex += 1;
    }
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

    for (auto &i: _allItem) {
        i.changeItemAnim();
        i.drawItem();
    }
    _player.drawPlayer(_camera.position);

    for (auto &i: _allIsland) {
        DrawModel(i._islandModel , i._islandPosition, i._islandSize, WHITE);
    }

    EndMode3D();
}

void DisplayGame::display2D(void)
{
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
}

void DisplayGame::launchGame(void)
{
    DisableCursor();

    SetTargetFPS(60);
    float seconds = 0.0f;
    while (!WindowShouldClose()) {
        useServerInfo();
        seconds += (GetFrameTime() / 2);

        SetShaderValue(_waterShader, _secondLoc, &seconds, SHADER_UNIFORM_FLOAT);
        updateCamera();

        BeginDrawing();

        ClearBackground(BLANK);

        display3D();
        display2D();

        EndDrawing();
    }
}
