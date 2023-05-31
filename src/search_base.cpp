#include "../header/search_base.hpp"

SearchBase::SearchBase(){
    bookDatabase = list<Book>();
    genreTable = unordered_map<Book::Genre, list<list<Book>::iterator>>();
    stringsTable = unordered_map<string, list<list<Book>::iterator>>();
}

void SearchBase::addBook(const Book& toAdd) {
    bookDatabase.push_back(toAdd);
    list<Book>::iterator added = bookDatabase.end();
    --added;
    vector<string> stringTerms = parseString(toAdd.getTitle() + " " + toAdd.getAuthor());
    for(auto it : stringTerms) {
        addBookTermEntry(added, it);
    }
    for(auto it : toAdd.getGenres()) {
        addBookGenreEntry(added, it);
    }
}

void SearchBase::removeBook(list<Book>::iterator &toRemove) {
    bookDatabase.erase(toRemove);
    //TODO: remove search entries from tables
}

list<Book>& SearchBase::getBooks() {
    return bookDatabase;
}

vector<string> SearchBase::parseString(const string&) {
    return vector<string>();
}

list<list<Book>::iterator> SearchBase::searchByTerm(const string&) {
    return list<list<Book>::iterator>();
}

list<list<Book>::iterator> SearchBase::searchByTerms(const string&) {
    return list<list<Book>::iterator>();
}

list<list<Book>::iterator> SearchBase::searchByGenre(Book::Genre) {
    return list<list<Book>::iterator>();
}

void SearchBase::addBookGenreEntry(list<Book>::iterator&, Book::Genre) {
    return;
}

void SearchBase::removeBookGenreEntry(list<Book>::iterator&, Book::Genre) {
    return;
}

void SearchBase::addBookTermEntry(list<Book>::iterator&, const string&) {
    return;
}

void SearchBase::removeBookTermEntry(list<Book>::iterator&, const string&) {
    return;
}