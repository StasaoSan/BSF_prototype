// #ifndef BSF_HANDLER_H
// #define BSF_HANDLER_H
// #include <string>
// #include <userver/components/component_list.hpp>
// #include <userver/server/handlers/http_handler_base.hpp>
//
//
// class HelloHandler final : public server::handlers::HttpHandlerBase {
// public:
//     // `kName` is used as the component name in static config
//     static constexpr std::string_view kName = "handler-hello-sample";
//
//     // Component is valid after construction and is able to accept requests
//     using HttpHandlerBase::HttpHandlerBase;
//
//     std::string HandleRequest(server::http::HttpRequest& request, server::request::RequestContext&) const override;
// };
//
//
//
// #endif //BSF_HANDLER_H
