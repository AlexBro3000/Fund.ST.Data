#include "TimeTable.h"

size_t _max(size_t s, size_t max)
{
    stringstream ss; ss << s;
    string str = ss.str();
    if (max < str.size())
        return str.size();
    else
        return max;
}
size_t _max(string s, size_t max)
{
    if (max < s.size())
        return s.size();
    else
        return max;
}
string _write(size_t s, size_t max)
{
    stringstream ss; ss << s;
    string str = ss.str();
    while (str.size() < max)
    {
        str = str + " ";
    }
    return str + " ";
}
string _write(string s, size_t max)
{
    while (s.size() < max)
    {
        s = s + " ";
    }
    return s + " ";
}
string _write(Time t, size_t maxh, size_t maxm)
{
    stringstream ssh; ssh << t.hour;
    stringstream ssm; ssm << t.minutes;
    string strh = ssh.str();
    string strm = ssm.str();
    if (strh.size() < maxh)
        strh = "0" + strh;
    if (strm.size() < maxm)
        strm = ":0" + strm;
    else
        strm = ":" + strm;
    return strh + strm + " ";
}

/* TimeTable  */
TimeTable::TimeTable(const size_t& _size) :
    size(_size)
{
    records = new _string_timetable[size];
}

void TimeTable::readFile(string str)
{
    ifstream f(str, ios::in);
    string temp;
    if (f.is_open())
    {
        getline(f, temp);

        for (size_t i = 0; i < size; i++)
        {
            getline(f, temp);
            setRecords(i, temp);
        }
    }
    else
        cout << "Ошибка: Не удалось прочитать файл.\n";
    f.close();
}

void TimeTable::quick_sort(int i, int j)
{
    _string_timetable support = records[(i + j + 2) / 2];
    int _i = i; int _j = j;

    while (i <= j)
    {
        while (records[i] < support) i++;
        while (records[j] > support) j--;

        if (i <= j)
        {
            swap(records[i], records[j]);
            i++; j--;
        }
    }
    if (_i < j) quick_sort(_i, j);
    if (i < _j) quick_sort(i, _j);
}

void TimeTable::writeFile()
{
    ofstream f("database_write.txt", ios::out);
    if (f.is_open())
    {
        int s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0, s8 = 0;
        for (int i = 0; i < size; i++)
        {
            s0 = _max(records[i].date.hour, s0);
            s1 = _max(records[i].date.minutes, s1);
            s2 = _max(records[i].number, s2);
            s3 = _max(records[i].discipline, s3);
            s4 = _max(records[i].group, s4);
            s5 = _max(records[i].classroom, s5);
            s6 = _max(records[i].FIO.surname, s6);
            s7 = _max(records[i].FIO.name, s7);
            s8 = _max(records[i].FIO.patronymic, s8);
        }
        for (int i = 0; i < size; i++)
        {
            f << _write(records[i].date, s0, s1) << _write(records[i].number, s2) << _write(records[i].discipline, s3) << _write(records[i].group, s4) <<
                _write(records[i].classroom, s5) << _write(records[i].FIO.surname, s6) << _write(records[i].FIO.name, s7) << _write(records[i].FIO.patronymic, s8) << endl;
        }
    }
    else
        cout << "Ошибка: Не удалось прочитать файл.\n";
    f.close();
}

size_t TimeTable::getSize()
{
    return size;
}

_string_timetable TimeTable::getRecords(size_t n)
{
    return records[n];
}

string TimeTable::getString(size_t n)
{
    return records[n].FIO.surname + " " + records[n].FIO.name + " " + records[n].FIO.patronymic + " " + records[n].discipline;
}

void TimeTable::setRecords(size_t n, string s)
{
    stringstream ss(s);
    string hour, minutes, number, discipline, group, classroom, F, I, O;

    try
    {
        getline(ss, hour, ':');
        getline(ss, minutes, ' ');
        getline(ss, number, ' ');
        getline(ss, discipline, ' ');
        getline(ss, group, ' ');
        getline(ss, classroom, ' ');
        getline(ss, F, ' ');
        getline(ss, I, ' ');
        getline(ss, O, ' ');

        records[n].date.hour = stoi(hour);
        records[n].date.minutes = stoi(minutes);
        records[n].number = stoi(number);
        records[n].discipline = discipline;
        records[n].group = stoi(group);
        records[n].classroom = stoi(classroom);
        records[n].FIO.surname = F;
        records[n].FIO.name = I;
        records[n].FIO.patronymic = O;

        records[n].number_str = n + 2;
    }
    catch (...)
    {
        cout << "Ошибка. Не удалось корректно считать строку: " << n + 1 << endl;
    }
}

void TimeTable::quick_sort()
{
    if (size > 1)
        quick_sort(0, size - 1);
}

size_t TimeTable::delta(size_t j)
{
    size_t j2 = 1;
    for (size_t i = 0; i < j; i++)
        j2 = 2 * j2;

    return (size + j2 / 2) / j2;
}

void writeFile(string str, size_t key, vector<size_t> array_data)
{
    ofstream f(str, ios::out);
    f << "Ключ:             " << key << endl;
    f << "Количество шагов: " << *(--array_data.end()) << endl;
    f << "Результат поиска:" << endl;
    for (size_t i = 0; i < array_data.size() - 1; i++)
        f << array_data[i] << endl;
    f.close();
}

size_t getSize(string str)
{
    ifstream f(str, ios::in);
    string temp; size_t size = 0;
    if (f.is_open())
    {
        getline(f, temp);
        size = stoi(temp);
    }
    else
        cout << "Ошибка: Не удалось прочитать файл.\n";
    f.close();

    return size;
}
