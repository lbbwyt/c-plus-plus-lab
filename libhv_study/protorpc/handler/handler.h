//
// Created by lbb on 2022/12/28.
//

#ifndef LIBHV_STUDY_HANDLER_H
#define LIBHV_STUDY_HANDLER_H
#include "../router.h"

void error_response(protorpc::Response* res, int code, const std::string& message) {
    res->mutable_error()->set_code(code);
    res->mutable_error()->set_message(message);
}

void not_found(const protorpc::Request& req, protorpc::Response* res) {
    error_response(res, 404, "Not Found");
}

void bad_request(const protorpc::Request& req, protorpc::Response* res) {
    error_response(res, 400, "Bad Request");
}
#endif //LIBHV_STUDY_HANDLER_H
