/*
** EPITECH PROJECT, 2024
** zappy_gui_merge_client
** File description:
** Item
*/

#include "Item.hpp"

Item::Item() : _rotation(0), _upValue(ALTITUDE_SPEED)
{
}

void Item::changeItemAnim(void)
{
    _rotation += 1;
    if (_rotation > MAX_ROTATION)
        _rotation = 0;
    _itemPosition.y += _upValue;
    if (_itemPosition.y <= LOWEST_POINT || _itemPosition.y >= HIGHTEST_POINT)
        _upValue *= -1;
    _itemModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 0, DEG2RAD * _rotation, DEG2RAD * 0});
}

void Item::render()
{
    changeItemAnim();
    DrawModel(_itemModel , _itemPosition, _itemSize, WHITE);
}

void Item::setModel(std::pair<Model, float> model)
{
    _itemModel = model.first;
    _itemSize = model.second;
}

void Item::setItemPosAndType(Vector2 pos, int type)
{
    _itemType = type;
    _realPos = pos;
    _itemPosition = (Vector3){(pos.x + 1) * spaceBetwenIsland, ITEM_ALTITUDE, pos.y * spaceBetwenIsland};
    _itemPosition.x += -(RAND_RANGE / 2) + (rand() % RAND_RANGE);
    _itemPosition.z += -(RAND_RANGE / 2) + (rand() % RAND_RANGE);
}

Vector2 Item::getRealPosition(void)
{
    return _realPos;
}

int Item::getType(void)
{
    return _itemType;
}
