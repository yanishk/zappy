/*
** EPITECH PROJECT, 2024
** zappy_gui_merge_client
** File description:
** Item
*/

#ifndef ITEM_HPP_
    #define ITEM_HPP_

    #include "Utils.hpp"

    #define MAX_ROTATION 360
    #define LOWEST_POINT 1.5
    #define HIGHTEST_POINT 2
    #define ALTITUDE_SPEED -0.005

class Item {
    public:
        Item();
        Model _itemModel;
        Vector3 _itemPosition;
        float _itemSize;
        int _itemType;
        Vector3 _realPos;

        void changeItemAnim(void);
        void drawItem(void);
    private:
        float _rotation;
        float _upValue;
};

#endif /* !ITEM_HPP_ */
