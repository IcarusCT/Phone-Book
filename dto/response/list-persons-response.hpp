#ifndef LIST_PERSONS_RESPONSE_HPP
#define LIST_PERSONS_RESPONSE_HPP

#include <nlohmann/json.hpp>
#include <vector>

class ListPersonsResponse {
public:

    struct Person
    {
        std::string id;
        std::string name;
        std::string surname;
        std::string phone;
        std::string mail;

        Person() = default;
        Person(std::string id, std::string name, std::string surname, std::string phone, std::string mail)
            : id(std::move(id)), name(std::move(name)), surname(std::move(surname)), phone(std::move(phone)), mail(std::move(mail)) {

        }

        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Person, id, name, surname, phone)
    };

    ListPersonsResponse() = default;

    ListPersonsResponse(const std::vector<Person>& persons) : persons(persons) {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ListPersonsResponse, persons);

private:
    std::vector<Person> persons;
};

#endif // LIST_PERSONS_RESPONSE_HPP
