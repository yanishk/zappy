/*
** EPITECH PROJECT, 2024
** zappy_gui_try1
** File description:
** ParsesModelConfig
*/

#ifndef PARSESMODELCONFIG_HPP_
    #define PARSESMODELCONFIG_HPP_

    #include <vector>
    #include <iostream>
    #include <string>
    #include <memory>
    #include <fstream>

    static const std::string ITEM = "Item";
    static const std::string ISLAND = "Island";
    static const std::string PLAYER = "Player";
    static const std::string EGG = "Egg";
    static const std::string SKYM = "SkyM";

using ZappyModel = std::vector<std::pair<std::pair<std::string, float>, int>>;

namespace Zappy {

    class ParsesModelConfig {
        public:
            ZappyModel parsesFile(std::string path);
        private:
            enum ModelType
            {
                Error = 0,
                Item = 1,
                Island = 2,
                Player = 3,
                Egg = 4,
                SkyM = 5,
            };
            void parsePathModel(std::string &line);
            void parseSizeModel(std::string &line);
            void parseTypeModel(std::string &line);

            std::vector<float> _sizeList;
            std::vector<std::string> _pathList;
            std::vector<int> _typeList;
            ZappyModel _parsedInfo;
    };
}

#endif /* !PARSESMODELCONFIG_HPP_ */
