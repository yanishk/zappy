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

class Item : public LoadAndRender {
    public:
        void render() override;
        void fillModel(std::pair<Model, float> model) override;
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

        float _rotation = 0;
        float _upValue = ALTITUDE_SPEED;
};

class AllItem {
    public:
        AllItem(CommandManager &cmd);

        void setAllItem(std::vector<std::pair<Model, float>> model);
        void renderAll(void);
        std::size_t getTotalNbrItem(void);
        Vector2 getItemRealPosition(int i);
        int getItemType(int i);
    private:
        CommandManager &_cmd;
        std::vector<Item> _allItem;

        void removeItem(Vector2 pos, int type);
        int getNbrItemAtPos(Vector2 pos, int type);
};

#endif /* !ITEM_HPP_ */
