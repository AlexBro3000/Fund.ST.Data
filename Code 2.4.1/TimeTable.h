#pragma once
#include <iostream>
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
    Time date;           // Дата
    size_t number;          // Номер пары
    string discipline;   // Название дисциплины
    size_t group;           // Номер группы
    size_t classroom;       // Номер аудитории
    FULL_NAME FIO;

    inline bool operator<(const _string_timetable& other)
    {
        if (discipline < other.discipline)
            return true;
        else
            if (discipline == other.discipline && group > other.group)
                return true;
        return false;
    }
    inline bool operator>(const _string_timetable& other)
    {
        if (discipline > other.discipline)
            return true;
        else
            if (discipline == other.discipline && group < other.group)
                return true;
        return false;
    }
};

class SampleList
{
protected:
    const size_t size;
    string* list;

public:
    SampleList(const size_t& _size);

    void readFile(string str);

    size_t getSize();
    string* getList();
private:

};

class TimeTable
{
protected:
    const size_t size;
    _string_timetable* records;

public:
    TimeTable(const size_t& _size);

    void readFile(string str);

    size_t getSize();
    _string_timetable getRecords(size_t n);
    string getString(size_t n);
private:
    void setRecords(size_t n, string s);
};

bool** AhoKarasika(TimeTable* t_AK, SampleList* t_L);
bool** KnuthMorrisPratt(TimeTable* t_KMP, SampleList* t_L);

void writeFile(string str, bool** arr, TimeTable* t_T, SampleList* t_L);
size_t getSize(string str);
