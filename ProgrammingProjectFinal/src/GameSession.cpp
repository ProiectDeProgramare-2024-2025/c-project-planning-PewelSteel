#include "../include/Gamesession.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>

GameSession::GameSession(Player* p) : score(0), current_question_index(0), player(p) {}

void GameSession::loadQuestions(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) throw std::runtime_error("Could not open questions file.");

    int num_questions;
    file >> num_questions;
    file.ignore();

    for (int i = 0; i < num_questions; ++i) {
        std::string category, text, options_str;
        int correct_index;
        std::getline(file, category, ' ');
        std::getline(file, text, '<');
        std::getline(file, options_str, '>');
        file >> correct_index;
        file.ignore();

        std::vector<std::string> options;
        std::stringstream ss(options_str);
        std::string opt;
        while (std::getline(ss, opt, ';')) options.push_back(opt);

        questions.emplace_back(category, text, options, correct_index);
    }
}

void GameSession::start() {
    score = 0;
    current_question_index = 0;
}

Question GameSession::getCurrentQuestion() {
    if (current_question_index >= questions.size())
        throw std::out_of_range("No more questions.");
    return questions[current_question_index];
}

bool GameSession::answerQuestion(int index) {
    if (current_question_index >= questions.size()) return false;
    bool correct = int(questions[current_question_index].correct_index) == index;
    if (correct) score++;
    current_question_index++;
    return correct;
}

bool GameSession::hasNextQuestion() {
    return current_question_index < questions.size();
}

void GameSession::endSession() {
    player->final_score = score;
    std::ofstream out("players.txt", std::ios::app);
    out << player->name << " " << score << "\n";

    std::ofstream log("session_log.txt", std::ios::app);
    time_t now = time(nullptr);
    log << ctime(&now);
    log << player->name << " " << score << "\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        log << questions[i].text << " " << ((i < current_question_index && questions[i].correct_index == i) ? "correct" : "incorrect") << "\n";
    }
}
