/*
** EPITECH PROJECT, 2024
** refacto
** File description:
** Render
*/

#ifndef RENDER_HPP_
    #define RENDER_HPP_

    #include "Utils.hpp"

namespace Zappy {

    class ILoadAndRenderObj {

        public:

            ILoadAndRenderObj() = default;
            virtual ~ILoadAndRenderObj() = default;

            virtual void render() = 0;
            virtual void setModel(std::pair<Model, float>) = 0;
    };
}

#endif /* !RENDER_HPP_ */