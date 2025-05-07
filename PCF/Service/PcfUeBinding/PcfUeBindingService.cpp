#include "PcfUeBindingService.h"

PcfUeBindingService::PcfUeBindingService(std::shared_ptr<IPcfUeBindingDao> dao)
        : m_dao(std::move(dao)) {}

std::uint64_t PcfUeBindingService::Register(const org::openapitools::server::model::PcfForUeBinding &binding) {
    return m_dao->Register(binding);
}

bool PcfUeBindingService::Delete(std::uint64_t uuid) {
    return m_dao->Delete(uuid);
}

std::vector<org::openapitools::server::model::PcfForUeBinding>
PcfUeBindingService::FindByGpsi(const std::string &gpsi) const {
    return m_dao->FindByGpsi(gpsi);
}

std::vector<org::openapitools::server::model::PcfForUeBinding>
PcfUeBindingService::FindBySupi(const std::string &supi) const {
    return m_dao->FindBySupi(supi);
}