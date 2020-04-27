#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

struct HTMLElement
{
	std::string name;
	std::string test;
	std::vector<HTMLElement> elements;
	const size_t indentSize = 2;

	HTMLElement(){}
	HTMLElement(const std::string& s) {}
};

struct HTMLBuilder 
{
	HTMLBuilder	
};
