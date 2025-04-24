#include <fstream>
#include <iostream>
#include <string_view>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include "PCF/PCF_json_bridge.h"

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

    json j = json::parse(input);

    PCF_dto dto = j.get<PCF_dto>();
    std::cout << "parsing from JSON complete!" << std::endl;
    std::cout << "Parsed SUPI: " << (dto.supi ? *dto.supi : "(none)") << std::endl;
    std::cout << "DNN: " << dto.dnn << std::endl;
    std::cout << "SST: " << dto.snssai.sst << std::endl;
    std::cout << std::endl;
    json out = dto;
    std::cout << "parsing from raw data complete" <<std::endl;
    std::cout << "Serialized JSON:\n" << out.dump(2) << std::endl;
    return 0;
}