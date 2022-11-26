# SNHU_CS300_Project
C++ coding project for CS-300 DSA: Analysis and Design

## What was the problem you were solving in the projects for this course?
The client handled student admissions for a local university. Employees wanted the ability to search through a list of available courses and view respective data like course ID, course name, and any course prerequisites. They also wanted to be able to print all courses alphanumerically by course ID.

## How did you approach the problem? Consider why data structures are important to understand.
I first identified what kind of information would need to be stored: the course ID, name, and any prerequisites. Naturally, this data was best stored in an object corresponding to exactly one course. Then, I determined that the best container to store the data was a binary tree; using a binary tree, each course would be implicitly sorted and searching and inserting courses would be a highly efficient process.

## How did you overcome any roadblocks you encountered while going through the activities or project?
Naturally, google was my greatest resource when developing the code. I had to look up C++ syntax on multiple occasions, like how exactly to open and close a file. However, when designing before developing actual code, time was my greatest resource. I reserved enough time to think about what would work and what would not, and this allowed me to correctly implement the binary tree.

## How has your work on this project expanded your approach to designing software and developing programs?
This project was a bit challenging, at least in some aspects. As a non-trivial task, it helped me realize the importance of thoroughly planning before beginning code development. Without detailed pseudocode, I would have had a much more difficult time developing the actual code.

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
I am happy to say that I have had acceptable habits when it comes to maintainability, readability, and adaptability thus far. I am aware of the importance of modular code, for instance, but I can say for certain that this project expanded my knowledge. For instance, by keeping the Search() function separate from the Print() function, any function is able to search the existing binary tree without redundant code.
