/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllItem
*/

#include "AllItem.hpp"

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
                _allItem.back().setModel(model[j - 2]);
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
