// main.cpp
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/network/Server.hpp"

#include "AppComponent.hpp"
#include "Controller/BookController.hpp"
void run()
{
    // 创建组件对象
    AppComponent components;

    // 为 HTTP 请求创建路由器
    auto router = oatpp::web::server::HttpRouter::createShared();

    // 创建API控制器
    auto bookController = std::make_shared<BookController>();

    // 添加API控制器
    router->addController(bookController);

    // 创建 HTTP 连接处理程序
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    // 创建 TCP 连接提供者
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"192.168.1.19", 8888, oatpp::network::Address::IP_4});

    // 创建服务器，它接受提供的 TCP 连接并将其传递给 HTTP 连接处理程序
    oatpp::network::Server server(connectionProvider, connectionHandler);

    // 打印服务器端口
    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    // 运行服务器
    server.run();
}

int main()
{
    // 初始化 oatpp 环境
    oatpp::base::Environment::init();

    // 运行应用
    run();

    // 销毁 oatpp 环境
    oatpp::base::Environment::destroy();

    return 0;
}
