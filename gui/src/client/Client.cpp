/*
** EPITECH PROJECT, 2024
** Client cpp
** File description:
** zap Proj
*/

#include "Client.hpp"
#include "Game.hpp"
#include "ParsesModelConfig.hpp"
#include "Utils.hpp"

#include <iostream>

Zappy::Client::Client(const std::string &port, const std::string &host,
    CommandManager &cmd, bool animation) : _socket(_ioContext), _cmd(cmd)
{
    asio::ip::tcp::resolver resolver(_ioContext);
    _endpoints = resolver.resolve(host, port);
    asio::connect(_socket, _endpoints);
    std::cerr << CON_SUCCESS_MSG << std::endl;
    _isAnimated = animation;
}

void Zappy::Client::run()
{
    std::thread display(&Zappy::Client::startDisplay, this);
    std::thread reader(&Zappy::Client::readServ, this);

    reader.join();
    display.join();
}

void Zappy::Client::startDisplay()
{
    std::srand(std::time(NULL));
    ParsesModelConfig parse;
    std::vector<std::pair<std::pair<std::string, float>, int>> parsedFile =
        parse.parsesFile(CONFIG_FILE_PATH);

    Zappy::Game game(WIN_SIZE_L, WIN_SIZE_W, _cmd, _socket, _isAnimated);
    try {
        game.fillAllModel(parsedFile);
    } catch (const ErrorHandling& e) {
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_VALUE);
    }

    asio::write(_socket, asio::buffer(MSZ_CMD_START));
    game.launchGame();
    std::exit(0);
}

void Zappy::Client::readServ()
{
    try {

        std::istream is(&_buff);

        while (true) {

            asio::error_code error;
            asio::read_until(_socket, _buff, '\n', error);

            if (error == asio::error::eof) {
                std::cerr << CON_CLOSE_MESSAGE << std::endl;
                exit(EXIT_SUCCESS);
            }
            if (error) {
                throw asio::system_error(error);
            }

            std::string line;
            std::getline(is, line);

            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.compare(KO_RESPONSE) == 0) {
                continue;
            }
            _cmd.receiveResponse(line);

            if (!line.compare(WELCOME_RESPONSE)) {
                asio::write(_socket, asio::buffer(GRAPHIC_MESSAGE));
            }
        }

    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

void Zappy::Client::writeToServ()
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
