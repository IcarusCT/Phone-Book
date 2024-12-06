#include <iostream>
#include <crow/app.h>
#include <asio.hpp>
#include <mongocxx/client.hpp>
#include "person/person-repository.hpp"
#include "person/person.hpp"
#include <mongocxx/exception/exception.hpp>
#include "person/person-service.hpp"
#include "phonebook-management-service.hpp"
#include "dto/dto-assembler.hpp"
#include "dto/request/add-person-request.hpp"
#include "dto/response/list-persons-response.hpp"
#include "dto/response/search-person-response.hpp"
#include <crow/json.h>
#include <nlohmann/json.hpp>

using nlohmann::json;


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
            try {
                AddPersonRequest requestDto = json::parse(req.body);

                phonebookService.addPersonToPhonebook(
                    requestDto.name,
                    requestDto.surname,
                    requestDto.phone,
                    requestDto.mail
                );
                return crow::response(200, "Kişi başarıyla oluşturuldu.");
            } catch (const std::exception) {
                return crow::response(400);
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

                json responseDto = DtoAssembler::toSearchPersonResponse(person);

                return crow::response("application/json", responseDto.dump());
            } catch (const std::exception) {
                return crow::response(404, "Kişi bulunamadı.");
            }
        });

    CROW_ROUTE(app, "/update_person").methods(crow::HTTPMethod::PUT)(
        [&phonebookService](const crow::request &req) {
            auto json_data = crow::json::load(req.body);
            if (!json_data) {
                return crow::response(400, "Hata");
            }
            try {
                UpdatePersonRequest requestDto = json::parse(req.body);
                phonebookService.updatePerson(
                    requestDto.id,
                    requestDto.name,
                    requestDto.surname,
                    requestDto.phone,
                    requestDto.mail);

                return crow::response(200, "Kişi başarıyla güncellendi.");
            } catch (const std::exception &e) {
                return crow::response(400, e.what());
            }
        });

    CROW_ROUTE(app, "/delete_person").methods(crow::HTTPMethod::DELETE)(
        [&phonebookService](const crow::request &req) {
            try {
                DeletePersonRequest requestDto = json::parse(req.body);
                phonebookService.deletePerson(requestDto.id);

                return crow::response("application/json", requestDto.id);
            } catch (const std::exception &e) {
                return crow::response(400, e.what());
            }
        });

    CROW_ROUTE(app, "/list_all").methods(crow::HTTPMethod::GET)(
        [&phonebookService]() {
            auto persons = phonebookService.listAllPersons();
            json responseDto = DtoAssembler::toListPersonsResponse(persons);

            return crow::response("application/json", responseDto.dump());
        });

    app.port(8080).multithreaded().run();
}
