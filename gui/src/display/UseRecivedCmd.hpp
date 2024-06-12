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
    #include "Item.hpp"

class UseRecivedCmd {
    public:
        UseRecivedCmd(CommandManager &cmd, AllPlayers &player);
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
        int _newPlayerIndex = 0;
        int _playerLevelIndex = 0;
        int _playerEboIndex = 0;
        int _collectingItemIndex = 0;
        int _droppingItemIndex = 0;
        int _inventoryIndex = 0;
        CommandManager &_cmd;
        AllPlayers &_player;
};

#endif /* !USERECIVEDCMD_HPP_ */
