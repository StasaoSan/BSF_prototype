#include "PcfUeBindingBaseHandler.h"
#include "../../Service/PcfUeBinding/IPcfUeBindingService.h"
#include "../../Service/PcfUeBinding/PcfUeBindingServiceComponent.h"

#include "userver/components/component_context.hpp"

PcfUeBindingBaseHandler::PcfUeBindingBaseHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : HttpHandlerBase(config, context)
{
    auto& service_component = context.FindComponent<PcfUeBindingServiceComponent>();
    m_service = service_component.GetService();
}