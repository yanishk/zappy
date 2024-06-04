/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** TeamAi
*/

#ifndef TEAM_AI_HPP_
    #define TEAM_AI_HPP_

    #define NAME_FLAG "-n"
    #define MIN_ARGS 5
    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0

    #include <iostream>
    #include <vector>

    #include "Ressources.hpp"
    #include "Network.hpp"
    #include "IAi.hpp"

namespace Zappy
{

    class TeamAi {

        public:

            TeamAi(const Network::Network &network, const std::string &teamName): _network(network), _teamName(teamName) {};

            int run();

        private:

            Network::Network _network;
            std::string _teamName;
            Ressources _ressources;
            std::vector<IAi> _team;

    };

};


#endif /* !TEAM_AI_HPP_ */
