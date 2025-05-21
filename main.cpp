#include <fstream>
#include <iostream>
#include <string_view>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include "gen/nbsf-management/model/PcfBindingPatch.h"
#include "UUID/UuidGenerator.h"
#include "BSF/DAO/PcfBinding/InMemoryPcfBindingDao.h"
#include "BSF/Handler/PcfBinding/PcfBindingBaseHandler.h"
#include "BSF/Handler/PcfBinding/Post/PcfBindingPostHandler.h"
#include "BSF/Handler/PcfBinding/Get/PcfBindingGetHandler.h"
#include "BSF/Handler/PcfBinding/Delete/PcfBindingDeleteHandler.h"
#include "BSF/Service/PcfBinding/PcfBindingService.h"
#include "BSF/Service/PcfBinding/PcfBindingServiceComponent.h"
#include "userver/logging/component.hpp"
#include "userver/server/component.hpp"
#include "userver/tracing/component.hpp"
#include "BSF/Service/PcfUeBinding/PcfUeBindingServiceComponent.h"
#include "BSF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.h"
#include "BSF/Handler/PcfUeBinding/Delete/PcfUeBindingDeleteHandler.h"
#include "BSF/Handler/PcfUeBinding/Get/PcfUeBindingGetHandler.h"
#include "BSF/Handler/PcfUeBinding/Post/PcfUeBindingPostHandler.h"

int main(int argc, char* argv[]) {
    auto component_list = userver::components::MinimalServerComponentList();
    component_list.Append<PcfBindingServiceComponent>();
    component_list.Append<PcfBindingPostHandler>();
    component_list.Append<PcfBindingGetHandler>();
    component_list.Append<PcfBindingDeleteHandler>();

    component_list.Append<PcfUeBindingServiceComponent>();
    component_list.Append<PcfUeBindingPostHandler>();
    component_list.Append<PcfUeBindingGetHandler>();
    component_list.Append<PcfUeBindingDeleteHandler>();

    auto dao = std::make_shared<InMemoryPcfBindingDao>(std::make_unique<UuidGenerator>());
    auto service = std::make_shared<PcfBindingService>(dao);

    return userver::utils::DaemonMain(argc, argv, component_list);
}
