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
    virtual ~Human(){};

    virtual void attend(int hours) { fatigue = fatigue + (hours * L); }

    virtual void teach(int hours) { fatigue = fatigue + (hours * L); }

    void print()
    {
        cout << Name << " with Fatigue: " << fatigue << endl;
    }

    int getnumclass() { return num_class; }

    int getnumfloor() { return num_floor; }

    string getname() { return Name; }
};

class Student : public Human
{
private:
public:
    Student(int f, int c, int L) : Human(f, c, L)
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

class Junior : public Student
{
private:
public:
    Junior(int f, int c, int lj) : Student(f, c, lj) {}
    virtual ~Junior(){};
};

class Senior : public Student
{
private:
public:
    Senior(int f, int c, int ls) : Student(f, c, ls) {}
    virtual ~Senior(){};
};

class Teacher : public Human
{
private:
public:
    Teacher(int f, int c, int lt) : Human(f, c, lt)
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
    Human *student;

public:
    Place() {}
    virtual ~Place(){};

    virtual void print(){};

    virtual void enter(Human *s) { student = s; }

    virtual Human *exit() { return student; }

    virtual void place(Human *t){};

    virtual void operate(int hours){};
};

class Class : public Place
{
private:
    int num_class;
    int num_floor;
    int capacity;
    int c_class;
    Human **arrays;
    Human *teacher;
    int i = 0;
    int test = 0;

public:
    Class(int cclass, int numfloor, int numclass)
    {
        capacity = cclass;
        c_class = cclass;
        num_floor = numfloor;
        num_class = numclass;
        arrays = new Human *[capacity];
        cout << "A New Class has been created! Class number " << num_class << ", in Floor number: " << num_floor << endl;
    }
    ~Class()
    {
        cout << endl;
        for (i = 0; i < c_class; i++)
        {
            delete arrays[i];
        };
        delete[] arrays;
        delete teacher;
        cout << "A Class to be destroyed! Class number: " << num_class << ", in Floor number: " << num_floor << endl;
    }

    void print()
    {
        cout << endl
             << "PEOPLE IN CLASS NUMBER " << num_class << ":" << endl;
        for (i = 0; i < c_class; i++)
        {
            arrays[i]->print();
        }
        cout << "THE TEACHER IS: ";
        teacher->print();
        cout << endl;
    }

    void enter(Human *s)
    {
        arrays[i] = s;
        cout << arrays[i]->getname() << " enters Class number: " << num_class << ", in Floor number: " << num_floor << endl;
        i++;
        capacity--;
        test++;
    }

    void place(Human *t)
    {
        teacher = t;
        cout << "Teacher " << teacher->getname() << " enters Class number: " << num_class << ", in Floor number: " << num_floor << endl;
    }

    void operate(int hours)
    {
        cout << "CLASS NUMBER " << num_class << ", IN FLOOR NUMBER " << num_floor << " OPERATES FOR " << hours << " HOURS!" << endl;
        for (i = 0; i < c_class; i++)
        {
            arrays[i]->attend(hours);
        }
        teacher->teach(hours);
    }
};

class Corridor : public Place
{
private:
    Human *student;

public:
    Corridor()
    {
        cout << "A New Corridor has been created!" << endl;
    }
    ~Corridor()
    {
        cout << "A Corridor to be destroyed!" << endl;
    }
    void enter(Human *student)
    {
        cout << student->getname() << " enters Corridor!" << endl;
        Place::enter(student);
    }
    Human *exit()
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
    Human *student;
    Human *teacher;
    Place **arrayc;
    Place *corridor;
    int classtoenter;
    int i = 0;

public:
    Floor(int c_class, int j)
    {
        num_floor = j;
        cout << endl
             << "A New Floor has been created! Floor number: " << num_floor << endl;
        corridor = new Corridor();
        arrayc = new Place *[6];
        for (j = 0; j < 6; j++)
        {
            arrayc[j] = new Class(c_class, num_floor, j);
        };
    }
    ~Floor()
    {
        for (i = 0; i < 6; i++)
        {
            delete arrayc[i];
        };
        delete[] arrayc;
        delete corridor;
        cout << "A Floor to be destroyed! Floor number: " << num_floor << endl;
    }

    void print()
    {
        cout << "FLOOR NUMBER " << num_floor << " CONTAINS: " << endl;
        for (i = 0; i < 6; i++)
        {
            arrayc[i]->print();
        }
    }

    void enter(Human *s)
    {
        student = s;
        cout << student->getname() << " enters Floor number: " << num_floor << "!" << endl;
        corridor->enter(student);
        student = corridor->exit();
        classtoenter = student->getnumclass();
        arrayc[classtoenter]->enter(student);
    }

    void place(Human *t)
    {
        teacher = t;
        classtoenter = teacher->getnumclass();
        arrayc[classtoenter]->place(teacher);
    }

    void operate(int hours)
    {
        cout << endl
             << "FLOOR NUMBER " << num_floor << " OPERATES FOR " << hours << " HOURS!" << endl;
        for (i = 0; i < 6; i++)
        {
            arrayc[i]->operate(hours);
        }
    }
};

class Stair : public Place
{
private:
    Human *student;

public:
    Stair()
    {
        cout << "A New Stair has been created!" << endl;
    }
    ~Stair()
    {
        cout << "A Stair to be destroyed!" << endl;
    }
    void enter(Human *student)
    {
        cout << student->getname() << " enters Stair!" << endl;
        Place::enter(student);
    }
    Human *exit()
    {
        student = Place::exit();
        cout << student->getname() << " exits Stair!" << endl;
        return student;
    }
};

class Yard : public Place
{
private:
    Human *student;

public:
    Yard()
    {
        cout << "A New Schoolyard has been created!" << endl;
    }
    ~Yard()
    {
        cout << "A Schoolyard to be destroyed!" << endl;
    }
    void enter(Human *student)
    {
        cout << student->getname() << " enters Schoolyard!" << endl;
        Place::enter(student);
    }
    Human *exit()
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
    Place **arrayf;
    Place **yard;
    Place **stair;
    int i = 0;
    int floortoenter;

public:
    School(int cclass)
    {
        cout << "A New School has been created!" << endl;
        c_class = cclass;
        yard = new Place *;
        stair = new Place *;
        arrayf = new Place *[3];
        yard[0] = new Yard();
        stair[0] = new Stair();
        for (i = 0; i < 3; i++)
        {
            arrayf[i] = new Floor(c_class, i);
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
        cout << endl
             << "SCHOOL LIFE CONSISTS OF: " << endl;
        for (i = 0; i < 3; i++)
        {
            arrayf[i]->print();
        }
    }

    void enter(Human *student)
    {
        cout << endl
             << student->getname() << " enters School!" << endl;
        (*yard)->enter(student);
        student = (*yard)->exit();
        (*stair)->enter(student);
        student = (*stair)->exit();
        floortoenter = student->getnumfloor();
        arrayf[floortoenter]->enter(student);
    }

    void place(Human *teacher)
    {
        floortoenter = teacher->getnumfloor();
        arrayf[floortoenter]->place(teacher);
    }

    void operate(int hours)
    {
        cout << endl
             << "SCHOOL OPERATES FOR " << hours << " HOURS!" << endl;
        for (i = 0; i < 3; i++)
        {
            arrayf[i]->operate(hours);
        }
    }
};

int main(int argc, char *argv[])
{
    int c_class = atoi(argv[1]);
    int capacity = 18 * c_class;
    int Lj = atoi(argv[2]);
    int Ls = atoi(argv[3]);
    int Lt = atoi(argv[4]);
    int N = atoi(argv[5]);
    int i = 0;
    int f = 0;
    int c = 0;
    int j = 0;
    int k = 0;
    Human **arrays;
    Human **arrayt;
    Human *temps;
    Human *tempt;

    //CREATING SCHOOL
    Place *sxoleio = new School(c_class);

    cout << endl;

    //CREATING STUDENTS WITH FLOOR AND CLASS NUMBER
    arrays = new Human *[capacity];
    while (i < capacity)
    {
        for (f = 0; f < 3; f++)
        {
            for (j = 0; j < c_class; j++)
            {
                for (c = 0; c < 3; c++)
                {
                    arrays[i] = new Junior(f, c, Lj);
                    i++;
                }
                for (c = 3; c < 6; c++)
                {
                    arrays[i] = new Senior(f, c, Ls);
                    i++;
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

    cout << endl;

    //CREATING TEACHER WITH FLOOR AND CLASS NUMBER
    i = 0;
    arrayt = new Human *[18];
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

    //ENTERING STUDENTS
    for (i = 0; i < capacity; i++)
    {
        sxoleio->enter(arrays[i]);
        arrays[i] = nullptr;
    }

    cout << endl;

    //ENTERING TEACHERS
    for (i = 0; i < 18; i++)
    {
        sxoleio->place(arrayt[i]);
        arrayt[i] = nullptr;
    }

    //OPERATING SCHOOL FOR N HOURS
    sxoleio->operate(N);

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
        if (arrays[i] != nullptr)
        {
            delete arrays[i];
        }
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