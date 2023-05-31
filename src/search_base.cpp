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
    genreTable = unordered_map<Book::Genre, list<Book>>();
    stringsTable = unordered_map<string, list<Book>>();
}
list<Book*> SearchBase::searchGenre(Book::Genre){
    return list<Book*>();
}
unordered_map<list<Book*>, int> SearchBase::searchByTerms(string){
    return unordered_map<list<Book*>, int>();
}
void SearchBase::removeBookGenreEntry(Book*, Book::Genre){

}
void SearchBase::removeBookTermEntries(Book*, string){

}
void SearchBase::addBookGenreEntry(Book*, Book::Genre){

}
void SearchBase::addBookTermEntries(Book*, string){

}