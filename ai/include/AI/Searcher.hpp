/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Searcher
*/

#ifndef SEARCHER_HPP_
    #define SEARCHER_HPP_

    #define SEARCHER_WELCOME "Searcher initialized.\n"

    #define PREFIX_ASK_ASSISTANT "Queen:AskAssistant:"
    #define PREFIX_ASK_RESPONSE_HERE "Queen:Here:"
    #define PREFIX_ASK_RESPONSE_NO "Queen:No:"
    #define RESPONSE_ASK(x) x + ":Coming:Queen"
    #define ASK_PING(x) std::to_string(x) + ":Ping:Queen"

    #define ELEVATION_UNDERWAY "Elevation underway"

    #define MAX_LAST_MESSAGE 50
    #define ONE_LEVEL 1
    #define START_ID 0

    #define FIRST_LEVEL_RANGE       1, 3
    #define SECOND_LEVEL_RANGE      4, 8
    #define THISRT_LEVEL_RANGE      9, 15
    #define FOURTH_LEVEL_RANGE      16, 24
    #define FIVE_LEVEL_RANGE        25, 35
    #define SIX_LEVEL_RANGE         36, 48
    #define SEVEN_LEVEL_RANGE       49, 63

    #define MIDDLE_FIRST_LEVEL      2
    #define MIDDLE_SECOND_LEVEL     6
    #define MIDDLE_THIRST_LEVEL     12
    #define MIDDLE_FOURTH_LEVEL     20
    #define MIDDLE_FIVE_LEVEL       30
    #define MIDDLE_SIX_LEVEL        42
    #define MIDDLE_SEVEN_LEVEL      56

    #define NB_SAME_MOVE_MAX        4

    #define MIN_FOOD                5

    #define MAX_CHECK_MESSAGE       50

    #define ASK_ASSISTANT           "AskAssistant"
    #define COMING                  "Coming"
    #define LEVEL                   "Level"
    #define INCANTATION             "Incantation"
    #define PING                    "Ping"
    #define HERE_BROADCAST          "Here"
    #define NO                      "No"

    #define QUEEN                   "Queen"

    #include <map>
    #include <iostream>
    #include <thread>
    #include "AAi.hpp"
    #include "Order.hpp"

namespace Zappy
{
    enum Mouvement{
        Forward,
        Left,
        Right,
        Back,
        Take
    };

    class Searcher : public AAi {

        using Message = std::pair<std::string, Orientation>;

        public:
            Searcher():
                AAi(),
                _order(Order(1, Ressources(1, 0, 0, 0, 0, 0))),
                _inDelivery(false),
                _goBackToQueen(false)
                {
                    std::cerr << "A Searcher spawn\n";
                    static int id = 0;
                    _id = id++;

                }

            bool run(Network::Network &network);

        private:

            Order _order;
            std::vector<std::string> _lastLook;
            std::vector<Mouvement> _nextMouvment;
            std::vector<Mouvement> _moveToStarter;
            int _howManySameMove;
            std::thread _thread;
            std::string _otherId;
            int _id;
            std::string _idInCollaboration;
            int _queenLevel;
            bool _inDelivery;

            bool _goBackToQueen;

            Zappy::Response move(Network::Network &network);
            void dumpMovement();

            void whereShouldIGo(std::vector<int> priority);

            std::vector<int> estimatePriority();
            void whereIsThePriority(int index);

            std::string takeThis(std::string tiled);
            Zappy::Response dropItem(Network::Network &network);

            void checkQueenLevel(Network::Network &network);
            bool checkComingIsGood();
            int checkQueenLevel();

            Message createMessage(const std::string &content);

            bool checkAskAssistants(Network::Network &network);
            bool waitAskResponse(Network::Network &network);

            bool backToQueen(Network::Network &network, bool incantation);
            bool launchIncantation(Network::Network &network);
            Orientation getOrientationToQueen(Network::Network &network);

            void updateOrder();
            void searchFood(Network::Network &network);

    };

}

#endif /* !SEARCHER_HPP_ */