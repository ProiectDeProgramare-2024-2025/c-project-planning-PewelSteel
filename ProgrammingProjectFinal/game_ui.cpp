#include "include/Gamesession.h"
#include "include/Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

std::unique_ptr<GameSession> session;

void loadSession() {
    std::ifstream file("current_player.txt");
    std::string name;
    if (!(file >> name)) throw std::runtime_error("No active player session found.");
    Player* player = new Player(name);
    session = std::make_unique<GameSession>(player);
    session->loadQuestions("questions.txt");
    session->start();
}

void handleNextQuestion() {
    if (!session) loadSession();
    if (!session->hasNextQuestion()) {
        std::cout << "\033[35mNo more questions. Use end_game to finish.\033[0m\n";
        return;
    }
    Question q = session->getCurrentQuestion();
    std::cout << "\033[36mCategory: " << q.category << "\033[0m\n";
    std::cout << q.text << "\n";
    for (size_t i = 0; i < q.options.size(); ++i) {
        std::cout << i << ": " << q.options[i] << "\n";
    }
}

void handleAnswer(const std::string& indexStr) {
    if (!session) loadSession();
    try {
        int index = std::stoi(indexStr);
        bool correct = session->answerQuestion(index);
        std::cout << (correct ? "\033[32mCorrect!\033[0m\n" : "\033[31mIncorrect.\033[0m\n");
    } catch (...) {
        std::cerr << "\033[31mInvalid answer index.\033[0m\n";
    }
}

void handleEndGame() {
    if (!session) loadSession();
    session->endSession();
    std::cout << "\033[34mGame ended. Score saved.\033[0m\n";
    session.reset();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage:\n"
                  << "  ./game_ui.exe next_question\n"
                  << "  ./game_ui.exe answer <option_index>\n"
                  << "  ./game_ui.exe end_game\n";
        return 1;
    }

    std::string command = argv[1];
    try {
        if (command == "next_question") {
            handleNextQuestion();
        } else if (command == "answer" && argc >= 3) {
            handleAnswer(argv[2]);
        } else if (command == "end_game") {
            handleEndGame();
        } else {
            std::cout << "Invalid command or missing argument.\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "\033[31mError: " << ex.what() << "\033[0m\n";
        return 1;
    }
    return 0;
}