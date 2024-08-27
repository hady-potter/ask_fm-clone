#include "../include/user.hpp"

// =======Construcor========
User::User() : _questionsIAsked(), _questionsIReplyed() {
  _username = "";
  _password = "";
  _id = 0;
  allow_anonymous_questions = false;
}

User::User(std::string username, std::string password) : _username(username), _password(password),allow_anonymous_questions(false), _questionsIAsked(), _questionsIReplyed() {}

User::User(int id, std::string username, std::string password, bool AQ):User(username, password) {
  this -> _id = id;
  allow_anonymous_questions = AQ;
}
// =======end of Construcor========

void User::setId(int id) { this -> _id = id; }

void User::setUsername(const std::string &username) { this->_username = username; }

void User::setPassword(const std::string &password) { this->_password = password; }

void User::set_anonymous(int AQ) {
  allow_anonymous_questions = AQ;
}

bool User::ask_question() {
  std::cout << "Enter user id or (-1) to cancel: ";
  int user_id;
  std::cin >> user_id;
  std::cin.ignore();
  if (user_id == -1) { return false; }
  
  // check if user with id is exist
  if (not DB::is_user_exist(user_id)) { return false; }

  User user = DB::get_user_by_id(user_id);
  char _AQ;
  int AQ = 0;
  if(user.get_anonymous()){
    std::cout << "do you want ask anonymously?[Y/N]: ";
    std::cin >> _AQ;
    std::cin.ignore();
    if(_AQ == 'Y' or _AQ == 'y') AQ = 1;
  }
  else {
    std::cout << "WARNING -> this user  [" << user.getUsername() <<"] does NOT allow anonymous questions\n";
  }


  std::cout << "Question: ";
  std::string question;
  std::getline(std::cin, question);

  Question q(_id, user_id, question, "NO answer yet", AQ);

  return DB::add_question(q);
}

void User::answer_question() {
  std::cout << "Question ID: ";
  int id;
  std::cin >> id;
  std::cin.ignore();

  _questionsIReplyed = DB::get_all_question(_id, '_');

  auto q = std::find_if(_questionsIReplyed.begin(), _questionsIReplyed.end(),
                          [id](auto &q)
                          { return q.questionId() == id; });

  if (_questionsIReplyed.empty() or (q == _questionsIReplyed.end())) {
    std::cout << "there is NO question with such ID.\n";
    return;
  }
  
  print_question(*q);

  std::cout << "Answer: ";
  std::string answer;
  std::getline(std::cin, answer);

  q -> set_answer(answer);

 print_question(*q);

  // ubdate data base
  DB::add_question(_questionsIReplyed, _id, q -> askerId());

}

void User::print_all_questions_i_asked() {
  auto data = DB::get_all_question(_id, '!');
  if(data.empty()) {
    std::cout << "  You don't ask any question. ask now\n";
    return;
  }
  print_all_questions(data);
}

void User::print_all_questions_asked_to_me() {
  auto data = DB::get_all_question(_id, '_');
  if (data.empty()) {
    std::cout << "  You don't have any question at this moment.\n";
    return;
  }
  print_all_questions(data);
}

void User::print_all_questions(std::vector<Question>& data) {
  // User user;
  for (auto &q : data) {
   print_question(q);
  }
}

bool User::delete_question() {
  std::cout <<"Question ID: ";
  int id;
  std::cin >> id;
  _questionsIAsked = DB::get_all_question(_id, '!');

  auto q = std::find_if(_questionsIAsked.begin(), _questionsIAsked.end(),
        [id](auto &q)
        { return q.questionId() == id; });

  if (_questionsIAsked.empty() or q -> empty()) {
    std::cout << "there is NO question with such ID.\n";
    return false;
  }

  if(q -> askerId() != _id) {
    std::cout << "YOU don't have the permission to delete this question.\n";
    return false;
  }

  _questionsIAsked.erase(q);
  std::cout <<"Question with ID [" << q -> questionId() << "] deleted susseccfuly\n";

  return DB::delete_question(_questionsIAsked, q -> replyerId(), q -> askerId());

}


void User::feed() {
  auto questions = DB::get_all_question(_id, '!');
  if(questions.empty()) {
    std::cout << "There is no feed at this moment!\n";
  }
  for(auto& q: questions) {
    if (q.answer() != "NO answer yet" and _id == q.askerId()) {
      print_question(q);
    }
  }
}

void User::thread() {
  std::cout << "Question ID: ";
  int q_id;
  std::cin >> q_id;
  auto questions = DB::get_all_question(_id, '!');

  auto q = std::find_if(questions.begin(), questions.end(), 
  [q_id](Question& q){ return q.questionId() == q_id; });

  // we did NOT find the question
  if(not (q != questions.end())) {
    std::cout << "there is no question with such ID. do you wnat to ask a new question?[Y/N]\n";

    char answer = 'N';
    std::cin >> answer;
    if(answer == 'Y' or answer == 'y') ask_question();
    else return;
  }
  else {
    // DB::thread(*q)
    std::cout << "Question: ";
    std::string question;
    std::getline(std::cin, question);
    // DB::thread(*q, question);
  }
}


std::string User::getUsername() const { return _username; }
std::string User::getPassword() const { return _password; }
int User::getId() const { return _id; }

std::string User::getUsername() { return _username; }
std::string User::getPassword() { return _password; }
int User::getId() { return _id; }
int User::get_anonymous() { return allow_anonymous_questions; }
int User::get_anonymous() const { return allow_anonymous_questions; }

bool User::operator==(const User& user) {
  return _username == user._username and _password == user._password;
}


void User::print_question(std::vector<Question>& data, User& user) {

}

void User::print_question(Question &q) {
  User asker_user = DB::get_user_by_id(q.askerId());
  User replyer_user = DB::get_user_by_id(q.replyerId());
  std::cout << "  ID: " << q.questionId() << "\n";
  if (not q.AQ()) {
    std::cout << "  " << asker_user.getUsername() << " says: " << q.question() << "\n";
  }
  else {
    std::cout << "  AQ Question: " << q.question() << "\n";
  }
  std::cout << "  " << replyer_user.getUsername() <<" Answers: " << q.answer() << "\n";
  std::cout << "=============================\n";
}