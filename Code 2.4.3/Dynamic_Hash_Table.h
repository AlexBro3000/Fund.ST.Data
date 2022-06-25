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
inline bool operator==(const Ingredients& lhs, const Ingredients& rhs)
{
	if (lhs.name == rhs.name && lhs.units == rhs.units && lhs.calories == rhs.calories)
		return true;
	return false;
}
inline bool operator!=(const Ingredients& lhs, const Ingredients& rhs)
{
	return lhs.name != rhs.name;
}

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
	void delete_key(Ingredients* data);
	bool seach(Ingredients* data);

	void print();
	void print_all();

private:
	void clear();
	size_t GCD(size_t var_1, size_t var_2);

	// Хэш функция (деление по модулю)
	size_t hash_1(string key);
	// Хэш функция (+ step)
	size_t hash_2(size_t key);

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
	step = 2;
	while (GCD(step, size) != 1)
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
	size_t hash = hash_1(data->name);
	if (Hash_Table[hash].flag != 1)
		Hash_Table[hash].data = data;
	else
	{
		while (Hash_Table[hash].flag == 1)
		{
			if (Hash_Table[hash].data->name == data->name)
				return;

			hash = hash_2(hash);
		}

		Hash_Table[hash].data = data;;
	}

	size_t hash_t = hash_2(hash);
	while (hash != hash_t && Hash_Table[hash_t].flag != 0)
		if (Hash_Table[hash_t].flag == 1 && Hash_Table[hash_t].data->name == data->name)
			return;
		else
			hash_t = hash_2(hash_t);
	Hash_Table[hash].flag = 1;
	size_k += 1;

	while (((double)size_k / (double)size) >= more_dynamic_factor || size_k == size)
		rehesh_more();
}

inline void Dynamic_Hash_Table::delete_key(Ingredients* data)
{
	size_t hash = hash_1(data->name);
	if (Hash_Table[hash].flag == 1 && *Hash_Table[hash].data == *data)
	{
		Hash_Table[hash].flag = 2;
		size_k -= 1;
	}
	else
	{
		while (Hash_Table[hash].flag == 1 && *Hash_Table[hash].data != *data || Hash_Table[hash].flag == 2)
			hash = hash_2(hash);

		if (Hash_Table[hash].flag == 1 && *Hash_Table[hash].data == *data)
		{
			Hash_Table[hash].flag = 2;
			size_k -= 1;
		}
	}

	while (((double)size_k / (double)size) <= less_dynamic_factor && size_k != size - 1 && size > min_size)
		rehesh_less();
}

inline bool Dynamic_Hash_Table::seach(Ingredients* data)
{
	size_t hash = hash_1(data->name);
	if (Hash_Table[hash].flag == 1 && *Hash_Table[hash].data == *data)
	{
		return true;
	}
	else
	{
		while (Hash_Table[hash].flag == 1 && *Hash_Table[hash].data != *data || Hash_Table[hash].flag == 2)
			hash = hash_2(hash);

		if (Hash_Table[hash].flag == 1 && *Hash_Table[hash].data == *data)
			return true;
	}
	return false;
}

inline void Dynamic_Hash_Table::print()
{
	for (size_t i = 0; i < size; i++)
		if (Hash_Table[i].flag == 1)
			cout << Hash_Table[i].data->name << " " << Hash_Table[i].data->units << " " << Hash_Table[i].data->calories << endl;
}

inline void Dynamic_Hash_Table::print_all()
{
	for (size_t i = 0; i < size; i++)
		if (Hash_Table[i].flag != 0)
			cout << i << "        " << Hash_Table[i].data->name << " " << Hash_Table[i].data->units << " " << Hash_Table[i].data->calories << "        " << Hash_Table[i].flag << endl;
		else
			cout << i << "        - - -       " << Hash_Table[i].flag << endl;
	cout << "Step = " << step << endl;
}

inline void Dynamic_Hash_Table::clear()
{
	for (size_t i = 0; i < size; i++)
		delete Hash_Table[i].data;
}

inline size_t Dynamic_Hash_Table::GCD(size_t var_1, size_t var_2)
{
	while (var_1 % var_2 != 0)
	{
		size_t temp = var_1 % var_2;
		var_1 = var_2;
		var_2 = temp;
	}
	return var_2;
}

inline size_t Dynamic_Hash_Table::hash_1(string key)
{
	int temp = 0;
	for (size_t i = 0; i < key.size(); i++)
		temp += (int)key[i];
	return temp % size;
}

inline size_t Dynamic_Hash_Table::hash_2(size_t key)
{
	return (key + step) % size;
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

	step = 2;
	while (GCD(step, size) != 1)
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

	step = 2;
	while (GCD(step, size) != 1)
		step += 1;

	Dynamic_Hash_Table_Cell* temp = Hash_Table;
	Hash_Table = new Dynamic_Hash_Table_Cell[size];

	for (size_t i = 0; i < temp_size; i++)
		if (temp[i].flag == 1)
			add(temp[i].data);

	delete [] temp;
}
