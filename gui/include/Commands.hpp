/*
** EPITECH PROJECT, 2024
** Commands management
** File description:
** Zap Proj
*/

#ifndef COMMANDMANAGER_H
    #define COMMANDMANAGER_H

    #include <string>
    #include <vector>
    #include <mutex>
    #include <asio.hpp>
    #include <unordered_map>

class CommandManager {

    public:

        CommandManager();
        void sendCommand(const std::string &command);
        void receiveResponse(const std::string &response);

        // a bit of parsing

        bool replaceOrAddPlayerInfos(std::vector<std::vector<std::string>> &cmdList,
            const std::vector<std::string> &params);
        bool replaceOrAdd(std::vector<std::vector<std::string>> &cmdList,
            const std::vector<std::string> &params);
        std::vector<std::string> strToVec(const std::string &input, char token);

        // get

        std::vector<std::string> getSentCommands() const;
        std::vector<std::string> getReceivedResponses() const;
        std::vector<std::vector<std::string>> getMszCmd() const;

        std::unordered_map<std::string, std::vector<std::vector<std::string>>> getMap();
        std::vector<std::string> getCommandAt(const std::string &cmd, std::size_t index);
        std::string getCommandInfoAt(const std::string& cmd,
            std::size_t vectorIndex, std::size_t elementIndex);

        void fillMapPlayerInfos(const std::string &cmd, std::vector<std::vector<std::string>> &cmdVec,
            const std::vector<std::string> &params);
        void fillMapIsland(const std::string &cmd, std::vector<std::vector<std::string>> &cmdVec,
            const std::vector<std::string> &params);
        std::vector<std::vector<std::string>> _bctCmd;

    private:

        // map for GUI

        std::unordered_map<std::string, std::vector<std::vector<std::string>>> _cmdMap;

        // Data from Serv

        std::vector<std::vector<std::string>> _mszCmd; // CORE
        std::vector<std::vector<std::string>> _tnaCmd;


        std::vector<std::vector<std::string>> _ppoCmd;
        std::vector<std::vector<std::string>> _plvCmd;
        std::vector<std::vector<std::string>> _pinCmd; // Player info
        std::vector<std::vector<std::string>> _pnwCmd;
        std::vector<std::vector<std::string>> _pdiCmd;
        std::vector<std::vector<std::string>> _pdrCmd;
        std::vector<std::vector<std::string>> _pgtCmd;


        std::vector<std::vector<std::string>> _sgtCmd;
        std::vector<std::vector<std::string>> _smgCmd; // time part
        std::vector<std::vector<std::string>> _sstCmd;

        std::vector<std::vector<std::string>> _eboCmd; // egg part

        std::vector<std::string> _sentCommands;
        std::vector<std::string> _receivedResponses;
        mutable std::mutex _mutex;
};

#endif