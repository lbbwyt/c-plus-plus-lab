//
// Created by lbb on 2022/12/28.
//

#ifndef LIBHV_STUDY_CALC_H
#define LIBHV_STUDY_CALC_H
#include "../router.h"

#include "../generated/calc.pb.h"

void calc_add(const protorpc::Request& req, protorpc::Response* res) {
    // params
    if (req.params_size() != 2) {
        return bad_request(req, res);
    }
    protorpc::CalcParam param1, param2;
    if (!param1.ParseFromString(req.params(0)) ||
        !param2.ParseFromString(req.params(1))) {
        return bad_request(req, res);
    }

    // result
    protorpc::CalcResult result;
    result.set_num(param1.num() + param2.num());
    res->set_result(result.SerializeAsString());
}

void calc_sub(const protorpc::Request& req, protorpc::Response* res) {
    // params
    if (req.params_size() != 2) {
        return bad_request(req, res);
    }
    protorpc::CalcParam param1, param2;
    if (!param1.ParseFromString(req.params(0)) ||
        !param2.ParseFromString(req.params(1))) {
        return bad_request(req, res);
    }

    // result
    protorpc::CalcResult result;
    result.set_num(param1.num() - param2.num());
    res->set_result(result.SerializeAsString());
}

void calc_mul(const protorpc::Request& req, protorpc::Response* res) {
    // params
    if (req.params_size() != 2) {
        return bad_request(req, res);
    }
    protorpc::CalcParam param1, param2;
    if (!param1.ParseFromString(req.params(0)) ||
        !param2.ParseFromString(req.params(1))) {
        return bad_request(req, res);
    }

    // result
    protorpc::CalcResult result;
    result.set_num(param1.num() * param2.num());
    res->set_result(result.SerializeAsString());
}

void calc_div(const protorpc::Request& req, protorpc::Response* res) {
    // params
    if (req.params_size() != 2) {
        return bad_request(req, res);
    }
    protorpc::CalcParam param1, param2;
    if (!param1.ParseFromString(req.params(0)) ||
        !param2.ParseFromString(req.params(1))) {
        return bad_request(req, res);
    }
    if (param2.num() == 0) {
        return bad_request(req, res);
    }

    // result
    protorpc::CalcResult result;
    result.set_num(param1.num() / param2.num());
    res->set_result(result.SerializeAsString());
}

#endif //LIBHV_STUDY_CALC_H
