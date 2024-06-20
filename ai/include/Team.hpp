/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_

    #include <string>
    #include <vector>
    #include <memory>
    #include <thread>

    #include "AI/IAi.hpp"
    #include "AI/Queen.hpp"

    #define GET Zappy::TeamOptions()

namespace Zappy {

    class TeamOptions {

        public:

            TeamOptions(const std::string &name, const std::string &port, const std::string &home,std::unique_ptr<Queen> queen):
                _name(name),
                _port(port),
                _home(home),
                _queen(std::move(queen))
            {};

            TeamOptions() = default;

            std::string _name;
            std::string _port;
            std::string _home;
            std::unique_ptr<Queen> _queen;

    };

    class Team {

        using Player = std::unique_ptr<IAi>;
        using Players = std::vector<Player>;
        
        public:

            Team(const std::string &name, const std::string &port, const std::string &home): _name(name), _port(port), _home(home) {};

            static Team &getTeam(TeamOptions options);
            const std::string &getName();
            Players _players;

            int run();

        private:

            std::string _name;
            std::string _port;
            std::string _home;

    };

};

#endif /* !TEAM_HPP_ */