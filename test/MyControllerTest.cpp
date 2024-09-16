#include "MyControllerTest.hpp"

#include "controller/MyController.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp-test/web/ClientServerTestRunner.hpp"

void MyControllerTest::onRun() {
  TestComponent components; // Register components

  oatpp::test::web::ClientServerTestRunner runner;

  runner.addController(std::make_shared<MyController>());

  runner.run([this, &runner] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers);

    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);
    auto client = MyApiTestClient::createShared(requestExecutor, contentMappers->getMapper("application/json"));

    auto response = client->getRoot();

    OATPP_ASSERT(response->getStatusCode() == 200);

    auto message = response->readBodyToDto<oatpp::Object<MessageDto>>( // Select mapper by headers
      contentMappers->selectMapperForContent(response->getHeader("Content-Type")));

    OATPP_ASSERT(message->message);
    OATPP_ASSERT(message->statusCode == 200);
    OATPP_ASSERT(message->message == "Hello world!");
  }, std::chrono::seconds(10));

  // Wait for server threads
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
