/*
** EPITECH PROJECT, 2024
** Commands management
** File description:
** Zap Proj
*/

#ifndef COMMANDMANAGER_H
    #define COMMANDMANAGER_H
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
    #define SMG_CMD "smg"
    #define EDI_CMD "edi"
    #define PIE_CMD "pie"
    #define SEG_CMD "seg"
    #define PARAMS_ERROR_MSG "Need 2 paramaters at least."
    #define INVALID_IDX "Invalid Index."
    #define EMPTY_MAP_MESSAGE "The vector of vectors at this key is already empty."
    #define BAD_CMD_MAP "This key does not exist in the map."
    #include <string>
    #include <vector>
    #include <mutex>
    #include <asio.hpp>
    #include <unordered_map>

namespace Zappy {

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

            std::unordered_map<std::string, std::vector<std::vector<std::string>>> getMap();
            std::vector<std::string> getCommandAt(const std::string &cmd, std::size_t index);
            std::string getCommandInfoAt(const std::string& cmd,
                std::size_t vectorIndex, std::size_t elementIndex);

            void eraseFirstCmdInMap(const std::string &cmd);

            // fill for GUI

            void fillMapPlayerInfos(const std::string &cmd, const std::vector<std::string> &params);
            void fillMapIsland(const std::string &cmd, const std::vector<std::string> &params);

        private:

            std::vector<std::vector<std::string>> _bctCmd;
            std::vector<std::vector<std::string>> _smgCmd;
            std::vector<std::vector<std::string>> _mszCmd;
            std::vector<std::vector<std::string>> _tnaCmd;


            std::vector<std::vector<std::string>> _ppoCmd;
            std::vector<std::vector<std::string>> _plvCmd;
            std::vector<std::vector<std::string>> _pinCmd;
            std::vector<std::vector<std::string>> _pnwCmd;
            std::vector<std::vector<std::string>> _pdiCmd;
            std::vector<std::vector<std::string>> _pdrCmd;
            std::vector<std::vector<std::string>> _pgtCmd;
            std::vector<std::vector<std::string>> _pbcCmd;
            std::vector<std::vector<std::string>> _picCmd;
            std::vector<std::vector<std::string>> _pieCmd;
            std::vector<std::vector<std::string>> _pexCmd;


            std::vector<std::vector<std::string>> _sgtCmd;
            std::vector<std::vector<std::string>> _sstCmd;
            std::vector<std::vector<std::string>> _segCmd;

            std::vector<std::vector<std::string>> _eboCmd;
            std::vector<std::vector<std::string>> _enwCmd;
            std::vector<std::vector<std::string>> _ediCmd;

            std::vector<std::string> _sentCommands;
            std::vector<std::string> _receivedResponses;

            std::unordered_map<std::string, std::vector<std::vector<std::string>>> _cmdMap {

                {MSZ_CMD, _mszCmd},
                {BCT_CMD, _bctCmd},
                {TNA_CMD, _tnaCmd},
                {PLV_CMD, _plvCmd},
                {PIN_CMD, _plvCmd},
                {PNW_CMD, _pnwCmd},
                {PDI_CMD, _pdiCmd},
                {PPO_CMD, _ppoCmd},
                {PDR_CMD, _pdrCmd},
                {PGT_CMD, _pgtCmd},
                {SST_CMD, _sstCmd},
                {SGT_CMD, _sgtCmd},
                {EBO_CMD, _eboCmd},
                {PEX_CMD, _pexCmd},
                {PBC_CMD, _pbcCmd},
                {PIC_CMD, _picCmd},
                {ENW_CMD, _enwCmd},
                {SMG_CMD, _smgCmd},
                {EDI_CMD, _ediCmd},
                {PIE_CMD, _pieCmd},
                {SEG_CMD, _segCmd},

            };

            mutable std::mutex _mutex;
    };
}

#endif