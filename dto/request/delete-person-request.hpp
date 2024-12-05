//
// Created by elif on 12/5/24.
//

#ifndef DELETE_PERSON_REQUEST_HPP
#define DELETE_PERSON_REQUEST_HPP
#include <string>
#include <crow.h>


class DeletePersonRequest {
public:
    std::string id;

    DeletePersonRequest(const std::string& id) : id(id) {}

    static DeletePersonRequest fromJson(const crow::json::rvalue& json) {
        return DeletePersonRequest(json["id"].s());
    }

    crow::json::wvalue toJson() const {
        crow::json::wvalue result;
        result["id"] = id;
        return result;
    }
};



#endif //DELETE_PERSON_REQUEST_HPP
