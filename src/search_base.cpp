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
    std::cout << "Called add book" << std::endl;
    bookDatabase.push_back(toAdd);
    std::cout << "BookDB size1: " << bookDatabase.size() << std::endl;
    list<Book>::iterator added = bookDatabase.end();
    --added;
    std::cout << "BookDB size2: " << bookDatabase.size() << std::endl;
    vector<string> stringTerms = parseString(toAdd.getTitle() + " " + toAdd.getAuthor());
    for(auto it : stringTerms) {
        addBookTermEntry(added, it);
    }
    std::cout << "BookDB size3: " << bookDatabase.size() << std::endl;
    for(auto it : toAdd.getGenres()) {
        addBookGenreEntry(added, it);
    }
    std::cout << "BookDB size4: " << bookDatabase.size() << std::endl;
}

void SearchBase::removeBook(list<Book>::iterator toRemove) {
    vector<string> termsToRemove = parseString(toRemove->getTitle() + " " + toRemove->getAuthor());

    for(auto it : termsToRemove) {
        removeBookTermEntry(toRemove, it);
    }
    for(auto it : toRemove->getGenres()) {
        removeBookGenreEntry(toRemove, it);
    }

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
    std::cout << "INDIVIDUAL ENTRIES SIZE: " << individualEntries.size() << std::endl;
    int timesLoopRan = 0;
    for(auto it : individualEntries) {
        timesLoopRan++;
        results.splice(results.end(), searchByTerm(it));
        std::cout << "RESULTS SIZE: " << results.size() << std::endl;
    }
    std::cout << timesLoopRan << std::endl;
    std::cout << "RESULTS END SIZE: " << results.size() << std::endl;
    return results;
}

list<list<Book>::iterator> SearchBase::searchByGenre(Book::Genre genre) {
    return genreTable[genre];
}

void SearchBase::addBookGenreEntry(list<Book>::iterator bookReference, Book::Genre genre) {
    genreTable[genre].push_back(bookReference);
}

void SearchBase::removeBookGenreEntry(list<Book>::iterator bookReference, Book::Genre genre) {
    list<list<Book>::iterator>& toChange = genreTable[genre]; //We need a reference to the table here to modify it
    for(auto it = toChange.begin(); it != toChange.end(); ++it) {
        if(*it == bookReference) {
            it = toChange.erase(it);
        }
    }
}

void SearchBase::addBookTermEntry(list<Book>::iterator bookReference, const string& term) {
    stringsTable[toLower(term)].push_back(bookReference);
}

void SearchBase::removeBookTermEntry(list<Book>::iterator bookReference, const string& term) {
    list<list<Book>::iterator>& toChange = stringsTable[toLower(term)]; //We need a reference to the table here to modify it
    for(auto it = toChange.begin(); it != toChange.end(); ++it) {
        if(*it == bookReference) {
            it = toChange.erase(it);
        }
    }
}