/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Vector3 position)
{
    _playerHight = 1.1;
    _realPos = position;
    _playerPosition = (Vector3){(position.x + 1) * spaceBetwenIsland, 1.1, position.z * spaceBetwenIsland};
    _playerPosition.x += -2 + (rand() % 4);
    _playerPosition.z += -2 + (rand() % 4);
    _isMooving = false;
    _rotationAngle = 0;
}

void Player::DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float scale, Color tint)
{
    int index = GetGlyphIndex(font, codepoint);

    Rectangle srcRec = {
        font.recs[index].x - (float)font.glyphPadding,
        font.recs[index].y - (float)font.glyphPadding,
        font.recs[index].width + 2.0f*font.glyphPadding,
        font.recs[index].height + 2.0f*font.glyphPadding
    };

    float width = (float)(font.recs[index].width + 2.0f * font.glyphPadding) / (float)font.baseSize*scale;
    float height = (float)(font.recs[index].height + 2.0f * font.glyphPadding) / (float)font.baseSize*scale;

    if (font.texture.id > 0) {
        const float x = 0.0f;
        const float y = 0.0f;
        const float z = 0.0f;

        const float tx = srcRec.x / font.texture.width;
        const float ty = srcRec.y / font.texture.height;
        const float tw = (srcRec.x + srcRec.width) / font.texture.width;
        const float th = (srcRec.y + srcRec.height) / font.texture.height;

        rlCheckRenderBatchLimit(4);
        rlSetTexture(font.texture.id);
        rlPushMatrix();
            rlTranslatef(position.x, position.y, position.z);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);

                rlTexCoord2f(tx, ty);
                rlVertex3f(x, y, z);

                rlTexCoord2f(tx, th);
                rlVertex3f(x, y, z + height);

                rlTexCoord2f(tw, th);
                rlVertex3f(x + width, y, z + height);

                rlTexCoord2f(tw, ty);
                rlVertex3f(x + width, y, z);

            rlEnd();
        rlPopMatrix();
        rlSetTexture(0);
    }
}

void Player::DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, Color tint)
{
    int length = TextLength(text);

    float textOffsetY = 0.0f;
    float textOffsetX = 0.0f;

    float scale = fontSize / (float)font.baseSize;
    int codepointByteCount = 0;

    for (int i = 0; i < length; i++) {
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        if (codepoint == '\n') {
            textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
            textOffsetX = 0.0f;
            continue;
        }
        if ((codepoint != ' ') && (codepoint != '\t'))
            DrawTextCodepoint3D(font, codepoint, (Vector3){ position.x + textOffsetX, position.y, position.z + textOffsetY }, scale, tint);

        if (font.glyphs[index].advanceX == 0)
            textOffsetX += (float)(font.recs[index].width + fontSpacing) / (float)font.baseSize*scale;
        else
            textOffsetX += (float)(font.glyphs[index].advanceX + fontSpacing) / (float)font.baseSize*scale;
    }
}

void Player::displayPlayerInfo(Vector3 camPosition)
{
    Font font = GetFontDefault();
    Vector3 cameraToText = Vector3Subtract(camPosition, _playerPosition);
    cameraToText.y = 0.0f;

    float angle = atan2f(cameraToText.x, cameraToText.z) * RAD2DEG;

    std::string textToDisplay;
    textToDisplay.append("Level : ");
    textToDisplay.append(std::to_string(_level));
    textToDisplay.append("\nTeam : ");
    textToDisplay += _team;

    rlPushMatrix();
        rlTranslatef(_playerPosition.x, _playerPosition.y + 3, _playerPosition.z);
        rlRotatef(angle, 0.0f, 1.0f, 0.0f);
        rlRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        DrawText3D(font, textToDisplay.c_str(), (Vector3){ 0.0f, 0.0f, 0.0f }, 3.0f, 0.5f, -1.0f, _playerColor);
    rlPopMatrix();
    UnloadFont(font);
}

void Player::setTeam(std::string team)
{
    _team = team;
}

std::string Player::getTeam(void)
{
    return _team;
}

void Player::setPlayerColor(void)
{
    int code = 0;
    for (std::size_t i = 0; i < _team.size(); i++) {
        code += _team.at(i);
    }
    code = code % MAX_RGB;
    _playerColor.a = MAX_RGB;
    _playerColor.r = code;
    _playerColor.g = code;
    _playerColor.b = code;
}

Vector3 Player::getPosition()
{
    if (!_isMooving)
        return _playerPosition;
    float dist = Vector2Distance((Vector2){_playerPosition.x, _playerPosition.z}, (Vector2){_destPosition.x, _destPosition.z});
    if (dist < 1) {
        _playerPosition = _destPosition;
        _isMooving = false;
        return _playerPosition;
    }
    float x = _playerPosition.x - _destPosition.x;

    float mooveSpeed = 0.5;

    if (x < 0)
        _playerPosition.x += mooveSpeed;
    else if (x > 0)
        _playerPosition.x -= mooveSpeed;

    float z = _playerPosition.z - _destPosition.z;

    if (z < 0)
        _playerPosition.z += mooveSpeed;
    else if (z > 0)
        _playerPosition.z -= mooveSpeed;


    if (dist > _distanceBetweenPos / 2)
        _playerPosition.y += mooveSpeed / 2;
    else if (dist < _distanceBetweenPos / 2 && dist > 0)
        _playerPosition.y -= mooveSpeed / 2;

    return _playerPosition;
}

void Player::moovePlayerToIsland(Vector3 position)
{
    _realPos = position;
    _destPosition = (Vector3){(position.x + 1) * spaceBetwenIsland, _playerHight, position.z * spaceBetwenIsland};
    _destPosition.x += -2 + (rand() % 4);
    _destPosition.z += -2 + (rand() % 4);
    _isMooving = true;
    _distanceBetweenPos = Vector3Distance(_playerPosition, _destPosition);
}

Vector3 Player::RotatePointAroundY(Vector3 point)
{
    float angle = DEG2RAD * _rotationAngle;
    float cosAngle = cosf(-angle);
    float sinAngle = sinf(-angle);
    return (Vector3){
        point.x * cosAngle - point.z * sinAngle,
        point.y,
        point.x * sinAngle + point.z * cosAngle
    };
}

BoundingBox Player::UpdateBoundingBox(BoundingBox box, Vector3 position)
{
    Vector3 corners[8] = {
        {box.min},
        {box.min.x, box.min.y, box.max.z},
        {box.min.x, box.max.y, box.min.z},
        {box.min.x, box.max.y, box.max.z},
        {box.max.x, box.min.y, box.min.z},
        {box.max.x, box.min.y, box.max.z},
        {box.max.x, box.max.y, box.min.z},
        {box.max}
    };

    for (int i = 0; i < 8; i++) {
        corners[i] = Vector3Add(position, RotatePointAroundY(corners[i]));
    }

    BoundingBox transformedBBox = { corners[0], corners[0] };
    for (int i = 1; i < 8; i++) {
        if (corners[i].x < transformedBBox.min.x)
            transformedBBox.min.x = corners[i].x;
        if (corners[i].y < transformedBBox.min.y)
            transformedBBox.min.y = corners[i].y;
        if (corners[i].z < transformedBBox.min.z)
            transformedBBox.min.z = corners[i].z;

        if (corners[i].x > transformedBBox.max.x)
            transformedBBox.max.x = corners[i].x;
        if (corners[i].y > transformedBBox.max.y)
            transformedBBox.max.y = corners[i].y;
        if (corners[i].z > transformedBBox.max.z)
            transformedBBox.max.z = corners[i].z;
    }

    return transformedBBox;
}

bool Player::isPlayerSelected(BoundingBox playerBox, Ray ray)
{
    playerBox = UpdateBoundingBox(playerBox, _playerPosition);

    DrawBoundingBox(playerBox, RED);
    if (GetRayCollisionBox(ray, playerBox).hit)
        return true;
    return false;
}

void Player::displayInfo2D(int x, int y)
{
    std::string text;
    text.append("Player ID : ");
    text.append(std::to_string(_playerID));
    text.append("\nPlayer level : ");
    text.append(std::to_string(_level));
    text.append("\nPlayer Team : ");
    text += _team;
    text.append("\nPlayer inventory : ");
    text.append("\nPlayer position : x ");
    text.append(std::to_string((int)_playerPosition.x));
    text.append(" y ");
    text.append(std::to_string((int)_playerPosition.y));
    text.append(" z ");
    text.append(std::to_string((int)_playerPosition.z));
    text.append("\ncolor : r ");
    text.append(std::to_string(_playerColor.r));
    text.append(" g ");
    text.append(std::to_string(_playerColor.g));
    text.append(" b ");
    text.append(std::to_string(_playerColor.b));
    text.append("\nis alive : ");
    if (isAlive)
        text.append("true");
    else
        text.append("false");
    DrawText(text.c_str(), x, y, 20, BLUE);
}
