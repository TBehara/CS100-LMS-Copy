[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10926756&assignment_repo_type=AssignmentRepo)


# Library Management System
 Authors: [Ryan Chien](https://github.com/Campionnn), [Andy Chen](https://github.com/achen409), [Taran Behara](https://github.com/TBehara), [William Bruce](https://github.com/Augustus-Caesar886)

## Project Description
 * Why did we choose this project?
      * This project is interesting to us because the Library Management System program will consist of many different objects of varying types (such as User, Book, etc.) working in tandem to create a complex, integrated program with features such as searchable databases and varying degrees of data manipulation based on user permissions. Similar programs are commonplace today and there are many web interfaces which integrate some of the features we will be implementing in our project, so we see this assignment as an opportunity to not only gain experience working on large projects with multiple collaboraters, but also to gain a greater, hands-on understanding of how modern systems and interfaces work under the hood.
 * Technologies we plan on using (This list may change over the course of the project):
      * We will be using C++ for our implementation of a library management system. 
      * We will use hashes to keep track of user passwords and accounts so users may securely log in.
      * There will be classes for books/users/admins that will allow users to checkout books as well as keep information about each book such as ISB and page count. 
      * We will create an automatic backend system that will keep track of checkout times and appropiately indicate when users are overdue for returning their books.
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
      * Paying a fine.
      * The program can recommend certain books in the data base based on a users checkout history.
      * Administrative users (ex. librarians) can add books to the system.
      * These administrative users will have their own account that they will log in to.
      * Authors can edit and publish books and send a request to librarians to add the books to the library.
      * Users can search for books by Title, Genre, or Author
      * Program can show a users debt and what book they owe the money for.

### User Interface Specification/ Navigation Diagram
![Navigation Diagram](https://cdn.discordapp.com/attachments/1098140638211485696/1104182590895837237/image.png)

### Screen Layouts
![Welcome Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007949857960017/Library.Management.System.Screen.Layout-02.png)
![Register Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950105432144/Library.Management.System.Screen.Layout-03.png)
![Login Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950369656842/Library.Management.System.Screen.Layout-04.png)
![User Menu Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950617128990/Library.Management.System.Screen.Layout-05.png)
![Admin Menu Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950881378365/Library.Management.System.Screen.Layout-06.png)
![Browse Books Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951133020170/Library.Management.System.Screen.Layout-07.png)
![View Books Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951472775218/Library.Management.System.Screen.Layout-08.png)
![Admin Manage Books Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951737000007/Library.Management.System.Screen.Layout-09.png)
![Admin Add Admin Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951992860724/Library.Management.System.Screen.Layout-10.png)
![Checkout Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007958447890473/Library.Management.System.Screen.Layout-11.png)

## Class Diagram
 ![Class Diagram](https://cdn.discordapp.com/attachments/903147534321582092/1111492444681412749/UML_Diagram-SOLID_incorporation.drawio_2.png) </br>
The project is centered around the LMS class, of which there will exist only 1 LMS object. The purpose of the LMS object is to integrate the CLI (Command Line Interface) with the underlying systems of the project which will provide the desired features specified by the user. The LMS object will have a single reference to the currently signed-in user (or nullptr if the user has not yet logged in) in order to grant the user the ability to perform actions according to their administrative permissions (or lack thereof). There will be a class for users, called User, which will store the typical user data such as the user's name, account balance, and list of checked-out books, along with getter and setter methods to modify these attributes, and other methods that implement actions that all users have the necessary permissions to perform. User also has a virtual method to display the typical User's prompt. There is an admin account which inherits from User and overloads the virtual menu method to add administrative actions to the default menu, with a new attribute and getter method which records the level of clearance that the administrative user has within the system, called priority. The LMS will have a list of all Book objects that exist within the library. The LMS will also contain a single object of the type SearchBase, which will be the class that implements all searching methods required by the program to work as intended. SearchBase will have 2 unordered maps (hashtables), one which maps strings to pointers to the Book objects in LMS's list of books, and one which maps book genres to pointers to the real book objects. Searchbase will have a number of helper functions to break up multi-word strings into lists of single-word strings and methods to add and remove books from the searching database. Finally, the Book class will hold the data relevant to true books in the library, such as a title, author, and genre, number of that book available to check out, and total number of that book belonging to the library. Book will have a custom enum called Genre to list out the genres. Book will also have getter and setter functions for all listed attributes, along with methods to add a specific number of that book to the total or available number of that book (with adding negative values signifying books leaving the library).
 
 ## Phase III
One SOLID principle we applied to the UML diagram was the open-closed principle to the Admin and User classes. The previous user class in the diagram required a boolean to represent whether or not it was an Admin object as well, which violates the open-closed principle because to perform certain actions on Users and Admins, the program had to explicitly check whether or not the User was also an Admin to perform different operations, and if we added more classes inheriting from User we would have to modify logic outside the new classes. To change this, we updated our UML diagram so that the User now has a permission level, with 0 representing no special permissions and anything above representing greater permissions within the program, so external logic only needs to know a User's permission level instead of whether or not it is an Admin object. This will help us write better code since if we decide to add a new User child class, we will not have to modify external logic that operates on users and admins to shoehorn in the new class. </br>

Another change that we made included moving the book database from the LMS class to the search_base class in accordance to the Single-Responsibility Principle. The LMS class' responsibility is to integrate the CLI with the backend of the project through displaying to and reading from the command line. Storing program data violates the single responsibility principle, so we moved the book database to the search_base class, which is supposed to search the database for books that match the queried criteria. This will help us write better code since the responsibilities of each class are now clearer, and as we implement the classes there will be less ambiguity as to which individual methods are responsible for the steps to achieving the higher-level goals.

We also added in a completely new class to manage JSON file I/O for our program's long-term data. This helps us better follow the single responsibility principle so that we can easily read/write data to our files wherever necessary through the use of this helper class. As a result, our code will be more clear and organized whenevr we need to invoke the routines for file I/O that the program relies on to work between multiple instances.
 
 > ## Final deliverable
 > All group members will give a demo to the reader during lab time. ou should schedule your demo on Calendly with the same reader who took your second scrum meeting. The reader will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Project board.
 > * Make sure your README file and Project board are up-to-date reflecting the current status of your project (e.g. any changes that you have made during the project such as changes to your class diagram). Previous versions should still be visible through your commit history. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.

