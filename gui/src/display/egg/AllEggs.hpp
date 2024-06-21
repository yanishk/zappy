/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllEggs
*/

#ifndef ALLEGGS_HPP_
    #define ALLEGGS_HPP_

    #include "Eggs.hpp"

class AllEggs {

    public:

        AllEggs(CommandManager &cmd);

        void setAllEggs(std::pair<Model, float> model);
        void removeEgg(int Id);
        void renderAll(void);

    private:

        CommandManager &_cmd;
        std::vector<Egg> _allEggs;
};

#endif /* !ALLEGGS_HPP_ */
