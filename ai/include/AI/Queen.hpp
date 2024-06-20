/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

    #define QUEEN_WELCOME "Queen welcome.\n"
    #define QUEEN_DEAD "Queen is dead.\n"
    #define QUEEN_INITIALIZE(x) "Queen create " << x << " fakes queens.\n"
    #define QUEEN_START "Queen start.\n"
    #define QUEEN_UPDATE_INVENTORY "Queen update inventory.\n"
    #define QUEEN_LOOK "Queen look:\n"
    #define QUEEN_LOOK_ITEM(x) "- " << x << "\n"
    #define QUEEN_FOOD(x) "Queen has " << x << " foods left.\n"
    #define QUEEN_FOOD_STOCK(x) "There are " << x << " foods on the floor.\n"
    #define QUEEN_TAKE_FOOD "Queen take food.\n"
    #define QUEEN_FORK "Queen fork.\n"

    #define QUEEN_LEVEL(x) "Queen broadcast [Queen:level:" + std::to_string(x) + "]\n"

    #define BROADCAST_QUEEN_LEVEL(x) "Queen:level" + std::to_string(x) + "\n"

    #define QUEEN_CHECK_INCANTATION "Queen check fork.\n"
    #define QUEEN_FORK_SEARCHER "Queen fork a searcher:\n"
    #define SEARCHER_LEVEL(x) "Level: " << x << "\n"
    #define QUEEN_INCANTATION "Queen incantation.\n"
    #define QUEEN_EXECUTE "Queen execute.\n"

    #define CRITICAL_FOOD 20
    #define CRITICAL_STOCK 50

    #define ONE_FOOD 1
    #define ONE_LEVEL 1
    #define ONE_COUNT 1
    #define LEVEL_INDEX 1

    #define MAX_ORDER 3
    #define LONG_COMMAND 5
    #define POSITIVE 0

    #define ONE_PLAYER 1
    #define TWO_PLAYERS 2
    #define FOUR_PLAYERS 4
    #define SIX_PLAYERS 6

    #define NB_TOURS_FOOD 7
    #define NB_TOURS_LOOK 7
    #define NB_TOURS_FORK 42
    #define NB_TOURS_INCANTATION 300

    #define NB_TOURS_MAX 126

    #define POSITION(a,b) std::make_pair<double, double>(a, b)

    #define NONE 0
    #define HERE 0
    #define INITIAL_COUNT 0

namespace Zappy {

    class Queen : public AAi {

        using Ressources = std::vector<std::string>;

        enum Action {

            Take,
            ForkQueen,
            Incantation

        };

        public:

            Queen(): AAi() {};

            ~Queen() {};

            bool run(Network::Network &network);

        private:

            bool initialize(Network::Network &network);

            bool checkFood();

            //bool checkIncantation();
            //bool checkRessources();
            //bool checkPlayers();

            bool execute(Network::Network &network);

            bool take(Network::Network &network);
            bool forkQueen(Network::Network &network);

            //bool makeIncantation();
            //bool setIncantation();
            //bool removeIncantation();

            //bool forkSearcher();
            //Zappy::Ressources getCommand(bool already);

            std::size_t countRessources(const std::string &ressources, const std::string &index);

            Ressources _look;
            std::size_t _stock;
            std::vector<Action> _actions;

            std::vector<std::pair<Action, std::function<bool(Network::Network &network)>>> _execute = {

                { Action::Take,         [this] (Network::Network &network) { return take(network);      } },
                { Action::ForkQueen,    [this] (Network::Network &network) { return forkQueen(network); } }

            };

            std::vector<std::pair<size_t, Zappy::Ressources>> _incatation = {

                { ONE_PLAYER,       Zappy::Ressources(1, NONE, NONE, NONE, NONE, NONE) },
                { TWO_PLAYERS,      Zappy::Ressources(1, 1, 1, NONE, NONE, NONE) },
                { TWO_PLAYERS,      Zappy::Ressources(2, NONE, 1, NONE, 2, NONE) },
                { FOUR_PLAYERS,     Zappy::Ressources(1, 1, 2, NONE, 1, NONE) },
                { FOUR_PLAYERS,     Zappy::Ressources(1, 2, 1, 3, NONE, NONE) },
                { SIX_PLAYERS,      Zappy::Ressources(1, 2, 3, NONE, 1, NONE) },
                { SIX_PLAYERS,      Zappy::Ressources(2, 2, 2, 2, 2, 1) }

            };

    };

};

#endif /* !SEARCHERAI_HPP_ */
