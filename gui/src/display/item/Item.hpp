/*
** EPITECH PROJECT, 2024
** zappy_gui_merge_client
** File description:
** Item
*/

#ifndef ITEM_HPP_
    #define ITEM_HPP_

    #include "Utils.hpp"
    #include "Render.hpp"
    #include "Commands.hpp"

    #define MAX_ROTATION 360
    #define LOWEST_POINT 1.5
    #define HIGHTEST_POINT 2
    #define ALTITUDE_SPEED -0.005
    #define ITEM_ALTITUDE 1.8
    #define RAND_RANGE 6

class Item : public ILoadAndRender {
    public:
        Item();
        void render() override;
        void setModel(std::pair<Model, float> model) override;
        void setItemPosAndType(Vector2 pos, int type);
        Vector2 getRealPosition(void);
        int getType(void);


    private:
        void changeItemAnim(void);
        Model _itemModel;
        Vector2 _realPos;
        Vector3 _itemPosition;
        float _itemSize;
        int _itemType;

        float _rotation;
        float _upValue;
};

#endif /* !ITEM_HPP_ */
