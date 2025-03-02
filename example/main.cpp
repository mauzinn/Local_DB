#include <iostream>
#include "../include/core/object.hpp"
#include "../include/managers/table.hpp"
#include "../include/utils/response.hpp"

int main() {
    Table users("users");

    if (users.haveHeader()) {
        users.loadDatabaseHeader();
    } else {
        users.setColumn("name", "1");
        users.setColumn("password", "1");
    }

    users.load();
    
    std::string buffer_text;
    while (true) {
        std::cout << "1->Login   2->Register   3->Quit\n";
        std::cin >> buffer_text;

        if (buffer_text == "1") {
            Object buffer_object;
            std::cout << "Enter your Name: ";
            std::cin >> buffer_text;
            buffer_object.setItem("name", buffer_text);

            std::cout << "Enter your Password: ";
            std::cin >> buffer_text;
            buffer_object.setItem("password", buffer_text);

            Response response = users.getObject("name", buffer_object.getValue("name"));
            if (response.success) {
                if (response.data.getValue("password") == buffer_object.getValue("password")) {
                    std::cout << "You are Logged.\n";
                } else {
                    std::cout << "Incorrect Password. Try again later\n";
                }
            } else {
                std::cout << "Name doens't Exist's.\n";
            }
        } else if (buffer_text == "2") {
            Object buffer_object;
            std::cout << "Enter a Name: ";
            std::cin >> buffer_text;
            buffer_object.setItem("name", buffer_text);

            std::cout << "Enter a Password: ";
            std::cin >> buffer_text;
            buffer_object.setItem("password", buffer_text);

            Response response = users.getObject("name", buffer_object.getValue("name"));

            if (!response.success) {
                users.setObject(buffer_object);
            } else {
                std::cout << "This Name is Alerdy used.\n";
            }
        } else {
            break;
        }

        users.save();
    }
    return 0;
}