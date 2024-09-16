#include "controller/MyController.hpp"
#include "AppComponents.hpp"

#include "oatpp/network/Server.hpp"

void run()
{
  AppComponent components;

  // router
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  router->addController(std::make_shared<MyController>());

  // The router's http request handler
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  // TCP connections provider
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  // HTTP server
  oatpp::network::Server server(connectionProvider, connectionHandler);

  // log
  OATPP_LOGi("CppWebBookManager", "Running on port {}", connectionProvider->getProperty("port").toString());

  // run server
  server.run();
}

int main()
{
  oatpp::Environment::init();

  run();

  oatpp::Environment::destroy();

  return 0;
}