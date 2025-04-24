#pragma once
#include <iostream>
#include "PCF_dto.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// ipEndPoint
void to_json(json& j, const IpEndPoint& p) {
    j = json{{"ipv4Address", p.ipv4Address}, {"port", p.port}};
}

void from_json(const json& j, IpEndPoint& p) {
    j.at("ipv4Address").get_to(p.ipv4Address);
    j.at("port").get_to(p.port);
}

// snssai
void to_json(json& j, const Snssai& s) {
    j = json{{"sst", s.sst}};
    if (s.sd) j["sd"] = *s.sd;
}

void from_json(const json& j, Snssai& s) {
    j.at("sst").get_to(s.sst);
    if (j.contains("sd")) s.sd = j.at("sd").get<int>();
}

// PCF_dto
void to_json(json& j, const PCF_dto& dto) {
    j = json{{"dnn", dto.dnn}, {"snssai", dto.snssai}};
    if (dto.supi) j["supi"] = *dto.supi;
    if (dto.pcfIpEndPoints) j["pcfIpEndPoints"] = *dto.pcfIpEndPoints;
}

void from_json(const json& j, PCF_dto& dto) {
    if (j.contains("supi")) dto.supi = j.at("supi").get<std::string>();
    j.at("dnn").get_to(dto.dnn);
    j.at("snssai").get_to(dto.snssai);
    if (j.contains("pcfIpEndPoints")) dto.pcfIpEndPoints = j.at("pcfIpEndPoints").get<std::vector<IpEndPoint>>();
}

