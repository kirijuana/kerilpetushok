#include "stdafx.h"
#include "lib.h"


map<char, int> symbols_freq_func(string str)
{
	map<char, int> symbols_freq;
	for (int i = 0; i < str.length(); i++)
	{
		symbols_freq[str[i]]++;
	}
	return symbols_freq;
}

map<char, cpp_dec_float_100> symbols_probab;
map<char, int>::iterator itr;
void find_symbols_probability(string str)
{
	
	auto symbols_freq = symbols_freq_func(str);
	for (itr = symbols_freq.begin(); itr != symbols_freq.end(); itr++)
	{
		symbols_probab[itr->first] = (cpp_dec_float_100)itr->second / (cpp_dec_float_100)str.length();
	}
}

map<char, cpp_dec_float_100> HighRange;
map<char, cpp_dec_float_100> LowRange;

void interval_search(map<char, int> const& symbols_freq)
{
	cpp_dec_float_100 x = 0;
	for (auto itr = symbols_freq.begin(); itr != symbols_freq.end(); itr++)
	{

		LowRange[itr->first] = x;
		x = x + symbols_probab[itr->first];

		HighRange[itr->first] = x;
	//	cout << fixed << setprecision(100) << "'" << itr->first << "\n"  << LowRange[itr->first] << "\n " << HighRange[itr->first] << " \n" << endl;
	}
}

cpp_dec_float_100 *OldLow;
cpp_dec_float_100 *OldHigh;
cpp_dec_float_100 *NewLow;
cpp_dec_float_100 *NewHigh;
cpp_dec_float_100 *code;

cpp_dec_float_100 string_encode(string str)
{
	OldLow = new cpp_dec_float_100[str.length()];
	OldHigh = new cpp_dec_float_100[str.length()];
	NewLow = new cpp_dec_float_100[str.length()];
	NewHigh = new cpp_dec_float_100[str.length()];
	code = new cpp_dec_float_100[str.length()];

	OldLow[0] = LowRange[str[0]];
	OldHigh[0] = HighRange[str[0]];
	NewHigh[0] = HighRange[str[0]];
	NewLow[0] = LowRange[str[0]];
	cout << fixed << setprecision(100) << "'" << str[0] << "\n" << NewLow[0] << " \n " << NewHigh[0] << " \n" << endl;
	for (int i = 0; i < str.length(); i++)
	{
		if (i + 1 == str.length())
			break;
		NewHigh[i + 1] = OldLow[i] + (OldHigh[i] - OldLow[i])*HighRange[str[i + 1]];
		NewLow[i + 1] = OldLow[i] + (OldHigh[i] - OldLow[i])*LowRange[str[i + 1]];
		OldLow[i + 1] = NewLow[i + 1];
		OldHigh[i + 1] = NewHigh[i + 1];

		cout << fixed << setprecision(100) << "'" << str[i + 1] << "\n" << NewLow[i + 1] << "\n" << NewHigh[i + 1] << " \n" << endl;
	}
	cpp_dec_float_100 mid_field = (((NewHigh[str.length() - 1] - NewLow[str.length() - 1]) / 2) + NewLow[str.length() - 1]);
	cout << "Код строки: " << mid_field << endl;
	return mid_field; // return last code
}

map<char, cpp_dec_float_100>::iterator itrfl;
char search_symbol_on_intreval(cpp_dec_float_100 code)
{
	char buffer = ' ';
	for (itrfl = LowRange.begin(); itrfl != LowRange.end(); itrfl++) // ищем символ, по найденному значению
	{
		if (code >= itrfl->second)
		{
			if (code < HighRange[itrfl->first])
			{
				buffer = itrfl->first;
				break;
			}
		}
	}
	return buffer;
}

string decode_function(cpp_dec_float_100 last_code, int length_str)
{
//	map<char, cpp_dec_float_100>::iterator itrfl;

	string decode_str(length_str, ' ');

	char buffer = search_symbol_on_intreval(last_code);
	code[0] = last_code;
	cpp_dec_float_100 check = 0;

	for (int i = 0;; i++)
	{
		decode_str[i] = buffer;
		code[i + 1] = ((code[i] - LowRange[buffer]) / (HighRange[buffer] - LowRange[buffer]));
		buffer = search_symbol_on_intreval(code[i + 1]);

		decode_str[i + 1] = buffer;
		check = code[i + 1] - ((((HighRange[buffer] - LowRange[buffer]) / 2) + LowRange[buffer]));
		if (check == 0)
			break;
	}
	return decode_str;
}
void clear_memory()
{
	delete[] NewLow;
	delete[] NewHigh;
	delete[] OldLow;
	delete[] OldHigh;
	delete[] code;
}