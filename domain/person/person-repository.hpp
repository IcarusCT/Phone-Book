//
// Created by elif on 12/2/24.
//

#ifndef PERSON_REPOSITORY_HPP
#define PERSON_REPOSITORY_HPP
#include <mongocxx/client.hpp>
#include <mongocxx/collection.hpp>
#include "person/person.hpp"


class PersonRepository {
public:
    PersonRepository()
        : client(mongocxx::uri{}),
          collection(client["phonebook"]["contacts"]) {
    }


    void add(const Person &person) {
        int nextRow = 1;
        auto cursor = collection.find({});
        for (auto &&doc: cursor) {
            if (doc.find("row") != doc.end()) {
                int currentRow = doc["row"].get_int32();
                if (currentRow >= nextRow) {
                    nextRow = currentRow + 1;
                }
            } //get max row tarzı bişey yazabilirsin buraya daha kısa
        }
        auto doc = bsoncxx::builder::basic::document{};
        doc.append(
            bsoncxx::builder::basic::kvp("row", nextRow),
            bsoncxx::builder::basic::kvp("name", person.name),
            bsoncxx::builder::basic::kvp("surname", person.surname),
            bsoncxx::builder::basic::kvp("phone", person.phone),
            bsoncxx::builder::basic::kvp("mail", person.mail)

        );
        collection.insert_one(doc.view());
    }

    void update(const int row, const Person &updated_person) {
        auto result = collection.update_one(
            bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("row", row)),
            bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                                                 bsoncxx::builder::basic::kvp("name", updated_person.name),
                                                 bsoncxx::builder::basic::kvp("surname", updated_person.surname),
                                                 bsoncxx::builder::basic::kvp("phone", updated_person.phone),
                                                 bsoncxx::builder::basic::kvp("mail", updated_person.mail))
                )
            )
        );
    }


    void remove(int row) {
        auto filter = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("row", row));

        auto result = collection.delete_one(filter.view());
    }

    Person findByRow(int row) {
        auto result = collection.find_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("row", row)

        ));


        if (result) {
            return Person(bsoncxx::document::value(result->view()));
        }
    }

    std::vector<Person> findPersonsByName(const std::string &name) {
        std::vector<Person> persons;

        auto cursor = collection.find(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("name", name)));

        for (auto &&doc: cursor) {
            Person person;
            if (doc["row"]) person.row = doc["row"].get_int32().value;
            if (doc["name"]) person.name = doc["name"].get_string().value.data();
            if (doc["surname"]) person.surname = doc["surname"].get_string().value.data();
            if (doc["phone"]) person.phone = doc["phone"].get_string().value.data();
            if (doc["mail"]) person.mail = doc["mail"].get_string().value.data();

            persons.push_back(person);
        }
        return persons;
    }

    std::vector<Person> listAll() {
        std::vector<Person> persons;

        for (auto &&doc: collection.find({})) {
            Person person;
            if (doc["row"]) person.row = doc["row"].get_int32().value;
            if (doc["name"]) person.name = doc["name"].get_string().value.data();
            if (doc["surname"]) person.surname = doc["surname"].get_string().value.data();
            if (doc["phone"]) person.phone = doc["phone"].get_string().value.data();
            if (doc["mail"]) person.mail = doc["mail"].get_string().value.data();

            persons.push_back(person);
        }

        return persons;
    }

private:
    mongocxx::client client;
    mongocxx::collection collection;
};
#endif //PERSON_REPOSITORY_HPP
