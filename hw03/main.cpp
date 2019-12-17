#include "bitcoin.h"

#include <stdexcept>

static void main_loop(Block& b)
{
    std::string command;

    while (std::cin.good() && !std::cin.eof()) {
        std::cout << ">>> ";
        size_t pos;
        getline(std::cin, command);

        try {
            if (command == "dump") {
                b.dump(std::cout);
            } else if (command == "quit") {
                break;
            } else if (command == "") {
                /* Do nothing */
            } else if ((pos = command.find("get ")) != std::string::npos) {
                std::string hash = command.substr(command.rfind(' ')+1);
                const Transaction& tx = b.getTransaction(hash);
                tx.dump(std::cout);
            } else if ((pos = command.find("decode")) != std::string::npos) {
                std::string hash = command.substr(command.rfind(' ')+1);
                const Transaction& tx = b.getTransaction(hash);
                tx.decode(std::cout);
            } else {
                std::cout << "Unrecognized command" << std::endl;
            }
        } catch (std::exception& e) {
            std::cout << " *** Error: " << e.what() << std::endl;
        }
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " INPUT_FILE" << std::endl;
        return 1;
    }
    try {
        Block b(argv[1]);
        main_loop(b);
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
