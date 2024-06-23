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

    #define MSZ_CMD "msz"
    #define BCT_CMD "bct"
    #define TNA_CMD "tna"
    #define PNW_CMD "pnw"
    #define PDI_CMD "pdi"
    #define PLV_CMD "plv"
    #define PIN_CMD "pin"
    #define PPO_CMD "ppo"
    #define PDR_CMD "pdr"
    #define PGT_CMD "pgt"
    #define SST_CMD "sst"
    #define EBO_CMD "ebo"
    #define SST_CMD "sst"
    #define SGT_CMD "sgt"
    #define PEX_CMD "pex"
    #define PBC_CMD "pbc"
    #define PIC_CMD "pic"
    #define ENW_CMD "enw"
    #define NEW_L "\n"
    #define SPACE_C " "

namespace Zappy {

    class Utils {

        public:

            static bool Vec3Comp(Vector3 vec1, Vector3 vec2)
            {
                if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
                    return true;
                return false;
            }

            static bool Vec2Comp(Vector2 vec1, Vector2 vec2)
            {
                if (vec1.x == vec2.x && vec1.y == vec2.y)
                    return true;
                return false;
            }
            static Vector3 Vec3(float x, float y, float z)
            {
                return (Vector3){x, y, z};
            }

    };
}

namespace Zappy {

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
}

#endif /* !UTILS_HPP_ */
