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


    void add(const bsoncxx::document::value &person) {
        collection.insert_one({person});
    }

    void update(const std::string &id, const bsoncxx::document::value &person) {
        auto result = collection.update_one(
            bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("_id", bsoncxx::oid{id})),
            {person}
        );
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
            return factory.createPersonFromDB(result->view());
        }
        throw std::runtime_error("id bulunamadı");
    }

    std::vector<Person> listAll() {
        std::vector<Person> persons;
        auto cursor = collection.find({});
        return factory.createListFromDB(cursor);
    }

private:
    mongocxx::client client;
    mongocxx::collection collection;
};
#endif //PERSON_REPOSITORY_HPP
