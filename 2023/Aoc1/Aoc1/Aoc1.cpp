#include <iostream>
#include <cctype>
#include <memory>
#include <utility>
#include <string>

std::pair<char, char> GetCalibrationValue(const std::string& input)
{
	std::unique_ptr<char> first_digit = nullptr;
	std::unique_ptr<char> last_digit = nullptr;

	for (const char& ch : input)
	{
		if (!std::isdigit(ch)) continue;

		if (first_digit == nullptr)
		{
			first_digit = std::make_unique<char>(ch);
		}
		else
		{
			last_digit = std::make_unique<char>(ch);
		}
	}

	// Check if there is only one digit provided in input.
	if (last_digit == nullptr && first_digit != nullptr)
	{
		last_digit = std::make_unique<char>(*first_digit);
	}

	if (first_digit && last_digit)
	{
		return { *first_digit, *last_digit };
	}
	return { -1, -1 }; // Invalid input, no digits provided
}

int main()
{
	std::string input;
	while (std::getline(std::cin, input))
	{
		std::pair<char, char> result = GetCalibrationValue(input);
		if (result == std::pair<char, char>(-1, -1))
		{
			std::cout << "Invalid input provided, terminating..." << std::endl;
			return 0;
		}

		std::string result_string = std::string{ result.first, result.second };
		std::cout << "Result was: " << result_string << "\n";
	}
}
