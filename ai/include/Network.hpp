/*
** EPITECH PROJECT, 2024
** ai
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #define PORT_FLAG "-p"
    #define DEFAULT_HOME "127.0.0.1"
    #include <string>
    #include <asio.hpp>
    #include <iostream>
    #include <memory>

namespace Network
{
    class Network {

        public:
            Network(): _port(""), _home(""), _io_context(asio::io_context()), _socket(std::make_shared<asio::ip::tcp::socket>(asio::ip::tcp::socket(_io_context))) {}

            Network(const Network &other): _port(other._port), _home(other._home), _io_context(asio::io_context()), _socket(std::make_shared<asio::ip::tcp::socket>(asio::ip::tcp::socket(_io_context))) {
                try {
                    asio::ip::tcp::resolver resolver(_io_context);
                    asio::connect(*_socket, resolver.resolve(_home, _port));
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            }

            Network(std::string port, std::string home = DEFAULT_HOME): _port(port), _home(home), _io_context(asio::io_context()), _socket(std::make_shared<asio::ip::tcp::socket>(asio::ip::tcp::socket(_io_context))){
                try {
                    asio::ip::tcp::resolver resolver(_io_context);
                    asio::connect(*_socket, resolver.resolve(_home, port));
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            }

            ~Network() {}

            std::string getInfoFromServer();
            void sendInformationToServer(const std::string &information);

        private:
            std::string _port;
            std::string _home;
            asio::io_context _io_context;
            std::shared_ptr<asio::ip::tcp::socket> _socket;
            asio::io_service _ioservice;
    };
}


#endif /* !NETWORK_HPP_ */
