//
// Created by elif on 12/5/24.
//

#ifndef SEARCH_PERSON_RESPONSE_HPP
#define SEARCH_PERSON_RESPONSE_HPP
#include <nlohmann/json.hpp>


class SearchPersonResponse {
public:
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    SearchPersonResponse() = default;
    SearchPersonResponse(const std::string& name, const std::string& surname,
                     const std::string& phone, const std::string& mail)
    : name(name), surname(surname), phone(phone), mail(mail) {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(SearchPersonResponse, name, surname, phone, mail);
};


#endif //SEARCH_PERSON_RESPONSE_HPP
