#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "AppComponents.hpp"

void run()
{
    // router
    auto router = oatpp::web::server::HttpRouter::createShared();

    // The router's http request handler
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    // TCP connections provider
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});

    // HTTP server
    oatpp::network::Server server(connectionProvider, connectionHandler);


    auto port = connectionProvider->getProperty("port").getData();
    // log
    OATPP_LOGI("CppWebBookManager", "Running on port %s", port);

    // run server
    server.run();
}

int main()
{
    oatpp::base::Environment::init();

    run();

    oatpp::base::Environment::destroy();

    return 0;
}