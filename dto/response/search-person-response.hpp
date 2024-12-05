//
// Created by elif on 12/5/24.
//

#ifndef SEARCH_PERSON_RESPONSE_HPP
#define SEARCH_PERSON_RESPONSE_HPP


class SearchPersonResponse {
public:
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    SearchPersonResponse(std::string name, std::string surname, std::string phone, std::string mail)
        : name(name), surname(surname), phone(phone), mail(mail) {
    }

    crow::json::wvalue toJson() const {
        crow::json::wvalue result;
        result["name"] = name;
        result["surname"] = surname;
        result["phone"] = phone;
        result["mail"] = mail;
        return result;
    }
};


#endif //SEARCH_PERSON_RESPONSE_HPP
