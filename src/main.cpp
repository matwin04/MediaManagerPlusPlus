#include <iostream>
#include "MediaServer.h"

void show_menu() {
    std::cout << "\n\nDLNA Media Server CLI\n";
    std::cout << "1. Start Server\n";
    std::cout << "2. Stop Server\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";

}

int main() {
    MediaServer server;
    int choice = 0;

    while (choice != 3) {
        show_menu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (server.start()) {
                    std::cout << "Server started successfully.\n";
                } else {
                    std::cerr << "Failed to start the server.\n";
                }
                break;

            case 2:
                server.stop();
                std::cout << "Server stopped.\n";
                break;

            case 3:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cerr << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}