/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllEggs
*/

#ifndef ALLEGGS_HPP_
    #define ALLEGGS_HPP_

    #include "Eggs.hpp"
    #include "AllObj.hpp"

namespace Zappy {

    class AllEggs : public IAllObj {

        public:

            AllEggs(CommandManager &cmd);

            void setAllElements(std::vector<std::pair<Model, float>> model) override;

            std::size_t getTotalNbrElements(void) override;
            void renderAllElements(void) override;
            void removeEgg(int Id);

        private:

            CommandManager &_cmd;
            std::vector<Egg> _allEggs;
    };
}

#endif /* !ALLEGGS_HPP_ */
