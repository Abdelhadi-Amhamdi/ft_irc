#include "Bot.hpp"

int main() {
    try {
        Bot b("127.0.0.1", "4242");
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
}