#include <fstream>
#include <iostream>
#include <string_view>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include "gen/model/PcfBindingPatch.h"

class AboutHandler final : public server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-about";
    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(const server::http::HttpRequest&,
                                   server::request::RequestContext&) const override {
        return "Hello World! I am a new BSF node!";
    }
};

int main() {
    std::string file = "../data.json";
    std::ifstream in(file);
    if (!in.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    std::string input((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());
    in.close();
    org::openapitools::server::model::PcfBindingPatch patch;
    patch.fromJsonString(input);
    std::cout << "JSON to data parse" << std::endl;
    std::cout << patch.getIpv4Addr() << std::endl;
    std::cout << patch.getPcfFqdn() << std::endl << std::endl;

    std::cout << "data to JSON parse" << std::endl;
    std::string data = patch.toJsonString(true);
    std::cout << data << std::endl;
    return 0;
}