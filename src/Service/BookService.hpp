#ifndef BOOK_SERVICE
#define BOOK_SERVICE

#include "../Model/Book.hpp"
#include <list>

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

class BookServiceDTO : public oatpp::DTO
{
    DTO_INIT(BookServiceDTO, DTO)

    DTO_FIELD(String, Name, "service");
    DTO_FIELD(String, User, "owner");
    DTO_FIELD(List<Object<BookDTO>>, Books, "books");
};

#include OATPP_CODEGEN_END(DTO)

class BookService
{
public:
    BookService(std::string name, std::string user) : Name(name), User(user), books(3, *(new Book("test", "test"))){};

    // 获取所有
    std::list<Book> GetAll() const { return this->books; }
    // 获取根据下标单本书
    Book Get(std::list<Book>::size_type index);
    // 添加至末尾
    void AddBack(Book book);
    // 按位置删除
    void Delete(std::list<Book>::size_type index);
    // 按位置修改
    void Update(std::list<Book>::size_type index, Book newBook);

    // 转化为DTO格式的对象
    BookServiceDTO::Wrapper toJson();

private:
    std::list<Book> books;

public:
    std::string Name;
    std::string User;
};
#endif