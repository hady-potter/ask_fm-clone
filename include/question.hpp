#pragma once


#include <iostream>
#include <vector>

#include "db.hpp"

class Question {
private:
  int _question_id;
  int _asker_id;
  int _replyer_id;
  std::string _question;
  std::string _answer;
  int _AQ;
  bool has_thread;
  

public:
  Question();
  Question(const std::string&);
  Question(int, int, const std::string&, const std::string&, int AQ);
  Question(int, int ,int, const std::string &, const std::string &, int AQ);


  bool empty();
  bool add_to_thread();
  void get_thread();
  int questionId();
  int askerId();
  int replyerId();
  std::string question();
  std::string answer();
  int AQ();
  void setAQ(int AQ);

  void set_answer(const std::string&);
  // void add_thread();
  // ~Question();
};

