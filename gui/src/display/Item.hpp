/*
** EPITECH PROJECT, 2024
** zappy_gui_merge_client
** File description:
** Item
*/

#ifndef ITEM_HPP_
    #define ITEM_HPP_

    #include "Utils.hpp"

class Item {
    public:
        Model _itemModel;
        Vector3 _itemPosition;
        float _itemSize;
        int _itemType;
        Vector3 _realPos;

        void changeItemAnim(void);
        void drawItem(void);
    private:
        float _rotation = 0;
        float _upValue = -0.005;
};

#endif /* !ITEM_HPP_ */
