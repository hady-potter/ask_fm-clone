#include "../include/question.hpp"

Question::Question() {
  _question_id = 0;
  _asker_id = 0;
  _replyer_id = 0;
  _AQ = 0;
  _question = "";
  _answer = "";
}

Question::Question(const std::string& question) {
  _question_id = DB::generateQuestionId();
  _question = question;
  _answer = "";
  _AQ = 0;
}

Question::Question(int asker_id, int replyer_id, const std::string& question, const std::string & answer, int AQ)
{
  _question_id = DB::generateQuestionId();
  _asker_id = asker_id;
  _replyer_id = replyer_id;
  _question = question;
  _answer = answer;
  _AQ = AQ;
}

Question::Question(int question_id, int asker_id, int replyer_id, const std::string &question, const std::string &answer, int AQ) {
  _question_id = question_id;
  _asker_id = asker_id;
  _replyer_id = replyer_id;
  _question = question;
  _answer = answer;
  _AQ = AQ;
}

bool Question::empty() { return _question_id == 0; }
void Question::set_answer(const std::string& ans) { _answer = ans; }

int Question::questionId() { return _question_id; }
int Question::askerId() { return _asker_id; }
int Question::replyerId() { return _replyer_id; }
int Question::AQ() { return _AQ; }
std::string Question::answer() { return _answer; }
std::string Question::question() { return _question; }
void Question::setAQ(int AQ) { _AQ = AQ; }



