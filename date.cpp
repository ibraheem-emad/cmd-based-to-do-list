#include "date.h"
#include <iostream>

void date::display() const
{
	std::cout << year << '/' << month << '/' << day;
}

void to_json(nlohmann::json& j, const date& d)
{
    j = nlohmann::json{
        {"year", d.year},
        {"month", d.month},
        {"day", d.day}
    };
}

void from_json(const nlohmann::json& j, date& d)
{
    j.at("year").get_to(d.year);
    j.at("month").get_to(d.month);
    j.at("day").get_to(d.day);
}