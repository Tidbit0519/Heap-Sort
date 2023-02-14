#pragma once
#include <string>
#include <iomanip>;

using namespace std;

class Person
{
private:
	string name;
	int id;
	int age;
	string job;
	int hireyear;

public:
	Person(string, int, int, string, int);
	int getId();
	string getName();
	int getAge();
	string getJob();
	int getHireYear();
};