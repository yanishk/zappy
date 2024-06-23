/*
** EPITECH PROJECT, 2024
** all obj file
** File description:
** Zappy proj
*/

#ifndef AllObj
    #define AllObj

    #include "Utils.hpp"
    #include <vector>

namespace Zappy {

    class IAllObj {

        public:

            IAllObj() = default;
            virtual ~IAllObj() = default;

            virtual void renderAllElements(void) = 0;
            virtual void setAllElements(std::vector<std::pair<Model, float>> model) = 0;
            virtual std::size_t getTotalNbrElements(void) = 0;


    };
}

#endif /* !IAllObj */
