/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

    #define FIRST_LEVEL 1

namespace Zappy {
    
    class Queen : public AAi {

        public:

            Queen(const std::string &port): AAi(port, INITIALIZE_MODE) {};

            int run();

        private:

            bool initialize();

    };

};

#endif /* !SEARCHERAI_HPP_ */
