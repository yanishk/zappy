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
        UseRecivedCmd(CommandManager &cmd, AllPlayers &player, AllEggs &egg, asio::ip::tcp::socket &socket);

        void getPnw(void);
        void getPpo(void);
        void getPlv(void);
        void getPin(void);
        void getPex(void);
        void getPbc(void);
        void getPic(void);
        void getPie(void);
        void getPdr(void);
        void getPgt(void);
        void getPdi(void);
        void getEnw(void);
        void getEbo(void);
        void getEdi(void);
        void getSgt(void);
        void getSst(void);
        void getSeg(void);
    private:

        CommandManager &_cmd;
        AllPlayers &_player;
        AllEggs &_egg;
        asio::ip::tcp::socket &_socket;
};

#endif /* !USERECIVEDCMD_HPP_ */
