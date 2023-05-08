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

 > ## Phase II
 > In addition to completing the "User Interface Specification" and "Class Diagram" sections below, you will need to:
 > * Create an "Epic" (note) for each feature. Place these epics in the `Product Backlog` column
 > * Complete your first *sprint planning* meeting to plan out the next 7 days of work.
 >   * Break down the "Epics" into smaller actionable user stories (i.e. smaller development tasks). Convert them into issues and assign them to team members. Place these in the `TODO` column.
 >   * These cards should represent roughly 7 days worth of development time for your team. Then, once the sprint is over you should be repeating these steps to plan a new sprint, taking you until your second scrum meeting with the reader in phase III.
 > * Schedule two check-ins using Calendly. You need to pick both time slots during your lab on week 6. Your entire team must be present for both check-ins.
 >   * The first check-in needs to be scheduled with your lab TA. During that meeting, you will discuss your project design/class diagram from phase II.
 >   * The second check-in should be scheduled with a reader. During that meeting you will discuss:
 >     * The tasks you are planning for the first sprint
 >     * How work will be divided between the team members
## User Interface Specification
 > Include a navigation diagram for your screens and the layout of each of those screens as desribed below. For all the layouts/diagrams, you can use any tool such as PowerPoint or a drawing program. (Specification requirement is adapted from [this template](https://redirect.cs.umbc.edu/~mgrass2/cmsc345/Template_UI.doc))

### Navigation Diagram
> ![Navigation Diagram](https://cdn.discordapp.com/attachments/1098140638211485696/1104182590895837237/image.png)

### Screen Layouts
> ![Welcome Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007949857960017/Library.Management.System.Screen.Layout-02.png)
> ![Register Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950105432144/Library.Management.System.Screen.Layout-03.png)
> ![Login Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950369656842/Library.Management.System.Screen.Layout-04.png)
> ![User Menu Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950617128990/Library.Management.System.Screen.Layout-05.png)
> ![Admin Menu Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007950881378365/Library.Management.System.Screen.Layout-06.png)
> ![Browse Books Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951133020170/Library.Management.System.Screen.Layout-07.png)
> ![View Books Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951472775218/Library.Management.System.Screen.Layout-08.png)
> ![Admin Manage Books Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951737000007/Library.Management.System.Screen.Layout-09.png)
> ![Admin Add Admin Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007951992860724/Library.Management.System.Screen.Layout-10.png)
> ![Checkout Screen](https://cdn.discordapp.com/attachments/1098140638211485696/1105007958447890473/Library.Management.System.Screen.Layout-11.png)

## Class Diagram
 > Include a **class diagram(s)** for your project and a **description** of the diagram(s). Your class diagram(s) should include all the main classes you plan for the project. This should be in sufficient detail that another group could pick up the project this point and successfully complete it. Use proper UML notation (as discussed in the course slides).
 
 > ## Phase III
 > You will need to schedule a check-in for the second scrum meeting with the same reader you had your first scrum meeting with (using Calendly). Your entire team must be present. This meeting will occur on week 8 during lab time.
 
 > BEFORE the meeting you should do the following:
 > * Update your class diagram from Phase II to include any feedback you received from your TA/grader.
 > * Considering the SOLID design principles, reflect back on your class diagram and think about how you can use the SOLID principles to improve your design. You should then update the README.md file by adding the following:
 >   * A new class diagram incorporating your changes after considering the SOLID principles.
 >   * For each update in your class diagram, you must explain in 3-4 sentences:
 >     * What SOLID principle(s) did you apply?
 >     * How did you apply it? i.e. describe the change.
 >     * How did this change help you write better code?
 > * Perform a new sprint plan like you did in Phase II.
 > * You should also make sure that your README file (and Project board) are up-to-date reflecting the current status of your project and the most recent class diagram. Previous versions of the README file should still be visible through your commit history.
 
> During the meeting with your reader you will discuss: 
 > * How effective your last sprint was (each member should talk about what they did)
 > * Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 > * Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 > * What tasks you are planning for this next sprint.

 
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

