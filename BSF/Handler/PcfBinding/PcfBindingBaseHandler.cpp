#include "PcfBindingBaseHandler.h"
#include "gen/nbsf-management/model/PcfBinding.h"
#include "userver/components/component_context.hpp"
#include "BSF/Service/PcfBinding/IPcfBindingService.h"
#include "BSF/Service/PcfBinding/PcfBindingServiceComponent.h"

PcfBindingBaseHandler::PcfBindingBaseHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : HttpHandlerBase(config, context)
{
    auto& service_component = context.FindComponent<PcfBindingServiceComponent>();
    m_service = service_component.GetService();
}