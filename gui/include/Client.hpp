/*
** EPITECH PROJECT, 2024
** Client Class
** File description:
** zap Proj
*/

#ifndef CLIENT_H
    #define CLIENT_H
    #define WIN_SIZE_L 1920
    #define WIN_SIZE_W 1080
    #define WELCOME_RESPONSE "WELCOME"
    #define GRAPHIC_MESSAGE "GRAPHIC\n"
    #define KO_RESPONSE "ko"
    #define CON_CLOSE_MESSAGE "Connection closed by server."
    #define CON_SUCCESS_MSG "Connected to the server !"
    #define MSZ_CMD_START "msz\n"
    #define ERROR_VALUE 84
    #define CONFIG_FILE_PATH "./gui/src/display/modelConfig.cfg"
    #include <asio.hpp>
    #include <thread>
    #include <atomic>
    #include "Commands.hpp"

namespace Zappy {

    class Client {

        public:

            Client(const std::string &host, const std::string &port,
                CommandManager &cmd, bool animation);
            void run();

        private:

            void readServ();
            void writeToServ();
            void startDisplay();

            asio::io_context _ioContext;
            asio::ip::tcp::socket _socket;
            asio::ip::tcp::resolver::results_type _endpoints;
            asio::streambuf _buff;
            bool _isAnimated;

            CommandManager &_cmd;
    };
}

#endif // CLIENT_H
