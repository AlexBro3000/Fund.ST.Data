#include <iostream>
#include "Dynamic_Hash_Table.h"

int main()
{
    setlocale(LC_ALL, "ru");

    Dynamic_Hash_Table* table = new Dynamic_Hash_Table(1);
    table->add(new Ingredients("Молоко", "Литр", 120));
    table->add(new Ingredients("Молоко", "Килограмм", 120));
    table->add(new Ingredients("Молоко", "Литр", 40));
    table->add(new Ingredients("Яблоко", "Килограмм", 400));

    table->add(new Ingredients("Соль", "Грамм", 0));
    table->add(new Ingredients("Перец черный", "Грамм", 251));
    table->add(new Ingredients("Масло сливочное", "Килограм", 7170));
    table->add(new Ingredients("Масло растительное", "Литр", 8840));
    table->add(new Ingredients("Масло оливковое", "Литр", 8840));
    table->print_all();

    cout << table->seach("Молоко");
    cout << endl << endl;

    table->delete_key("Молоко");
    table->delete_key("Молоко");
    table->delete_key("Яблоко");
    table->delete_key("Соль");
    table->print_all();

    cout << table->seach("Молоко");
    cout << endl << endl;

}
