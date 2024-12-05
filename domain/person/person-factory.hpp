//
// Created by elif on 12/2/24.
//
#ifndef PERSON_FACTORY_HPP
#define PERSON_FACTORY_HPP
#include "person.hpp"

class PersonFactory {
public:
    PersonFactory() {

    }

    static Person createPersonFromDB(const bsoncxx::document::view& doc) {

        Person person;
        if (doc["_id"]) {
            person._id = doc["_id"].get_oid().value.to_string();
        }
        if (doc["name"]) {
            person.name = doc["name"].get_string().value.data();
        }
        if (doc["surname"]) {
            person.surname = doc["surname"].get_string().value.data();
        }
        if (doc["phone"]) {
            person.phone = doc["phone"].get_string().value.data();
        }
        if (doc["mail"]) {
            person.mail = doc["mail"].get_string().value.data();
        }
        return person;
    }

    static std::vector<Person> createListFromDB(mongocxx::cursor& cursor) {
        std::vector<Person> persons;

        for (const auto& doc : cursor) {
            Person person;
            if (doc["_id"]) {
                person._id = doc["_id"].get_oid().value.to_string();
            }
            if (doc["name"]) {
                person.name = doc["name"].get_string().value.data();
            }
            if (doc["surname"]) {
                person.surname = doc["surname"].get_string().value.data();
            }
            if (doc["phone"]) {
                person.phone = doc["phone"].get_string().value.data();
            }
            if (doc["mail"]) {
                person.mail = doc["mail"].get_string().value.data();
            }
            persons.emplace_back(createPersonFromDB(doc));
        }

        return persons;
    }

    bsoncxx::document::value createDocumentForDB(const std::string &name, const std::string &surname, const std::string &phone, const std::string &mail) {
        auto doc = bsoncxx::builder::basic::document{};
        doc.append(
            bsoncxx::builder::basic::kvp("name", name),
            bsoncxx::builder::basic::kvp("surname", surname),
            bsoncxx::builder::basic::kvp("phone", phone),
            bsoncxx::builder::basic::kvp("mail", mail)
        );

        return doc.extract();
    }

    bsoncxx::document::value createUpdatedDocumentForDB(const std::string &name, const std::string &surname, const std::string &phone, const std::string &mail) {
        auto doc = bsoncxx::builder::basic::document{};
        doc.append(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                                             bsoncxx::builder::basic::kvp("name", name),
                                             bsoncxx::builder::basic::kvp("surname",surname),
                                             bsoncxx::builder::basic::kvp("phone", phone),
                                             bsoncxx::builder::basic::kvp("mail", mail)
                                         ))
        );
        return doc.extract();
    }
};




#endif //PERSON_FACTORY_HPP
