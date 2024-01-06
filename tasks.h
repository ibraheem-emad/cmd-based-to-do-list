#pragma once
#include <string>
#include "date.h"
#include <nlohmann\json.hpp>

class tasks
{
	

	

private:
	
	std::string name{"no name"};
	std::string description{"no description"};
	date implementation_date{};
	bool completion_state{ false };

	

public:
	
	tasks()
	{}

	tasks(std::string name_, std::string description_, date implementation_date_) :
		name(name_),
		description(description_),
		implementation_date(implementation_date_)
	{



	}


	tasks(const tasks& other) :
		name(other.name),
		description(other.description),
		implementation_date(other.implementation_date),
		completion_state(other.completion_state)
	{}



	bool operator> (tasks& other)
	{

		if (this->implementation_date.year == other.implementation_date.year)
		{

			if (this->implementation_date.month == other.implementation_date.month)
			{

				if (this->implementation_date.day == other.implementation_date.day)
				{

					return true;

				}
				else if (this->implementation_date.day > other.implementation_date.day)
				{

					return true;

				}
				else { return false; }
			}
			else if (this->implementation_date.month > other.implementation_date.month)
			{

				return true;

			}
			else { return false; }

		}
		else if (this->implementation_date.year > other.implementation_date.year)
		{

			return true;

		}
		else { return false; }
	}

	void display_name() const;
	void display_description() const;
	void display_implementation_date() const;
	void display_completion_state() const;
	bool is_complete();
    std::string get_name();
	std::string get_description();
	void change_completion_state();

	friend void to_json(nlohmann::json& j, const tasks& t);
	friend void from_json(const nlohmann::json& j, tasks& t);
	
};