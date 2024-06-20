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

        using SOCKET = asio::ip::tcp::socket;

        public:

            Network(): _port(""), _name(""), _home(""), _io_context(asio::io_context()), _socket(std::make_shared<SOCKET>(SOCKET(_io_context))) {};

            Network(const Network &other): _port(other._port), _name(other._name), _home(other._home), _io_context(asio::io_context()), _socket(std::make_shared<SOCKET>(SOCKET(_io_context))) {

                try {
                    asio::ip::tcp::resolver resolver(_io_context);
                    asio::connect(*_socket, resolver.resolve(_home, _port));
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }

            };

            Network(std::string port, std::string name, std::string home = DEFAULT_HOME): _port(port), _name(name), _home(home), _io_context(asio::io_context()), _socket(std::make_shared<SOCKET>(SOCKET(_io_context))){

                try {
                    asio::ip::tcp::resolver resolver(_io_context);
                    asio::connect(*_socket, resolver.resolve(_home, port));
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }

            };

            ~Network() = default;

            std::string getPort() { return _port; };
            std::string getHome() { return _home; };
            std::string getName() { return _name; };

            std::string getInfoFromServer();
            void sendInformationToServer(const std::string &information);

        private:

            std::string _port;
            std::string _name;
            std::string _home;
            asio::io_context _io_context;
            std::shared_ptr<SOCKET> _socket;
            asio::io_service _ioservice;

    };

};

#endif /* !NETWORK_HPP_ */
