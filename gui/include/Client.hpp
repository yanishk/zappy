/*
** EPITECH PROJECT, 2024
** Client Class
** File description:
** zap Proj
*/

#ifndef CLIENT_H
    #define CLIENT_H

    #include <asio.hpp>
    #include <thread>
    #include "Commands.hpp"

class Client {

    public:

        Client(const std::string &host, const std::string &port, CommandManager &cmd);
        void run();

    private:

        void readServ();
        void writeToServ();
        void startDisplay();

        asio::io_context _ioContext;
        asio::ip::tcp::socket _socket;
        asio::ip::tcp::resolver::results_type _endpoints;
        asio::streambuf _buff;

        CommandManager &_cmd;
};

#endif // CLIENT_H
