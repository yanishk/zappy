/*
** EPITECH PROJECT, 2024
** my_branch_with_timo
** File description:
** UseRecivedCmd
*/

#include "UseRecivedCmd.hpp"

UseRecivedCmd::UseRecivedCmd(CommandManager &cmd, asio::ip::tcp::socket &socket) : _cmd(cmd), _socket(socket)
{
}

void UseRecivedCmd::callAllFunctions(void)
{
    getSgt();
    getSst();
    getSeg();
}

void UseRecivedCmd::getSgt(void)
{
    if (!_cmd.getCommandAt(SGT_CMD, 0).empty()) {
        std::vector<std::string> cmd = _cmd.getCommandAt(SGT_CMD, 0);
        _sgtValue = std::stoi(cmd[0]);
        _cmd.eraseFirstCmdInMap(SGT_CMD);
    }
}

void UseRecivedCmd::getSst(void)
{
    if (IsKeyPressed(KEY_UP)) {
        _sgtValue += SST_CHANGE;
        std::string value = std::to_string(_sgtValue);
        std::string sstCmd = SST_CMD;
        sstCmd += SPACE_C;
        sstCmd += value;
        sstCmd += NEW_L;
        asio::write(_socket, asio::buffer(sstCmd));
    } else if (IsKeyPressed(KEY_DOWN)) {
        _sgtValue -= SST_CHANGE;
        std::string value = std::to_string(_sgtValue);
        std::string sstCmd = SST_CMD;
        sstCmd += SPACE_C;
        sstCmd += value;
        sstCmd += NEW_L;
        asio::write(_socket, asio::buffer(sstCmd));
    }
}

bool UseRecivedCmd::getGameStatus()
{
    return _isFinished;
}

void UseRecivedCmd::getSeg(void)
{
    if (!_cmd.getCommandAt(SEG_CMD, 0).empty()) {
        _isFinished = true;
    }
}
