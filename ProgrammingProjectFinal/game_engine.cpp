#include "include/Gamesession.h"
#include "include/Player.h"
#include <iostream>
#include <fstream>
#include <string>

void printUsage() {
    std::cout << "Usage:\n"
              << "  ./game_engine.exe load_questions <file_path>\n"
              << "  ./game_engine.exe start_game <player_name>\n"
              << "  ./game_engine.exe show_score <player_name>\n";
}

int main(int argc, char* argv[]) {

    std::cout<<"testtestest"<<std::endl;
    if (argc < 3) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    std::string argument = argv[2];

    try {
        if (command == "load_questions") {
            Player dummy("temp");
            GameSession session(&dummy);
            session.loadQuestions(argument);
            std::cout << "\033[32mQuestions loaded successfully from " << argument << "\033[0m\n";
        } else if (command == "start_game") {
            std::ofstream out("current_player.txt");
            out << argument;
            out.close();
            std::cout << "\033[34mGame started for player: " << argument << "\033[0m\n";
        } else if (command == "show_score") {
            std::ifstream file("players.txt");
            std::string name;
            int score;
            bool found = false;
            while (file >> name >> score) {
                if (name == argument) {
                    std::cout << "\033[33m" << name << "'s latest score: " << score << "\033[0m\n";
                    found = true;
                }
            }
            if (!found) {
                std::cout << "\033[31mPlayer not found.\033[0m\n";
            }
        } else {
            printUsage();
        }
    } catch (const std::exception& ex) {
        std::cerr << "\033[31mError: " << ex.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}
