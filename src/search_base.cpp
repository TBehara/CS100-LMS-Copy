#include "../header/search_base.hpp"

// private
vector<string> searchBase::parseString(string){
    
}
void searchBase::searchByTerm(unordered_map<list<Book*>, int>, string){

}
void searchBase::removeBookTermEntry(Book*, string){

}
void searchBase::addBookTermEntry(Book*, string){

}

// public
searchBase::searchBase(){
    bookDatabase = new List<Book>();
    genreTable = new unordered_map<Book::Genre, list<Book>>();
    stringsTable = new unordered_map<string, list<Book>>();
}
list<Book*> searchBase::searchGenre(Book::Genre){
    return nullptr;
}
unordered_map<list<Book*>, int> searchBase::searchByTerms(string){
    return nullptr;
}
void searchBase::removeBookGenreEntry(Book*, Book::Genre){

}
void searchBase::removeBookTermEntries(Book*, string){

}
void searchBase::addBookGenreEntry(Book*, Book::Genre){

}
void searchBase::addBookTermEntries(Book*, string){

}