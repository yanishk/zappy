/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Ressources
*/

#ifndef RESSOURCES_HPP_
    #define RESSOURCES_HPP_

    #define FOOD "food"
    #define LINEMATE "linemate"
    #define DERAUMERE "deraumere"
    #define SIBUR "sibur"
    #define MENDIANE "mendiane"
    #define PHIRAS "phiras"
    #define THYSTAME "thystame"

    #define FOOD_START_VALUE 10
    #define NONE 0

    #include <string>
    #include <unordered_map>

namespace Zappy {

    enum RessourceType {
        Food,
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };

    class Ressources {

        public:

            bool addRessources(const std::string &ressource, int value);
            bool removeRessources(const std::string &ressource, int value);

            void operator+=(const Ressources &other) {

                for (const auto &i: other._ressources) {

                    for (auto &j: _ressources) {
                        if (i.first == j.first) {
                            j.second += i.second;
                        }
                    }

                }

            };

            int getRessource(const std::string &ressource) {
                return _ressources[ressource];
            };

        private:

            std::unordered_map<std::string, int> _ressources {
                { FOOD,         FOOD_START_VALUE },
                { LINEMATE,     NONE },
                { DERAUMERE,    NONE },
                { SIBUR,        NONE },
                { MENDIANE,     NONE },
                { PHIRAS,       NONE },
                { THYSTAME,     NONE }
            };

    };

};


#endif /* !RESSOURCES_HPP_ */
