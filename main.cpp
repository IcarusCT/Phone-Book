#include <iostream>
#include <crow/app.h>
#include <asio.hpp>
#include <mongocxx/client.hpp>
#include "person/person-repository.hpp"
#include "person/person.hpp"
#include <mongocxx/exception/exception.hpp>
#include "person/person-service.hpp"
#include "phonebook-management-service.hpp"
#include <crow/json.h>


void print_info(const Person &person) {
    std::cout << "ID: " << person._id << std::endl;
    std::cout << "Name: " << person.name << std::endl;
    std::cout << "Surname: " << person.surname << std::endl;
    std::cout << "Phone: " << person.phone << std::endl;
    std::cout << "Mail: " << person.mail << std::endl;
    std::cout << "------------------------------" << std::endl;
}

int main() {
    crow::SimpleApp app;

    PersonRepository repository;
    PersonFactory factory;
    PersonService service(repository, factory);
    PhonebookManagementService phonebookService(service);

    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
    auto db = client["phonebook"];
    auto collection = db["contacts"];

    CROW_ROUTE(app, "/add_person").methods(crow::HTTPMethod::POST)(
        [&phonebookService](const crow::request &req) {
            auto json_data = crow::json::load(req.body);
            if (!json_data) {
                return crow::response(400, "Hata");
            }

            std::string name = json_data["name"].s();
            std::string surname = json_data["surname"].s();
            std::string phone = json_data["phone"].s();
            std::string mail = json_data["mail"].s();

            try {
                phonebookService.addPersonToPhonebook(name, surname, phone, mail);
                return crow::response(200, "Kişi başarıyla oluşturuldu.");
            } catch (const std::exception &e) {
                return crow::response(400, e.what());
            }
        });

    CROW_ROUTE(app, "/search_person").methods(crow::HTTPMethod::GET)(
        [&phonebookService](const crow::request &req) {
            auto id = req.url_params.get("id");
            if (!id) {
                return crow::response(400, "Id parametresi alınamadı.");
            }

            try {
                auto person = phonebookService.findPersonsById(id);
                //alınan data DtoAssembler'a gider, burada SearchPersonResponse oluşur, sonra dönüş yapılır.
                crow::json::wvalue result;
                result["name"] = person.name;
                result["surname"] = person.surname;
                result["phone"] = person.phone;
                result["mail"] = person.mail;
                return crow::response(result);
            } catch (const std::exception) {
                return crow::response(404, "Kişi bulunamadı.");
            }
        });

    CROW_ROUTE(app, "/update_person/<string>").methods(crow::HTTPMethod::PUT)(
        [&phonebookService](const crow::request &req, const std::string &id) {
            auto json_data = crow::json::load(req.body);
            if (!json_data) {
                return crow::response(400, "Hata");
            }

            std::string name = json_data["name"].s();
            std::string surname = json_data["surname"].s();
            std::string phone = json_data["phone"].s();
            std::string mail = json_data["mail"].s();

            try {
                phonebookService.updatePerson(id, name, surname, phone, mail);
                return crow::response(200, "Kişi başarıyla güncellendi.");
            } catch (const std::exception &e) {
                return crow::response(400, e.what());
            }
        });

    CROW_ROUTE(app, "/delete_person").methods(crow::HTTPMethod::DELETE)(
        [&phonebookService]( const crow::request &req) {
            auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "Hata");
        }
            std::string id = json_data["id"].s();
            try {
                phonebookService.deletePerson(id);
                return crow::response(200, "Kişi başarıyla silindi.");
            } catch (const std::exception &e) {
                return crow::response(400, e.what());
            }
        });

    CROW_ROUTE(app, "/list_all").methods(crow::HTTPMethod::GET)(
     [&phonebookService]() {
         auto persons = phonebookService.listAllPersons();

         crow::json::wvalue result;
         crow::json::wvalue::list json_array;

         for (const auto &person : persons) {
             crow::json::wvalue person_obj;
             person_obj["name"] = person.name;
             person_obj["surname"] = person.surname;
             person_obj["phone"] = person.phone;
             person_obj["mail"] = person.mail;

             json_array.emplace_back(std::move(person_obj));
         }

         result["persons"] = std::move(json_array);
         return crow::response(std::move(result));
     });

    app.port(8080).multithreaded().run();
}
