/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AIFactory
*/

#ifndef AIFACTORY_HPP_
    #define AIFACTORY_HPP_

    #include <string>
    #include <unordered_map>
    #include <memory>
    #include "IAi.hpp"

    #define CREATE_COMPONENT(AI) [](const std::string name){ return std::make_unique<AI>(name); }

namespace Zappy
{
    
    class AIFactory {
        public:
            AIFactory();
            ~AIFactory() = default;

            std::unique_ptr<IAi> createComponent(const std::string &value);

        private:
            std::unordered_map<std::string, IAi> _table;
    };

}

#endif /* !AIFACTORY_HPP_ */
