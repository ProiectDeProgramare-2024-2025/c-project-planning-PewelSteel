#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <vector>
#include <string>
#include "question.h"
#include "player.h"

class GameSession {
public:
    std::vector<Question> questions;
    int score;
    size_t current_question_index;
    Player* player;

    GameSession(Player* p);
    void loadQuestions(const std::string& file_path);
    void start();
    Question getCurrentQuestion();
    bool answerQuestion(int index);
    bool hasNextQuestion();
    void endSession();
};

#endif