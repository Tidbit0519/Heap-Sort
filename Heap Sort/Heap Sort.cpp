#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Person.h"
#include <sstream>

using namespace std;
vector<Person> record;
int comparisons;

// Match the attributes of Person class to the method parameters.
Person::Person(string n, int i, int a, string j, int h) {
    name = n;
    id = i;
    age = a;
    job = j;
    hireyear = h;
}

int Person::getId() {
    return id;
}

string Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

string Person::getJob() {
    return job;
}

int Person::getHireYear() {
    return hireyear;
}


// A helper function that prints the ID.
void printIdOnly() {
    for (Person person : record)
    {
        cout << person.getId() << " ";
    }
    cout << endl;
}

// writes the sorted record to a .txt file
void writeToFile() {
    ofstream ofs;
    ofs.open("C:/Users/Jason Tan/OneDrive - Brigham Young University Hawaii/Documents/output.txt");
    for (Person person : record) {
        ofs << person.getName() << "|" << person.getId() << "|" << person.getAge() << "|" << person.getJob() << "|" << person.getHireYear() << endl;
    }
}

// parent node
int parent(int i) {
    return i / 2;
}

// left child node
int left(int i) {
    return 2*i+1;
}

// right child node
int right(int i) {
    return 2*(i+1);
}

// makes sure the data is in max heap format.
void maxHeapify(int n, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    comparisons += 1;
    // the if conditions checks for the largest value and arranges the parent, left and right child node in a heap format
    if (l <= n && record[l].getId() > record[i].getId()) {
        largest = l;
    } 
    comparisons += 1;
    if (r <= n && record[r].getId() > record[largest].getId()) {
        largest = r;
    }
    if (largest != i) {
        swap(record[i], record[largest]);
        maxHeapify(n, largest);
    }
}

// Calls the maxHeapify function in a loop to make sure the data is in max heap format
void buildMaxHeap(int n) {
    for (int i = record.size()/2; i >= 0; i--) {
        maxHeapify(n, i);
    }
}

// Heap Sort Function.
// Build a max heap each time after it sorts. Starts sorting from the back.
void heapSort(int n) {
    //printIdOnly();
    buildMaxHeap(n);
    for (int i = n; i >= 1; i--) {
        //printIdOnly();
        swap(record[0], record[i]);
        n = n - 1;
        maxHeapify(n, 0);
    }
}

// agrc = total argument count, argv = the arguments passed into the function
int main(int argc, char** argv) {
    // check for errors: missing argument or file not found
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // checks the first line of the file to determine the number of records in the file, and the number of times to be looped.
    string firstLine;
    // getline gets the first line from the ifstream and stores it into a string variable
    getline(ifs, firstLine);
    // Convert firstLine into an int
    int recordNum = stoi(firstLine);


    for (int i = 0; i < recordNum; i++)
    {
        string nextLine;
        // gets the nextline
        getline(ifs, nextLine);

        string name;
        int id;
        int age;
        string job;
        int hireyear;

        char delimiter = '|';
        string words;
        stringstream ss(nextLine);
        // gets the next word until it spots a pipe "|" delimeter
        // initializing each object's fields with data from the file
        getline(ss, words, delimiter);
        name = words;
        getline(ss, words, delimiter);
        id = stoi(words);
        getline(ss, words, delimiter);
        age = stoi(words);
        getline(ss, words, delimiter);
        job = words;
        getline(ss, words, delimiter);
        hireyear = stoi(words);

        // instantiating a new object for each record in the file
        Person employee(name, id, age, job, hireyear);
        record.push_back(employee);
    }
    int heapSize = record.size()-1;
    heapSort(heapSize);
    //printIdOnly();
    cout << "It took " << comparisons << " comparisons to sort this list.";
    //writeToFile();
}

// Big O of Heap Sort is O(n log n).