#ifndef MY_CONTROLLER
#define MY_CONTROLLER

#include "constants/LogFlag.hpp"

// Dto
#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"

// macros to inject component
#include "oatpp/macro/component.hpp"

// macros to create endpoints
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * Use API Controller instead of reqeust handler
 */
class MyController : public oatpp::web::server::api::ApiController
{
public:
  MyController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers))
      : oatpp::web::server::api::ApiController(contentMappers) {}

public:
  static std::shared_ptr<MyController> createShared(
      OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
  )
  {
    return std::make_shared<MyController>(apiContentMappers);
  }

  ENDPOINT("GET", "/", getHome)
  {
    auto dto = MessageDto::createShared();

    dto->statusCode = 200;
    dto->message = "Hello world!";

    return createDtoResponse(Status::CODE_200, dto);
  }
};

#include OATPP_CODEGEN_END(ApiController)

#endif