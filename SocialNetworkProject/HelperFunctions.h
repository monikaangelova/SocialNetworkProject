#pragma once
#include "String.h"
#include <iostream>
#include <fstream>
void readString(std::istream& in, String& str);
String intToString(unsigned a);
bool searchInText(const char* text, const char* pattern);