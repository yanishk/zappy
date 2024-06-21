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
        UseRecivedCmd(CommandManager &cmd, AllPlayers &player, asio::ip::tcp::socket &socket);

        void callAllFunctions(Vector3 camPosition);
        bool getGameStatus(void);

    private:
        CommandManager &_cmd;
        AllPlayers &_player;
        asio::ip::tcp::socket &_socket;

        bool _isFinished = false;
        int _sgtValue;
        int getNbrItemTypeOnIsland(Vector3 pos, int type);
        void removeItemFromIsland(Vector3 position, int type);
        void addItemToIsland(Vector3 position, int type);

        void getBct(void);
        void getTna(void);
        void getPnw(void);
        void getPpo(void);
        void getPlv(void);
        void getPin(void);
        void getPbc(Vector3 camPosition);
        void getPex(void);
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
        void getSmg(void);
};

#endif /* !USERECIVEDCMD_HPP_ */
