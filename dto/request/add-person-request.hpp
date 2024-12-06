//
// Created by elif on 12/5/24.
//

#ifndef ADD_PERSON_REQUEST_HPP
#define ADD_PERSON_REQUEST_HPP
#include <string>
#include <nlohmann/json.hpp>


class AddPersonRequest {
public:
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    AddPersonRequest() = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AddPersonRequest, name, surname, phone, mail)
};


#endif //ADD_PERSON_REQUEST_HPP
