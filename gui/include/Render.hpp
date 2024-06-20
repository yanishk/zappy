/*
** EPITECH PROJECT, 2024
** refacto
** File description:
** Render
*/

#ifndef RENDER_HPP_
    #define RENDER_HPP_

    #include "Utils.hpp"

class LoadAndRender {

    public:

        LoadAndRender() = default;
        virtual ~LoadAndRender() = default;

        virtual void render() = 0;
        virtual void fillModel(std::pair<Model, float>) = 0;
};

#endif /* !RENDER_HPP_ */