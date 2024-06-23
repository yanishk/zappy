/*
** EPITECH PROJECT, 2024
** Sea
** File description:
** Sea
*/

#include "Sea.hpp"

Zappy::Sea::Sea()
{
    _seconds = 0.0;
    _seaShader = LoadShader(0, TextFormat(SEA_SHADER, SHADER_FORMAT));

    _seaSecondLoc = GetShaderLocation(_seaShader, SHADER_SECONDS);
    int freqXLoc = GetShaderLocation(_seaShader, SHADER_FREQX);
    int freqYLoc = GetShaderLocation(_seaShader, SHADER_FREQY);
    int ampXLoc = GetShaderLocation(_seaShader, SHADER_AMPX);
    int ampYLoc = GetShaderLocation(_seaShader, SHADER_AMPY);
    int speedXLoc = GetShaderLocation(_seaShader, SHADER_SPEEDX);
    int speedYLoc = GetShaderLocation(_seaShader, SHADER_SPEEDY);

    float freqX = VALUE_SHADER_FREQX;
    float freqY = VALUE_SHADER_FREQY;
    float ampX = VALUE_SHADER_AMPX;
    float ampY = VALUE_SHADER_AMPY;
    float speedX = VALUE_SHADER_SPEEDX;
    float speedY = VALUE_SHADER_SPEEDY;

    float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(_seaShader, GetShaderLocation(_seaShader, SHADER_SIZE), &screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(_seaShader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_seaShader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_seaShader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_seaShader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_seaShader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_seaShader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    Texture2D texture = LoadTexture(SEA_TEXTURE);
    _seaModel = LoadModelFromMesh(GenMeshPlane(SEA_SIZE, SEA_SIZE, SEA_RESXZ, SEA_RESXZ));
    _seaModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _seaModel.materials[0].shader = _seaShader;
}

void Zappy::Sea::render()
{
    BeginShaderMode(_seaShader);
        DrawModel(_seaModel, _subSeaPosition, 1, WHITE);
        DrawModel(_seaModel, _seaPosition, 1, WHITE);
    EndShaderMode();
}

void Zappy::Sea::setSeaPos(Vector3 camera, std::pair<int, int> mapSize)
{
    _seconds += GetFrameTime() / 2;
    SetShaderValue(_seaShader, _seaSecondLoc, &_seconds, SHADER_UNIFORM_FLOAT);
    _subSeaPosition = Utils::Vec3(camera.x, SUB_SEA_ALTITUDE, camera.z);
    _seaPosition = Utils::Vec3((mapSize.first * spaceBetwenIsland) / 2,
        SEA_ALTITUDE, (mapSize.second * spaceBetwenIsland) / 2);
}

void Zappy::Sea::setModel(std::pair<Model, float> model)
{
    _seaModel = model.first;
    _seaSize = model.second;
}