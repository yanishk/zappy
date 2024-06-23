/*
** EPITECH PROJECT, 2024
** zappy_gui_merge_client
** File description:
** Item
*/

#ifndef ITEM_HPP_
    #define ITEM_HPP_

    #include "Render.hpp"
    #include "Commands.hpp"

    #define MAX_ROTATION 360
    #define LOWEST_POINT 1.5
    #define HIGHTEST_POINT 2
    #define ALTITUDE_SPEED -0.005
    #define ITEM_ALTITUDE 1.8
    #define RAND_RANGE 6

namespace Zappy {

    class Item : public ILoadAndRenderObj {

        public:

            Item();

            Vector2 getRealPosition(void);
            void render() override;
            void setModel(std::pair<Model, float> model) override;
            void setItemPosAndType(Vector2 pos, int type);
            int getType(void);

        private:

            Model _itemModel;
            Vector2 _realPos;
            Vector3 _itemPosition;
            void changeItemAnim(void);
            int _itemType;

            float _itemSize;
            float _rotation;
            float _upValue;
    };
}

#endif /* !ITEM_HPP_ */
