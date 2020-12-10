#include <iostream>
#include <string>
using namespace std;

int RandIndex;

string array[38] = {"George", "John", "Mike", "Jack", "Bryan", "Samantha", "Samuel", "Michele", "Mary", "Sofia", "Clair", "Kathrin", "Jonas", "Jenny", "Sean", "Donald", "Barrack", "Billy", "Oliver", "Jake", "Noah", "James", "Mason", "Robert", "Jacob", "Michael", "Charlie", "William", "Margaret", "Megan", "Jessica", "Lilly", "Tracy", "Sarah", "Mia", "Elizabeth", "Jennifer", "Emma"};

string get_random_name()
{
    RandIndex = rand() % 38;
    return array[RandIndex];
}
