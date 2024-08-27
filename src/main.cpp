#include <iostream>
#include "login.hpp"
#include "db.hpp"

void mainMenu() {
  std::cout << "===================================\n";
  std::cout << "  1) Ask question\n"; // DONE
  std::cout << "  2) Answer question\n"; // DONE
  std::cout << "  3) Print all questions to me\n"; // DONE
  std::cout << "  4) Print all questions i asked\n"; // DONE
  std::cout << "  5) Delete question\n";  // DONE
  std::cout << "  6) List System Users\n"; // DONE
  std::cout << "  7) Feed\n"; // DONE
  // std::cout << "  8) thread\n"; // DONE
  std::cout << "  8) Logout\n"; // DONE 
  std::cout << "===================================\n";
}


int main() {
  User user;
  bool flag = true;
  while (!loged_in(user));
  
  mainMenu();
  while(flag) {
    int answer;
    std::cout << "huuh?: ";
    std::cin >> answer;
    switch (answer)
    {
    case 1:
      /* code */
      user.ask_question();
      break;
    case 2:
      /* code */
      user.answer_question();
      break;
    case 3:
      /* code */
      user.print_all_questions_asked_to_me();
      break;
    case 4:
      /* code */
      user.print_all_questions_i_asked();
      break;
    case 5:
      /* code */
      user.delete_question();
      break;
    case 6:
      /* code */
      DB::list_system_users();
      break;
    case 7:
      /* code */
      user.feed();
      break;
    case 8:
      /* code */
      logout();
      flag = false;
      break;

    default:
      std::cout << "what?\n";
      break;
    }
  }

  return 0;
}