#include "UserManagement.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include "hl_sha1wrapper.h"

namespace yifan {

    void UserManagement::start() {
        while (true) {
            int user_input = get_input();
            take_action(user_input);
        }
    }

    void UserManagement::handle_login() {
        std::string username, password;
        std::string saved_password;

        std::cout << "请输入用户名： ";
        std::cin >> username;
        std::cout << "请输入密码： ";
        std::cin >> password;

        std::ifstream user_file{username + USER_FILE_SUFFIX};
        // 检查是否打开文件成功。原因可能是文件不存在，或者其他占用原因
        if (!user_file) {
            std::cerr << "用户名不存在，登录失败!\n";
            return;
        }
        getline(user_file, saved_password);

        std::unique_ptr<hashwrapper> hash_wrapper = std::make_unique<sha1wrapper>();
        password = hash_wrapper->getHashFromString(password);
        // 判断加密后的用户输入和保存的输入是否相等
        if (saved_password == password) {
            std::cout << "登陆成功!\n";
        } else {
            std::cout << "密码不匹配,登陆失败!\n";
        }
        user_file.close();
    }

    void UserManagement::handle_signup() {
        std::string username, password;
        std::cout << "请输入用户名： ";
        std::cin >> username;
        std::cout << "请输入密码： ";
        std::cin >> password;

        std::ofstream user_file{username + USER_FILE_SUFFIX};
        // 检查是否打开成功
        if (!user_file) {
            std::cerr << "打开用户文件失败，请稍后重试。\n";
            return;
        }

        // 处理加密 使用的是hashlib++库的 SHA1
        const std::unique_ptr<hashwrapper> hash_wrapper = std::make_unique<sha1wrapper>();
        user_file << hash_wrapper->getHashFromString(password);
        std::cout << "注册成功!\n";
        user_file.close();
    }

    void UserManagement::handle_delete() {
        std::string filename_to_remove;

        std::cout << "请输入要删除的用户名： ";
        std::cin >> filename_to_remove;
        if (std::filesystem::remove(filename_to_remove + USER_FILE_SUFFIX)) {
            std::cout << "删除成功!" << "\n";
        } else {
            std::cout << "删除失败!" << "\n";
        }
    }

    void UserManagement::handle_list_users() {
        std::vector<std::string> user_names;
        for (const auto &entry : std::filesystem::directory_iterator(".")) {
            if (entry.path().has_extension() && entry.path().extension() == USER_FILE_SUFFIX) {
                user_names.push_back(entry.path().filename().stem());
            }
        }

        if (user_names.empty()) {
            std::cout << ">> Oops. 目前没有任何已注册用户" << "\n";
            return;
        }

        for (const std::string &user_name : user_names) {
            std::cout << user_name << "\n";
        }
    }

    void UserManagement::take_action(int user_input) {
        switch (user_input) {
            case 0:
                std::cout << "欢迎使用本系统。再见!" << std::endl;
                exit(0);
            case 1:
                handle_login();
                break;
            case 2:
                handle_signup();
                break;
            case 3:
                handle_delete();
                break;
            case 4:
                handle_list_users();
                break;
            default:
                std::cout << "接收到异常输入" << user_input << "!" << std::endl;
                break;
        }
    }


/**
 * 打印用户输入提示，包含数字0-3
 */
    void UserManagement::print_prompt() {
        std::cout << "=======================" << std::endl;
        std::cout << "请输入希望完成的操作: " << std::endl;
        std::cout << "1) 用户登录" << std::endl;
        std::cout << "2) 新用户注册" << std::endl;
        std::cout << "3) 删除用户" << std::endl;
        std::cout << "4) 查看已有用户" << std::endl;
        std::cout << "0) 退出操作" << std::endl;
        std::cout << "=======================" << std::endl;
    }

/**
 * 读取用户输入，只允许用户输入整数0,1,2,3
 */
    int UserManagement::get_input() {
        int user_input = -1;
        // 必须读取到合法输入
        print_prompt();
        while (!(std::cin >> user_input)) {
            std::cout << "输入有误，请重新输入" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            print_prompt();
        }
        return user_input;
    }

}

