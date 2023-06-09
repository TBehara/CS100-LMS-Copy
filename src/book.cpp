#include "../header/book.hpp"
#include <string>
#include <list>
#include <stdexcept>
#include <cassert>
#include <iostream>

using std::string;
using std::list;
using std::runtime_error;
using std::cout;
using std::endl;

Book::Book(const string& title, const string& author, const list<Book::Genre> &genres, int total) : title(title), author(author), genres(genres), available(total), total(total) {
}

string Book::getTitle() const {
    return title;
}


void Book::setTitle(const string& newTitle) {
    title = newTitle;
}

const list<Book::Genre>& Book::getGenres() const {
    return genres;
}

void Book::addGenre(Book::Genre genre) {
    for(auto it : genres) {
        if(it == genre) {
            throw runtime_error("a genre was added twice to the book " + title + " by " + author);
        }
    }
    genres.push_back(genre);
}

void Book::removeGenre(Book::Genre genre) {
    for(auto it : genres) {
        if(it == genre) {
            genres.remove(it);
            return;
        }
    }
    return;
}

string Book::getAuthor() const {
    return author;
}

void Book::setAuthor(const string& newAuthor) {
    author = newAuthor;
}

int Book::getAvailable() const {
    return available;
}

int Book::getTotal() const {
    return total;
}

void Book::addTotal(int toAdd) {
    total += toAdd;
    if(total < 0) throw runtime_error("the library is tracking negative quantiters of book " + title + " by " + author + " ");
    addAvailable(toAdd);
}

void Book::addAvailable(int toAdd) {
    available += toAdd;
    if(available < 0) throw runtime_error("book " + title + " by " + author + " has a negative availability");
    if(available > total) {
        available = total;
        throw runtime_error("book " + title + " by " + author + " has more availability than library is tracking");
    }
}

bool Book::genresEqual(const list<Genre>& operand1, const list<Genre>& operand2) {
    assert(operand1.size() <= Book::Genre::ALWAYS_AT_END);
    if(operand1.size() != operand2.size()) return false;

    unsigned toMatch[Book::Genre::ALWAYS_AT_END] = {}; //Used to map each distinct enum value to a slot in the array that will represent its appearances in both genre lists
    auto op1It = operand1.begin(), op2It = operand2.begin();
    for(unsigned i = 0; i < operand1.size(); ++i) {
        ++toMatch[*op1It];
        ++toMatch[*op2It];
        ++op1It;
        ++op2It;
    }
    for(auto it : toMatch) {
        if(it == 1) return false;
    }
    return true;
}

Book::Genre Book::stringToGenre(const string &genre) {
    if(genre=="Fiction"){
        return Book::Genre::FICTION;
    }
    else if(genre=="Nonfiction"){
        return Book::Genre::NONFICTION;
    }
    else if(genre=="Fantasy"){
        return Book::Genre::FANTASY;
    }
    else if(genre=="Novel"){
        return Book::Genre::NOVEL;
    }
    else if(genre=="Mystery"){
        return Book::Genre::MYSTERY;
    }
    else if(genre=="SciFi"){
        return Book::Genre::SCIFI;
    }
    else if(genre=="Historical Fiction"){
        return Book::Genre::HISTORICAL_FICTION;
    }
    else if(genre=="Literary Fiction"){
        return Book::Genre::LITERARY_FICTION;
    }
    else if(genre=="Narrative"){
        return Book::Genre::NARRATIVE;
    }
    else{
        std::cout << "Invalid Genre. Try Again." << std::endl;
        return Book::Genre::ALWAYS_AT_END;
    }
}

bool Book::operator==(const Book& operand) const {
    return title == operand.title and
            author == operand.author and
            genresEqual(genres, operand.genres);
}

bool Book::operator!=(const Book& operand) const {
    return !(*this == operand);
}

bool Book::operator<(const Book& operand) const {
    return ( title + author ) < ( operand.title + operand.author );
}