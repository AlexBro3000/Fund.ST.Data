#include "TimeTable.h"
using namespace std;

string str_TimeTable = "Test/database_read 1.txt";
string str_LinearSearch = "LinearSearch.txt";
string str_BinarySearchHomogeneous = "BinarySearchHomogeneous.txt";

int main()
{
    setlocale(LC_ALL, "ru");

    // Считывание ключа
    size_t key;
    cin >> key;

    // Считывание "Расписание"
    TimeTable* t = new TimeTable(getSize(str_TimeTable));
    t->readFile(str_TimeTable);
    t->quick_sort();
    t->writeFile();

    vector<size_t> result_LinearSearch = t->LinearSearch(key);
    writeFile(str_LinearSearch, key, result_LinearSearch);

    vector<size_t> result_BinarySearchHomogeneous = t->BinarySearchHomogeneous(key);
    writeFile(str_BinarySearchHomogeneous, key, result_BinarySearchHomogeneous);
}
