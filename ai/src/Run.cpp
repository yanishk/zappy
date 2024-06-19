/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Run
*/

#include "Run.hpp"
#include "Network.hpp"
#include "CreateAI.hpp"

bool Zappy::run(const std::string &name, const std::string &port) 
{
    Network::Network network(port);

    network.sendInformationToServer(name + "\n");

    std::string welcome = network.getInfoFromServer();
    std::string info1 = network.getInfoFromServer();

    bool hasFork = false;

    while (true) {

        if (!hasFork) {
            network.sendInformationToServer("Fork\n");
            std::string forkResult = network.getInfoFromServer();
            std::cout << std::this_thread::get_id() << ": Fork -> " << forkResult << "\n";

            Zappy::createAI(name, port);
            hasFork = true;
        }

        network.sendInformationToServer("Forward\n");
        std::string forwardResult = network.getInfoFromServer();
        std::cout << std::this_thread::get_id() << ": Forward -> " << forwardResult << "\n";
    
    }

    return true;
}
