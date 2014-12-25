/*
 * main.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: wim
 */

#include <iostream>

#include "GreenLeaf/MsgServer/MsgServer.h"

using namespace GreenLeaf;

int main(int argc, char** argv) {
    try {
        Server::MsgServer server;
        server.run();

    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;

    } catch(...) {
        std::cout << "..." << std::endl;

    }
}
