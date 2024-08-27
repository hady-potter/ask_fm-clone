#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "question.hpp"
class Question; // forward declaration.

class User {
private:
  int _id;
  std::string _username;
  std::string _password;
  bool allow_anonymous_questions;
  std::vector<Question> _questionsIAsked;
  std::vector<Question> _questionsIReplyed;

  void print_question(std::vector<Question>& data, User& user);
  void print_question(Question& q);

 
public:
  User();
  User(std::string, std::string);
  User(int, std::string, std::string, bool);

  bool ask_question();
  void answer_question();
  void thread();
  void print_all_questions_i_asked();
  void print_all_questions_asked_to_me();
  void print_all_questions(std::vector<Question>&);
  bool delete_question();

  void feed();

  std::string getUsername() const;
  std::string getPassword() const;
  int getId() const;
  int get_anonymous() const;

  bool operator==(const User&);

  int getId();
  std::string getUsername();
  std::string getPassword();
  int get_anonymous();

  void set_anonymous(int AQ);
  void setId(int);
  void setUsername(const std::string&);
  void setPassword(const std::string &);
};

