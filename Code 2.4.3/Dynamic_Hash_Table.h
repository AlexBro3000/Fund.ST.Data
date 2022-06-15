#pragma once
#include <iostream>
#include <sstream>
using namespace std;

struct Ingredients
{
	Ingredients(string name, string units, size_t calories) :
		name(name), units(units), calories(calories)
	{ }

	string name;
	string units;
	size_t calories;
};

struct Dynamic_Hash_Table_Cell
{
	Ingredients* data;
	size_t flag = 0;
	// 0 - пусто
	// 1 - занято
	// 2 - удалено
};

class Dynamic_Hash_Table
{
public:
	Dynamic_Hash_Table(size_t size, double_t less_dynamic_factor = 0.6, double_t more_dynamic_factor = 0.95);
	~Dynamic_Hash_Table();

	void add(Ingredients* data);
	void delete_key(string key);
	bool seach(string key);

	void print();
	void print_all();

private:
	void clear();
	// Хэш функция (умножения)
	size_t hash_1(string key);
	// Хэш функция (деление по модулю)
	size_t hash_2(string key);

	void rehesh_less();
	void rehesh_more();

private:
	size_t size;
	size_t size_k;
	double_t less_dynamic_factor;
	double_t more_dynamic_factor;

	size_t min_size;
	size_t step;

	Dynamic_Hash_Table_Cell* Hash_Table;

};

Dynamic_Hash_Table::Dynamic_Hash_Table(size_t size, double_t less_dynamic_factor, double_t more_dynamic_factor)
{
	this->size = size;
	this->size_k = 0;
	this->less_dynamic_factor = less_dynamic_factor;
	this->more_dynamic_factor = more_dynamic_factor;

	min_size = size;
	step = size / ((2 / less_dynamic_factor) / more_dynamic_factor);
	if ((step % 2 == 0))
		step += 1;

	Hash_Table = new Dynamic_Hash_Table_Cell[size];
}

Dynamic_Hash_Table::~Dynamic_Hash_Table()
{
	clear();
	delete [] Hash_Table;
}

inline void Dynamic_Hash_Table::add(Ingredients* data)
{
	if (seach(data->name))
		return;

	size_t pos = hash_1(data->name);
	if (Hash_Table[pos].flag != 1)
	{
		Hash_Table[pos].data = data;
		Hash_Table[pos].flag = 1;
		size_k += 1;
	}
	else
	{
		pos = hash_2(data->name);
		while (Hash_Table[pos].flag == 1)
		{
			pos += step;
			if (pos >= size)
				pos -= size;
		}
		Hash_Table[pos].data = data;
		Hash_Table[pos].flag = 1;
		size_k += 1;
	}

	while (((double)size_k / (double)size) >= more_dynamic_factor || size_k == size)
		rehesh_more();
}

inline void Dynamic_Hash_Table::delete_key(string key)
{
	if (!seach(key))
		return;

	size_t pos = hash_1(key);
	if (Hash_Table[pos].data->name == key && Hash_Table[pos].flag == 1)
	{
		Hash_Table[pos].flag = 2;
		size_k -= 1;
	}
	else
	{
		pos = hash_2(key);
		while (Hash_Table[pos].flag == 1 && Hash_Table[pos].data->name != key || Hash_Table[pos].flag == 2)
		{
			pos += step;
			if (pos >= size)
				pos -= size;
		}
		if (Hash_Table[pos].data->name == key)
		{
			Hash_Table[pos].flag = 2;
			size_k -= 1;
		}
	}

	while (((double)size_k / (double)size) <= less_dynamic_factor && size_k != size - 1 && size > min_size)
		rehesh_less();
}

inline bool Dynamic_Hash_Table::seach(string key)
{
	size_t pos = hash_1(key);
	if (Hash_Table[pos].flag == 1 && Hash_Table[pos].data->name == key)
	{
		return true;
	}
	else
	{
		pos = hash_2(key);
		while (Hash_Table[pos].flag == 1 && Hash_Table[pos].data->name != key || Hash_Table[pos].flag == 2)
		{
			pos += step;
			if (pos >= size)
				pos -= size;
		}
		if (Hash_Table[pos].flag == 1 && Hash_Table[pos].data->name == key)
		{
			return true;
		}
	}
	return false;
}

inline void Dynamic_Hash_Table::print()
{
	for (size_t i = 0; i < size; i++)
		if (Hash_Table[i].flag == 1)
			cout << Hash_Table[i].data->name << " " << Hash_Table[i].data->units << " " << Hash_Table[i].data->calories << endl;
	cout << step << endl;
}

inline void Dynamic_Hash_Table::print_all()
{
	for (size_t i = 0; i < size; i++)
		if (Hash_Table[i].flag == 1)
			cout << Hash_Table[i].flag << "   " << Hash_Table[i].data->name << " " << Hash_Table[i].data->units << " " << Hash_Table[i].data->calories << endl;
		else
			cout << Hash_Table[i].flag << endl;
	cout << step << endl;
}

inline void Dynamic_Hash_Table::clear()
{
	for (size_t i = 0; i < size; i++)
		delete Hash_Table[i].data;
}

inline size_t Dynamic_Hash_Table::hash_1(string key)
{
	size_t temp = 0;
	for (size_t i = 0; i < key.size(); i++)
		temp += (int)key[i];
	double_t temp_d = size * temp * less_dynamic_factor * more_dynamic_factor;
	return (size_t)temp_d % size;
}

inline size_t Dynamic_Hash_Table::hash_2(string key)
{
	size_t temp = 0;
	for (size_t i = 0; i < key.size(); i++)
		temp += (int)key[i];
	return temp % size;
}

inline void Dynamic_Hash_Table::rehesh_less()
{
	size_t temp_size = size;
	size = size * more_dynamic_factor;
	if (temp_size <= size)
		size = temp_size - 1;
	if (size < min_size)
		size = min_size;
	size_k = 0;

	step = size / ((2 / less_dynamic_factor) / more_dynamic_factor);
	if ((step % 2 == 0))
		step += 1;

	Dynamic_Hash_Table_Cell* temp = Hash_Table;
	Hash_Table = new Dynamic_Hash_Table_Cell[size];

	for (size_t i = 0; i < temp_size; i++)
		if (temp[i].flag == 1)
			add(temp[i].data);

	delete[] temp;

}

inline void Dynamic_Hash_Table::rehesh_more()
{
	size_t temp_size = size;
	size = size / less_dynamic_factor;
	if (temp_size >= size)
		size = temp_size + 1;
	size_k = 0;

	step = size / ((2 / less_dynamic_factor) / more_dynamic_factor);
	if ((step % 2 == 0))
		step += 1;

	Dynamic_Hash_Table_Cell* temp = Hash_Table;
	Hash_Table = new Dynamic_Hash_Table_Cell[size];

	for (size_t i = 0; i < temp_size; i++)
		if (temp[i].flag == 1)
			add(temp[i].data);

	delete [] temp;

}
