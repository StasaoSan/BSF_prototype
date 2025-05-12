#include <fstream>
#include <iostream>
#include <string_view>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include "gen/model/PcfBindingPatch.h"
#include "UUID/UuidGenerator.h"
#include "PCF/DAO/PcfBinding/InMemoryPcfBindingDao.h"
#include "PCF/Handler/PcfBinding/PcfBindingBaseHandler.h"
#include "PCF/Handler/PcfBinding/Post/PcfBindingPostHandler.h"
#include "PCF/Handler/PcfBinding/Get/PcfBindingGetHandler.h"
#include "PCF/Handler/PcfBinding/Delete/PcfBindingDeleteHandler.h"
#include "PCF/Service/PcfBinding/PcfBindingService.h"
#include "PCF/Service/PcfBinding/PcfBindingServiceComponent.h"
#include "userver/logging/component.hpp"
#include "userver/server/component.hpp"
#include "userver/tracing/component.hpp"
#include "PCF/Service/PcfUeBinding/PcfUeBindingServiceComponent.h"
#include "PCF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.h"

int main(int argc, char* argv[]) {
    auto component_list = userver::components::MinimalServerComponentList();
    component_list.Append<PcfBindingServiceComponent>();
    component_list.Append<PcfBindingPostHandler>();
    component_list.Append<PcfBindingGetHandler>();
    component_list.Append<PcfBindingDeleteHandler>();

    component_list.Append<PcfUeBindingServiceComponent>();
    component_list.Append<PcfUeBindingBaseHandler>();

    auto dao = std::make_shared<InMemoryPcfBindingDao>(std::make_unique<UuidGenerator>());
    auto service = std::make_shared<PcfBindingService>(dao);

    return userver::utils::DaemonMain(argc, argv, component_list);
}