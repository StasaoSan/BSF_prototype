#include "PcfBindingService.h"
#include <boost/regex.hpp>

PcfBindingService::PcfBindingService(const std::shared_ptr<IPcfBindingDao>& dao) {
    m_dao = dao;
}

int64_t PcfBindingService::Register(org::openapitools::server::model::PcfBinding binding) {
    Validate(binding);
    return m_dao->Register(binding);
}

bool PcfBindingService::Delete(std::uint64_t uuid) {
    return m_dao->Delete(uuid);
}

std::optional<org::openapitools::server::model::PcfBinding> PcfBindingService::FindByIpv4(std::string ipv4) {
    return m_dao->FindByIpv4(ipv4);
}

std::optional<org::openapitools::server::model::PcfBinding> PcfBindingService::FindByMac(std::string mac) {
    return m_dao->FindByMac(mac);
}

void PcfBindingService::Validate(const org::openapitools::server::model::PcfBinding& binding) {
    bool has_valid_address = false;

    if (!binding.getIpv4Addr().empty()) {
        if (!isValidIPv4(binding.getIpv4Addr()))
            throw std::invalid_argument("Invalid IPv4 address format");
        has_valid_address = true;
    }

    // IPv6Prefix.h ??? hasnt storage for ipv6...
    // if need work with ipv6: also need validation here:
    // now ipv6 just ignore
    //
    // const auto &pt =  binding.getIpv6Prefix().toPropertyTree();
    // const auto &ipv6 = pt.get_value<std::string>();
    //
    // if (!ipv6.empty()) {
    //     if (!isValidIPv6(ipv6)) {
    //         throw std::invalid_argument("Invalid IPv6 address format");
    //     }
    //     has_valid_address = true;
    // }

    if (!binding.getMacAddr48().empty()) {
        if (!isValidMac(binding.getMacAddr48()))
            throw std::invalid_argument("Invalid MAC address format");
        has_valid_address = true;
    }

    if (!has_valid_address)
        throw std::invalid_argument("At least one of ipv4Addr, ipv6Prefix or macAddr48 must be provided");

    if (binding.getDnn().empty())
        throw std::invalid_argument("DNN must not be empty");

    if (binding.getSnssai().getSst() == 0)
        throw std::invalid_argument("SNSSAI SST must not be zero");
}

bool PcfBindingService::isValidIPv4(const std::string &ipv4){
    const std::string number_0_255 = "((([0-9])|([1-9][0-9])|(1[0-9][0-9]|2[0-4][0-9]|25[0-5])){1})";
    const std::string dot = "(\\.){1}";
    static const boost::regex pattern(number_0_255 + dot + number_0_255 + dot + number_0_255 + dot + number_0_255);
    return boost::regex_match(ipv4, pattern);
}

bool PcfBindingService::isValidIPv6(const std::string& ipv6) {
    static const boost::regex pattern(
            R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)"
        );
    return boost::regex_match(ipv6, pattern);
}

bool PcfBindingService::isValidMac(const std::string& mac) {
    const boost::regex pattern(
          R"(^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$)"
      );
    return boost::regex_match(mac, pattern);
}
