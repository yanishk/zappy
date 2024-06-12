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

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #define FOOD_START_VALUE 10
    #define NONE 0

    #include <string>
    #include <vector>
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

            int operator[](const std::string &ressource) {
                return _ressources[ressource];
            }

            int getRessource(const std::string &ressource) {
                return _ressources[ressource];
            };

            bool empty() {

                for (const auto &i:_ressources) {
                    if (i.second > 0) {
                        return false;
                    }
                }

                return true;
            }

            std::string indexToRessource(int index);

            std::vector<int> getAllValueRessources();

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