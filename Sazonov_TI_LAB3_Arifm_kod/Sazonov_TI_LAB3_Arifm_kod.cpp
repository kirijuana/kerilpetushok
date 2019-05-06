#include "stdafx.h"
#include "lib.h"

int main()
{	
	ofstream fout("E://уч/3 курс/2й семестр/Теория информации/lab 3/out.txt");
	ifstream fin("E://уч/3 курс/2й семестр/Теория информации/lab 3/in.txt");
	string str;
	getline(fin, str);

	find_symbols_probability(str);
	
	interval_search(symbols_freq_func(str));

	string str_decode = decode_function(string_encode(str), str.length());
	for (int i = 0; i < str_decode.length(); i++)
	{
		cout << fixed << setprecision(100) << " Декод:  " << str_decode[i] << " \n" << endl;
	}
	
	clear_memory();
	system("pause");
	return 0;
}

