#pragma once
#include <optional>
#include <string>
#include <vector>
struct Snssai {
    int sst;
    std::optional<int> sd;
};

struct IpEndPoint {
    std::string ipv4Address;
    int port;
};

struct PCF_dto {
    std::optional<std::string> supi; //
    std::optional<std::string> gpsi;
    std::optional<std::string> ipv4Addr; //
    std::optional<std::string> ipv6Prefix;
    std::optional<std::vector<std::string>> addIpv6Prefixes;
    std::optional<std::string> ipDomain;
    std::optional<std::string> macAddr48;
    std::optional<std::vector<std::string>> addMacAddrs;
    std::string dnn; //
    std::optional<std::string> pcfFqdn;
    std::optional<std::vector<IpEndPoint>> pcfIpEndPoints; //
    std::optional<std::string> pcfDiamHost;
    std::optional<std::string> pcfDiamRealm;
    std::optional<std::string> pcfSmFqdn;
    std::optional<std::vector<IpEndPoint>> pcfSmIpEndPoints;
    Snssai snssai; //
    std::optional<std::string> suppFeat; //
    std::optional<std::string> pcfId;
    std::optional<std::string> pcfSetId;
    std::optional<std::string> recoveryTime;
    std::optional<std::string> paraCom;
    std::optional<std::string> bindLevel;
    std::optional<std::vector<std::string>> ipv4FrameRouteList;
    std::optional<std::vector<std::string>> ipv6FrameRouteList;
};