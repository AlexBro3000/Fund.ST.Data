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
        return BinarySearchHomogeneous<size_t>(val, delta(1), 2, 0, size + 1);
    }
    template<typename Type = size_t>
    vector<size_t> BinarySearchHomogeneous(Type val, size_t i, size_t j, size_t _begin, size_t _end)
    {
        vector<size_t> result;
        size_t step = 1;

        while (true)
        {
            if (val == records[i - 1].classroom)
            {
                if (i != _begin && i != _end)
                    result.push_back(records[i - 1].number_str);

                if (delta(j) != 0)
                {
                    vector<size_t> result_l = BinarySearchHomogeneous<size_t>(val, i - delta(j), j + 1, _begin, i);
                    for (auto k = result_l.begin(); k < --result_l.end(); ++k)
                        result.push_back(*k);

                    vector<size_t> result_r = BinarySearchHomogeneous(val, i + delta(j), j + 1, i, _end);
                    for (auto k = result_r.begin(); k < --result_r.end(); ++k)
                        result.push_back(*k);

                    result.push_back(step + *(--result_l.end()) + *(--result_r.end()));
                }
                else
                    result.push_back(step);

                return result;
            }
            else
                if (val < records[i - 1].classroom)
                {
                    if (delta(j) == 0 || i == _begin + 1)
                    {
                        result.push_back(step);
                        return result;
                    }
                    i = i - delta(j);
                    j++;
                }
                else
                {
                    if (delta(j) == 0 || i == _end - 1)
                    {
                        result.push_back(step);
                        return result;
                    }
                    i = i + delta(j);
                    j++;
                }
            step++;
        }
    }

private:
    void setRecords(size_t n, string s);
    void quick_sort(int i, int j);

    size_t delta(size_t j);

};

void writeFile(string str, size_t key, vector<size_t> array_data);
size_t getSize(string str);
