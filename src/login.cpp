#include "../include/login.hpp"

bool login(User& user) {
  std::cout << "Username: ";
  std::string username;
  std::cin>> username;
  std::cout << "Password: ";
  std::string password;
  std::cin >> password;

  int id = DB::is_user_exist(User(0, username, password, 0));

  if (not id) {
    std::cout << "WRONG password or username please try again or sign up.\n";
    return false;
  }

  std::cout << "\n\tWelcome back " << username << "\n";
  user.setId(id);
  user.setUsername(username);
  user.setPassword(password);
  return true;
}

bool signUp(User& user) {
  std::cout << "Username [NO SPACE]: ";
  std::string username;
  std::cin >> username;
  std::cout << "Password: ";
  std::string password;
  std::cin >> password;
  std::cout << "Do you allow anonymous questions? [Y/N]: ";
  char char_AQ;
  int AQ = 0;
  std::cin >> char_AQ;

  if(char_AQ == 'Y' or char_AQ == 'y') AQ = 1;

      // check is username already taken
  if (DB::is_username_taken(username)) {
    std::cout << "Username already taken. Try diffrent name.\n";
    return false;
  }
  // add user to db
  int id = DB::generateUserId();
  DB::generateQuestionFile(id);
  if (not DB::add_user(User(id,username, password, AQ))) {
    std::cout << "Sorry internal server error please try again later.\n";
    return {};
  }

  std::cout << "\n\tWelcome " << username << " on ASK.FM\n";
  user.setId(id);
  user.setUsername(username);
  user.setPassword(password);
  user.set_anonymous(AQ);
  return true;
}

bool loged_in(User& user) {
  while (true)
  {
    std::cout << "1) Login\n";
    std::cout << "2) Sign Up\n";
    std::cout << "3) Exit\n";
    std::cout << "================\n";
    std::cout << "  choose: ";
    int choose;
    std::cin >> choose;
    if(choose == 1) return login(user);
    else if(choose == 2) return signUp(user);
    else if (choose == 3) exit(1);
    else std::cout << "Wrong choose\n";
    
  }
  
}


void logout() { 
  std::string s = "LOGGING OUT...";
  for(auto& c: s) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout << c << std::flush;
      // std::cout.flush();
  }
  std::cout << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(400));
}
