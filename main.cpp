#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "nlohmann/json.hpp"
#include "tasks.h"

using json = nlohmann::json;

void save_tasks_to_json(const std::vector<tasks>& tasks_list)
{
    std::ofstream output("data.json");
    if (output.is_open())
    {
        nlohmann::json j(tasks_list);
        output << std::setw(4) << j << std::endl;
        output.close();

    }
    else {
        std::cerr << "Error opening 'data.json' for writing" << std::endl;
    }
}

void load_tasks_from_json(std::vector<tasks>& tasks_list)
{
    std::ifstream input("data.json");
    if (input.is_open())
    {
        nlohmann::json loaded_json;
        input >> loaded_json;
        input.close();

        tasks_list.clear(); // Clear the existing vector
        for (const auto& element : loaded_json)
        {
            tasks task;
            element.get_to(task);
            tasks_list.push_back(task);
        }

    }
    else {
        // If the file doesn't exist, create a new one
        save_tasks_to_json(tasks_list);
    }
}

int get_longest_name_lenght(std::vector<tasks> list)
{
    int lenght{0};

    for (int c{ 0 }; c < list.size(); c++)
    {

        if (list[c].get_name().length() > lenght) { lenght = list[c].get_name().length(); }
    }

    return lenght;
}

bool check_empty_list(std::vector<tasks>& list)
{

    if (list.size() == 0) { return true; }
    else { return false; }

}

void draw_list(std::vector<tasks> list)
{
    system("cls");


    if (check_empty_list(list))
    {

        std::cout << "you have no tasks to do.\n\n";
        system("pause");

    }
    else
    {    

        int longest_name_lenght{ get_longest_name_lenght(list) };

        std::cout << "|   Num   " << '|' << "    Status           " << '|' << "    " << "Name";
        if (longest_name_lenght > 4)
        {
            for (int c{ 0 }; c < longest_name_lenght - 4; c++)
            {

                std::cout << ' ';

            }

            std::cout << "     |";
        }
        else
        {

            std::cout << "    |";

        }

        std::cout << "    Date    \n\n";
        

        for (int c{ 0 }; c < list.size(); c++)
        {

            if (c + 1 < 10) { std::cout << "|    " << c + 1 << "    " << '|'; }
            else if( c + 1 >= 10 && c + 1 < 100) { std::cout << "|    " << c + 1 << "   " << '|'; }
            else { std::cout << "|    " << c + 1 << "  " << '|'; }

            if (list[c].is_complete()) { std::cout << "    " << "completed" << "    " << "    " << '|'; }
            else { std::cout << "    " << "not completed" << "    " << '|'; }

            std::cout << "    " << list[c].get_name();


            if (longest_name_lenght > 4)
            {
                for (int i{ 0 }; i < longest_name_lenght - list[c].get_name().length(); i++)
                {
                    std::cout << ' ';
                }
                
            }
            else
            {

                for (int i{ 0 }; i < longest_name_lenght - list[c].get_name().length(); i++)
                {

                    std::cout << ' ';
                }

            }

            std::cout << "     " << '|' << "    ";
            list[c].display_implementation_date();
            std::cout << '\n';

        }


    }
}

void show_description(std::vector<tasks> list, int choice)
{

    system("cls");

    list[choice - 1].display_description();

    system("pause");

}

void view_tasks(std::vector<tasks>& tasks_list)
{
    int choice1{ 0 }, choice2{ 0 };
    do
    {
        draw_list(tasks_list);
        if (check_empty_list(tasks_list))
        {

            break;

        }

        if (!check_empty_list(tasks_list))
        {

            std::cout << "\nwhat do you want to do? \n1- read the description of one of the tasks \n2- change a task state to completed or to not completed \n3- go back to main menu \nchoose by number: ";
            while (!(std::cin >> choice1))
            {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                draw_list(tasks_list);
                std::cout << "\nInvalid input. Please enter an integer\n\n1- read the description of one of the tasks \n2- mark a task as completed \n3- go back to main menu \nchoose by number: ";
            }

            switch (choice1)
            {
            case 1:
                do
                {
                    std::cout << "\nenter the number of the task that you want to see its description: ";

                    while (!(std::cin >> choice2))
                    {

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        draw_list(tasks_list);
                        std::cout << "Invalid input. enter the number of the task that you want to see its description: ";
                    }

                    if (choice2 <= 0 || choice2 > tasks_list.size())
                    {
                        system("cls");
                        draw_list(tasks_list);
                        std::cout << "\nthere is no task with this number, please try again\n";

                    }



                } while (choice2 <= 0 || choice2 > tasks_list.size());

                show_description(tasks_list, choice2);
                break;

            case 2:
                system("cls");
                do
                {
                    draw_list(tasks_list);
                    std::cout << "\nenter the number of the task that you want to change its completion state: ";

                    while (!(std::cin >> choice2))
                    {

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        draw_list(tasks_list);
                        std::cout << "Invalid input. enter the number of the task that you want to see its description: ";
                    }

                    if (choice2 <= 0 || choice2 > tasks_list.size())
                    {
                        system("cls");
                        draw_list(tasks_list);
                        std::cout << "\nthere is no task with this number, please try again\n";

                    }



                } while (choice2 <= 0 || choice2 > tasks_list.size());
                
                tasks_list[choice2 - 1].change_completion_state();

                save_tasks_to_json(tasks_list);

                break;

            }
        }


    } while (choice1 != 3);

    choice2 = 0;
    std::cout << '\n';
        
}

void add_task(std::vector<tasks>& list)
{



    system("cls");

    std::string temp_name{ };
    std::cout << "enter the name of the task: ";
    std::getline(std::cin >> std::ws, temp_name);


    system("cls");
    std::string temp_description{ "no_description" };
    int decision{ 0 };

    do {


        std::cout << "do you want to add a description to your task? \n1- Yes \n2- No \n(choose by number): ";
        while (!(std::cin >> decision)) {

            system("cls");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter something from the choices list \ndo you want to add a description to your task? \n1- Yes \n2- No \n(choose by number):";
        }

        if (decision == 1 || decision == 2)
        {
            std::cin.ignore();

            if (decision == 1)
            {
                system("cls");
                std::cout << "write down the task description:\n";
                std::getline(std::cin >> std::ws, temp_description);

            }

        }
        else
        {

            system("cls");
            std::cout << "invalid input, please try again\n";
            decision = 0;

        }
    } while (!decision);


    int temp_year{};
    int temp_month{};
    int temp_day{};

    system("cls");
    std::cout << "now add the date that you aim to achieve your task in \nfirst the year: ";
    while (!(std::cin >> temp_year)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter an integer: ";
    }

    system("cls");
    std::cout << "now the month: ";
    while (!(std::cin >> temp_month)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter an integer: ";
    }

    system("cls");
    std::cout << "finally the day: ";
    while (!(std::cin >> temp_day)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter an integer: ";
    }

    date temp_date(temp_year, temp_month, temp_day);

    tasks temp_task(temp_name, temp_description, temp_date);

    list.push_back(temp_task);
    save_tasks_to_json(list);

    system("cls");
    std::cout << "the task has been added successfully\n";
    system("pause");
}
    



    void remove_task(std::vector<tasks>& list)
    {
        
        int choice{ 0 }, index{ -1 };


        draw_list(list);

        do
        {
            std::cout << "\nwhat do you want to do?\n \n1- delete a specific task \n2- delete all completed tasks \n3- return to main menu \n\nenter the number of your choice: ";
            while (!(std::cin >> choice))
            {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Invalid input. Please enter an integer: ";
            }

            if (choice < 1 || choice > 3)
            {

               system("cls");
               std::cout << "there is no option with that number, please try again \n\n";

            }

        } while (choice < 1 || choice > 3);


        switch (choice)
        {


        case 1:

            system("cls");

            do
            {

                draw_list(list);

                std::cout << "\nenter the number of the task that you want to delete: ";

                while (!(std::cin >> index))
                {

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Invalid input. Please enter an integer: ";
                }

                if (index < 1 || index > list.size())
                {

                    system("cls");
                    std::cout << "there is no task with this number, please try again \n\n";

                }

            } while (index < 1 || index > list.size());

            list.erase(list.begin() + index - 1);
            save_tasks_to_json(list);
            break;

        case 2:

            for (int c{ 0 }; c < list.size(); c++)
            {

                if (list[c].is_complete())
                {

                    list.erase(list.begin() + c);

                }

            }

            save_tasks_to_json(list);

            break;

        }
    }
    
    
           
int main()
{

    
    std::vector<tasks> tasks_list{ };
    
    load_tasks_from_json(tasks_list);

    int choice{ 0 };

        do{
            system("cls");
            std::cout << "1- see my tasks \n2- add a new task \n3- delete a task \n4- exit the program \nenter the number of the operation that you want to do: ";
            while (!(std::cin >> choice)) {

                system("cls");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Invalid input. Please enter an integer \n1- see my tasks \n2- add a new task \n3- delete a task \n4- exit the program \nenter the number of the operation that you want to do: ";
            }

            switch (choice)
            {

            case 1: //showing tasks list

                
                view_tasks(tasks_list);
                choice = 0;
                break;
                
            case 2: // add new tasks

                add_task(tasks_list);

                break;

            case 3: // remove a task

                if(check_empty_list(tasks_list) == true) 
                {

                    system("cls");
                    std::cout << "there is no tasks to delete!";
                    break;

                }
                remove_task(tasks_list);
                break;

            
            }

        } while (choice != 4);

        save_tasks_to_json(tasks_list);

        return 0;

                    
}
