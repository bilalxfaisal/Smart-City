#pragma once
#include "Nodes.h"
using namespace std;

//Student Map
//Hashing based on ID
class Student_Hash_Map
{
private:
    Student** Map_Arr = nullptr;
    int capacity = 0;
    int curr_size = 0;

public:
    Student_Hash_Map(int init = 10)
    {
        capacity = init;
        curr_size = 0;
        Map_Arr = new Student * [capacity]();
        for (int i = 0; i < capacity; i++)
        {
            Map_Arr[i] = nullptr;
        }
    }
    void Insert(Student* new_Student)
    {
        if (float(curr_size) / capacity > 0.7)
        {
            Resize();
        }
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(new_Student->studentID) % capacity);
        Student* Slot = Map_Arr[index];
        if (Slot == nullptr)
        {
            Map_Arr[index] = new_Student; 
            curr_size++;
        }
        else
        {
            while (Slot != nullptr)
            {
                if (Slot->studentID == new_Student->studentID)
                {
                    //Update vals?
                    Slot->name = new_Student->name;
                    Slot->age = new_Student->age;
                    return;
                }
                Slot = Slot->next;
            }
            //O(1) chain insertion
            new_Student->next = Map_Arr[index];
            Map_Arr[index] = new_Student;
            curr_size++;
        }

    }
    //Well 
    void Resize()
    {
        //Save old valss
        int oldcap = capacity;
        Student** old_map = Map_Arr;

        capacity *= 2;
        Student** Map_Arr = new Student * [capacity];

        for (int i = 0; i < oldcap; i++)
        {
            Student* temp = old_map[i];
            while (temp != nullptr)
            {
                Student* nxt = temp->next;

                //Rehash 
                int index = (HashFuncs::Polynomial_Rolling_Hash_V1(temp->studentID) % capacity);
                temp->next = Map_Arr[index];
                Map_Arr[index] = temp;
                temp = nxt;


            }
        }
        delete[] old_map;
    }
    bool Contains(string studentID)
    {
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(studentID) % capacity);
        Student* Slot = Map_Arr[index];
        while (Slot != nullptr)
        {
            if (Slot->studentID == studentID)
            {
                return true;
            }
            Slot = Slot->next;
        }
        return false;
    }
    Student* Get(string studentID)
    {
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(studentID) % capacity);
        Student* Slot = Map_Arr[index];
        while (Slot != nullptr)
        {
            if (Slot->studentID == studentID)
            {
                return Slot;
            }
            Slot = Slot->next;
        }
        return nullptr;
    }
    //An operator overload for easier access
    Student& operator[](string studentID)
    {
        Student* result = Get(studentID);
        if (result == nullptr)
        {
            // Handle the case where the student is not found
            throw std::runtime_error("Student not found");
        }
        return *result;
    }
    int get_size()
    {
        return curr_size;
    }

    ~Student_Hash_Map()
    {
        for (int i = 0; i < capacity; i++)
        {
            Student* temp = Map_Arr[i];
            while (temp != nullptr)
            {
                Student* nxt = temp->next;
                delete temp;
                temp = nxt;
            }
        }
        delete[] Map_Arr;
    }


};
class Teacher_Hash_Map
{
private:
    Teacher** Map_Arr = nullptr;
    int capacity = 0;
    int curr_size = 0;

public:
    Teacher_Hash_Map(int init = 10)
    {
        capacity = init;
        curr_size = 0;
        Map_Arr = new Teacher * [capacity]();
        for (int i = 0; i < capacity; i++)
        {
            Map_Arr[i] = nullptr;
        }
    }

    void Insert(Teacher* new_Teacher)
    {
        if (float(curr_size) / capacity > 0.7)
        {
            Resize();
        }

        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(new_Teacher->teacherID) % capacity);
        Teacher* Slot = Map_Arr[index];

        if (Slot == nullptr)
        {
            Map_Arr[index] = new_Teacher;
            curr_size++;
        }
        else
        {
            while (Slot != nullptr)
            {
                if (Slot->teacherID == new_Teacher->teacherID)
                {
                    Slot->name = new_Teacher->name;
                    Slot->specialization = new_Teacher->specialization;
                    return;
                }
                Slot = Slot->next;
            }

            new_Teacher->next = Map_Arr[index];
            Map_Arr[index] = new_Teacher;
            curr_size++;
        }
    }

    void Resize()
    {
        int oldcap = capacity;
        Teacher** old_map = Map_Arr;

        capacity *= 2;
        Map_Arr = new Teacher * [capacity]();

        for (int i = 0; i < oldcap; i++)
        {
            Teacher* temp = old_map[i];
            while (temp != nullptr)
            {
                Teacher* nxt = temp->next;

                int index = (HashFuncs::Polynomial_Rolling_Hash_V1(temp->teacherID) % capacity);
                temp->next = Map_Arr[index];
                Map_Arr[index] = temp;

                temp = nxt;
            }
        }

        delete[] old_map;
    }

    bool Contains(string teacherID)
    {
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(teacherID) % capacity);
        Teacher* Slot = Map_Arr[index];

        while (Slot != nullptr)
        {
            if (Slot->teacherID == teacherID)
            {
                return true;
            }
            Slot = Slot->next;
        }
        return false;
    }

    Teacher* Get(string teacherID)
    {
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(teacherID) % capacity);
        Teacher* Slot = Map_Arr[index];

        while (Slot != nullptr)
        {
            if (Slot->teacherID == teacherID)
            {
                return Slot;
            }
            Slot = Slot->next;
        }
        return nullptr;
    }

    Teacher& operator[](string teacherID)
    {
        Teacher* result = Get(teacherID);
        if (result == nullptr)
        {
            throw runtime_error("Teacher not found");
        }
        return *result;
    }

    int get_size()
    {
        return curr_size;
    }

    ~Teacher_Hash_Map()
    {
        for (int i = 0; i < capacity; i++)
        {
            Teacher* temp = Map_Arr[i];
            while (temp != nullptr)
            {
                Teacher* nxt = temp->next;
                delete temp;
                temp = nxt;
            }
        }
        delete[] Map_Arr;
    }
};

class School_Hash_Map
{
private:
    School** Map_Arr = nullptr;
    int capacity = 0;
    int curr_size = 0;

public:
    School_Hash_Map(int init = 10)
    {
        capacity = init;
        curr_size = 0;
        Map_Arr = new School * [capacity]();
        for (int i = 0; i < capacity; i++)
        {
            Map_Arr[i] = nullptr;
        }
    }

    void Insert(School* new_School)
    {
        if (float(curr_size) / capacity > 0.7)
        {
            Resize();
        }

        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(new_School->schoolID) % capacity);
        School* Slot = Map_Arr[index];

        if (Slot == nullptr)
        {
            Map_Arr[index] = new_School;
            curr_size++;
        }
        else
        {
            while (Slot != nullptr)
            {
                if (Slot->schoolID == new_School->schoolID)
                {
                    Slot->schoolName = new_School->schoolName;
                    Slot->sector = new_School->sector;
                    Slot->rating = new_School->rating;
                    Slot->subjects = new_School->subjects;
                    Slot->subjectCount = new_School->subjectCount;
                    return;
                }
                Slot = Slot->next;
            }

            new_School->next = Map_Arr[index];
            Map_Arr[index] = new_School;
            curr_size++;
        }
    }

    void Resize()
    {
        int oldcap = capacity;
        School** old_map = Map_Arr;

        capacity *= 2;
        Map_Arr = new School * [capacity]();

        for (int i = 0; i < oldcap; i++)
        {
            School* temp = old_map[i];
            while (temp != nullptr)
            {
                School* nxt = temp->next;

                int index = (HashFuncs::Polynomial_Rolling_Hash_V1(temp->schoolID) % capacity);
                temp->next = Map_Arr[index];
                Map_Arr[index] = temp;

                temp = nxt;
            }
        }

        delete[] old_map;
    }

    bool Contains(string schoolID)
    {
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(schoolID) % capacity);
        School* Slot = Map_Arr[index];

        while (Slot != nullptr)
        {
            if (Slot->schoolID == schoolID)
            {
                return true;
            }
            Slot = Slot->next;
        }
        return false;
    }

    School* Get(string schoolID)
    {
        int index = (HashFuncs::Polynomial_Rolling_Hash_V1(schoolID) % capacity)_

