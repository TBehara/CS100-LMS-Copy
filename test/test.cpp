#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../header/user.hpp"
#include "../header/book.hpp"

#include "../libraries/hash/sha256.h"

using ::testing::_;
using ::testing::InSequence;
using namespace std;

TEST(bookTests, testBookConstructorDefault) {
    const string title = "title", author = "John Doe";
    list<Book::Genre> genres;
    Book b(title, author, genres);
    EXPECT_EQ(b.getTitle(), title);
    EXPECT_EQ(b.getAuthor(), author);
    EXPECT_EQ(b.getGenres(), genres);
    EXPECT_EQ(b.getAvailable(), 0);
    EXPECT_EQ(b.getTotal(), 0);
}

TEST(bookTests, testBookConstructorTotalSpecified) {
    const string title = "title", author = "John Doe";
    list<Book::Genre> genres;
    const int total = 1;
    Book b(title, author, genres, total);
    EXPECT_EQ(b.getTitle(), title);
    EXPECT_EQ(b.getAuthor(), author);
    EXPECT_EQ(b.getGenres(), genres);
    EXPECT_EQ(b.getAvailable(), total);
    EXPECT_EQ(b.getTotal(), total);
}

TEST(bookTests, testSetTitle) {
    const string newTitle = "title";
    list<Book::Genre> genres;
    Book b("", "", genres);
    b.setTitle(newTitle);
    EXPECT_EQ(b.getTitle(), newTitle);
}

TEST(bookTests, testSetAuthor) {
    const string newAuthor = "author";
    list<Book::Genre> genres;
    Book b("", "", genres);
    b.setAuthor(newAuthor);
    EXPECT_EQ(b.getAuthor(), newAuthor);
}

TEST(bookTests, testAddAvailableOverflowException) {
    list<Book::Genre> genres;
    const int total = 5;
    Book b("", "", genres, total);
    const int toAdd = 3;
    EXPECT_THROW({
        b.addAvailable(toAdd);
    }, runtime_error);
}

TEST(bookTests, testAddAvailableUnderflowException) {
    list<Book::Genre> genres;
    const int total = 5;
    Book b("", "", genres, total);
    const int toRemove = 6;
    EXPECT_THROW({
        b.addAvailable(-toRemove);
    }, runtime_error);
}

TEST(bookTests, testAddTotal) {
    list<Book::Genre> genres;
    Book b("", "", genres);
    const int toAdd = 5;
    b.addTotal(toAdd);
    EXPECT_EQ(b.getTotal(), toAdd);
    EXPECT_EQ(b.getAvailable(), toAdd);
}

TEST(bookTests, testAddTotalUnderflowException) {
    list<Book::Genre> genres;
    const int initialTotal = 5, toRemove = 6;
    Book b("", "", genres, initialTotal);
    EXPECT_THROW({
        b.addTotal(-toRemove);
    }, runtime_error);
}

TEST(bookTests, testAddAvailableAndTotal) {
    list<Book::Genre> genres;
    const int total = 10, toRemove = 5;
    Book b("", "", genres, total);
    b.addAvailable(-toRemove);

    EXPECT_EQ(b.getTotal(), total);
    EXPECT_EQ(b.getAvailable(), total - toRemove);

    const int toAdd = 3;
    b.addTotal(toAdd);

    EXPECT_EQ(b.getTotal(), total + toAdd);
    EXPECT_EQ(b.getAvailable(), total + toAdd - toRemove);

    b.addAvailable(toRemove);
    EXPECT_EQ(b.getTotal(), total + toAdd);
    EXPECT_EQ(b.getAvailable(), total + toAdd);
}

TEST(bookTests, testAddGenre) {
    list<Book::Genre> genres;
    Book b("", "", genres);
    b.addGenre(Book::Genre::NONFICTION);
    EXPECT_EQ(b.getGenres().front(), Book::Genre::NONFICTION);
    EXPECT_EQ(b.getGenres().size(), 1);
}

TEST(bookTests, testAddGenreThrowsException) {
    list<Book::Genre> genres;
    Book b("", "", genres);
    b.addGenre(Book::Genre::NONFICTION);
    EXPECT_THROW({
        b.addGenre(Book::Genre::NONFICTION);
    }, runtime_error);
}

TEST(bookTests, testRemoveGenre) {
    list<Book::Genre> genres;
    genres.push_back(Book::Genre::FICTION);
    genres.push_back(Book::Genre::NONFICTION);
    Book b("", "", genres);
    b.removeGenre(Book::Genre::FICTION);
    EXPECT_EQ(b.getGenres().size(), 1);
    EXPECT_EQ(b.getGenres().front(), Book::Genre::NONFICTION);
}

TEST(bookTests, testGenreEquality) {
    list<Book::Genre> g1, g2, g3;
    g1.push_back(Book::Genre::FICTION);
    g1.push_back(Book::Genre::NONFICTION);

    g2.push_back(Book::Genre::NONFICTION);
    g2.push_back(Book::Genre::FICTION);
    EXPECT_TRUE(Book::genresEqual(g1, g2));

    g3.push_back(Book::Genre::FICTION);
    g3.push_back(Book::Genre::NONFICTION);
    g3.push_back(Book::Genre::FANTASY);
    EXPECT_FALSE(Book::genresEqual(g1, g3));
    EXPECT_FALSE(Book::genresEqual(g2, g3));
    EXPECT_FALSE(Book::genresEqual(g3, g1));
}

TEST(bookTests, testBookEquality) {
    list<Book::Genre> genres1, genres2, genres3;
    genres1.push_back(Book::Genre::FICTION);
    genres2.push_back(Book::Genre::FICTION);
    genres3.push_back(Book::Genre::NONFICTION);
    Book b1("1", "1", genres1);
    Book b2("1", "1", genres2);
    Book b3("3", "3", genres3);
    EXPECT_EQ(b1, b2);
    EXPECT_NE(b2, b3);
}

TEST(bookTests, testBookEqualityMultiGenre) {
    list<Book::Genre> genres1, genres2;
    genres1.push_back(Book::Genre::NONFICTION);
    genres1.push_back(Book::Genre::FICTION);

    genres2.push_back(Book::Genre::FICTION);
    genres2.push_back(Book::Genre::NONFICTION);

    Book b1("1", "1", genres1), b2("1", "1", genres2);
    EXPECT_EQ(b1, b2);

    genres2.push_back(Book::Genre::FANTASY);
    EXPECT_EQ(b1, b2);

    Book b3("1", "1", genres2);
    EXPECT_NE(b1, b3);
    EXPECT_NE(b2, b3);
    EXPECT_NE(b3, b1);
    EXPECT_NE(b3, b2);
}

TEST(userTests, testGuestUser) {
    User defaultUser;
    EXPECT_EQ(defaultUser.getUsername(), "Guest");
    EXPECT_EQ(defaultUser.hashPassword(), "");
}

TEST(userTests, testExampleUserLogin) {
    const string username = "JohnDoe47", password = sha256("password");
    User exampleUser(username, password);
    EXPECT_EQ(exampleUser.getUsername(), username);
    EXPECT_EQ(exampleUser.hashPassword(), (password));
    EXPECT_NE(exampleUser.getUsername(), username + "0");
    EXPECT_NE(exampleUser.hashPassword(), sha256("passwore"));
}

TEST(userTests, testDefaultFine) {
    User defaultUser;
    EXPECT_DOUBLE_EQ(defaultUser.getFine(), 0.0);
}

TEST(userTests, testCustomFine) {
    User exampleUser("", "");
    EXPECT_DOUBLE_EQ(exampleUser.getFine(), 0.0);
}

TEST(userTests, testUsernameMethods) {
    User exampleUser("", "");
    const string username = "JohnDoe47";
    exampleUser.setUsername(username);
    EXPECT_EQ(exampleUser.getUsername(), username);
}

TEST(userTests, testFineMethods) {
    User defaultUser;
    defaultUser.setFine(defaultUser.getFine() + 5);
    EXPECT_DOUBLE_EQ(defaultUser.getFine(), 5);
}

TEST(userTests, testBookAdd) {
    User defaultUser;
    list<Book::Genre> genres;
    Book b("", "", genres);
    defaultUser.addBook(b);
    const list<Book>& books = defaultUser.getBooks();
    EXPECT_EQ(defaultUser.getBooks().size(), 1);
    EXPECT_EQ(defaultUser.getBooks().front(), b);
}

TEST(userTests, bookAddThrowsException) {
    User defaultUser;
    list<Book::Genre> genres;
    Book b("", "", genres);
    defaultUser.addBook(b);
    EXPECT_THROW({
        defaultUser.addBook(b);
    }, runtime_error);
    EXPECT_EQ(defaultUser.getBooks().size(), 1);
}

TEST(userTests, testBookRemove) {
    User defaultUser;
    list<Book::Genre> genres;
    Book b1("1", "1", genres), b2("2", "2", genres); 
    defaultUser.addBook(b1);
    defaultUser.addBook(b2);
    defaultUser.removeBook(b1);
    EXPECT_EQ(defaultUser.getBooks().size(), 1);
    EXPECT_EQ(defaultUser.getBooks().front(), b2);
}


TEST(userTests, testSetPrevBookNames) {
    User defaultUser("", "");
    vector<string> bookNames = {"The Lord of the Rings"};

    defaultUser.setPrevBookNames(bookNames);
    EXPECT_EQ(defaultUser.getPrevBookNames(), bookNames);

    bookNames.push_back("Harry Potter");
    EXPECT_NE(defaultUser.getPrevBookNames(), bookNames);

    defaultUser.getPrevBookNames().push_back("Harry Potter");
    EXPECT_EQ(defaultUser.getPrevBookNames(), bookNames);
}

TEST(userTests, testSetCurrBookNames) {
    User defaultUser("", "");
    vector<string> bookNames = {"The Lord of the Rings"};

    defaultUser.setCurrBookNames(bookNames);
    EXPECT_EQ(defaultUser.getCurrBookNames(), bookNames);

    bookNames.push_back("Harry Potter");
    EXPECT_NE(defaultUser.getCurrBookNames(), bookNames);

    defaultUser.getCurrBookNames().push_back("Harry Potter");
    EXPECT_EQ(defaultUser.getCurrBookNames(), bookNames);
}

TEST(userTests, testSetInterestKeywords) {
    User defaultUser("", "");
    vector<string> keywords = {"fantasy", "mystery", "nonfiction"};

    defaultUser.setInterestKeywords(keywords);
    EXPECT_EQ(defaultUser.getInterestKeywords(), keywords);

    keywords.push_back("adventure");
    EXPECT_NE(defaultUser.getInterestKeywords(), keywords);

    defaultUser.getInterestKeywords().push_back("adventure");
    EXPECT_EQ(defaultUser.getInterestKeywords(), keywords);
}