#include "../include/db.hpp"

DB::DB() = default;

bool DB::is_user_exist(int id) {
  std::string path = "../db/users.txt";
  auto users = getUsers(path);

  for(const auto& user: users) {
    if(user.getId() == id) return true;
  }

  return false;
}

int DB::is_user_exist(const User& user) {
  std::string path = "../db/users.txt";
  auto users = getUsers(path);

  for (auto& u : users) {
    if(u == user) return u.getId();
  }

  return 0;
}

User DB::get_user_by_id(int id) {
  std::string path = "../db/users.txt";
  auto users = getUsers(path);

  for (const auto &user : users) {
    if (user.getId() == id)
      return user;
  }

  return {};
}

bool DB::is_username_taken(std::string username) {
  std::string path = "../db/users.txt";
  auto users = getUsers(path);

  for(const auto& user: users) {
    if(user.getUsername() == username) return true; 
  }

  return false;
}

bool DB::add_user(const User& user) {
  std::string path = "../db/users.txt";
  std::ofstream file_handler(path, std::ios::app);
  if(file_handler.fail()) return false;

  auto users = getUsers(path);

  for(auto& u: users) {
    if(u == user) return false;
  }

  file_handler << user.getId() << " " << user.getUsername() << " " << user.getPassword() << " " << user.get_anonymous() <<"\n";

  file_handler.close();
  return true;
}

int DB::generateUserId() {
  return generateId("../db/userid.txt");
}

int DB::generateQuestionId() {
  return generateId("../db/questionid.txt");
}

void DB::generateQuestionFile(int id) {
  std::string path = "../db/user_" + std::to_string(id);
  generateDir(path);
  path += "/" + std::to_string(id);
  std::ofstream outfile(path);
  outfile.close();

  path += "_";
  outfile.open(path);
  outfile.close();
}

bool DB::add_question(Question question) {
  
  std::string path = "../db/user_" + std::to_string(question.askerId()) + "/" + std::to_string(question.askerId());

  std::ofstream outfile(path, std::ios::app);

  if(outfile.fail()) { 
    std::cout <<"FAIL\n";
    return false;
  };

  outfile << question.questionId() << "," << question.askerId() << "," << question.replyerId() << "," << question.question() << "," << question.answer() << "," << question.AQ() << "\n";

  outfile.close();

  path = "../db/user_" + std::to_string(question.replyerId()) + "/" + std::to_string(question.replyerId()) + "_";
  outfile.open(path, std::ios::app);
  if(outfile.fail()) {
    std::cout << "FAAAAAIL\n";
  }

  outfile << question.questionId() << "," << question.askerId() << "," << question.replyerId() << "," << question.question() << "," << question.answer() << "," << question.AQ() << "\n";

  outfile.close();

  return true;
}

bool DB::add_question(std::vector<Question>& data, int replyer_id, int asker_id) {

    std::string path = "../db/user_" + std::to_string(asker_id) + "/" + std::to_string(asker_id);
    std::ofstream outfile(path, std::ios::trunc);

    if (outfile.fail()) {
      std::cout << "FAIL\n";
      return false;
    };

  for (auto &question : data){
    outfile << question.questionId() << "," << question.askerId() << "," << question.replyerId() << "," << question.question() << "," << question.answer() << "," << question.AQ() <<  "\n";
  }
  outfile.close();

  path = "../db/user_" + std::to_string(replyer_id) + "/" + std::to_string(replyer_id) + "_";
  outfile.open(path, std::ios::trunc);
  if (outfile.fail()) {
    std::cout << "FAAAAAIL\n";
  }

  for (auto &question : data) {
    outfile << question.questionId() << "," << question.askerId() << "," << question.replyerId() << "," << question.question() << "," << question.answer() << "," << question.AQ() << "\n";
  }
  outfile.close();

  return true;
}

std::vector<Question> DB::get_all_question(int id, char c) {
  std::string path = "../db/user_" + std::to_string(id) + "/" + std::to_string(id);
  
  if(c == '_') path += "_";

  std::vector<Question> questions;
  std::vector<std::string> tempvec;
  std::string tmp;

  std::ifstream infile(path);
  std::string line;

  while (std::getline(infile, line)) {
    std::istringstream stream(line);

    while (std::getline(stream, tmp,  ',')) {
      tempvec.push_back(tmp);
    }
    
    int q_id = std::stoi(tempvec[0]);
    int asker_id = std::stoi(tempvec[1]);
    int replyer_id = std::stoi(tempvec[2]);
    std::string question = tempvec[3];
    std::string answer = tempvec[4];
    int AQ = std::stoi(tempvec[5]);
    tempvec.clear();
    questions.push_back(Question(q_id, asker_id, replyer_id, question, answer, AQ));
    
  }
  infile.close();
  return questions;
}

bool DB::delete_question(std::vector<Question> &data, int replyer_id, int asker_id){
    return add_question(data, replyer_id, asker_id); 
}


void DB::list_system_users() {
  std::string path = "../db/users.txt";
  std::ifstream file_handler(path);
  std::string line;
  std::string name;
  int id;
  std::cout << "ID\t\t" << "Name\n";
  std::cout << "--------------------------\n";
  while (std::getline(file_handler, line))
  {
    std::stringstream stream(line);
    stream >> id >> name;
    std::cout << id << "\t\t" << name << "\n";
  }
  std::cout << "--------------------------\n";
}

// void DB::thread(Question& q, std::string& question) {
//   std::string path = "../db/user_" + q.askerId() + '/' + q.questionId();
//   std::ofstream file_handler(path, std::ios::app);
//   file_handler << q.questionId() << "," << q.askerId() << "," << q.replyerId() << question << ",NO answer yet\n";
// }

// =================private================

std::vector<User> DB::getUsers(const std::string &path)
{
  std::ifstream file_handler(path);
  std::vector<std::string> content;
  std::string line;
  while(std::getline(file_handler, line)) {
    content.push_back(line);
  }
  
  file_handler.close();
  return convert_string_to_users(content);
}

std::vector<User> DB::convert_string_to_users(std::vector<std::string> &users) {
  std::vector<User> _users;
  int id;
  int AQ;
  std::string username;
  std::string password;
  for(const auto& u: users) {
    std::istringstream stream(u);
    stream >> id >> username >> password >> AQ;
    _users.push_back(User(id, username, password, AQ));
  }
  return _users;
}

int DB::generateId(const std::string &path) {
  std::ifstream input(path);
  int id;
  input >> id;
  input.close();

  std::ofstream output(path);
  output << id + 1;
  output.close();
  return id;
}

bool DB::generateDir(const std::string& path) {
  if(mkdir(path.c_str(), 0777) == -1) {
    return false;
  }
  return true;
}