//
// Created by elif on 12/2/24.
//

#ifndef PERSON_REPOSITORY_HPP
#define PERSON_REPOSITORY_HPP
#include <mongocxx/client.hpp>
#include <mongocxx/collection.hpp>
#include "person/person.hpp"
#include "person/person-factory.hpp"

class PersonRepository {
    PersonFactory factory;
public:
    PersonRepository()
        : client(mongocxx::uri{}),
          collection(client["phonebook"]["contacts"]) {
    }


    void add(const Person &person) {
        auto doc = bsoncxx::builder::basic::document{};
        doc.append(
            bsoncxx::builder::basic::kvp("name", person.name),
            bsoncxx::builder::basic::kvp("surname", person.surname),
            bsoncxx::builder::basic::kvp("phone", person.phone),
            bsoncxx::builder::basic::kvp("mail", person.mail)

        );
        Person newPerson = PersonFactory::createPerson( person.name , person.surname , person.phone , person.mail);
        collection.insert_one(doc.view());
    }

    void update(const std::string &id, const Person &updated_person) {
        bsoncxx::oid oid(id);
        auto result = collection.update_one(
        bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("_id", oid)
        ),
        bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("name", updated_person.name),
                bsoncxx::builder::basic::kvp("surname", updated_person.surname),
                bsoncxx::builder::basic::kvp("phone", updated_person.phone),
                bsoncxx::builder::basic::kvp("mail", updated_person.mail)
            ))
        )
    );
        Person updatedPerson = PersonFactory::createPerson(updated_person.name, updated_person.surname, updated_person.phone, updated_person.mail);

    }


    void remove(const std::string &id) {
        bsoncxx::oid oid(id);
        const auto filter = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("_id", oid));

        auto result = collection.delete_one(filter.view());
    }

    Person findById(const std::string &id) {
        bsoncxx::oid oid(id);
        auto result = collection.find_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("_id", oid)
        ));
        if (result) {
            Person person;
            auto doc = result->view();
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
            throw std::runtime_error("id bulunamadı");

    }

    std::vector<Person> listAll() {
        std::vector<Person> persons;

        for (auto &&doc: collection.find({})) {
            std::string id = doc["_id"].get_oid().value.to_string();
            std::string name = doc["name"].get_string().value.data();
            std::string surname = doc["surname"].get_string().value.data();
            std::string phone = doc["phone"].get_string().value.data();
            std::string mail = doc["mail"].get_string().value.data();

            persons.push_back(PersonFactory::createPerson(name, surname, phone, mail));
        }

        return persons;
    }

private:
    mongocxx::client client;
    mongocxx::collection collection;
};
#endif //PERSON_REPOSITORY_HPP
