/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Queen
*/

#ifndef QUEEN_HPP_
    #define QUEEN_HPP_

    #include "AAi.hpp"

    #define WELCOME_QUEEN "Queen initialized.\n"
    #define QUEEN_FOOD(x) "Queen has " << x << " food left.\n"
    #define QUEEN_FOOD_STOCK(x) "There are " << x << " food at floor.\n"
    #define QUEEN_TAKE_FOOD "Queen take food.\n"
    #define QUEEN_FORK_FOOD "Queen fork food.\n"
    #define QUEEN_FORK_SEARCHER "Queen fork a searcher:\n"
    #define SEARCHER_LEVEL(x) "Level: " << x << "\n"
    #define QUEEN_INCANTATION "Queen incantation.\n"

    #define CRITICAL_FOOD 10
    #define CRITICAL_STOCK 20

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

            Look,
            TakeFood,
            ForkFood,
            ForkSearcher,
            Incantation

        };

        public:

            Queen(const std::string &port, const std::string &name): AAi(port, name) {

                std::cout << WELCOME_QUEEN;

                _network.sendInformationToServer(_name);

                if (_network.getInfoFromServer() == RESPONSE_KO) {
                    return;
                }

                _network.getInfoFromServer();
                _thread = std::thread(&Queen::run, this);
                _thread.join();

            };

            bool run();

        private:

            bool initialize();

            bool checkFood();

            bool checkIncantation();
            bool checkRessources();
            bool checkPlayers();

            bool execute();

            bool takeFood();
            bool forkFood();

            bool makeIncantation();
            bool setIncantation();
            bool removeIncantation();

            bool forkSearcher();
            Zappy::Ressources getCommand(bool already);

            std::size_t countRessources(const std::string &ressources, const std::string &index);

            Ressources _look;

            std::size_t _stock;
            std::thread _thread;
            std::vector<Action> _actions;

            std::vector<std::pair<Action, std::function<bool()>>> _execute = {

                { Action::TakeFood,     [this] { return takeFood();         } },
                { Action::ForkFood,     [this] { return forkFood();         } },
                { Action::ForkSearcher, [this] { return forkSearcher();     } },
                { Action::Incantation,  [this] { return makeIncantation();  } }

            };

            std::size_t _nbCommands;
            std::size_t _nbTours;

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
