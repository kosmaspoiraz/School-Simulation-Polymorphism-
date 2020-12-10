#include <iostream>
#include <stdlib.h>
#include <string>
#include "getnames.cpp"
#include <time.h>

using namespace std;

class Student
{
private:
    string Name;
    string Place;
    int num_class;
    int num_floor;

public:
    Student(int f, int c)
    {
        Name = get_random_student_name();
        Place = "Out of School";
        num_class = c;
        num_floor = f;
        cout << "A New Student has been created!"
             << " " << Name << ". Floor number: " << num_floor << ". Class number " << num_class << endl;
    }
    ~Student()
    {
        cout << "A Student to be destroyed!"
             << " " << Name << ", in floor number: " << num_floor << ", in class number " << num_class << ", " << Place << endl;
    }

    void print_student()
    {
        cout << endl
             << Name << ". Floor number: " << num_floor << ". Class number: " << num_class << ". " << Place;
    }

    string getname() { return Name; }
    int getfloornum() { return num_floor; }
    int getclassnum() { return num_class; }
    void setplace(string place) { Place = place; }
};

class Teacher
{
private:
    string Name;
    bool in_class;
    int num_class;
    int num_floor;

public:
    Teacher(int f, int c)
    {
        Name = get_random_teacher_name();
        in_class = false;
        num_class = c;
        num_floor = f;
        cout << "A New Teacher has been created!"
             << ". " << Name << ". Floor number: " << num_floor << ". Class number: " << num_class << endl;
    }
    ~Teacher()
    {
        cout << "A Teacher to be destroyed!"
             << ", " << Name << ", in floor number: " << num_floor << ", in class number: " << num_class << endl;
    }

    void print_teacher()
    {
        cout << endl
             << "The teacher is: " << Name << ". Floor number: " << num_floor << ". Class number " << num_class;
        if (in_class == true)
        {
            cout << ". In Class" << endl;
        }
        else
        {
            cout << ". Not in Class" << endl;
        }
    }

    void placeinclass() { in_class = true; }
    string getname() { return Name; }
    int getfloornum() { return num_floor; }
    int getclassnum() { return num_class; }
};

class Class
{
private:
    int num_floor;
    int num_class;
    int capacity;
    int k = 0;
    int i = 0;
    Student **arraystofclass;
    Teacher **teacher_of_class;

public:
    Class(int c_class, int numfloor, int numclass)
    {
        capacity = c_class;
        num_floor = numfloor;
        num_class = numclass;
        arraystofclass = new Student *[capacity];
        teacher_of_class = new Teacher *;
        teacher_of_class[0] = nullptr;
        cout << "A New Class has been created! In Floor number: " << num_floor << ". Class Number: " << num_class << ", Capacity: " << capacity << endl;
    }
    ~Class()
    {
        for (i = 0; i < k; i++)
        {
            delete arraystofclass[i];
        };
        delete[] arraystofclass;
        delete teacher_of_class[0];
        delete[] teacher_of_class;
        cout << "A Class to be destroyed!" << endl;
    }

    void print_class()
    {
        cout << endl
             << "PEOPLE IN CLASS " << num_class << " ARE: ";
        for (i = 0; i < k; i++)
        {
            if (arraystofclass[i] != nullptr)
            {
                arraystofclass[i]->print_student();
            }
            else
            {
                break;
            }
        };
        if (teacher_of_class[0] != nullptr)
        {
            (*teacher_of_class)->print_teacher();
        }
        else
        {
            cout << endl
                 << "There is NO Teacher in class number: " << num_class << ", in floor number: " << num_class << endl;
        }
    }

    void enter_class(Student *student)
    {
        arraystofclass[k] = student;
        arraystofclass[k]->setplace("In Class");
        cout << arraystofclass[k]->getname() << " enters Class number: " << num_class << " ,in floor num: " << num_floor << endl;
        k++;
        capacity--;
    }

    void place_teacher(Teacher *teacher)
    {
        *teacher_of_class = teacher;
        cout << endl
             << "Teacher " << (*teacher_of_class)->getname() << " placed in class number: " << num_class << " in floor number: " << num_floor;
        (*teacher_of_class)->placeinclass();
    }

    Teacher *getteacherofclass() { return *teacher_of_class; }

    int get_class_cap() { return capacity; }
};

class Corridor
{
private:
    int capacity;
    int num_floor;
    Student **arraystofcorr;
    int j = 0;
    int i;
    int times = 0;

public:
    Corridor(int c_corr, int numfloor)
    {
        capacity = c_corr;
        num_floor = numfloor;
        arraystofcorr = new Student *[capacity];
        for (i = 0; i < capacity; i++)
        {
            arraystofcorr[i] = nullptr;
        }
        cout << "A New Corridor has been created!"
             << " In Floor number: " << num_floor << " and Capacity = " << capacity << endl;
    }
    ~Corridor()
    {
        for (i = 0; i < capacity; i++)
        {
            if (arraystofcorr[i] == nullptr)
            {
                delete arraystofcorr[i];
            }
        };
        delete[] arraystofcorr;
        cout << "A Corridor to be destroyed!" << endl;
    }

    void print_corr()
    {
        cout << endl
             << "PEOPLE IN CORRIDOR ARE: ";
        for (i = 0; i < capacity; i++)
        {
            if (arraystofcorr[i] != nullptr)
            {
                arraystofcorr[i]->print_student();
                cout << endl;
            }
        };
    }

    void enter_corr(Student *student)
    {
        arraystofcorr[j] = student;
        arraystofcorr[j]->setplace("In Corridor");
        cout << arraystofcorr[j]->getname() << " enters corridor! In floor: " << num_floor << endl;
        cout << endl;
        capacity--;
        j++;
    }

    Student *exit_corr()
    {
        cout << endl
             << arraystofcorr[j - 1]->getname() << " exits corridor!" << endl;
        Student *dummy = arraystofcorr[j - 1];
        arraystofcorr[j - 1] = nullptr;
        capacity++;
        j--;
        return dummy;
    }

    int setindex()
    {
        if (j >= 1)
        {
            j--;
            times++;
            return 0;
        }
        else
        {
            j = j + times;
            times = 0;
            return 1;
        }
    }
    int get_corr_cap() { return capacity; }
    int getnumclassbeforeexit()
    {
        if (j == 0)
        {
            return 100;
        }
        if (arraystofcorr[j - 1] != nullptr)
        {
            return arraystofcorr[j - 1]->getclassnum();
        }
        else
        {
            return 200;
        }
    }
};

class Floor
{
private:
    Class **arrayc;
    Corridor *corridor;
    Student *dummy;
    int num_floor;
    int c_class;
    int c_corr;
    int i = 0;
    int j = 0;
    int classtoenter = 0;
    int capacity = 0;

public:
    Floor(int cclass, int ccorr, int i)
    {
        c_class = cclass;
        c_corr = ccorr;
        num_floor = i;
        cout << "A New Floor has been created! Floor number: " << num_floor << endl;
        corridor = new Corridor(c_corr, num_floor);
        arrayc = new Class *[6];
        for (j = 0; j < 6; j++)
        {
            arrayc[j] = new Class(c_class, num_floor, j);
        };
    }

    ~Floor()
    {
        for (j = 0; j < 6; j++)
        {
            delete arrayc[j];
        }
        delete[] arrayc;
        delete corridor;
        cout << "A Floor to be destroyed!" << endl;
    }

    void print_floor()
    {
        cout << endl
             << "FLOOR NUMBER " << num_floor << " CONTAINS: ";
        corridor->print_corr();
        for (j = 0; j < 6; j++)
        {
            arrayc[j]->print_class();
        };
    }

    void enter_floor(Student *student)
    {
        //ENTER STUDENT IN CORR
        if (student != nullptr)
        {
            cout << student->getname() << " enters floor! Floor number: " << num_floor << endl;
            student->setplace("In Floor");
            corridor->enter_corr(student);
        }
        //NULL DUMMY ENTERED
        else
        {
            //START ENTERING STUDENTS FROM CORR TO CLASS, UNTIL CORR IS EMPTY
            while (corridor->get_corr_cap() < c_corr)
            {
                //CHECK IF STUDENT'S CLASSTOENTER IS FULL AND IF CLASSTOENTER HAS TEACHER AND ENTER
                classtoenter = corridor->getnumclassbeforeexit();
                if (classtoenter == 100)
                {
                    break;
                }
                //IF STUDENT = NULL CHECK NEXT STUDENT
                else if (classtoenter == 200)
                {
                    if (corridor->setindex() == 1)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if ((arrayc[classtoenter]->get_class_cap() > 0) and (arrayc[classtoenter]->getteacherofclass() == nullptr))
                {
                    student = corridor->exit_corr();
                    arrayc[classtoenter]->enter_class(student);
                }
                //ELSE CHECK NEXT STUDENT IN CORR
                else
                {
                    if (arrayc[classtoenter]->get_class_cap() == 0)
                    {
                        cout << "NO CAPACITY in class number: " << classtoenter << " ! Can't enter Class!" << endl;
                    }
                    if (arrayc[classtoenter]->getteacherofclass() == nullptr)
                    {
                        cout << "TEACHER ALREADY IN CLASS NUMBER: " << classtoenter << " ! CAN'T ENTER!" << endl;
                    }
                    //IF NO STUDENT LEFT TO CHECK IN CORR STOP ENTER FORM CORR TO CLASS
                    if (corridor->setindex() == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    int get_corr_cap() { return corridor->get_corr_cap(); }

    void place_teacher(Teacher *teacher)
    {
        classtoenter = teacher->getclassnum();
        arrayc[classtoenter]->place_teacher(teacher);
    }
};

class Stair
{
private:
    int capacity;
    Student **arraystofstair;
    Student *dummy;
    int j = 0;
    int i = 0;
    int times = 0;

public:
    Stair(int c_stair)
    {
        capacity = c_stair;
        arraystofstair = new Student *[capacity];
        cout << "A New Stair has been created!" << endl;
    }
    ~Stair()
    {
        for (i = 0; i < capacity; i++)
        {
            delete arraystofstair[i];
        };
        delete[] arraystofstair;
        cout << "A Stair to be destroyed!" << endl;
    }

    void print_stair()
    {
        cout << endl
             << endl
             << "PEOPLE IN STAIR ARE: ";
        for (i = 0; i < capacity; i++)
        {
            if (arraystofstair[i] == nullptr)
            {
                cout << "NO STUDENTS IN STAIR!" << endl;
                break;
            }
            arraystofstair[i]->print_student();
        };
    }

    void enter_stair(Student *student)
    {
        arraystofstair[j] = student;
        arraystofstair[j]->setplace("In Stair");
        cout << arraystofstair[j]->getname() << " enters stair!" << endl;
        capacity--;
        j++;
    }

    Student *exit_stair()
    {
        cout << endl
             << arraystofstair[j - 1]->getname() << " exits stair!" << endl;
        dummy = arraystofstair[j - 1];
        arraystofstair[j - 1] = nullptr;
        capacity++;
        j--;
        return dummy;
    }

    int getnumfloorbeforeexit() { return arraystofstair[j - 1]->getfloornum(); }
    int get_stair_cap() { return capacity; }
    int setindex()
    {
        if (j >= 1)
        {
            j--;
            times++;
            return 0;
        }
        else
        {
            j = j + times;
            times = 0;
            return 1;
        }
    }
};

class Yard
{
private:
    int capacity;
    Student **arraystofyard;
    Student *dummy;
    int j = 0;
    int i = 0;

public:
    Yard(int c_yard)
    {
        capacity = c_yard;
        arraystofyard = new Student *[capacity];
        cout << "A New Yard has been created!" << endl;
    }
    ~Yard()
    {
        for (i = 0; i < capacity; i++)
        {
            delete arraystofyard[i];
        };
        delete[] arraystofyard;
        cout << "A Yard to be destroyed!" << endl;
    }

    void print_yard()
    {
        cout << endl
             << "PEOPLE IN SCHOOLYARD ARE: ";
        for (i = 0; i < capacity; i++)
        {
            if (arraystofyard[i] == nullptr)
            {
                cout << endl
                     << "NO MORE STUDENTS IN SCHOOLYARD!" << endl;
                break;
            }
            arraystofyard[i]->print_student();
        };
    }

    void enter_schoolyard(Student *student)
    {
        arraystofyard[j] = student;
        arraystofyard[j]->setplace("In Schoolyard");
        cout << arraystofyard[j]->getname() << " enters schoolyard!" << endl;
        capacity--;
        j++;
    }

    Student *exit_schoolyard()
    {
        cout << endl
             << arraystofyard[j - 1]->getname() << " exits schoolyard!" << endl;
        dummy = arraystofyard[j - 1];
        arraystofyard[j - 1] = nullptr;
        capacity++;
        j--;
        return dummy;
    }

    int get_yard_cap() { return capacity; }
};

class School
{
private:
    Floor **arrayf;
    Yard **yard;
    Stair **stair;
    int i = 0;
    int floortoenter = 0;
    int c_class;
    int c_corr;
    int c_stair;
    int c_yard;

public:
    School(int cclass, int cyard, int cstair, int ccorr)
    {
        cout << "A New School has been created!" << endl;
        c_class = cclass;
        c_yard = cyard;
        c_stair = cstair;
        c_corr = ccorr;
        yard = new Yard *;
        stair = new Stair *;
        arrayf = new Floor *[3];
        yard[0] = new Yard(c_yard);
        stair[0] = new Stair(c_stair);
        for (i = 0; i < 3; i++)
        {
            arrayf[i] = new Floor(c_class, c_corr, i);
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

    void print_school()
    {
        cout << endl
             << endl
             << "SCHOOL LIFE CONSISTS OF: ";
        (*yard)->print_yard();
        (*stair)->print_stair();
        for (i = 0; i < 3; i++)
        {
            arrayf[i]->print_floor();
        };
    };

    void enter_school(Student *student)
    {
        //ENTER STUDENTS UNTIL YARD IS FULL OR DIFFERENT PLACES ENTER IS TRIGGERED WITH NULL DUMMY
        if ((student != nullptr) && (*yard)->get_yard_cap() > 0)
        {
            cout << endl
                 << student->getname() << " enters school!" << endl;
            student->setplace("In School");
            (*yard)->enter_schoolyard(student);
        }
        else
        {
            cout << endl
                 << "NO CAPACITY in schoolyard! Can't enter School!" << endl;
            //START ENTERING STUDENTS IN STAIR FROM YARD, UNTIL YARD IS EMPTY OR STAIR IS FULL
            while (((*stair)->get_stair_cap() > 0) && ((*yard)->get_yard_cap() < c_yard))
            {
                student = (*yard)->exit_schoolyard();
                (*stair)->enter_stair(student);
            }
            if ((*stair)->get_stair_cap() == 0)
            {
                cout << endl
                     << "NO CAPACITY in stair! Can't enter Stair!" << endl;
            }
            if ((*yard)->get_yard_cap() == c_yard)
            {
                cout << endl
                     << "YARD IS EMPTY!" << endl;
            }
            //START LOOP OF ENTERING STUDENTS IN FLOORS FROM STAIR, UNTIL STAIR IS EMPTY
            while ((*stair)->get_stair_cap() < c_stair)
            {
                //CHECK IF STUDENT'S FLOORTOENTER IS FULL AND ENTER
                floortoenter = (*stair)->getnumfloorbeforeexit();
                if (arrayf[floortoenter]->get_corr_cap() > 0)
                {
                    student = (*stair)->exit_stair();
                    arrayf[floortoenter]->enter_floor(student);
                }
                //IF FLOORTOENTER IS FULL CHECKING NEXT STUDENT IN STAIR
                else
                {
                    cout << "NO CAPACITY in floor! Can't enter Floor!" << endl;
                    if ((*stair)->setindex() == 1)
                    {
                        break;
                    }
                }
            }
            if ((*stair)->get_stair_cap() == c_stair)
            {
                cout << "STAIR IS EMPTY!" << endl;
            }
            //TRIGGER ENTER FOR EACH FLOOR WITH NULL DUMMY
            Student *dummy = nullptr;
            for (i = 0; i < 3; i++)
            {
                arrayf[i]->enter_floor(dummy);
            }
        }
    }

    void enter_school_inarray(Student *student[], int size)
    {
        for (i = 0; i > size; i++)
        {
            enter_school(student[i]);
        };
    }

    void place_teacher(Teacher *teacher)
    {
        floortoenter = teacher->getfloornum();
        arrayf[floortoenter]->place_teacher(teacher);
    }

    int getyardcap() { return (*yard)->get_yard_cap(); }
};

int main()
{
    //INITIALIZING NEEDED VARIABLES AND TYPES
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    int c = 1;
    int c_class = 10;
    int capacity = (c_class * 18);
    int randnum = 0;
    int tcap = 18;
    srand(time(NULL));

    School *sxoleio;
    sxoleio = new School(c_class);
    Student **arrays;
    Teacher **arrayt;
    Student *temps;
    Teacher *tempt;
    Student *dummy = nullptr;

    //CREATING STUDENTS WITH FLOOR AND CLASS NUMBER
    arrays = new Student *[capacity];
    while (i < capacity)
    {
        for (f = 0; f < 3; f++)
        {
            for (c = 0; c < 6; c++)
            {
                arrays[i] = new Student(f, c);
                i++;
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
                arrayt[i] = new Teacher(f, c);
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

    //ENTERING LOOP
    while (capacity > 0)
    {
        //ENTERING STUDENTS UNTIL YARD HAS NO MORE CAP
        i = 0;
        while ((sxoleio->getyardcap() > 0) and (capacity > 0))
        {
            sxoleio->enter_school(arrays[i]);
            arrays[i] = nullptr;
            capacity--;
            i++;
        };
        //INITIALIZING ENTER FOR DIFFERENT PLACES
        sxoleio->enter_school(dummy);
        //GETTING RANDOM NUMBER OF ENTERING TEACHERS(INCLUDING 0)
        if (tcap > 0)
        {
            randnum = rand() % tcap;
            //ENTERING TEACHERS
            for (i = (tcap - randnum - 1); i < tcap; i++)
            {
                sxoleio->place_teacher(arrayt[i]);
                arrayt[i] = nullptr;
            };
            tcap = tcap - randnum - 1;
        }
    }

    //COMMAND FOR ENTERING SCHOOL INARRAY OF STUDENTS
    //sxoleio.enter_school_inarray(arrays, sizeof(arrays))

    //PRINTING SCHOOL
    sxoleio->print_school();

    cout << endl
         << "END OF SIMULATION!" << endl
         << endl;

    //INITIALIZING THE DESTRUCTION OF SCHOOL
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

    //END OF PROGRAM
    return 0;
}
