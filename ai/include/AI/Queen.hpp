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
    #define QUEEN_START_INCANTATION(x) "Queen start incantation to level " << x << ".\n"
    #define QUEEN_INCANTATION(x) "Queen is now level " << x << ".\n"

    #define QUEEN_SAY_LEVEL(x) "Queen broadcast [Queen:Level:" + std::to_string(x) + "]\n"
    #define QUEEN_SAY_INCANTATION(x) "Queen broadcast [" << x << "]\n"
    #define QUEEN_SAY_ASK_ASSISTANT(x) "Queen broadcast [Queen:AskAssistant:" + std::to_string(x + 1) + "]\n"
    #define QUEEN_SAY_NO(x) "Queen broadcast [Queen:No:" + x + "]\n"
    #define QUEEN_SAY_HERE(x) "Queen broadcast [Queen:Here:" + x + "]\n"
    #define QUEEN_SAY_HERE_COME(x) "Queen broadcast [Queen:Here:" + x + "] to come.\n"

    #define QUEEN_ASSISTANTS(x) "Queen has " + std::to_string(x) + " assistants.\n"
    #define QUEEN_ASSISTANTS_INCOMMING(x) "Queen has " + std::to_string(x) + " assistants in comming.\n"
    #define QUEEN_ASSISTANT_IS_HERE(x) "Queen see that assistant " + x + " is here.\n"

    #define BROADCAST_QUEEN_LEVEL(x) "Queen:Level:" + std::to_string(x) + "\n"
    #define BROADCAST_QUEEN_INCANTATION "Queen:Incantation"
    #define BROADCAST_PREFIXE ":"
    #define BROADCAST_QUEEN_ASK_ASSISTANTS(x) "Queen:AskAssistant:" + std::to_string(x + 1) + "\n"
    #define BROADCAST_ASK_SUFFIX ":Comming:Queen"
    #define BROADCAST_QUEEN_HERE(x) "Queen:Here:" + x + "\n"
    #define BROADCAST_QUEEN_NO(x) "Queen:No:" + x + "\n"
    #define BROADCAST_PING_SUFFIX ":Ping:Queen"
    #define BROADCAST_HERE_ALL "Queen:Here:All\n"
    #define QUEEN_SAY_HERE_ALL "Queen broadcast [Queen:Here:All]\n"

    #define QUEEN_CHECK_INCANTATION "Queen check fork.\n"
    #define QUEEN_FORK_SEARCHER "Queen fork a searcher:\n"
    #define SEARCHER_LEVEL(x) "Level: " << x << "\n"
    #define QUEEN_EXECUTE "Queen execute.\n"

    #define CRITICAL_FOOD 50
    #define CRITICAL_STOCK 10

    #define MAX_LAST_MESSAGE 50

    #define ONE_FOOD 1
    #define ONE_LEVEL 1
    #define ONE_COUNT 1
    #define LEVEL_INDEX 1

    #define FIRST_LEVEL ONE_LEVEL

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
        using Assistants = std::vector<std::string>;

        enum Action {

            Take,
            ForkQueen,
            Incantation,
            AskAssistants

        };

        public:

            Queen(): AAi() {};
            ~Queen() {};

            bool run(Network::Network &network);

        private:

            bool initialize(Network::Network &network);

            bool checkFood();
            bool checkIncantation();

            bool checkRessources();
            bool checkPlayers();

            bool checkHere(Network::Network &network);
            
            bool askAssistants(Network::Network &network);
            bool addAssistantsIncomming(Network::Network &network);
            bool addAssistants(Network::Network &network);
            bool sendMessageToAssistant(Network::Network &network, const std::string &content, const Orientation &orientation);

            bool execute(Network::Network &network);

            bool take(Network::Network &network);
            bool forkQueen(Network::Network &network);
            bool makeIncantation(Network::Network &network);

            std::size_t countRessources(const std::string &ressources, const std::string &index);

            Ressources _look;

            std::size_t _nbAssistants;
            Assistants _assistants;
            Assistants _assistantsIncomming;

            std::size_t _stock;
            std::vector<Action> _actions;

            std::vector<std::pair<Action, std::function<bool(Network::Network &network)>>> _execute = {

                { Action::Take,             [this] (Network::Network &network) { return take(network);              } },
                { Action::ForkQueen,        [this] (Network::Network &network) { return forkQueen(network);         } },
                { Action::Incantation,      [this] (Network::Network &network) { return makeIncantation(network);   } },
                { Action::AskAssistants,    [this] (Network::Network &network) { return askAssistants(network);     } }

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
