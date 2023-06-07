#ifndef BOOK_HPP
#define BOOK_HPP
#include <string>
#include <list>
using std::string;
using std::list;

class Book {
    private:
        string title, author;
        int total, available;
    public:
        enum Genre {
            FICTION, NONFICTION, FANTASY, NOVEL, MYSTERY, SCIFI, HISTORICAL_FICTION, LITERARY_FICTION, NARRATIVE, ALWAYS_AT_END
        };

        Book(const string&, const string&, const list<Genre>&, int total = 0);

        string getTitle() const;

        void setTitle(const string&);

        const list<Genre>& getGenres() const;

        void addGenre(Genre);

        void removeGenre(Genre);

        static Genre stringToGenre(const string &genre);

        string getAuthor() const;

        void setAuthor(const string&);

        int getAvailable() const;

        int getTotal() const;

        void addTotal(int);

        void addAvailable(int);

        static bool genresEqual(const list<Genre>&, const list<Genre>&);

        bool operator==(const Book&) const;

        bool operator!=(const Book&) const;
    private:
        list<Genre> genres;
};
#endif