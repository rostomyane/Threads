#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

struct HTMLElement
{
	std::string name;
	std::string text;
	std::vector<HTMLElement> elements;
	const size_t indentSize = 2;

	HTMLElement(){}
	HTMLElement(const std::string& n, const std::string& t)
		:name{n}, text{t}
	{}

	std::string str(int indent = 0)const
	{
		std::ostringstream oss;
		std::string i(indentSize * indent, ' ');
		oss << i << "<" << name << ">" << std::endl;
		if (!text.empty()) {
			oss << std::string(indentSize * (indent + 1), ' ') << text << std::endl;
		}

		for (const auto& e : elements) {
			oss << e.str(indent + 1);
		}
		oss << i << "</" << name << ">" << std::endl;
		return oss.str();
	}
};

struct HTMLBuilder 
{
	HTMLElement root;
	HTMLBuilder(const std::string& name)
	{
		root.name = name;
	}

	std::string str() const
	{
		return root.str();
	}

	void addChild(std::string name, std::string text) 
	{
		HTMLElement elem(name, text);
		root.elements.push_back(elem);
	}
};
