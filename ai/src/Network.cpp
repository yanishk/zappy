/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Network
*/

#include <asio.hpp>
#include <iostream>

#include "Network.hpp"

void Network::Network::sendInformationToServer(const std::string &information)
{
    try {

        asio::write(*_socket, asio::buffer(information + "\n"));

    } catch (const std::system_error &err) {

        std::cerr << err.what() << std::endl;

    }
}

std::string Network::Network::getInfoFromServer()
{
    try {

        asio::streambuf buffer;
        asio::error_code error;
        std::istream is(&buffer);
        asio::read_until(*_socket, buffer, '\n', error);

        if (error == asio::error::eof) {
            std::cerr << "Connection closed by server." << std::endl;
            return std::string("end");
        } else if (error) {
            throw asio::system_error(error);
            std::cerr << "error\n";
        }

        std::string line;
        std::getline(is, line);

        return line;

    } catch (const std::exception &e) {

        std::cerr << e.what() << std::endl;

    }

    return std::string("none");
}

