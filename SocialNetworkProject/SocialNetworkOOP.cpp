#include "System.h"
#include "UserSystem.h"
#include <iostream>
#include <cstring>
#include "HelperFunctions.h"

const unsigned MAX_BUFFER_SIZE = 512;
int main()
{
    UserSystem userSys;
    System sys;
    std::cout << "> ";
    char command[MAX_BUFFER_SIZE];
    while (std::cin >> command)
    {
        if (strcmp( command, "signup")==0) {
            char firstname[MAX_BUFFER_SIZE], lastname[MAX_BUFFER_SIZE], password[MAX_BUFFER_SIZE];
            std::cout << "> Enter first name: ";
            std::cin >> firstname;
            std::cout << "> Enter last name: ";
            std::cin >> lastname;
            std::cout << "> Enter your password: ";
            std::cin >> password;
            bool res = userSys.signup(firstname, lastname, password, 0);
            if (res) {
                std::cout << "> Successful!" << std::endl;
            }
            else {
                std::cout << "> There is logged user!" << std::endl;
            }
        }
        else if (strcmp(command, "login") == 0) {
            char firstname[MAX_BUFFER_SIZE], password[MAX_BUFFER_SIZE];
            std::cout << "> Enter first name: ";
            std::cin >> firstname;
            std::cout << "> Enter your password: ";
            std::cin >> password;
            bool isLogged = userSys.login(firstname, password);
            if (isLogged) {
                std::cout << "> Welcome back, " << userSys.getLoggedUser()->getFullName() << "!" << std::endl;;
            }
            else
            {
                std::cout << "> Invalid credentials!" << std::endl;
            }
        }
        else if (strcmp(command, "logout") == 0) {
            User* res = userSys.logout();
            if (res != nullptr) {
                std::cout << "> Goodbye, " << res->getFullName() << "!" << std::endl;
            }
            else
            {
                std::cout << "> There is not logged user!" << std::endl;
            }
        }
        else if (strcmp( command, "search")==0) {
            char text[MAX_BUFFER_SIZE];
            std::cin.ignore();
            std::cin.getline(text, MAX_BUFFER_SIZE);
            sys.search(text);
        }
        else if (strcmp(command, "create") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                char title[MAX_BUFFER_SIZE], desc[MAX_BUFFER_SIZE];
                std::cout << "> Enter topic title: ";
                std::cin.ignore();
                std::cin.getline(title, MAX_BUFFER_SIZE);
                std::cout << "> Enter topic description: ";
                std::cin.getline( desc, MAX_BUFFER_SIZE);
                sys.createTopic(title, desc, userSys.getLoggedUser()->shortUserInfo());
                std::cout << "> Success!" << std::endl;
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "open") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                unsigned id;
                std::cin >> id;
                Topic* openTopic;
                if (std::cin) {
                    openTopic = sys.openTopic(id);
                }
                else {
                    std::cin.clear();
                    char title[MAX_BUFFER_SIZE];
                    std::cin.getline(title, MAX_BUFFER_SIZE);
                    openTopic = sys.openTopic(title);
                }
                if (openTopic != nullptr) {
                    std::cout << "> Welcome to \"" << openTopic->getTitle() << "\"!" << std::endl;
                }
                else {
                    std::cout << "> This topic does not exist!" << std::endl;
                }
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp( command, "about")==0) {
            unsigned id;
            std::cin >> id;
            sys.about(id);
        }
        else if (strcmp(command, "list") == 0) {
            sys.listPost();
        }
        else if (strcmp(command, "post") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                char title[MAX_BUFFER_SIZE], content[MAX_BUFFER_SIZE];
                std::cout << "> Enter post title: ";
                std::cin.ignore();
                std::cin.getline( title, MAX_BUFFER_SIZE);
                std::cout << "> Enter post content: ";
                std::cin.getline(content, MAX_BUFFER_SIZE);
                sys.post(title, content, userSys.getLoggedUser()->shortUserInfo());
                std::cout << "> Posted!" << std::endl;
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "p_open") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                unsigned id;
                std::cin >> id;
                Post* openPost;
                if (std::cin) {
                    openPost = sys.openPost(id);
                }
                else {
                    std::cin.clear();
                    char title[MAX_BUFFER_SIZE];
                    std::cin.getline(title, MAX_BUFFER_SIZE);
                    openPost = sys.openPost(title);
                }
                if (openPost != nullptr) {
                    std::cout << "> Welcome to \"" << openPost->getTitle() << "\"!" << std::endl;
                }
                else {
                    std::cout << ">Error! Possible reasons:\n   This post does not exist!\n   There is not open topic!\n   There is already open post!" << std::endl;
                }
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "comment") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                char content[MAX_BUFFER_SIZE];
                std::cout << "> Say something:: ";
                std::cin.ignore();
                std::cin.getline(content, MAX_BUFFER_SIZE);
                sys.comment(content, userSys.getLoggedUser()->shortUserInfo());
                std::cout << "> Posted!" << std::endl;
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "comments") == 0) {
            sys.listComments();
        }
        else if (strcmp(command, "reply") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                unsigned id;
                std::cin >> id;
                char content[MAX_BUFFER_SIZE];
                std::cout << "> Say something:: ";
                std::cin.ignore();
                std::cin.getline(content, MAX_BUFFER_SIZE);
                bool isPosted = sys.reply(id, content, userSys.getLoggedUser()->shortUserInfo());
                if (isPosted) {
                    std::cout << "> Posted!" << std::endl;
                }
                else {
                    std::cout << "> It could not find the comment!" << std::endl;
                }
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "upvote") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                unsigned id;
                std::cin >> id;
                bool res = sys.upvote(id, userSys.getLoggedUser()->getId());
                if (res) {
                    std::cout << "> Voted!" << std::endl;
                }
                else {
                    std::cout << "> It could not find the comment!" << std::endl;
                }
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "downvote") == 0) {
            if (userSys.getLoggedUser() != nullptr) {
                unsigned id;
                std::cin >> id;
                bool res = sys.downvote(id, userSys.getLoggedUser()->getId());
                if (res) {
                    std::cout << "> Voted!" << std::endl;
                }
                else {
                    std::cout << "> It could not find the comment!" << std::endl;
                }
            }
            else {
                std::cout << "> Login first!" << std::endl;
            }
        }
        else if (strcmp(command, "p_close") == 0)
        {
            Post* leftPost = sys.closePost();
            if (leftPost != nullptr) {
                std::cout << "> You just left \"" << leftPost->getTitle() << "\"!" << std::endl;
            }
            else {
                std::cout << "There is no open post!" << std::endl;
            }
        }
        else if (strcmp(command, "quit") == 0)
        {
            Topic* leftTopic = sys.closeTopic();
            if (leftTopic != nullptr) {
                std::cout << "> You just left topic \"" << leftTopic->getTitle() << "\"!" << std::endl;
            }
            else {
                std::cout << "There is no open topic!" << std::endl;
            }
        }

        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        std::cout << "> ";
    }
}

