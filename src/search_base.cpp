#include "../header/search_base.hpp"

// private
vector<string> SearchBase::parseString(string){
    return vector<string>();
}
void SearchBase::searchByTerm(unordered_map<list<Book*>, int>, string){

}
void SearchBase::removeBookTermEntry(Book*, string){

}
void SearchBase::addBookTermEntry(Book*, string){

}

// public
SearchBase::SearchBase(){
    bookDatabase = list<Book>();
    genreTable = unordered_map<Book::Genre, list<Book>::iterator>();
    stringsTable = unordered_map<string, list<Book>::iterator>();
}
list<Book*> SearchBase::searchGenre(Book::Genre){
    return list<Book*>();
}
list<list<Book>::iterator> SearchBase::searchByTerms(string){
    return list<list<Book>::iterator>();
}
void SearchBase::removeBookGenreEntry(Book*, Book::Genre){

}
void SearchBase::removeBookTermEntries(Book*, string){

}
void SearchBase::addBookGenreEntry(Book*, Book::Genre){

}
void SearchBase::addBookTermEntries(Book*, string){

}