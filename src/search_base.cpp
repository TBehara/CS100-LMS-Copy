#include <sstream>
#include "../header/search_base.hpp"

using std::istringstream;

SearchBase::SearchBase(){
    bookDatabase = list<Book>();
    genreTable = unordered_map<Book::Genre, list<list<Book>::iterator>>();
    stringsTable = unordered_map<string, list<list<Book>::iterator>>();
}

//Returns lowercase mixed string
string toLower(string mixed) {
    for(unsigned i = 0; i < mixed.size(); ++i) {
        mixed[i] = tolower(mixed[i]);
    }
    return mixed;
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

void SearchBase::removeBook(list<Book>::iterator toRemove) {
    /*vector<string> titleTerms = parseString(toRemove->getTitle());
    vector<string> authorTerms = parseString(toRemove->getAuthor());
    list<Book::Genre> genres = toRemove->getGenres();

    //TODO: remove duplicate terms from containers

    for(auto it1 : titleTerms) {
        list<list<Book>::iterator> searchResults = searchByTerm(it1);
        for(auto it2 : searchResults) {
            if(*it2 == *toRemove) {
                removeBookTermEntry(it2, it1);
            }
        }
    }
    for(auto it1 : authorTerms) {
        list<list<Book>::iterator> searchResults = searchByTerm(it1);
        for(auto it2 : searchResults) {
            if(*it2 == *toRemove) {
                removeBookTermEntry(it2, it1);
            }
        }
    }
    for(auto it1 : genres) {
        list<list<Book>::iterator> searchResults = searchByGenre(it1);
        for(auto it2 : searchResults) {
            if(*it2 == *toRemove) {
                removeBookGenreEntry(it2, it1);
            }
        }
    }*/

    bookDatabase.erase(toRemove);
}

list<Book>& SearchBase::getBooks() {
    return bookDatabase;
}

vector<string> SearchBase::parseString(const string& wholeString) {
    vector<string> terms;

    istringstream stream(wholeString);
    string newTerm = "";
    while(stream >> newTerm) {
        terms.push_back(newTerm);
    }

    return terms;
}

list<list<Book>::iterator> SearchBase::searchByTerm(const string& term) {
    return stringsTable[toLower(term)];
}

list<list<Book>::iterator> SearchBase::searchByTerms(const string& fullEntry) {
    list<list<Book>::iterator> results;
    vector<string> individualEntries = parseString(fullEntry);
    for(auto it : individualEntries) {
        results.splice(results.end(), searchByTerm(it));
    }
    return results;
}

list<list<Book>::iterator> SearchBase::searchByGenre(Book::Genre genre) {
    return genreTable[genre];
}

void SearchBase::addBookGenreEntry(list<Book>::iterator bookReference, Book::Genre genre) {
    genreTable[genre].push_back(bookReference);
}

void SearchBase::removeBookGenreEntry(list<Book>::iterator, Book::Genre) {
    return;
}

void SearchBase::addBookTermEntry(list<Book>::iterator bookReference, const string& term) {
    stringsTable[toLower(term)].push_back(bookReference);
}

void SearchBase::removeBookTermEntry(list<Book>::iterator bookReference, const string& term) {
    return;
}