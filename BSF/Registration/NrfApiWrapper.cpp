//
// Created by tikhonov-a on 5/27/25.
//
#include "gen/nrf-nfm-restsdk/include/CppRestOpenAPIClient/ModelBase.h"

template<>
web::json::value org::openapitools::client::model::ModelBase::toJson<std::string>(const std::shared_ptr<std::string>& val) {
    if (!val) return web::json::value::null();
    return web::json::value::string(*val);
}

template<>
bool org::openapitools::client::model::ModelBase::fromJson<std::string>(const web::json::value& val, std::shared_ptr<std::string> &outVal) {
    if (val.is_null()) { outVal.reset(); return true; }
    outVal = std::make_shared<std::string>(val.as_string());
    return true;
}
