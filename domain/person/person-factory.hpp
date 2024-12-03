//
// Created by elif on 12/2/24.
//
#ifndef PERSON_FACTORY_HPP
#define PERSON_FACTORY_HPP
#include "person.hpp"
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/collection.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/document/value.hpp>
#include "person-repository.hpp"


class PersonFactory {

    static Person createPerson(const int row, const std::string& name, const std::string& surname, const std::string& phone, const std::string& mail) {

        Person person(row, name, surname, phone, mail);

        return person;
    }
};

#endif //PERSON_FACTORY_HPP
