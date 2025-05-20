#include "PcfUeBindingService.h"
#include <boost/regex.hpp>

PcfUeBindingService::PcfUeBindingService(std::shared_ptr<IPcfUeBindingDao> dao)
        : m_dao(std::move(dao)) {}

std::uint64_t PcfUeBindingService::Register(const org::openapitools::server::model::PcfForUeBinding &binding) {
    Validate(binding);
    return m_dao->Register(binding);
}

bool PcfUeBindingService::Delete(std::uint64_t uuid) {
    return m_dao->Delete(uuid);
}

bool PcfUeBindingService::Exist(const org::openapitools::server::model::PcfForUeBinding &binding) {
    return m_dao->Exist(binding);
}

std::vector<org::openapitools::server::model::PcfForUeBinding>
PcfUeBindingService::FindByGpsi(const std::string &gpsi) const {
    return m_dao->FindByGpsi(gpsi);
}

std::vector<org::openapitools::server::model::PcfForUeBinding>
PcfUeBindingService::FindBySupi(const std::string &supi) const {
    return m_dao->FindBySupi(supi);
}

void PcfUeBindingService::Validate(const org::openapitools::server::model::PcfForUeBinding& binding) {
    if (binding.getSupi().empty() || !isValidSupi(binding.getSupi())) {
        throw std::invalid_argument("PcfUeBindingService::Validate: Supi is empty");
    }

    if (!binding.getGpsi().empty() && !isValidGpsi(binding.getGpsi())) {
        throw std::invalid_argument("Invalid GPSI format");
    }
    bool hasAddress = false;
    if (!binding.getPcfForUeFqdn().empty()) {
        if (!isValidFqdn(binding.getPcfForUeFqdn()))
            throw std::invalid_argument("Invalid pcfForUeFqdn format");
        hasAddress = true;
    }

    const auto& endpoints = binding.getPcfForUeIpEndPoints();
    if (!endpoints.empty()) {
        for (const auto& ep : endpoints)
            if (!isValidEndpoint(ep))
                throw std::invalid_argument("Invalid endpoint" + ep.toJsonString());
        hasAddress = true;
    }

    if (!hasAddress)
        throw std::invalid_argument("Either pcfForUeFqdn or pcfForUeIpEndPoints must be provided");
}


bool PcfUeBindingService::isValidSupi(const std::string &supi) {
    static const boost::regex re("^imsi-\\d{15}$");
    return boost::regex_match(supi, re);
}

bool PcfUeBindingService::isValidGpsi(const std::string &gpsi) {
    static const boost::regex re("^msisdn-\\d{10}$");
    return boost::regex_match(gpsi, re);
}

bool PcfUeBindingService::isValidFqdn(const std::string &fqdn) {
    boost::regex re(R"(^aaa://((\d{1,3}\.){3}\d{1,3}):\d{1,5}$)");
    return boost::regex_match(fqdn, re);
}

bool PcfUeBindingService::isValidEndpoint(const org::openapitools::server::model::IpEndPoint &endpoint) {
    auto port = endpoint.getPort();
    if (port == 0 || port > 65535)
        return false;
    auto ipAddr = endpoint.getIpv4Address();
    return isValidIpv4(ipAddr);
}

bool PcfUeBindingService::isValidIpv4(const std::string &ipAddr) {
    const std::string number_0_255 = "((([0-9])|([1-9][0-9])|(1[0-9][0-9]|2[0-4][0-9]|25[0-5])){1})";
    const std::string dot = "(\\.){1}";
    static const boost::regex pattern(number_0_255 + dot + number_0_255 + dot + number_0_255 + dot + number_0_255);
    return boost::regex_match(ipAddr, pattern);
}