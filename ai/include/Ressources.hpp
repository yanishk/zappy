/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Ressources
*/

#ifndef RESSOURCES_HPP_
    #define RESSOURCES_HPP_

    #define FOOD                "food"
    #define LINEMATE            "linemate"
    #define DERAUMERE           "deraumere"
    #define SIBUR               "sibur"
    #define MENDIANE            "mendiane"
    #define PHIRAS              "phiras"
    #define THYSTAME            "thystame"
    #define PLAYER              "player"

    #define FOOD_DENSITY        0.5
    #define LINEMATE_DENSITY    0.3
    #define DERAUMERE_DENSITY   0.15
    #define SIBUR_DENSITY       0.1
    #define MENDIANE_DENSITY    0.1
    #define PHIRAS_DENSITY      0.08
    #define THYSTAME_DENSITY    0.05

    #define CINT(ressource) const int ressource

    #define FOOD_START_VALUE 10
    #define NONE 0

    #include <string>
    #include <vector>
    #include <iostream>
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

            Ressources(CINT(linemate), CINT(deraumere), CINT(sibur), CINT(mendiane), CINT(phiras), CINT(thystame))
            {
                _ressources[LINEMATE] = linemate;
                _ressources[DERAUMERE] = deraumere;
                _ressources[SIBUR] = sibur;
                _ressources[MENDIANE] = mendiane;
                _ressources[PHIRAS] = phiras;
                _ressources[THYSTAME] = thystame;
            };

            Ressources() = default;

            bool addRessources(const std::string &ressource, int value);
            bool updateRessources(const std::string &ressource, int value);
            bool removeRessources(const std::string &ressource, int value);

            void operator+=(const Ressources &other)
            {

                for (const auto &i: other._ressources) {

                    for (auto &j: _ressources) {

                        if (i.first == j.first) {
                            j.second += i.second;
                        }

                    }

                }

            };

            int &operator[](const std::string &ressource)
            {
                return _ressources[ressource];
            };

            void dump() {

                std::cerr << "Linemate: " << _ressources[LINEMATE] << "\n";
                std::cerr << "Deraumere: " << _ressources[DERAUMERE] << "\n";
                std::cerr << "Sibur: " << _ressources[SIBUR] << "\n";
                std::cerr << "Mendiane: " << _ressources[MENDIANE] << "\n";
                std::cerr << "Phiras: " << _ressources[PHIRAS] << "\n";
                std::cerr << "Thystame: " << _ressources[THYSTAME] << "\n";

            };

            int getRessource(const std::string &ressource)
            {
                return _ressources[ressource];
            };

            std::unordered_map<std::string, int> getRessources()
            {
                return _ressources;
            }

            bool empty()
            {

                for (const auto &i:_ressources) {

                    if (i.second > 0) {
                        return false;
                    }

                }

                return true;
            };

            std::string indexToRessource(int index);
            std::vector<int> getAllValueRessources();

        private:

            std::unordered_map<std::string, int> _ressources {

                { FOOD,         FOOD_START_VALUE    },
                { LINEMATE,     NONE                },
                { DERAUMERE,    NONE                },
                { SIBUR,        NONE                },
                { MENDIANE,     NONE                },
                { PHIRAS,       NONE                },
                { THYSTAME,     NONE                }

            };

    };

};


#endif /* !RESSOURCES_HPP_ */