#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <experimental/filesystem>
// generate dirs
#include <sys/stat.h>
#include <sys/types.h>

#include "user.hpp"
#include "question.hpp"

class User; // forward declaration of class User.
class Question; // forward declaration of class Question.

class DB {
private:
  static std::vector<User> getUsers(const std::string &);
  static std::vector<User> convert_string_to_users(std::vector<std::string>&);

  static int generateId(const std::string&);
  static bool generateDir(const std::string&);

public:
  DB();
  static bool is_user_exist(int);
  static int is_user_exist(const User&);
  static bool is_username_taken(std::string);
  static User get_user_by_id(int id);
  static bool add_user(const User&);
  static int generateUserId();
  static int generateQuestionId();
  static void generateQuestionFile(int);
  static bool add_question(Question);
  static bool add_question(std::vector<Question>&, int, int);
  static std::vector<Question> get_all_question(int id, char);
  static bool delete_question(std::vector<Question> &data, int replyer_id, int asker_id);

  // static void thread(Question &q, std::string& question);

  static void list_system_users();
};

