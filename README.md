# AskFm clone
## Simple AskFM clone with basic capabilities

## let's take helicopter view of this project
  - People ask questions and others answers them
  - This is files-based system
    - Every time the user run it, you see the previous state (users/questions/answers)
    - Multiple users can use it in same time (parallel)
      - You send question. I see it
      - I answer the question or remove it, you see this update
  
  - Login/Sign up/Sign Out
    - Any system allow a user to sign up (name, email, password, username, password)
    - Also: As a user do you allow anonymous questions?
  - User operations
    - Print questions: From you, To you, Feed Questions
    - Ask and answer questions. System support threads
    - Delete a question


## how to compile (in terminal)
  1. cd ask_fm-clone
  2. mkdir build
  3. cmake -G "Unix Makefiles" ..
  4. make
  5. ./main
