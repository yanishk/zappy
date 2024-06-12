/*
** EPITECH PROJECT, 2024
** Commands file
** File description:
** zap Proj
*/

#include "Commands.hpp"
#include <iostream>

CommandManager::CommandManager()
{
}

void CommandManager::sendCommand(const std::string &command)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _sentCommands.push_back(command);
}

void CommandManager::receiveResponse(const std::string &response)
{
    std::lock_guard<std::mutex> lock(_mutex);

    int token = 3;
    std::string cmd = response.substr(0, token);
    std::vector<std::string> params = strToVec(response.substr(token), ' ');

    std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commandMap = {
        {MSZ_CMD, [this](const std::vector<std::string>& params) {
            fillMapIsland(MSZ_CMD, _mszCmd, params);
            }},
        {BCT_CMD, [this](const std::vector<std::string>& params) {
            fillMapIsland(BCT_CMD, _bctCmd, params);
            }},
        {TNA_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(TNA_CMD, _tnaCmd, params);
            }},
        {PNW_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PNW_CMD, _pnwCmd, params);
            }},
        {PDI_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PDI_CMD, _pdiCmd, params);
            }},
        {PLV_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PLV_CMD, _plvCmd, params);
            }},
        {PIN_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PIN_CMD, _pinCmd, params);
            }},
        {PPO_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PPO_CMD, _ppoCmd, params);
            }},
        {PDR_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PDR_CMD, _pdrCmd, params);
            }},
        {PGT_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(PGT_CMD, _pgtCmd, params);
            }},
        {SST_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(SST_CMD, _sstCmd, params);
            }},
        {SGT_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(SGT_CMD, _sgtCmd, params);
            }},
        {EBO_CMD, [this](const std::vector<std::string> &params) {
            fillMapPlayerInfos(EBO_CMD, _eboCmd, params);
            }},
    };

    auto it = commandMap.find(cmd);
    if (it != commandMap.end()) {
        it->second(params);
    }

    std::cout << response << std::endl;
}


void CommandManager::fillMapPlayerInfos(const std::string &cmd, std::vector<std::vector<std::string>> &cmdVec, const std::vector<std::string> &params)
{
    if (replaceOrAddPlayerInfos(cmdVec, params) == true) {
        _cmdMap[cmd].pop_back();
        _cmdMap[cmd].push_back(params);
        return;
    }

    _cmdMap[cmd].push_back(params);
}

void CommandManager::fillMapIsland(const std::string &cmd, std::vector<std::vector<std::string>> &cmdVec, const std::vector<std::string> &params)
{
    if (replaceOrAdd(cmdVec, params) == true) {
        _cmdMap[cmd].pop_back();
        _cmdMap[cmd].push_back(params);
        return;
    }

    _cmdMap[cmd].push_back(params);
}

bool CommandManager::replaceOrAddPlayerInfos(std::vector<std::vector<std::string>> &cmdList,
    const std::vector<std::string> &params)
{
    for (auto &item : cmdList) {
        if (!item.empty() && item.at(0) == params.at(0)) {
            item = params;
            return true;
        }
    }
    cmdList.push_back(params);

    return false;
}

bool CommandManager::replaceOrAdd(std::vector<std::vector<std::string>> &cmdList,
    const std::vector<std::string> &params)
{
    if (params.size() < 2) {
        throw std::invalid_argument(PARAMS_ERROR_MSG);
    }

    for (auto &item : cmdList) {
        if (item.size() >= 2 && item.at(0) == params.at(0) && item.at(1) == params.at(1)) {
            item = params;
            return true;
        }
    }
    cmdList.push_back(params);

    return false;
}


std::vector<std::string> CommandManager::getSentCommands() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _sentCommands;
}

std::vector<std::string> CommandManager::getReceivedResponses() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _receivedResponses;
}

std::vector<std::vector<std::string>> CommandManager::getMszCmd() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _mszCmd;
}

std::unordered_map<std::string, std::vector<std::vector<std::string>>> CommandManager::getMap()
{
    return _cmdMap;
}

std::vector<std::string> CommandManager::getCommandAt(const std::string &cmd,
    std::size_t index)
{
    auto it = _cmdMap.find(cmd);

    std::vector<std::string> vide;
    if (it != _cmdMap.end() && index < it->second.size()) {
        return it->second.at(index);
    } else {
        return vide;
    }
    throw std::out_of_range(INVALID_IDX);
}

std::string CommandManager::getCommandInfoAt(const std::string &cmd,
    std::size_t vectorIndex, std::size_t elementIndex)
{
    auto it = _cmdMap.find(cmd);

    if (it != _cmdMap.end() && vectorIndex <= it->second.size() &&
        elementIndex < it->second[vectorIndex].size()) {
        return it->second.at(vectorIndex).at(elementIndex);
    }
    throw std::out_of_range(INVALID_IDX);
}

std::vector<std::string> CommandManager::strToVec(const std::string &input, char token)
{
    std::vector<std::string> res;
    std::string tmp;

    for (std::size_t t = 0; t < input.size(); t++) {
        if (input.at(t) == token) {
            if (!tmp.empty()) {
                res.push_back(tmp);
                tmp.clear();
            }

        } else {
            tmp.push_back(input[t]);
        }
    }

    if (!tmp.empty()) {
        res.push_back(tmp);
    }

    return res;
}