#ifndef SEARCH_BASE_HPP
#define SEARCH_BASE_HPP

#include "book.hpp"
#include <unordered_map>

class searchBase {
    private:
        list<Book> bookDatabase;
        unordered_map<Book::Genre, list<Book>> genreTable;
        unordered_map<string, list<Book>> stringsTable;
        vector<string> parseString(string);
        void searchByTerm(unordered_map<list<Book*>, int>, string);
        void removeBookTermEntry(Book*, string);
        void addBookTermEntry(Book*, string);
    public:
        searchBase();
        list<Book*> searchGenre(Book::Genre);
        unordered_map<list<Book*>, int> searchByTerms(string);
        void removeBookGenreEntry(Book*, Book::Genre);
        void removeBookTermEntries(Book*, string);
        void addBookGenreEntry(Book*, Book::Genre);
        void addBookTermEntries(Book*, string);
};
#endif