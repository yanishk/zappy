/*
** EPITECH PROJECT, 2024
** my_branch_with_timo
** File description:
** UseRecivedCmd
*/

#ifndef USERECIVEDCMD_HPP_
    #define USERECIVEDCMD_HPP_

    #include "Commands.hpp"
    #include "Client.hpp"
    #include "Player.hpp"
    #include "Eggs.hpp"
    #include "Item.hpp"

class UseRecivedCmd {
    public:
        UseRecivedCmd(CommandManager &cmd, asio::ip::tcp::socket &socket);

        void callAllFunctions(void);
        bool getGameStatus(void);

    private:
        CommandManager &_cmd;
        asio::ip::tcp::socket &_socket;

        bool _isFinished = false;
        int _sgtValue;

        void getSgt(void);
        void getSst(void);
        void getSeg(void);
};

#endif /* !USERECIVEDCMD_HPP_ */
