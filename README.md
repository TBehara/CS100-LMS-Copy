[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10926756&assignment_repo_type=AssignmentRepo)


# Library Management System
 Authors: [Ryan Chien](https://github.com/Campionnn), [Andy Chen](https://github.com/achen409), [Taran Behara](https://github.com/TBehara), [William Bruce](https://github.com/Augustus-Caesar886)

## Project Description
 * Why did we choose this project?
      * This project is interesting to us because the Library Management System program will consist of many different objects of varying types (such as User, Book, etc.) working in tandem to create a complex, integrated program with features such as searchable databases and varying degrees of data manipulation based on user permissions. Similar programs are commonplace today and there are many web interfaces which integrate some of the features we will be implementing in our project, so we see this assignment as an opportunity to not only gain experience working on large projects with multiple collaboraters, but also to gain a greater, hands-on understanding of how modern systems and interfaces work under the hood.
 * Technologies we plan on using (This list may change over the course of the project):
      * We will be using C++ for our implementation of a library management system. 
      * We will use hashes to keep track of user passwords and accounts so users may securely log in.
      * There will be classes for books/users/admins that will allow users to checkout books as well as keep information about each book such as title and author
      * We will be using nlohmann's JSON (https://github.com/nlohmann/json) for C++ library to save program data in JSON files
      * We will be using an external sha256 hash library to keep password data secure
 * What will be the input/output of our project?
      * All user inputs and program outputs will be done in the terminal. 
      * The initial output will be a menu screen that will prompt the user for a username to login and password or sign up for accounts. 
      * Once the user is in their account, the program outputs options to the user, prompting them to choose from a few options listed below: 
        * borrow a book(if so, the user will be prompted for which book)
        * display their balance
        * display available books
        * display books under a certain genre.
        * If the user account is an administrator, there are additional user inputs that allows the admin user to add, remove, or edit book entries.
 * What are the features that the project provides? </br>
      Some of the features for our Library Management system include:
      * Allow users to have library accounts with user names and passwords.
      * Users will have to log in to access any features
      * Checking out or borrowing a book.
      * Returning a book.
      * The program can recommend certain books in the data base based on a users checkout history.
      * Administrative users (ex. librarians) can add books to the system.
      * These administrative users will have their own account that they will log in to.
      * Users can search for books by Title, Genre, or Author
      * Program can show a users debt.

### User Interface Specification/ Navigation Diagram
![Navigation Diagram](https://cdn.discordapp.com/attachments/1098140638211485696/1104182590895837237/image.png)

### Screen Layouts
![Welcome Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775284742557796/Screen_Layout_1.PNG)
![Register Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775285061337200/Screen_Layout_2.PNG)
![Login Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775285531091004/Screen_Layout_3.PNG)
![User Menu Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775285820506202/Screen_Layout_4.PNG)
![Admin Menu Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775286105710775/Screen_Layout_5.PNG)
![Browse Books Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775286403502100/Screen_Layout_6.PNG)
![View Books Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775286638395512/Screen_Layout_7.PNG)
![Admin Manage Books Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775287036846220/Screen_Layout_8.PNG)
![Admin Add Admin Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775287330443425/Screen_Layout_9.PNG)
![Checkout Screen](https://media.discordapp.net/attachments/1098140638211485696/1116775287569531011/Screen_Layout_10.PNG)

## Class Diagram
 ![Class Diagram](https://cdn.discordapp.com/attachments/1098140638211485696/1116560452130971728/image.png) </br>
The project is centered around the LMS class, of which there will exist only 1 LMS object. The purpose of the LMS object is to integrate the CLI (Command Line Interface) with the underlying systems of the project which will provide the desired features specified by the user. The LMS object will have a single reference to the currently signed-in user (or nullptr if the user has not yet logged in) in order to grant the user the ability to perform actions according to their administrative permissions (or lack thereof). There will be a class for users, called User, which will store the typical user data such as the user's name, account balance, and list of checked-out books, along with getter and setter methods to modify these attributes, and other methods that implement actions that all users have the necessary permissions to perform. User also has a virtual method to display the typical User's prompt. There is an admin account which inherits from User and overloads the virtual menu method to add administrative actions to the default menu, with a new attribute and getter method which records the level of clearance that the administrative user has within the system, called priority. The LMS will have a list of all Book objects that exist within the library. The LMS will also contain a single object of the type SearchBase, which will be the class that implements all searching methods required by the program to work as intended. SearchBase will have 2 unordered maps (hashtables), one which maps strings to pointers to the Book objects in LMS's list of books, and one which maps book genres to pointers to the real book objects. Searchbase will have a number of helper functions to break up multi-word strings into lists of single-word strings and methods to add and remove books from the searching database. Finally, the Book class will hold the data relevant to true books in the library, such as a title, author, and genre, number of that book available to check out, and total number of that book belonging to the library. Book will have a custom enum called Genre to list out the genres. Book will also have getter and setter functions for all listed attributes, along with methods to add a specific number of that book to the total or available number of that book (with adding negative values signifying books leaving the library).
 
 ## Phase III
One SOLID principle we applied to the UML diagram was the open-closed principle to the Admin and User classes. The previous user class in the diagram required a boolean to represent whether or not it was an Admin object as well, which violates the open-closed principle because to perform certain actions on Users and Admins, the program had to explicitly check whether or not the User was also an Admin to perform different operations, and if we added more classes inheriting from User we would have to modify logic outside the new classes. To change this, we updated our UML diagram so that the User now has a permission level, with 0 representing no special permissions and anything above representing greater permissions within the program, so external logic only needs to know a User's permission level instead of whether or not it is an Admin object. This will help us write better code since if we decide to add a new User child class, we will not have to modify external logic that operates on users and admins to shoehorn in the new class. </br>

Another change that we made included moving the book database from the LMS class to the search_base class in accordance to the Single-Responsibility Principle. The LMS class' responsibility is to integrate the CLI with the backend of the project through displaying to and reading from the command line. Storing program data violates the single responsibility principle, so we moved the book database to the search_base class, which is supposed to search the database for books that match the queried criteria. This will help us write better code since the responsibilities of each class are now clearer, and as we implement the classes there will be less ambiguity as to which individual methods are responsible for the steps to achieving the higher-level goals.

We also added in a completely new class to manage JSON file I/O for our program's long-term data. This helps us better follow the single responsibility principle so that we can easily read/write data to our files wherever necessary through the use of this helper class. As a result, our code will be more clear and organized whenevr we need to invoke the routines for file I/O that the program relies on to work between multiple instances.
 
 ## Screenshots
### Signing up and Logging in
![Sign Up](https://cdn.discordapp.com/attachments/903147534321582092/1116567701654077490/Screen_Shot_2023-06-08_at_8.19.40_PM.png) </br>
![Login](https://cdn.discordapp.com/attachments/903147534321582092/1116568320188096545/Screen_Shot_2023-06-08_at_8.23.43_PM.png) </br>
### Adding and Removing Books from the System
![Add Books](https://cdn.discordapp.com/attachments/903147534321582092/1116609581733388328/Screen_Shot_2023-06-08_at_11.07.26_PM.png)</br>
![Remove Books](https://cdn.discordapp.com/attachments/903147534321582092/1116610570834169916/Screen_Shot_2023-06-08_at_11.11.36_PM.png)</br>
### Recommending Books to Users
![Recommend Books](https://cdn.discordapp.com/attachments/903147534321582092/1116611985560322048/Screen_Shot_2023-06-08_at_11.17.14_PM.png)</br>
### Searching for Books and Adding to Cart
![Search by Genre and Add to Cart](https://cdn.discordapp.com/attachments/903147534321582092/1116612962992521257/Screen_Shot_2023-06-08_at_11.21.07_PM.png)</br>
![Search by Title or Author](https://cdn.discordapp.com/attachments/903147534321582092/1116614605431656448/Screen_Shot_2023-06-08_at_11.27.38_PM.png)</br>
### Checking out the Current Cart
![Checkout Cart](https://cdn.discordapp.com/attachments/903147534321582092/1116613421073453077/Screen_Shot_2023-06-08_at_11.22.56_PM.png)</br>
### Returning Books (and viewing fines/currently checked out books)
![Returning Books](https://cdn.discordapp.com/attachments/903147534321582092/1116613868182044693/Screen_Shot_2023-06-08_at_11.24.43_PM.png)</br>
### Making an existing user an admin
![Making them an admin](https://cdn.discordapp.com/attachments/903147534321582092/1116615135071580160/Screen_Shot_2023-06-08_at_11.29.44_PM.png) </br>
![Logging in as the new admin](https://cdn.discordapp.com/attachments/903147534321582092/1116615272502153336/Screen_Shot_2023-06-08_at_11.30.17_PM.png)</br>
### Renewing Books
Currently, there is no tracking of when a book must be returned, so attempting to renew a book returns the user to their regular menu options.
 ## Installation/Usage
 Clone this repo (or create a fork to clone from) locally, making sure to recursively clone submodules (or init submodules after cloning)</br>
 Run the following terminal commands in the following order within the project directory: <br>
 cmake . <br>
 make <br>
 ./bin/LMS
 ## Testing
 We used googletest to unit test individual functions, adding new unit tests for new functions we added. Mimicking continuous integration, we made sure the tests succeeded after changes were made before and after pushing and merging into the master branch. <br>
 We ran many manual tests to test functions on the front-end, making sure the program's output conformed to our planned screen layouts. <br>
 We tested for memory leaks by running valgrind on the executable and going through the various options multiple times, with different combinations/scenarios, and ensured that we had achieved MEMCHECK-CLEAN when we quit the program.

