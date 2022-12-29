#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDTO : public oatpp::DTO {
    DTO_INIT(BookDTO, DTO);

    DTO_FIELD(String, title, "title");
    DTO_FIELD(String, author, "author");
};

#include OATPP_CODEGEN_END(DTO)

class Book
{
public:
    // 构造函数
    Book(std::string Title, std::string Author) : title(Title), author(Author) {}

    std::string title;
    std::string author;
    BookDTO::Wrapper toJson();
};


#endif