/*
** EPITECH PROJECT, 2024
** zappy_gui_merge_client
** File description:
** Item
*/

#include "Item.hpp"

void Item::changeItemAnim(void)
{
    _rotation += 1;
    if (_rotation > 360)
        _rotation = 0;
    _itemPosition.y += _upValue;
    if (_itemPosition.y <= 1.5 || _itemPosition.y >= 2)
        _upValue *= -1;
    _itemModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0, DEG2RAD*_rotation, DEG2RAD*0});
}

void Item::drawItem(void)
{
    DrawModel(_itemModel , _itemPosition, _itemSize, WHITE);
}
