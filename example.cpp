#include <iostream>
#include <stdlib.h>
#include <string>
#include "getnames.cpp"
#include <time.h>

using namespace std;

class Human
{
private:
    string Name;
    bool inclass;
    int num_class;
    int num_floor;
    int fatigue;
    int L;

public:
    Human(int f, int c, int l)
    {
        Name = get_random_name();
        inclass = false;
        num_class = c;
        num_floor = f;
        fatigue = 0;
        L = l;
    }
    ~Human() {}

    void attend(int hours)
    {
        fatigue = fatigue + (hours * L);
    }

    void teach(int hours) { fatigue = fatigue + (hours * L); }

    void print()
    {
        cout << endl
             << Name << " with Fatigue: " << fatigue << endl;
    }

    int getnumclass() { return num_class; }

    int getnumfloor() { return num_floor; }

    string getname() { return Name; }
};

class Student : public Human
{
private:
public:
    Student(int f, int c, int l) : Human(f, c, l)
    {
        cout << "A New Student has been created!"
             << " " << getname() << ". Floor number: " << getnumfloor() << ". Class number " << getnumclass() << endl;
    }
    ~Student()
    {
        cout << "A Student to be destroyed!"
             << " " << getname() << ". Floor number: " << getnumfloor() << ". Class number " << getnumclass() << endl;
    }
};

class Teacher : public Human
{
private:
public:
    Teacher(int f, int c, int l) : Human(f, c, l)
    {
        cout << "A New Teacher has been created!"
             << " " << getname() << ". Floor number: " << getnumfloor() << ". Class number " << getnumclass() << endl;
    }
    ~Teacher()
    {
        cout << "A Teacher to be destroyed!"
             << " " << getname() << ". Floor number: " << getnumfloor() << ". Class number " << getnumclass() << endl;
    }
};

class Place
{
private:
    int hours;
    Student *student;

public:
    Place(int N)
    {
        hours = N;
    }
    virtual ~Place(){};

    virtual void enter(Student *s) { student = s; }

    virtual Student *exit() { return student; }

    void operate(int hours) {}
};

class Class : public Place
{
private:
    int num_class;
    int num_floor;
    int capacity;
    Student **arrays;
    Teacher *teacher;
    int i = 0;

public:
    Class(int cclass, int numfloor, int numclass, int N) : Place(N)
    {
        capacity = cclass;
        num_floor = numfloor;
        num_class = numclass;
        arrays = new Student *[capacity];
        cout << "A New Class has been created! Class number " << num_class << ", in Floor number: " << num_floor << endl;
    }
    ~Class()
    {
        cout << "A Class to be destroyed! Class number: " << num_class << ", in Floor number: " << num_floor << endl;
    }

    void print()
    {
        cout << "People in class number " << num_class << ":" << endl;
        for (i = 0; i < sizeof(arrays); i++)
        {
            arrays[i]->print();
        }
        cout << "The teacher is: ";
        teacher->print();
        cout << endl;
    }

    void enter(Student *s)
    {
        if (capacity > 0)
        {
            arrays[i] = s;
            cout << arrays[i]->getname() << " enters Class number: " << num_class << ", in Floor number: " << num_floor << endl;
            i++;
            capacity--;
        }
        else
        {
            cout << "CLASS IS FULL!" << endl;
        }
    }

    void place(Teacher *t)
    {
        teacher = t;
        cout << "Teacher " << teacher->getname() << " enters Class number: " << num_class << ", in Floor number: " << num_floor << endl;
    }
};

class Corridor : public Place
{
private:
    Student *student;

public:
    Corridor(int N) : Place(N)
    {
        cout << "A New Corridor has been created!" << endl;
    }
    ~Corridor()
    {
        cout << "A Corridor to be destroyed!" << endl;
    }
    void enter(Student *student)
    {
        cout << student->getname() << " enters Corridor!" << endl;
        Place::enter(student);
    }
    Student *exit()
    {
        student = Place::exit();
        cout << student->getname() << " exits Corridor!" << endl;
        return student;
    }
};

class Floor : public Place
{
private:
    int num_floor;
    Student *student;
    Teacher *teacher;
    Class **arrayc;
    Corridor *corridor;
    int classtoenter;
    int i = 0;

public:
    Floor(int N, int c_class, int j) : Place(N)
    {
        num_floor = j;
        cout << "A New Floor has been created! Floor number: " << num_floor << endl;
        corridor = new Corridor(N);
        arrayc = new Class *[6];
        for (j = 0; j < 6; j++)
        {
            arrayc[j] = new Class(c_class, num_floor, j, N);
        };
    }
    ~Floor()
    {
        cout << "A Floor to be destroyed! Floor number: " << num_floor << endl;
    }

    void print()
    {
        cout << "Floor number " << num_floor << " contains: " << endl;
        for (i = 0; i < 6; i++)
        {
            arrayc[i]->print();
        }
    }

    void enter(Student *s)
    {
        student = s;
        cout << student->getname() << " enters Floor number: " << num_floor << "!" << endl;
        corridor->enter(student);
        student = corridor->exit();
        classtoenter = student->getnumclass();
        arrayc[classtoenter]->enter(student);
    }

    void place(Teacher *t)
    {
        teacher = t;
        classtoenter = teacher->getnumclass();
        arrayc[classtoenter]->place(teacher);
    }
};

class Stair : public Place
{
private:
    Student *student;

public:
    Stair(int N) : Place(N)
    {
        cout << "A New Stair has been created!" << endl;
    }
    ~Stair()
    {
        cout << "A Stair to be destroyed!" << endl;
    }
    void enter(Student *student)
    {
        cout << student->getname() << " enters Stair!" << endl;
        Place::enter(student);
    }
    Student *exit()
    {
        student = Place::exit();
        cout << student->getname() << " exits Stair!" << endl;
        return student;
    }
};

class Yard : public Place
{
private:
    Student *student;

public:
    Yard(int N) : Place(N)
    {
        cout << "A New Schoolyard has been created!" << endl;
    }
    ~Yard()
    {
        cout << "A Schoolyard to be destroyed!" << endl;
    }
    void enter(Student *student)
    {
        cout << student->getname() << " enters Schoolyard!" << endl;
        Place::enter(student);
    }
    Student *exit()
    {
        student = Place::exit();

        cout << student->getname() << " exits Schoolyard!" << endl;
        return student;
    }
};

class School : public Place
{
private:
    int c_class;
    Floor **arrayf;
    Yard **yard;
    Stair **stair;
    int i = 0;
    int floortoenter;

public:
    School(int cclass, int N) : Place(N)
    {
        cout << "A New School has been created!" << endl;
        c_class = cclass;
        yard = new Yard *;
        stair = new Stair *;
        arrayf = new Floor *[3];
        yard[0] = new Yard(N);
        stair[0] = new Stair(N);
        for (i = 0; i < 3; i++)
        {
            arrayf[i] = new Floor(N, c_class, i);
        };
    }
    ~School()
    {
        for (i = 0; i < 3; i++)
        {
            delete arrayf[i];
        };
        delete[] arrayf;
        delete stair[0];
        delete[] stair;
        delete yard[0];
        delete[] yard;
        cout << "A School to be destroyed!" << endl;
    }

    void print()
    {
        cout << "School life consists of: " << endl;
        for (i = 0; i < 3; i++)
        {
            arrayf[i]->print();
        }
    }

    void enter(Student *student)
    {
        cout << student->getname() << " enters School!" << endl;
        (*yard)->enter(student);
        student = (*yard)->exit();
        (*stair)->enter(student);
        student = (*stair)->exit();
        floortoenter = student->getnumfloor();
        arrayf[floortoenter]->enter(student);
    }

    void place(Teacher *teacher)
    {
        floortoenter = teacher->getnumfloor();
        arrayf[floortoenter]->place(teacher);
    }
};

int main()
{
    int c_class = 5;
    int capacity = 18 * c_class;
    int Lj = 3;
    int Ls = 2;
    int Lt = 2;
    int N = 8;
    int i = 0;
    int f = 0;
    int c = 0;
    int j = 0;
    int k = 0;
    Student **arrays;
    Teacher **arrayt;
    Student *temps;
    Teacher *tempt;

    //CREATING SCHOOL
    School *sxoleio;
    sxoleio = new School(c_class, N);

    //CREATING STUDENTS WITH FLOOR AND CLASS NUMBER
    arrays = new Student *[capacity];
    while (i < capacity)
    {
        for (f = 0; f < 3; f++)
        {
            for (j = 0; j < c_class; j++)
            {
                for (c = 0; c < 3; c++)
                {
                    arrays[i] = new Student(f, c, Lj);
                    i++;
                }
                for (c = 3; c < 6; c++)
                {
                    arrays[i] = new Student(f, c, Ls);
                }
            }
        }
    }

    //MIXING STUDENTS SO THAT ENTER IS RANDOM
    for (i = 0; i < capacity; i++)
    {
        j = rand() % capacity;
        k = rand() % capacity;
        temps = arrays[j];
        arrays[j] = arrays[k];
        arrays[k] = temps;
    };

    //CREATING TEACHER WITH FLOOR AND CLASS NUMBER
    i = 0;
    arrayt = new Teacher *[18];
    while (i < 18)
    {
        for (f = 0; f < 3; f++)
        {
            for (c = 0; c < 6; c++)
            {
                arrayt[i] = new Teacher(f, c, Lt);
                i++;
            }
        }
    }
    //MIXING THEM SO THAT ENTER IS RANDOM
    for (i = 0; i < 18; i++)
    {
        j = rand() % 18;
        k = rand() % 18;
        tempt = arrayt[j];
        arrayt[j] = arrayt[k];
        arrayt[k] = tempt;
    };

    for (i = 0; i < capacity; i++)
    {
        sxoleio->enter(arrays[i]);
    }
    for (i = 0; i < 18; i++)
    {
        sxoleio->place(arrayt[i]);
    }

    //PRINT SCHOOL
    sxoleio->print();

    //END OF SIMULATION
    cout << "END OF SIMULATION!" << endl
         << endl;

    //DESTROY SCHOOL
    delete sxoleio;

    cout << endl;

    //DESTRUCTION OF ANY STUDENT AND TEACHER NOT ENTERED SCHOOL
    for (i = 0; i < capacity; i++)
    {
        delete arrays[i];
    };
    delete[] arrays;
    for (i = 0; i < 18; i++)
    {
        if (arrayt[i] != nullptr)
        {
            delete arrayt[i];
        }
    };
    delete[] arrayt;

    return 0;
}