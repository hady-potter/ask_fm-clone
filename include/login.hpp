#pragma once
#include <iostream>
#include <optional>
#include <chrono>
#include <thread>

#include "db.hpp"
#include "user.hpp"

bool login(User&);
bool signUp(User&);

bool loged_in(User&);

void logout();