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

class ParsesModelConfig {
    public:
        std::vector<std::pair<std::pair<std::string, float>, int>> parsesFile(std::string path);
    private:
        enum ModelType
        {
            Error = 0,
            Item = 1,
            Island = 2,
            Player = 3
        };
        void parsePathModel(std::string &line);
        void parseSizeModel(std::string &line);
        void parseTypeModel(std::string &line);

        std::vector<float> _sizeList;
        std::vector<std::string> _pathList;
        std::vector<int> _typeList;
        std::vector<std::pair<std::pair<std::string, float>, int>> _parsedInfo;
};

#endif /* !PARSESMODELCONFIG_HPP_ */
