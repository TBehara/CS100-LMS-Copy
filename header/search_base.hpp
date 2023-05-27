#ifndef SEARCH_BASE_HPP
#define SEARCH_BASE_HPP

#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include "book.hpp"

using std::list;
using std::string;
using std::vector;
using std::unordered_map;

class SearchBase {
    private:
        list<Book> bookDatabase;
        unordered_map<Book::Genre, list<list<Book>::iterator>> genreTable;
        unordered_map<string, list<list<Book>::iterator>> stringsTable;
    public:
        void addBook(const Book&);
        void removeBook(list<Book>::iterator&);
        list<Book> &getBooks();
        static vector<string> parseString(const string&);
        list<list<Book>::iterator> searchByTerm(const string&);
        list<list<Book>::iterator> searchByTerms(const string&);
        list<list<Book>::iterator> searchByGenre(Book::Genre);
        void addBookGenreEntry(list<Book>::iterator&, Book::Genre);
        void removeBookGenreEntry(list<Book>::iterator&, Book::Genre);
        void addBookTermEntry(list<Book>::iterator&, const string&);
        void removeBookTermEntry(list<Book>::iterator&, const string&);
};
#endif