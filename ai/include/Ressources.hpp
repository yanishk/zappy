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

    #include <string>
    #include <unordered_map>

namespace Zappy
{
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

            void addRessources(const std::string &ressource, int value);

            void operator+=(const Ressources &other) {

                for (const auto &i: other._ressources) {

                    for (auto &j: _ressources) {
                        if (i.first == j.first) {
                            j.second += i.second;
                        }
                    }

                }

            }

        private:
            std::unordered_map<std::string, int> _ressources {
                                                            { FOOD, 0 },
                                                            { LINEMATE, 0 },
                                                            { DERAUMERE, 0 },
                                                            { SIBUR, 0 },
                                                            { MENDIANE, 0 },
                                                            { PHIRAS, 0 },
                                                            { THYSTAME, 0 }
            };
    };

}


#endif /* !RESSOURCES_HPP_ */
