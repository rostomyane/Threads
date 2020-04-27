#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace html {
	struct HTMLElement
	{
		std::string name;
		std::string text;
		std::vector<HTMLElement> elements;
		const size_t indentSize = 2;

		HTMLElement() {}
		HTMLElement(const std::string& n, const std::string& t)
			:name{ n }, text{ t }
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
}




namespace BuilderFacets {
	class PersonBuilder;
	class Person;
	class PersonJobBuilder;

	class Person
	{
		// address
		std::string streetAddress;
		std::string postCode;
		std::string city;

		//employment
		std::string companyName;
		std::string companyPositioin;
		int income;
	public:
		Person() {}

	public:
		static PersonBuilder create();
		friend class PersonAddressBuilder;
		friend class PersonBuilder;
		friend class PersonJobBuilder;
	};

	class PersonBuilder
	{
		Person p;
	protected:
		Person& person;
		explicit PersonBuilder(Person& per)
			:person{ per }
		{
		}
	public:
		PersonBuilder() :person{ p } {}
		PersonAddressBuilder lives();
		PersonJobBuilder works();
		operator Person();
	};

	class PersonAddressBuilder : public PersonBuilder
	{
	public:
		explicit PersonAddressBuilder(Person& person)
			:PersonBuilder(person)
		{
		}
		PersonAddressBuilder& at(const std::string& address)
		{
			person.streetAddress = address;
			return *this;
		}
		PersonAddressBuilder& withPostCode(const std::string& postCode)
		{
			person.postCode = postCode;
			return *this;
		}
		PersonAddressBuilder& in(const std::string& city)
		{
			person.city = city;
			return *this;
		}
	};

	class PersonJobBuilder : public PersonBuilder
	{
	public:
		explicit PersonJobBuilder(Person& person)
			:PersonBuilder(person)
		{
		}

		PersonJobBuilder& at(const std::string& comp)
		{
			person.companyName = comp;
			return *this;
		}

		PersonJobBuilder& asA(const std::string& pos)
		{
			person.companyPositioin = pos;
			return *this;
		}
	};

	PersonBuilder Person::create()
	{
		return PersonBuilder();
	}

	PersonAddressBuilder PersonBuilder::lives()
	{
		return PersonAddressBuilder{ person };
	}
	PersonJobBuilder PersonBuilder::works()
	{
		return PersonJobBuilder{ person };
	}

	PersonBuilder::operator Person()
	{
		return std::move(person);
	}

	void sample()
	{
		Person p = Person::create().lives().at("somewhere").withPostCode("e149ja").in("London").works().at("GS").asA("VP");
	}
}
