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
    #include <functional>

    #include "AI/IAi.hpp"

    #define CREATE_COMPONENT(AI) [](const std::string &port){ return std::make_unique<AI>(port); }

    #define QUEEN "Queen"

namespace Zappy {

    using CreateAI = std::function<std::unique_ptr<Zappy::IAi>(const std::string &value)>;

    class AIFactory {

        public:

            std::unique_ptr<Zappy::IAi> createComponent(const std::string &value, const std::string &port);

        private:

            std::unordered_map<std::string, CreateAI> _table;

    };

};

#endif /* !AIFACTORY_HPP_ */
