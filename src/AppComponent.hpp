#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/core/macro/component.hpp"

class AppComponent {
public:
    /**
     * 创建连接监听者监听8888端口
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8888, oatpp::network::Address::IP_4});
    }());

    /**
     * 创建路由组件
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    /**
     * 创建使用路由组件路由连接的连接实现
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    /**
     * 创建对象链接器对DTO进行序列化和反序列化
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {\
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());
};

#endif