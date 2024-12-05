//
// Created by elif on 12/5/24.
//

#ifndef UPDATE_PERSON_REQUEST_HPP
#define UPDATE_PERSON_REQUEST_HPP
#include <string>
#include <crow.h>


class UpdatePersonRequest {
public:
    std::string id;
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    UpdatePersonRequest(const std::string id, const std::string name, const std::string surname, const std::string phone, const std::string mail)
        : id(id), name(name), surname(surname), phone(phone), mail(mail) {}


    static UpdatePersonRequest fromJson(const crow::json::rvalue &json) {
        return UpdatePersonRequest(
            json["id"].s(),
            json["name"].s(),
            json["surname"].s(),
            json["phone"].s(),
            json["mail"].s()
        );
    }

    crow::json::wvalue toJson() const {
        crow::json::wvalue result;
        result["id"] = id;
        result["name"] = name;
        result["surname"] = surname;
        result["phone"] = phone;
        result["mail"] = mail;
        return result;
    }
};


#endif //UPDATE_PERSON_REQUEST_HPP
