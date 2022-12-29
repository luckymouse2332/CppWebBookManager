#include "Book.hpp"

BookDTO::Wrapper Book::toJson()
{
    BookDTO::Wrapper bookDto = BookDTO::createShared();
    bookDto->author = this->author;
    bookDto->title = this->title;
    return bookDto;
}