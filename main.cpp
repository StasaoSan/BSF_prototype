#include <userver/components/run.hpp>
#include "hello_handler.h"
#include "src/handlers/hello_handler.h"

int main(int argc, char* argv[]) {
    auto component_list = userver::components::ComponentList()
        .Append<samples::hello::HelloHandler>();

    return userver::components::Run(argc, argv, component_list);
}