/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Order
*/

#ifndef ORDER_HPP_
    #define ORDER_HPP_

    #include <map>
    #include "Ressources.hpp"

namespace Zappy
{

    class Order {
        public:
            Order(int levelToReach, Ressources ressourcesNeeded):
                _levelToReach(levelToReach), _ressourcesNeeded(ressourcesNeeded)
                {}

            int getLevel() const {
                return _levelToReach;
            }

            void setLevel(int levelToReach) {
                _levelToReach = levelToReach;
            }

            Ressources getRessources() const {
                return _ressourcesNeeded;
            }

            int &operator[](const std::string &value) {
                return _ressourcesNeeded[value];
            }

            bool empty() {
                return _ressourcesNeeded.empty();
            }

            bool removeRessources(const std::string &ressource, int value) {
                return _ressourcesNeeded.removeRessources(ressource, value);
            }

            void setRessources(const Ressources &ressource) {
                _ressourcesNeeded = ressource;
            }

            Ressources getLevelRessources(int level) {
                std::map<int, Ressources> ressourcesForLevel {
                    {1, Ressources(1, 0, 0, 0, 0, 0)},
                    {2, Ressources(1, 1, 1, 0, 0, 0)},
                    {3, Ressources(2, 0, 1, 0, 2, 0)},
                    {4, Ressources(1, 1, 2, 0, 1, 0)},
                    {5, Ressources(1, 2, 1, 3, 0, 0)},
                    {6, Ressources(1, 2, 3, 0, 1, 0)},
                    {7, Ressources(2, 2, 2, 2, 2, 1)},
                };

                return ressourcesForLevel[level];
            }

        private:
            int _levelToReach;
            Ressources _ressourcesNeeded;

    };

}

#endif /* !ORDER_HPP_ */