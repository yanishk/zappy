/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Vector2 position, bool isAnimated)
{
    _realPos = position;
    _playerPosition = (Vector3){(position.x + 1) * spaceBetwenIsland, 1.1, position.y * spaceBetwenIsland};
    _playerPosition.x += -2 + (std::rand() % 4);
    _playerPosition.z += -2 + (std::rand() % 4);
    _isMooving = false;
    _isTimerStart = false;
    _rotationAngle = 0;
    for (std::size_t i = 0; i < NBR_ITEM; i++) {
        _inventory.push_back(0);
    }
    _infoBackground = LoadModelFromMesh(GenMeshPlane(2, 0.7, 2, 2));
    _isIncantation = false;
    _speedX = (float)((std::rand() % 100) - 50) / 50;
    _speedY = (float)((std::rand() % 200) - 100) / 100;
    _speedZ = (float)((std::rand() % 100) - 50) / 50;
    if (_speedY < _speedX || _speedY < _speedZ)
        _speedY += (_speedX + _speedZ) / 2;
    _incantAngle = (Vector3){_speedX, _speedY, -90};
    _isAnimated = isAnimated;
}

void Player::render()
{
    if (!_isAnimated) {
        DrawModel(_playerModel , getPosition(), _playerSize, WHITE);
        return;
    }
    _animFrameCounter++;
    if (_animFrameCounter >= _playerAnimation[0].frameCount)
        _animFrameCounter = 0;
    UpdateModelAnimation(_playerModel, _playerAnimation[0], _animFrameCounter);
    DrawModelEx(_playerModel , getPosition(), (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){_playerSize, _playerSize, _playerSize}, WHITE);
}

void Player::fillModel(std::pair<Model, float> model)
{
    _playerModel = model.first;
    _playerSize = model.second;
}

void Player::setPlayerAnimation(ModelAnimation *playerAnimation)
{
    _playerAnimation = playerAnimation;
}

void Player::setIncantModel(Model incantModel)
{
    _incantationModel = incantModel;
}
void Player::setEjectModel(Model ejectModel)
{
    _expulsionModel = ejectModel;
}

void Player::setPlayerID(int ID)
{
    _playerID = ID;
}

int Player::getPlayerID(void)
{
    return _playerID;
}

void Player::setPlayerPos(Vector2 pos)
{
    if (Utils::Vec2Comp(pos, _realPos))
        return;
    _realPos = pos;
    _destPosition = (Vector3){(pos.x + 1) * spaceBetwenIsland, PLAYER_HIGHT, pos.y * spaceBetwenIsland};
    _destPosition.x += -2 + (rand() % 4);
    _destPosition.z += -2 + (rand() % 4);
    _isMooving = true;
    _distanceBetweenPos = Vector3Distance(_playerPosition, _destPosition);
}

void Player::setPlayerDirection(int direction)
{
    _playerModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 0, DEG2RAD * (-direction * 90), DEG2RAD * 0});
    _rotationAngle = direction * 90;
    _playerOrientation = direction;
}

void Player::setLevel(int level)
{
    _level = level;
}

int Player::getLevel(void)
{
    return _level;
}


void Player::setTeam(std::string team)
{
    _team = team;
}

std::string Player::getTeam(void)
{
    return _team;
}

void Player::setPlayerColor(Color color)
{
    _playerColor = color;
}

void Player::drawMessage(std::string msg, Vector3 camPosition)
{
    if (msg.empty())
        return;
    Font font = GetFontDefault();
    Vector3 cameraToText = Vector3Subtract(camPosition, _playerPosition);
    std::chrono::time_point<std::chrono::system_clock> timer = std::chrono::system_clock::now();
    cameraToText.y = 0.0f;

    float angle = atan2f(cameraToText.x, cameraToText.z) * RAD2DEG;

    rlPushMatrix();
        rlTranslatef(_playerPosition.x, _playerPosition.y + 4, _playerPosition.z);
        rlRotatef(angle, 0.0f, 1.0f, 0.0f);
        rlRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        float decalage = msg.size() * 4;
        decalage /= 40;
        DrawText3D(font, msg.c_str(), (Vector3){-decalage, 0.1f, 0.0f }, 4.0f, 0.5f, -1.0f, _playerColor);
    rlPopMatrix();
    UnloadFont(font);

    if (!_isTimerStart) {
        _startTime = std::chrono::system_clock::now();
        _isTimerStart = true;
        _broadcastMsg = msg;
        float backgroundWight = msg.size() * 9;
        backgroundWight /= 40;
        _broadcastBackground = LoadModelFromMesh(GenMeshPlane(backgroundWight, 0.5, 1, 2));
    }
    if (std::chrono::duration_cast<std::chrono::seconds>(timer - _startTime).count() >= 5) {
        _isTimerStart = false;
        _broadcastMsg.erase();
    }
    _broadcastBackground.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 90, DEG2RAD * 0, DEG2RAD * -angle});
    DrawModel(_broadcastBackground, (Vector3){_playerPosition.x, _playerPosition.y + 3.83f, _playerPosition.z}, 1, Fade(getNegativeColor(_playerColor), 0.5f));
}

void Player::displayInfo2D(int x, int y, std::unique_ptr<AllItem> &_allItem)
{
    std::string text;

    text += "Player ID : " + std::to_string(_playerID) + "\n";
    text += "Player level : " + std::to_string(_level) + "\n";
    text += "Player Team : " + _team + "\n";
    text += "Player position : x " + std::to_string((int)_playerPosition.x) + " y " + std::to_string((int)_playerPosition.y) + " z " + std::to_string((int)_playerPosition.z) + "\n";
    text += "Player real position : x " + std::to_string((int)_realPos.x) + " z " + std::to_string((int)_realPos.y) + "\n";
    text += "Player orientation : " + PLAYER_ORIENTATION.at(_playerOrientation) + "\n";
    text += ("Player inventory :\n| q0 | q1 | q2 | q3 | q4 | q5 | q6 |\n");
    for (std::size_t i = 0; i < NBR_ITEM; i++) {
        text += "|\t" + std::to_string(_inventory[i]) + "\t";
    }
    text += "|\n\n";
    std::vector<int> itemHere;

    for (std::size_t i = 0; i < NBR_ITEM; i++) {
        itemHere.push_back(0);
    }

    text += ("Island Ressources :\n| q0 | q1 | q2 | q3 | q4 | q5 | q6 |\n");
    for (std::size_t i = 0; i < _allItem.get()->getTotalNbrItem(); i++) {
        Vector2 itemPos = _allItem.get()->getItemRealPosition(i);
        if (_realPos.x == itemPos.x && _realPos.y == itemPos.y) {
            itemHere[_allItem.get()->getItemType(i)] += 1;
        }
    }
    for (std::size_t i = 0; i < itemHere.size(); i++) {
        text += "|\t" + std::to_string(itemHere[i]) + "\t";
    }
    text += "|\n";
    DrawText(text.c_str(), x, y, TEXT_SIZE, BLUE);
}

void Player::displayPlayerInfo(Vector3 camPosition)
{
    Font font = GetFontDefault();
    Vector3 cameraToText = Vector3Subtract(camPosition, _playerPosition);
    cameraToText.y = 0.0f;

    float angle = atan2f(cameraToText.x, cameraToText.z) * RAD2DEG;

    std::string textToDisplay;
    textToDisplay.append(TEXT_LEVEL);
    textToDisplay.append(std::to_string(_level));
    textToDisplay.append(TEXT_TEAM);
    textToDisplay += _team;

    rlPushMatrix();
        rlTranslatef(_playerPosition.x, _playerPosition.y + 3, _playerPosition.z);
        rlRotatef(angle, 0.0f, 1.0f, 0.0f);
        rlRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        DrawText3D(font, textToDisplay.c_str(), (Vector3){ -0.9f, 0.1f, 0.0f }, 3.0f, 0.5f, -1.0f, _playerColor);
    rlPopMatrix();
    UnloadFont(font);

    _infoBackground.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 90, DEG2RAD * 0, DEG2RAD * -angle});
    DrawModel(_infoBackground, (Vector3){_playerPosition.x, _playerPosition.y + 2.65f, _playerPosition.z}, 1, Fade(getNegativeColor(_playerColor), 0.5f));

    if (_isTimerStart) {
        drawMessage(_broadcastMsg, camPosition);
    }
}

void Player::setMessage(std::string msg)
{
    _msg = msg;
}

std::string Player::getMessage(void)
{
    std::string msg = _msg;
    _msg.erase();
    return msg;
}

bool Player::isPlayerSelected(BoundingBox playerBox, Ray ray)
{
    playerBox = UpdateBoundingBox(playerBox, _playerPosition);

    DrawBoundingBox(playerBox, RED);
    if (GetRayCollisionBox(ray, playerBox).hit)
        return true;
    return false;
}

void Player::addOrRemoveItem(int itemType, bool addOrRemove)
{
    if (addOrRemove == ADD_ITEM)
        _inventory[itemType] += 1;
    else
        _inventory[itemType] -= 1;
}

std::vector<int> Player::getInventory(void)
{
    return _inventory;
}

void Player::setInventory(std::vector<int> newInv)
{
    for (std::size_t i = 0; i < _inventory.size(); i++) {
        _inventory[i] = newInv[i];
    }
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

Vector2 Player::getRealPos(void)
{
    return _realPos;
}

void Player::enableIncantationMode(Vector2 pos)
{
    _incantPos = pos;
    _isIncantation = true;
}

void Player::disableIncantationMode(void)
{
    _isIncantationExpload = true;
}

Vector2 Player::getIncantationPos(void)
{
    return _incantPos;
}

void Player::drawIncantation(void)
{
    if (!_isIncantation)
        return;
    if (_incantAngle.z > 30 || _incantAngle.z < -30)
        _speedZ = (-_speedZ);
    if (_incantAngle.x > 30 || _incantAngle.x < -30)
        _speedX = (-_speedX);
    _incantAngle.x += _speedX;
    _incantAngle.y += _speedY;
    _incantAngle.z += _speedZ;
    _incantationModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * _incantAngle.x, DEG2RAD * _incantAngle.y, DEG2RAD * _incantAngle.z});
    Vector3 pos = _playerPosition;
    pos.y += 2;
    if (_isIncantationExpload) {
        _incantationSize += 0.01;
        _incantationOpacity -= 0.05;
    }
    if (_incantationSize >= 0.2) {
        _isIncantationExpload = false;
        _isIncantation = false;
        _incantationSize = 0.1;
        _incantationOpacity = 0.5;
    }
    DrawModel(_incantationModel, pos, _incantationSize, Fade(_playerColor, _incantationOpacity));
}

void Player::playerExpulsion(void)
{
    _isExpulsion = true;
    _expulsionSize = 0.1;
    _expulsionOrientation = 0;
}

void Player::drawExpulsion(void)
{
    if (!_isExpulsion)
        return;
    _expulsionModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 0, DEG2RAD * _expulsionOrientation, DEG2RAD * 0});
    _expulsionOrientation += 10;
    Vector3 pos = _playerPosition;
    pos.y += 2;
    _expulsionSize += 0.05;
    if (_expulsionSize >= 0.8) {
        _isExpulsion = false;
    }
    DrawModel(_expulsionModel, pos, _expulsionSize, WHITE);
}

Model Player::getPlayerModel(void)
{
    return _playerModel;
}

//    Fonction in private

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

Color Player::getNegativeColor(Color color)
{
    Color newColor;
    newColor.r = 255 - color.r;
    newColor.g = 255 - color.g;
    newColor.b = 255 - color.b;
    newColor.a = color.a;
    return newColor;
}
