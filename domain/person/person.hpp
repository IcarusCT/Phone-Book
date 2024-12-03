//
// Created by elif on 12/2/24.
//

#ifndef PERSON_HPP
#define PERSON_HPP
#include <string>
#include <bsoncxx/types.hpp>
#include <regex>

#include "person-repository.hpp"


class Person {

public:

    bsoncxx::oid id;
    int row;
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    Person() : id(bsoncxx::oid()), row(0) {}

    Person(const int row, const std::string& name, const std::string& surname, const std::string& phone, const std::string& mail)
        : id(bsoncxx::oid()) , row(0), name(name), surname(surname), phone(phone), mail(mail) {}

    explicit Person(bsoncxx::document::view view);
};

#endif //PERSON_HPP
