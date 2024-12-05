//
// Created by elif on 12/5/24.
//

#ifndef ADD_PERSON_REQUEST_HPP
#define ADD_PERSON_REQUEST_HPP
#include <string>


class AddPersonRequest {
public:

    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    AddPersonRequest(const std::string name, const std::string surname, const std::string phone, const std::string mail)
        : name(name), surname(surname), phone(phone), mail(mail) {}

    crow::json::wvalue toJson() const {
        crow::json::wvalue result;
        result["name"] = name;
        result["surname"] = surname;
        result["phone"] = phone;
        result["mail"] = mail;
        return result;
    }

};



#endif //ADD_PERSON_REQUEST_HPP
