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

void Item::fillModel(std::pair<Model, float> model)
{
    _itemModel = model.first;
    _itemSize = model.second;
}

void Item::setItemPosAndType(Vector2 pos, int type)
{
    _itemType = type;
    _realPos = pos;
    _itemPosition = (Vector3){(pos.x + 1) * spaceBetwenIsland, 1.8, pos.y * spaceBetwenIsland};
    _itemPosition.x += -3 + (rand() % 6);
    _itemPosition.z += -3 + (rand() % 6);
}

Vector2 Item::getRealPosition(void)
{
    return _realPos;
}

int Item::getType(void)
{
    return _itemType;
}



AllItem::AllItem(CommandManager &cmd) : _cmd(cmd)
{

}

void AllItem::removeItem(Vector2 pos, int type)
{
    for (std::size_t i = 0; i < _allItem.size(); i++) {
        Vector2 itemPos = _allItem[i].getRealPosition();
        if (itemPos.x == pos.x && itemPos.y == pos.y && _allItem[i].getType() == type) {
            _allItem.erase(_allItem.begin() + i);
            break;
        }
    }
}

int AllItem::getNbrItemAtPos(Vector2 pos, int type)
{
    int nbr = 0;
    for (auto &i : _allItem) {
        Vector2 itemPos = i.getRealPosition();
        if (itemPos.x == pos.x && itemPos.y == pos.y && i.getType() == type) {
            nbr++;
        }
    }
    return nbr;
}

void AllItem::setAllItem(std::vector<std::pair<Model, float>> model)
{
    while (_cmd.getCommandAt(BCT_CMD, 0).size() > 1) {
        std::vector<std::string> cmd = _cmd.getCommandAt(BCT_CMD, 0);
        float x = std::stof(cmd.front().c_str());
        float y = std::stof(cmd[1].c_str());
        Vector2 itemPosition = (Vector2){x, y};
        for (std::size_t j = 2; j < cmd.size(); j++) {
            int nbItem = std::atoi(cmd[j].c_str());
            int nbItemOnIsland = getNbrItemAtPos(itemPosition, j - 2);
            while (nbItemOnIsland > 0) {
                removeItem(itemPosition, j - 2);
                nbItemOnIsland--;
            }
            for (int k = 0; k < nbItem; k++) {
                Item item;
                _allItem.push_back(item);
                _allItem.back().fillModel(model[j - 2]);
                _allItem.back().setItemPosAndType(itemPosition, j - 2);
            }
        }
        _cmd.eraseFirstCmdInMap(BCT_CMD);
    }
}

void AllItem::renderAll(void)
{
    for (auto &i : _allItem) {
        i.render();
    }
}

std::size_t AllItem::getTotalNbrItem(void)
{
    return _allItem.size();
}

Vector2 AllItem::getItemRealPosition(int i)
{
    return _allItem[i].getRealPosition();
}

int AllItem::getItemType(int i)
{
    return _allItem[i].getType();
}
