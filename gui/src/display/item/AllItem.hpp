/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllItem
*/

#ifndef ALLITEM_HPP_
    #define ALLITEM_HPP_

    #include "Item.hpp"
    #include "AllObj.hpp"

namespace Zappy {

    class AllItem : public IAllObj {

        public:

            AllItem(CommandManager &cmd);

            void setAllElements(std::vector<std::pair<Model, float>> model) override;
            void renderAllElements(void) override;
            std::size_t getTotalNbrElements(void) override;

            Vector2 getItemRealPosition(int i);
            int getItemType(int i);

        private:

            CommandManager &_cmd;
            std::vector<Item> _allItem;

            void removeItem(Vector2 pos, int type);
            int getNbrItemAtPos(Vector2 pos, int type);
    };
}

#endif /* !ALLITEM_HPP_ */
