/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllIsland
*/

#ifndef ALLISLAND_HPP_
    #define ALLISLAND_HPP_

    #include "Island.hpp"

    #define CIRCUMFERENCE 360

class AllIsland {

    public:

        AllIsland(CommandManager &cmd);

        void setAllIsland(std::vector<std::pair<Model, float>> model);
        void renderAll(void);

    private:

        CommandManager &_cmd;
        std::vector<Island> _allIsland;

};

#endif /* !ALLISLAND_HPP_ */
