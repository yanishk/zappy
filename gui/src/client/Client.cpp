/*
** EPITECH PROJECT, 2024
** Client cpp
** File description:
** zap Proj
*/

#include "Client.hpp"
#include "DisplayGame.hpp"
#include "ParsesModelConfig.hpp"
#include "Utils.hpp"

#include <iostream>

Client::Client(const std::string &port, const std::string &host,
    CommandManager &cmd) : _socket(_ioContext), _cmd(cmd)
{
    asio::ip::tcp::resolver resolver(_ioContext);
    _endpoints = resolver.resolve(host, port);
    asio::connect(_socket, _endpoints);
    std::cout << "Connected to the server !" << std::endl;
}

void Client::run()
{
    std::thread display(&Client::startDisplay, this);
    std::thread reader(&Client::readServ, this);
    std::thread writer(&Client::writeToServ, this);

    reader.join();
    writer.join();
    display.join();
}

void Client::startDisplay()
{
    std::srand(std::time(NULL));
    ParsesModelConfig parse;
    std::vector<std::pair<std::pair<std::string, float>, int>> parsedFile = parse.parsesFile("./gui/src/display/modelConfig.cfg");
    DisplayGame game(WIN_SIZE_L, WIN_SIZE_W, _cmd);
    try {
        game.fillAllModel(parsedFile);
    } catch (const ErrorHandling& e) {
        std::cerr << "unexpected error: " << e.what() << std::endl;
        std::exit(84);
    }
    asio::write(_socket, asio::buffer("msz\n"));
    game.launchGame();
    exit(0);
}

void Client::readServ()
{
    try {

        std::istream is(&_buff);

        while (true) {

            asio::error_code error;
            asio::read_until(_socket, _buff, '\n', error);

            if (error == asio::error::eof) {
                std::cout << "Connection closed by server." << std::endl;
                //_isRunning = false;
                //_socket.close();
                exit(EXIT_SUCCESS);
            } else if (error) {
                throw asio::system_error(error);
            }

            std::string line;
            std::getline(is, line);

            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.compare("ko") == 0) {
                continue;
            }
            _cmd.receiveResponse(line);

            if (!line.compare("WELCOME")) {
                asio::write(_socket, asio::buffer("GRAPHIC\n"));
            }
        }

    } catch (std::exception &e) {
        std::cerr << "Reader failed: " << e.what() << "\n";
    }
}

void Client::writeToServ()
{
    while (true) {

        std::string command;
        std::getline(std::cin, command);

        if (command.empty()) {
            continue;
        }

        command += "\n";
        _cmd.sendCommand(command);

        asio::write(_socket, asio::buffer(command));
    }
}
