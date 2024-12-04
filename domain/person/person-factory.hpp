//
// Created by elif on 12/2/24.
//
#ifndef PERSON_FACTORY_HPP
#define PERSON_FACTORY_HPP
#include "person.hpp"

class PersonFactory {
public:
    static Person createPerson(const int row, const std::string &name, const std::string &surname,
                               const std::string &phone, const std::string &mail) {
        Person person(row, name, surname, phone, mail);

        return person;
    }
};

#endif //PERSON_FACTORY_HPP
