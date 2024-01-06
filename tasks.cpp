#include "tasks.h"
#include <iostream>
#include <nlohmann\json.hpp>

void tasks::display_name() const
{
	std::cout << name;
}

void tasks::display_description() const
{
	std::cout << '\n' << description << "\n\n";
}

void tasks::display_implementation_date() const
{ 
	std::cout << implementation_date.day << '/' << implementation_date.month << '/' << implementation_date.year;
}

void tasks::display_completion_state() const
{

	if (completion_state == true) { std::cout << "completed"; }
	else { std::cout << "not completed"; }

}
std::string tasks::get_name()
{

	return name;

}

std::string tasks::get_description()
{

	return description;

}

bool tasks::is_complete() 
{

	return completion_state;

}

void tasks::change_completion_state()
{

	if (completion_state == true) 
	{ 

		system("cls");
		completion_state = false;
	   
		std::cout << "task's state been changed from (completed) to (not completed)\n\n";
		system("pause");

	}
	else 
	{ 

		system("cls");
		completion_state = true; 

		std::cout << "task's state been changed from (not completed) to (completed)\n\n";
		system("pause");

	}

}

void to_json(nlohmann::json& j, const tasks& t)
{
	j = nlohmann::json{
		{"name", t.name},
		{"description", t.description},
		{"implementation_date", t.implementation_date},
		{"completion_state", t.completion_state}
	};
}

void from_json(const nlohmann::json& j, tasks& t)
{
	j.at("name").get_to(t.name);
	j.at("description").get_to(t.description);
	j.at("implementation_date").get_to(t.implementation_date);
	j.at("completion_state").get_to(t.completion_state);
}
