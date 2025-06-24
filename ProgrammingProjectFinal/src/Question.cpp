#include "../include/Question.h"

Question::Question(std::string cat, std::string qtext, std::vector<std::string> opts, int correct)
    : category(std::move(cat)), text(std::move(qtext)), options(std::move(opts)), correct_index(correct) {}
