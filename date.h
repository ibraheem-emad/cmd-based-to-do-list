#pragma once
#include <nlohmann/json.hpp>

class date
{
	friend class tasks;
	


private:
	int year{};
	int month{};
	int day{};

public:
	void display() const;
	
	date()
	{}

	date(int year_, int month_, int day_) :
		year(year_),
		month(month_),
		day(day_)
	{



	}

	date(const date& copy) :
		year(copy.year),
		month(copy.month),
		day(copy.day)
	{



	}

	friend void to_json(nlohmann::json& j, const date& d);
	friend void from_json(const nlohmann::json& j, date& d);

};