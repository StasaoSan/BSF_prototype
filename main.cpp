#include <fstream>
#include <iostream>
#include <string_view>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include "gen/model/PcfBindingPatch.h"
#include "UUID/UuidGenerator.h"
<<<<<<< Updated upstream
#include "PCF/DAO/InMemoryPcfBindingDao.h"
#include "PCF/Handler/PcfBindingHandler.h"
#include "PCF/Service/PcfBindingService.h"
#include "PCF/Service/PcfBindingServiceComponent.h"
#include "userver/logging/component.hpp"
#include "userver/server/component.hpp"
#include "userver/tracing/component.hpp"
=======
#include "PCF/DAO/PcfBinding/InMemoryPcfBindingDao.h"
#include "PCF/Handler/PcfBinding/PcfBindingHandler.h"
#include "PCF/Service/PcfBinding/PcfBindingService.h"
#include "PCF/Service/PcfBinding/PcfBindingServiceComponent.h"
#include "userver/logging/component.hpp"
#include "userver/server/component.hpp"
#include "userver/tracing/component.hpp"
#include "PCF/Service/PcfUeBinding/PcfUeBindingServiceComponent.h"
#include "PCF/Handler/PcfUeBinding/PcfUeBindingHandler.h"
>>>>>>> Stashed changes

int main(int argc, char* argv[]) {
    auto component_list = userver::components::MinimalServerComponentList();
    component_list.Append<PcfBindingServiceComponent>();
    component_list.Append<PcfBindingHandler>();

<<<<<<< Updated upstream
    auto dao = std::make_shared<InMemoryPcfBindingDao>(std::make_unique<UuidGenerator>());
    auto service = std::make_shared<PcfBindingService>(dao);

=======
    component_list.Append<PcfUeBindingServiceComponent>();
    component_list.Append<PcfUeBindingHandler>();

    auto dao = std::make_shared<InMemoryPcfBindingDao>(std::make_unique<UuidGenerator>());
    auto service = std::make_shared<PcfBindingService>(dao);

>>>>>>> Stashed changes
    return userver::utils::DaemonMain(argc, argv, component_list);
}