/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_
    #include <string>
    #include "raylib.h"
    #include "raymath.h"
    #include "rlgl.h"

    #define spaceBetwenIsland 12

class Utils {
    public:
        static bool Vec3Comp(Vector3 vec1, Vector3 vec2)
        {
            if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
                return true;
            return false;
        }
};

class ErrorHandling : public std::exception {
    public:
        ErrorHandling(std::string errorMsg) : _errorMessage(errorMsg) {};

        const char *what() const noexcept
        {
            return _errorMessage.c_str();
        };
    private:
        std::string _errorMessage;
};

#endif /* !UTILS_HPP_ */
