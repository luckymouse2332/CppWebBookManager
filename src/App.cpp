#include "controller/MyController.hpp"
#include "AppComponents.hpp"

#include "oatpp/network/Server.hpp"

#include "oatpp-swagger/Controller.hpp"

void run()
{
  AppComponent components;

  // router
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  oatpp::web::server::api::Endpoints docEndpoints;

  docEndpoints.append(router->addController(MyController::createShared())->getEndpoints());

  router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

  // The router's http request handler
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  // TCP connections provider
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  // HTTP server
  oatpp::network::Server server(connectionProvider, connectionHandler);

  // log
  OATPP_LOGi(APP_NAME, "Running on port {}", connectionProvider->getProperty("port").toString());

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