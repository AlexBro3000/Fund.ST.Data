#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

struct Time
{
    size_t hour;
    size_t minutes;
};
struct FULL_NAME
{
    string surname;      // Фамилия
    string name;         // Имя
    string patronymic;   // Отчество
};
struct _string_timetable
{
    size_t number_str;   // Номер строки

    Time date;           // Дата
    size_t number;       // Номер пары
    string discipline;   // Название дисциплины
    size_t group;        // Номер группы
    size_t classroom;    // Номер аудитории
    FULL_NAME FIO;

    inline bool operator<(const _string_timetable& other)
    {
        if (classroom  < other.classroom)
            return true;
        return false;
    }
    inline bool operator>(const _string_timetable& other)
    {
        if (classroom > other.classroom)
            return true;
        return false;
    }
};

class TimeTable
{
protected:
    const size_t size;
    _string_timetable* records;

public:
    TimeTable(const size_t& _size);

    void readFile(string str);
    void quick_sort();

    void writeFile();

    size_t getSize();
    _string_timetable getRecords(size_t n);
    string getString(size_t n);

    template<typename Type = size_t>
    vector<size_t> LinearSearch(Type val)
    {
        _string_timetable* temp = new _string_timetable[size];
        for (size_t i = 0; i < size; i++)
        {
            temp[i].number_str = records[i].number_str;
            temp[i].date = records[i].date;
            temp[i].number = records[i].number;
            temp[i].discipline = records[i].discipline;
            temp[i].group = records[i].group;
            temp[i].classroom = records[i].classroom;
            temp[i].FIO = records[i].FIO;
        }
        vector<size_t> result; size_t step = 0;

        size_t i = 0;
        while (i < size)
        {
            if (temp[i].classroom == val)
                result.push_back(temp[i].number_str);
            i++; step++;
        }
        result.push_back(step);

        return result;
    }
    template<typename Type = size_t>
    vector<size_t> BinarySearchHomogeneous(Type val)
    {
        _string_timetable* temp = new _string_timetable[size];
        for (size_t i = 0; i < size; i++)
        {
            temp[i].number_str = records[i].number_str;
            temp[i].date = records[i].date;
            temp[i].number = records[i].number;
            temp[i].discipline = records[i].discipline;
            temp[i].group = records[i].group;
            temp[i].classroom = records[i].classroom;
            temp[i].FIO = records[i].FIO;
        }
        vector<size_t> result; size_t step = 0;

        bool bool_t1 = true;
        while (bool_t1)
        {
            bool_t1 = false;

            int i = delta(1, size - result.size());
            int j = 2;

            bool bool_t2 = true;
            while (bool_t2)
            {
                if (val == temp[i - 1].classroom)
                {
                    result.push_back(temp[i - 1].number_str);
                    for (size_t j = i - 1; j < size - result.size(); j++)
                        temp[j] = temp[j + 1];
                    bool_t1 = true;
                    bool_t2 = false;
                }
                else
                    if (val < temp[i - 1].classroom)
                    {
                        if (delta(j, size - result.size()) == 0 || i == 0 || i == size - 1)
                            bool_t2 = false;
                        i = i - delta(j, size - result.size());
                        j++;
                    }
                    else
                    {
                        if (delta(j, size - result.size()) == 0 || i == 0 || i == size - 1)
                            bool_t2 = false;
                        i = i + delta(j, size - result.size());
                        j++;
                    }
                step++;
            }
        }
        result.push_back(step);

        return result;
    }

private:
    void setRecords(size_t n, string s);
    void quick_sort(int i, int j);

    size_t delta(size_t j, size_t size);

};

void writeFile(string str, size_t key, vector<size_t> array_data);
size_t getSize(string str);
