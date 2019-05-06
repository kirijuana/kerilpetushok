#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cpp_dec_float.hpp>
using namespace std;
using boost::multiprecision::cpp_dec_float_100;

map<char, int> symbols_freq_func(string str);
void find_symbols_probability(string str);
void interval_search(map<char, int> const& symbols_freq);
cpp_dec_float_100 string_encode(string str);
char search_symbol_on_intreval(cpp_dec_float_100 code);
string decode_function(cpp_dec_float_100 last_code, int length_str);
void clear_memory();
