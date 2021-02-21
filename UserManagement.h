#ifndef USERMANAGEMENT_USERMANAGEMENT_H
#define USERMANAGEMENT_USERMANAGEMENT_H

#include <string>

namespace yifan{

class UserManagement {
public:
    [[ noreturn ]] void start();
private:
    void handle_login();
    void handle_signup();
    void handle_delete();
    void handle_list_users();

    void take_action(int user_input);
    void print_prompt();
    int get_input();

    const std::string USER_FILE_SUFFIX = ".user";
};

}

#endif //USERMANAGEMENT_USERMANAGEMENT_H
