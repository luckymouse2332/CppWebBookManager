#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include "../Data/Utils.hpp"
#include "../Service/BookService.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

class BookController : public oatpp::web::server::api::ApiController
{
public:
    BookController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {
    }

public:
    // 定义节点
    // 获取全部书籍
    ENDPOINT("GET", "/book/all", getAllBooks)
    {
        OATPP_LOGI("Request", "Get all books");
        auto jsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        try
        {
            auto json = jsonObjectMapper->writeToString(service.toJson());
            return createResponse(Status::CODE_200, json);
        }
        catch (const std::exception &e)
        {
            OATPP_LOGI("Error", e.what());
            return createDtoResponse(Status::CODE_405, *(new oatpp::Void));
        }
    }

    // 根据id删除书籍
    ENDPOINT("DELETE", "/book/delete/{id}", deleteBookById,
             PATH(Int64, BookId, "id"))
    {
        OATPP_LOGI("Request", "Delete book where id=%d", BookId.getValue(0));
        try
        {
            service.Delete(BookId.getValue(0));
            OATPP_LOGI("Delete", "delete book %d", BookId.getValue(0));
            return createResponse(Status::CODE_204, "Delete ok!");
        }
        catch (std::runtime_error &e)
        {
            OATPP_LOGE("Delete Book Failed!", "\"%s\"", e.what());
            return createResponse(Status::CODE_400, "Failed to delete book");
        }
        return createResponse(Status::CODE_204, "delete ok!");
    }
};

#include OATPP_CODEGEN_END(ApiController)