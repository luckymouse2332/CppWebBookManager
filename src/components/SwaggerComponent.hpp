#ifndef SWAGGER_COMPONENT
#define SWAGGER_COMPONENT

#include "oatpp/macro/component.hpp"

// Swagger-ui headers
#include "oatpp-swagger/Resources.hpp"
#include "oatpp-swagger/Model.hpp"

#include "oatpp/base/Log.hpp"
#include "constants/LogFlag.hpp"

/**
 * Register Swagger-ui component in oatpp
 * The url is http://localhost:8000/swagger/ui
 */
class SwaggerComponent
{
public:

  /**
   * Configure swagger document settings
   * Please change personal information if you want to learn
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
    oatpp::swagger::DocumentInfo::Builder builder;

    OATPP_LOGi(APP_NAME, "Initializing swagger component!");

    builder
      .setTitle("CppWebBookManager")
      .setDescription("A Web API server use to manage book resources. It's powered by oatpp framework")
      .setVersion("1.0.0")
      .setContactName("luckymouse2332")
      .setContactEmail("mousexiaoqi111@gmail.com")
      .setContactUrl("https://github.com/luckymouse2332")
      
      .setLicenseName("MIT License")
      .addServer("http://localhost:8000", "Server on localhost");

      return builder.build();
  }());


  /**
   *  Swagger-Ui Resources
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
    // The environment variable is defined in CMakeLists.txt
    // It's ok to run this code
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());
};

#endif