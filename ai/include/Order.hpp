/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Order
*/

#ifndef ORDER_HPP_
    #define ORDER_HPP_

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

            Ressources getRessources() const {
                return _ressourcesNeeded;
            }

            int operator[](const std::string &value) {
                return _ressourcesNeeded[value];
            }

            bool empty() {
                return _ressourcesNeeded.empty();
            }

            bool removeRessources(const std::string &ressource, int value) {
                return _ressourcesNeeded.removeRessources(ressource, value);
            }

        private:
            int _levelToReach;
            Ressources _ressourcesNeeded;

    };

}

#endif /* !ORDER_HPP_ */