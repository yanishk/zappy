/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Broadcast
*/

#ifndef BROADCAST_HPP_
    #define BROADCAST_HPP_

    #include "Network.hpp"

    #define INCANTATION4LEVEL_BROADCAST ":Incantation4Level:"
    #define CWM_BROADCAST ":cwm:"
    #define AY_BROADCAST ":ay:"
    #define LDI_BROADCAST ":ldi:"
    #define YIM_BROADCAST ":yim:"
    #define INCANTATION_BROADCAST ":Incantation:"
    #define PING_BROADCAST ":Ping:"
    #define HERE_BROADCAST ":Here:"

    #define HERE_POS 8

namespace Zappy
{
    
    class Broadcast {

        public:

            Broadcast(const std::string &name, const std::string &id):
                _name(name),
                _id(id)
            {}

            std::string ping(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + PING_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

            std::string askForIncantation(Network::Network network, int level) {

                network.sendInformationToServer(_name + "|" + _id + INCANTATION4LEVEL_BROADCAST + std::to_string(level));

                return network.getInfoFromServer();
            }

            std::string cwm(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + CWM_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

            std::string ay(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + AY_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

            std::string ldi(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + LDI_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

            std::string yim(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + YIM_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

            std::string letsIncantate(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + INCANTATION_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

            std::string here(Network::Network network, const std::string &otherId) {

                network.sendInformationToServer(_name + "|" + _id + HERE_BROADCAST + otherId);

                return network.getInfoFromServer();
            }

        private:
            std::string _name;
            std::string _id;
    };

}

#endif /* !BROADCAST_HPP_ */
