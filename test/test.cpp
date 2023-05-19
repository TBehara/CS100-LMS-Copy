#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../header/user.hpp"
#include "../header/book.hpp"

using ::testing::_;
using ::testing::InSequence;
using namespace std;

//To be removed when Book is implemented
bool operator==(const Book&, const Book&) {
    return false;
}

TEST(googletestSetup, expect0) {
    EXPECT_EQ(0, 0);
}

TEST(userTests, testGuestUser) {
    User defaultUser;
    EXPECT_EQ(defaultUser.getUsername(), "Guest");
    EXPECT_EQ(defaultUser.hashPassword(), 0);
}

TEST(userTests, testExampleUserLogin) {
    const string username = "JohnDoe47", password = "password";
    User exampleUser(username, password);
    EXPECT_EQ(exampleUser.getUsername(), username);
    EXPECT_EQ(exampleUser.hashPassword(), (int)hash<string>{}(password));
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
    Book b;
    defaultUser.addBook(b);
    const list<Book>& books = defaultUser.getBooks();
    EXPECT_EQ(books.size(), 1);
    EXPECT_EQ(books.front(), b);
}

TEST(userTests, testBookRemove) {
    User defaultUser;
    Book b1, b2; //To be updated when Book is implemented
    defaultUser.addBook(b1);
    defaultUser.addBook(b2);
    defaultUser.removeBook(b1);
    EXPECT_EQ(defaultUser.getBooks().size(), 1);
    EXPECT_EQ(defaultUser.getBooks().front(), b2);
}