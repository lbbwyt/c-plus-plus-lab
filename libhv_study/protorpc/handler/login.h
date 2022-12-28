//
// Created by lbb on 2022/12/28.
//

#ifndef LIBHV_STUDY_LOGIN_H
#define LIBHV_STUDY_LOGIN_H


#include "../router.h"

#include "../generated/login.pb.h"

void login(const protorpc::Request& req, protorpc::Response* res) {
    // params
    if (req.params_size() == 0) {
        return bad_request(req, res);
    }
    protorpc::LoginParam param;
    if (!param.ParseFromString(req.params(0))) {
        return bad_request(req, res);
    }

    // result
    protorpc::LoginResult result;
    result.set_user_id(123456);
    result.set_token(param.username() + ":" + param.password());
    res->set_result(result.SerializeAsString());
}



#endif //LIBHV_STUDY_LOGIN_H
