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
    _cmdMap["msz"] = _mszCmd;
    _cmdMap["bct"] = _bctCmd;
    _cmdMap["tna"] = _tnaCmd;
    _cmdMap["plv"] = _plvCmd;
    _cmdMap["pin"] = _plvCmd;
    _cmdMap["pnw"] = _pnwCmd;
    _cmdMap["pdi"] = _pdiCmd;
    _cmdMap["ppo"] = _ppoCmd;
    _cmdMap["pdr"] = _pdrCmd;
    _cmdMap["pgt"] = _pgtCmd;
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

    if (cmd.compare("msz") == 0) {
        fillMapIsland("msz", _mszCmd, params);
    } else if (cmd.compare("bct") == 0) {
        fillMapIsland("bct", _bctCmd, params);
    } else if (cmd.compare("tna") == 0) {
        fillMapPlayerInfos("tna", _tnaCmd, params);
    } else if (cmd.compare("pnw") == 0) {
        fillMapPlayerInfos("pnw", _pnwCmd, params);
    } else if (cmd.compare("pdi") == 0) {
        fillMapPlayerInfos("pdi", _pdiCmd, params);
    } else if (cmd.compare("plv") == 0) {
        fillMapPlayerInfos("plv", _plvCmd, params);
    } else if (cmd.compare("pin") == 0) {
        fillMapPlayerInfos("pin", _pinCmd, params);
    } else if (cmd.compare("ppo") == 0) {
        fillMapPlayerInfos("ppo", _ppoCmd, params);
    } else if (cmd.compare("pdr") == 0) {
        fillMapPlayerInfos("pdr", _pdrCmd, params);
    } else if (cmd.compare("pgt") == 0) {
        fillMapPlayerInfos("pgt", _pgtCmd, params);
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
        throw std::invalid_argument("params must have at least 2 elements");
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
    throw std::out_of_range("Invalid index");
}

std::string CommandManager::getCommandInfoAt(const std::string &cmd,
    std::size_t vectorIndex, std::size_t elementIndex)
{
    auto it = _cmdMap.find(cmd);

    if (it != _cmdMap.end() && vectorIndex <= it->second.size() &&
        elementIndex < it->second[vectorIndex].size()) {
        return it->second.at(vectorIndex).at(elementIndex);
    }
    throw std::out_of_range("Invalid index");
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