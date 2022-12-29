#include "BookService.hpp"
#include <stdexcept>

using namespace std;

// 获取根据下标单本书
Book BookService::Get(std::list<Book>::size_type index)
{
    // 下标超出范围
    if (index >= books.size())
        throw runtime_error("Index overflow!");
    // 遍历链表
    auto iter = books.begin();
    for (int i = 0; i < index; ++i)
    {
        ++iter;
    }
    return *iter;
}

// 添加至末尾
void BookService::AddBack(Book book)
{
    books.push_back(book);
}

// 按位置删除
void BookService::Delete(std::list<Book>::size_type index)
{
    // 下标超出范围
    if (index >= books.size())
        throw runtime_error("Index overflow!");
    // 遍历链表
    auto iter = books.begin();
    for (int i = 0; i < index; ++i)
    {
        ++iter;
    }
    books.erase(iter);
}

// 按位置修改
void BookService::Update(std::list<Book>::size_type index, Book newBook)
{
    // 下标超出范围
    if (index >= books.size())
        throw runtime_error("Index overflow!");
    // 遍历链表
    auto iter = books.begin();
    for (int i = 0; i < index; ++i)
    {
        ++iter;
    }
    *iter = newBook;
}

// 转化为DTO格式的数据
BookServiceDTO::Wrapper BookService::toJson()
{
    auto service = BookServiceDTO::createShared();
    service->Name = this->Name;
    service->User = this->User;

    service->Books->push_back(books.begin()->toJson());
    return service;
}