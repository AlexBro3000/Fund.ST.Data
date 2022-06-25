#include <iostream>
#include "Dynamic_Hash_Table.h"

int main()
{
    setlocale(LC_ALL, "ru");
    Dynamic_Hash_Table* table = new Dynamic_Hash_Table(10);
    
    string s = "AaaaaZ";
    for (int i = 1; i < 10; i++) {
        table->add(new Ingredients(s, "Грамм", 0));
        s[0] += 2;
        s[5] -= 2;
        table->add(new Ingredients(s, "Грамм2", 1));
    }
    table->print_all();
    cout << endl << endl;



    for (int i = 1; i < 6; i++) {
        table->delete_key(new Ingredients(s, "Грамм", 0));
        s[0] -= 4;
        s[5] += 4;

    }
    table->print_all();
    cout << endl << endl;



    s = "OaabaL";
    for (int i = 1; i < 5; i++) {

        table->add(new Ingredients(s, "Грамм1", 0));
        s[0] -= 2;
        s[5] += 2;

    }
    table->print_all();
    cout << endl << endl;
}
