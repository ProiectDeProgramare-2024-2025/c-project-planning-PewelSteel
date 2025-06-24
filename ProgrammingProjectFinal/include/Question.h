#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>

class Question {
public:
    std::string category;
    std::string text;
    std::vector<std::string> options;
    size_t correct_index;

    Question(std::string cat, std::string qtext, std::vector<std::string> opts, int correct);
};

#endif