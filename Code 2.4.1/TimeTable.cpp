#include "TimeTable.h"

struct bohr_vrtx
{
    bohr_vrtx* vrtx[256] = {};
    bohr_vrtx* parents = nullptr;
    bohr_vrtx* prefix = nullptr;
    int flag = -1;
};

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
string strToSize_t(size_t n)
{
    stringstream ss; ss << n;
    return ss.str();
}
size_t** alignment(size_t size_L, size_t size_T, bool** arr, TimeTable* t_T)
{
    size_t** s = new size_t* [size_L];
    for (size_t i = 0; i < size_L; i++)
    {
        s[i] = new size_t[9];
        for (size_t j = 0; j < 9; j++)
            s[i][j] = 0;
    }

    for (size_t i = 0; i < size_T; i++)
    {
        for (size_t j = 0; j < size_L; j++)
        {
            if (arr[i][j])
            {
                _string_timetable str = t_T->getRecords(i);

                s[j][0] = _max(str.date.hour, s[j][0]);
                s[j][1] = _max(str.date.minutes, s[j][1]);
                s[j][2] = _max(str.number, s[j][2]);
                s[j][3] = _max(str.discipline, s[j][3]);
                s[j][4] = _max(str.group, s[j][4]);
                s[j][5] = _max(str.classroom, s[j][5]);
                s[j][6] = _max(str.FIO.surname, s[j][6]);
                s[j][7] = _max(str.FIO.name, s[j][7]);
                s[j][8] = _max(str.FIO.patronymic, s[j][8]);
            }
        }
    }

    return s;
}



/* SampleList */
SampleList::SampleList(const size_t& _size) :
    size(_size)
{
    list = new string[size];
}

void SampleList::readFile(string str)
{
    ifstream f(str, ios::in);
    string temp;
    if (f.is_open())
    {
        getline(f, temp);

        for (size_t i = 0; i < size; i++)
        {
            getline(f, temp);
            list[i] = temp;
        }
    }
    else
        cout << "Ошибка: Не удалось прочитать файл.\n";
    f.close();
}

size_t SampleList::getSize()
{
    return size;
}
string* SampleList::getList()
{
    return list;
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
    }
    catch (...)
    {
        cout << "Ошибка. Не удалось корректно считать строку: " << n + 1 << endl;
    }
}



bohr_vrtx* GetPrefix(bohr_vrtx* ver)
{
    if (ver->prefix != nullptr)
        return ver->prefix;
    else if (ver->parents == nullptr)
        return ver;
    else if (ver->parents->parents == nullptr)
        return ver->parents;
    else
    {
        size_t c = 0;
        while (ver != ver->parents->vrtx[c])
            c++;

        bohr_vrtx* delta = GetPrefix(ver->parents);
        while (delta->parents != nullptr && delta->vrtx[c] == nullptr)
            delta = GetPrefix(delta);
        if (delta->parents != nullptr)
            return delta->vrtx[c];
        else
            return delta;
    }
}
bohr_vrtx* FindBohr(SampleList* t)
{
    bohr_vrtx* root = new bohr_vrtx();

    // Построение
    for (size_t i = 0; i < t->getSize(); i++)
    {
        string* str = t->getList();
        bohr_vrtx* ver = root;

        for (size_t j = 0; j < str[i].size(); j++)
        {
            if (ver->vrtx[(size_t)str[i][j]] == nullptr)
            {
                ver->vrtx[(size_t)str[i][j]] = new bohr_vrtx();
                ver->vrtx[(size_t)str[i][j]]->parents = ver;
            }
            ver = ver->vrtx[(size_t)str[i][j]];
        }
        ver->flag = i;
    }

    // Префиксы
    for (size_t i = 0; i < t->getSize(); i++)
    {
        string* str = t->getList();
        bohr_vrtx* ver = root;

        ver->prefix = GetPrefix(ver);
        for (size_t j = 0; j < str[i].size(); j++)
        {
            ver = ver->vrtx[(size_t)str[i][j]];
            ver->prefix = GetPrefix(ver);
        }
    }

    return root;
}
bool** AhoKarasika(TimeTable* t_AK, SampleList* t_L)
{
    size_t size_AK = t_AK->getSize();
    size_t size_L = t_L->getSize();

    bohr_vrtx* root_bohr = FindBohr(t_L);
    
    bool** arr = new bool* [size_AK];
    for (size_t i = 0; i < size_AK; i++)
    {
        arr[i] = new bool[size_L];
        for (size_t j = 0; j < size_L; j++)
            arr[i][j] = false;

        bohr_vrtx* bohr = root_bohr;
        string records = t_AK->getString(i);
        size_t n = records.size();

        for (size_t j = 0; j < n; j++)
        {
            if (bohr->vrtx[(size_t)records[j]] == nullptr)
            {
                while ((bohr->prefix != bohr) && (bohr->vrtx[(size_t)records[j]] == nullptr))
                {
                    bohr = bohr->prefix;
                    if (bohr->flag != -1)
                        arr[i][bohr->flag] = true;
                }
            }
            if (bohr->vrtx[(size_t)records[j]] != nullptr)
            {
                bohr = bohr->vrtx[(size_t)records[j]];
            }
            if (bohr->flag != -1)
                arr[i][bohr->flag] = true;
        }
    }
    
    return arr;
}

size_t** FindBorders(SampleList* t)
{
    size_t** arr = new size_t* [t->getSize()];

    for (size_t i = 0; i < t->getSize(); i++)
    {
        string* list = t->getList();
        size_t m = list[i].size();
        arr[i] = new size_t[m + 1];
        size_t k = 0;
        arr[i][0] = k;
        arr[i][1] = k;

        for (size_t j = 1; j < m; j++)
        {
            while ((k > 0) && (list[i][j] != list[i][k]))
                k = arr[i][k];
            if (list[i][j] == list[i][k])
                k = k + 1;
            arr[i][j + 1] = k;
        }

        /*for (size_t j = 0; j < m + 1; j++)
            cout << arr[i][j];
        cout << endl;*/
    }

    return arr;
}
bool** KnuthMorrisPratt(TimeTable* t_KMP, SampleList* t_L)
{
    size_t size_KMP = t_KMP->getSize();
    size_t size_L = t_L->getSize();

    bool** arr = new bool* [size_KMP];
    for (size_t i = 0; i < size_KMP; i++)
    {
        arr[i] = new bool[size_L];
        string records = t_KMP->getString(i);

        for (size_t j = 0; j < size_L; j++)
        {
            string* list = t_L->getList();
            bool q = false;
            size_t m = list[j].size();
            size_t n = records.size();
            size_t* b = FindBorders(t_L)[j];
            size_t l = 0;

            for (size_t k = 0; k < n; k++)
            {
                if (!q)
                {
                    while ((l > 0) && (records[k] != list[j][l]))
                        l = b[l];
                    if (records[k] == list[j][l])
                        l++;
                    if (l == m)
                    {
                        q = true;
                        l = b[l];
                    }
                }
            }
            arr[i][j] = q;
        }
    }

    return arr;
}

void writeFile(string str, bool** arr, TimeTable* t_T, SampleList* t_L)
{

    size_t size_T = t_T->getSize();
    size_t size_L = t_L->getSize();

    size_t** s = alignment(size_L, size_T, arr, t_T);

    for (size_t i = 0; i < size_L; i++)
    {
        ofstream f(str + "[" + strToSize_t(i + 1) + "][" + t_L->getList()[i] + "].txt", ios::out); // ios::app
        if (f.is_open())
        {
            for (size_t j = 0; j < size_T; j++)
            {
                if (arr[j][i])
                {
                    _string_timetable str = t_T->getRecords(j);
                    
                    f << _write(str.date, s[i][0], s[i][1]) << _write(str.number, s[i][2]) << _write(str.discipline, s[i][3]) + _write(str.group, s[i][4]) <<
                        _write(str.classroom, s[i][5]) << _write(str.FIO.surname, s[i][6]) << _write(str.FIO.name, s[i][7]) << _write(str.FIO.patronymic, s[i][8]) << endl;
                }
            }
        }
        else
            cout << "Ошибка: Не удалось прочитать файл.\n";
        f.close();
    }
    
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
