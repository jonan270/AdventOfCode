// AoC1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <set>
#include <iterator>

/*
	The jungle must be too overgrown and difficult to navigate in vehicles or access from the air; the Elves' expedition traditionally goes on foot. As your boats approach land, the Elves begin taking inventory of their supplies. One important consideration is food - in particular, the number of Calories each Elf is carrying (your puzzle input).

	The Elves take turns writing down the number of Calories contained by the various meals, snacks, rations, etc. that they've brought with them, one item per line. Each Elf separates their own inventory from the previous Elf's inventory (if any) by a blank line.

	For example, suppose the Elves finish writing their items' Calories and end up with the following list:

	1000
	2000
	3000

	4000

	5000
	6000

	7000
	8000
	9000

	10000
	This list represents the Calories of the food carried by five Elves:

	The first Elf is carrying food with 1000, 2000, and 3000 Calories, a total of 6000 Calories.
	The second Elf is carrying one food item with 4000 Calories.
	The third Elf is carrying food with 5000 and 6000 Calories, a total of 11000 Calories.
	The fourth Elf is carrying food with 7000, 8000, and 9000 Calories, a total of 24000 Calories.
	The fifth Elf is carrying one food item with 10000 Calories.
	In case the Elves get hungry and need extra snacks, they need to know which Elf to ask: they'd like to know how many Calories are being carried by the Elf carrying the most Calories. In the example above, this is 24000 (carried by the fourth Elf).

	Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?
*/

// Purely for readability/extendability :)
struct Elf
{
	unsigned int m_CarriedCalories = 0;
};


// Part 1
unsigned int GetMostLoadedElfCalories()
{
	Elf currently_parsed_elf;
	Elf most_loaded_elf;

	std::cout << "Input Part 1: \n";
	std::string item_calories_string;
	while (std::getline(std::cin, item_calories_string))
	{
		// If a new line is encountered, we begin parsing next elf.
		if (item_calories_string.empty())
		{
			currently_parsed_elf = Elf();
		}
		else
		{
			try
			{
				currently_parsed_elf.m_CarriedCalories += std::stoi(item_calories_string);
				if (currently_parsed_elf.m_CarriedCalories > most_loaded_elf.m_CarriedCalories)
				{
					most_loaded_elf = currently_parsed_elf;
				}
			}
			catch (std::exception& e)
			{
				std::cout << "Could not parse as int, ignoring input " << item_calories_string << std::endl;
			}
		}
	}
	return most_loaded_elf.m_CarriedCalories;
}

// Part 2
unsigned int GetTopThreeElfCaloriesSum()
{
	// Obviously encapsulating what is really just an unsigned int inside its own struct makes this overly
	// complicated for what is is however in real life applications structs typically are more complex than this.
	auto comparator = [](const Elf e1, const Elf e2) { return e1.m_CarriedCalories > e2.m_CarriedCalories; };
	std::multiset<Elf, decltype(comparator)> elves(comparator);

	Elf currently_parsed_elf;
	std::string item_calories_string;
	std::cout << "Input Part 2: \n";
	while (std::getline(std::cin, item_calories_string))
	{
		// If a new line is encountered, we begin parsing next elf.
		if (item_calories_string.empty())
		{
			// Insert previous elf
			elves.insert(currently_parsed_elf);

			// Make new Elf
			currently_parsed_elf = Elf();
		}
		else
		{
			try
			{
				currently_parsed_elf.m_CarriedCalories += std::stoi(item_calories_string);
			}
			catch (std::exception& e)
			{
				std::cout << "Could not parse as int, ignoring input " << item_calories_string << std::endl;
			}
		}
	}
	elves.insert(currently_parsed_elf); // Final elf needs to be inserted as well.

	// Sum values of 3 (if possible) most loaded elves.
	unsigned int sum = 0;
	constexpr static int n_to_sum = 3;
	std::multiset<Elf>::iterator begin = elves.begin();
	std::multiset<Elf>::iterator end = elves.end();
	std::multiset<Elf>::iterator stop = end;
	if (elves.size() >= n_to_sum)
	{
		std::multiset<Elf>::iterator goal = begin;
		std::advance(goal, n_to_sum);
		stop = goal;
	}

	for (std::multiset<Elf>::iterator i = begin; i != stop; i++)
	{
		sum += i->m_CarriedCalories;
	}

	return sum;
}

int main()
{
	//std::cout << "The elf who carries the most calories carries " << GetMostLoadedElfCalories() << " calories." << std::endl;
	std::cout << "The top three most loaded elves carry in total " << GetTopThreeElfCaloriesSum() << " calories." << std::endl;
}
