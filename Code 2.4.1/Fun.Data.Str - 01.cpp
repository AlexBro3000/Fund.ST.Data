#include "TimeTable.h"
using namespace std;

string str_TimeTable = "Test/database_read 2.txt";
string str_List = "Test/list.txt";
string str_AK = "Ахо-Карасика/Ахо-Карасика";
string str_KMP = "Кнута-Морриса-Пратта/Кнута-Морриса-Пратта";

int main()
{
    setlocale(LC_ALL, "ru");

    // Считывание "Список образцов"
    SampleList* t_L = new SampleList(getSize(str_List));
    t_L->readFile(str_List);

    // Считывание "Расписание"
    TimeTable* t = new TimeTable(getSize(str_TimeTable));
    t->readFile(str_TimeTable);

    // ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** //
    // ***** ***** ***** ***** Ахо-Карасика                                                            ***** ***** ***** ***** //
    // ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** //
    chrono::system_clock::time_point start_Code_AK= chrono::system_clock::now();
    bool** arr_AK = AhoKarasika(t, t_L);
    chrono::system_clock::time_point finish_Code_AK = chrono::system_clock::now();

    ofstream f_AK(str_AK + ".txt", ios::out);
    if (f_AK.is_open())
        f_AK << chrono::duration_cast<chrono::nanoseconds> (finish_Code_AK - start_Code_AK).count() << " ns\n";
    else
        cout << "Ошибка: Не удалось прочитать файл.\n";
    f_AK.close();
    writeFile(str_AK, arr_AK, t, t_L);

    // ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** //
    // ***** ***** ***** ***** Кнута-Морриса-Пратта                                                    ***** ***** ***** ***** //
    // ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** //
    chrono::system_clock::time_point start_Code_KMP = chrono::system_clock::now();
    bool** arr_KMP = KnuthMorrisPratt(t, t_L);
    chrono::system_clock::time_point finish_Code_KMP = chrono::system_clock::now();

    ofstream f_KMP(str_KMP + ".txt", ios::out);
    if (f_KMP.is_open())
        f_KMP << chrono::duration_cast<chrono::nanoseconds> (finish_Code_KMP - start_Code_KMP).count() << " ns\n";
    else
        cout << "Ошибка: Не удалось прочитать файл.\n";
    f_KMP.close();
    writeFile(str_KMP, arr_KMP, t, t_L);
}
