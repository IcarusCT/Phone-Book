//
// Created by elif on 12/2/24.
//

#ifndef PERSON_HPP
#define PERSON_HPP
#include <string>
#include <bsoncxx/types.hpp>
#include <regex>
#include <nlohmann/json.hpp>
#include "person-repository.hpp"


class Person {
public:
    std::string _id;
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    Person()= default;

    Person(const std::string &name, const std::string &surname, const std::string &phone,
           const std::string &mail)
        : name(name), surname(surname), phone(phone), mail(mail) {
    }

};

#endif //PERSON_HPP
