/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllIsland
*/

#ifndef ALLISLAND_HPP_
    #define ALLISLAND_HPP_

    #include "Island.hpp"
    #include "AllObj.hpp"
    #define CIRCUMFERENCE 360

namespace Zappy {

    class AllIsland : public IAllObj {

        public:

            AllIsland(CommandManager &cmd);

            void setAllElements(std::vector<std::pair<Model, float>> model) override;
            void renderAllElements(void) override;
            std::size_t getTotalNbrElements(void) override;

        private:

            CommandManager &_cmd;
            std::vector<Island> _allIsland;

    };
}

#endif /* !ALLISLAND_HPP_ */
