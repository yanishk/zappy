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
    static int id = 0;

    id += 1;

    Network::Network network(port);

    network.sendInformationToServer(name);
    network.getInfoFromServer();
    network.getInfoFromServer();

    while (true) {

        network.sendInformationToServer("Forward\n");
        std::string forwardResult = network.getInfoFromServer();
        std::cout << id << ": Forward -> " << forwardResult << "\n";

        network.sendInformationToServer("Fork\n");
        std::string forkResult = network.getInfoFromServer();
        std::cout << id << ": Forkl -> " << forkResult << "\n";

        //Zappy::createAI(name, port);
    }

    return true;
}
