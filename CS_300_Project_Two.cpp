// CS_300_Project_Two.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//define classes for Course data and binary tree Nodes
class Course
{
public:
    string id;
    string name;
    vector<string> prereqs;

    Course(string id, string name)
    {
        this->id = id;
        this->name = name;
    }
    Course()
    {
        //default empty constructor
    }
};
class Node
{
public:
    Node* left;
    Node* right;
    Course course;

    Node(Course course)
    {
        this->course = course;
        left = nullptr;
        right = nullptr;
    }
};

//declare universally accessible root pointer
Node* root = nullptr;

/// <summary>
/// Searches binary tree data structure and returns found Course object (empty object if not found).
/// </summary>
/// <param name="idToFind">: Course ID to search for</param>
/// <returns></returns>
Course Search(string idToFind)
{
    Node* temp = root;
    while (temp != nullptr)
    {
        if (temp->course.id == idToFind)
        {
            //match found, so return this course
            return temp->course;
        }
        else if (temp->course.id < idToFind)
        {
            //search ID is larger, so move to right
            temp = temp->right;
        }
        else
        {
            //else search ID is smaller, so move to left
            temp = temp->left;
        }
    }

    //else not found (did not return above), so return empty course
    return Course();
}

/// <summary>
/// Takes a Course object and prints ID, name, and any prerequisites to console
/// </summary>
/// <param name="course">: Course object to print data of</param>
void PrintCourseInfo(Course course)
{
    cout << "Course ID:     " << course.id << "\nCourse name:   " << course.name << endl;
    cout << "Prerequisites: ";
    for (int i = 0; i < course.prereqs.size() - 1; i++)
    {
        //print each prerequisited ID (string) followed by a comma and a space EXCEPT last
        cout << course.prereqs[i] << ", ";
    }
    cout << course.prereqs[course.prereqs.size() - 1];  //print last item
}

/// <summary>
/// Recursively iterates through each Node in binary tree and prints ID and name alphnumerically
/// </summary>
/// <param name="node">: Node to print and recursively call from</param>
void PrintAllCourses(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    //recursively call this function on left, then print this, then call on right
    PrintAllCourses(node->left);
    cout << node->course.id << ", " << node->course.name << endl;
    PrintAllCourses(node->right);
}

/// <summary>
/// Creates Course object, converts to Node, then inserts in binary tree at sorted location
/// </summary>
/// <param name="line">: Raw line as string from input file</param>
/// <param name="courseIDs">: Vector containing all existing Course IDs</param>
void InsertCourse(string line, vector<string> courseIDs)
{
    //first, split string to parts vector
    vector<string> parts;
    int start = 0;
    int end = line.find(',');
    while (end != -1)
    {
        parts.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find(',', start);
    }
    parts.push_back(line.substr(start, line.length() - start)); //add last item

    //create Course object with ID, name, and any prerequisites
    Course temp = Course(parts[0], parts[1]);
    for (int i = 2; i < parts.size(); i++)
    {
        //validate each prerequisite, adding to Course's prereqs vector if valid
        for (int j = 0; j < courseIDs.size(); j++)
        {
            if (courseIDs[j] == parts[i])
            {
                //if found match, add this prerequisite (from parts array) to Course object
                temp.prereqs.push_back(parts[i]);
            }
        }
    }

    //create Node object from new Course object and insert as root if root is null
    Node* newNode = new Node(temp);
    Node* currNode = root;
    if (currNode == nullptr)
    {
        //if root is null, set root to newNode and return
        root = newNode;
        //cout << "inserted as root" << endl;
        return;
    }

    //else root node not null, so find correct insert location and insert
    while (currNode != nullptr)
    {
        if (newNode->course.id < currNode->course.id)
        {
            //if new less than current, insert on left if null, else traverse left
            if (currNode->left == nullptr)
            {
                currNode->left = newNode;
                //cout << "inserted on left" << endl;
                return;
            }
            currNode = currNode->left;
            //cout << "moved left, ";
        }
        else
        {
            //if greater, insert on right if null, else traverse right
            if (currNode->right == nullptr)
            {
                currNode->right = newNode;
                //cout << "inserted on right" << endl;
                return;
            }
            currNode = currNode->right;
            //cout << "moved right, ";
        }
    }
}

/// <summary>
/// Opens input file and reads data to be converted to Course objects and inserted into binary tree
/// </summary>
void LoadCoursesFromFile()
{
    ifstream inStream;
    inStream.open("courses.dat");
    string line;
    vector<string> courseIDs;

    if (inStream.is_open())
    {
        //first, add each existing course ID to vector for validation
        while (getline(inStream, line))
        {
            //find location of first comma, then get substring up to that (course ID) and push back
            int end = line.find(',');
            if (end != -1)
            {
                courseIDs.push_back(line.substr(0, end));
            }
        }

        //after first file traversal, must clear inStream and return to line 0
        inStream.clear();
        inStream.seekg(0);

        //second, iterate through each line and actually add course to binary tree
        while (getline(inStream, line))
        {
            if (line.find(','))
            {
                //if there is a comma, then there are at least two items on the line (ID and name)
                InsertCourse(line, courseIDs);
            }
        }
        inStream.close();
    }
    else
    {
        cout << "Failed to open file." << endl;
    }
}


int main()
{
    cout << "Default data file: courses.dat";
    bool alreadyLoaded = false;

    string userInput = "";
    while (userInput != "0")
    {
        cout << "\n\n1: Load courses from file\n2: Print courses list\n" <<
            "3: Print specific course information\n0: Exit\n";
        cin >> userInput;
        cout << "\n";

        //load courses
        if (userInput == "1")
        {
            if (!alreadyLoaded)
            {
                LoadCoursesFromFile();
                alreadyLoaded = true;
            }
            else
            {
                cout << "Courses have already been loaded into data structure." << endl;
            }
        }
        //print all courses
        else if (userInput == "2")
        {
            PrintAllCourses(root);
        }
        //find and print specific course
        else if (userInput == "3")
        {
            cout << "Enter course ID: ";
            cin >> userInput;
            cout << "\n";

            Course temp = Search(userInput);
            if (temp.id == "")
            {
                cout << "Course " << userInput << " was not found." << endl;
            }
            else
            {
                PrintCourseInfo(temp);
            }
        }
        //exit
        else if (userInput == "0")
        {
            cout << "Goodbye.";
            return 0;
        }
        //invalid
        else
        {
            cout << "Invalid input. Please try again.\n";
            continue;
        }
    }
}
