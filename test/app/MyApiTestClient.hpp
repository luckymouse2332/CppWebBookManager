#ifndef MY_API_TEST_CLIENT
#define MY_API_TEST_CLIENT

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class MyApiTestClient : public oatpp::web::client::ApiClient {
  API_CLIENT_INIT(MyApiTestClient)

  API_CALL("GET", "/", getRoot)
};

#include OATPP_CODEGEN_END(ApiClient)

#endif