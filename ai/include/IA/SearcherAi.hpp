/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** SearcherAi
*/

#ifndef SEARCHERAI_HPP_
    #define SEARCHERAI_HPP_

    #include "AAi.hpp"

namespace Zappy
{
    
    class SearcherAi : public AAi {

        public:

            bool forward() const;
            bool right() const;
            bool left() const;
            std::vector<std::string> look() const;
            std::vector<std::string> inventory() const;
            bool broadcastText() const;
            size_t connectNumber() const;
            bool fork() const;
            bool eject() const;
            bool takeObject() const;
            bool setObject() const;
            bool incantation() const;

        private:

    };

}

#endif /* !SEARCHERAI_HPP_ */
