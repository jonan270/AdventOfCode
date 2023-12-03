// AoC3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cctype>

struct Schematic
{
	enum class SlotType
	{
		E_NONE,
		E_PART_SYMBOL,
		E_PART_NUMBER
	};

	struct PartNumber
	{
		PartNumber(std::string value_string) : m_ValueString(value_string) {};
		bool m_Checked = false;
		std::string m_ValueString;
	};

	struct GridSlot
	{
		SlotType m_Type = SlotType::E_NONE;
		std::shared_ptr<PartNumber> m_PartNumberPtr = nullptr;
	};


	unsigned int SumActiveParts()
	{
		size_t num_rows = m_Grid.size();
		size_t num_columns = num_rows < 1 ? -1 : m_Grid[0].size();
		unsigned int sum = 0;

		for (int c = 0; c < num_columns; c++)
		{
			for (int r = 0; r < num_rows; r++)
			{
				if (SlotHasAdjacentPart(r, c))
				{
					std::shared_ptr<PartNumber> part_number_ptr = m_Grid[r][c].m_PartNumberPtr;
					const std::string& slot_value_string = part_number_ptr ? part_number_ptr->m_ValueString : "";

					if (!slot_value_string.empty() && !part_number_ptr->m_Checked)
					{
						sum += std::stoi(slot_value_string);
						part_number_ptr->m_Checked = true;
						//std::cout << "Slot [" << r << "][" << c << "]" << ": "
						//	<< std::stoi(slot_value_string) << "\n"
						//	<< "Sum: " << sum << std::endl;
					}
				}
			}
		}
		return sum;
	}

	bool SlotHasAdjacentPart(size_t parse_row, size_t parse_column)
	{
		size_t start_row = static_cast<int>(parse_row) - 1 >= 0 ? parse_row - 1 : 0;
		size_t start_column = static_cast<int>(parse_column) - 1 >= 0 ? parse_column - 1 : 0;

		for (size_t r = start_row; r <= parse_row + 1 && r < m_Grid.size(); r++)
		{
			for (size_t c = start_column; c <= parse_column + 1 && c < m_Grid[0].size(); c++)
			{
				if (m_Grid[r][c].m_Type == SlotType::E_PART_SYMBOL)
				{
					return true;
				}
			}
		}
		return false;
	}

	void AppendRow(const std::string& input)
	{
		const size_t input_size = input.size();
		std::vector<GridSlot> row = std::vector<GridSlot>(input_size);

		bool part_number_started = false;
		std::shared_ptr<PartNumber> parsed_part_number = nullptr;

		for (size_t i = 0; i < input_size; i++)
		{
			char c = input[i];
			if (std::isdigit(c))
			{
				if (!part_number_started)
				{
					parsed_part_number =
						std::make_shared<PartNumber>(std::string(1, c));

					part_number_started = true;
				}
				else if (parsed_part_number)
				{
					parsed_part_number->m_ValueString += c;
				}
				row[i].m_PartNumberPtr = parsed_part_number;
				row[i].m_Type = SlotType::E_PART_NUMBER;
			}
			else
			{
				if (parsed_part_number)
				{
					parsed_part_number = nullptr;
					part_number_started = false;
				}
				row[i].m_Type = c == '.' ? SlotType::E_NONE : SlotType::E_PART_SYMBOL;
			}
		}

		m_Grid.push_back(row);
	}
	std::vector<std::vector<GridSlot>> m_Grid;
};

int main()
{
	Schematic schematic{};

	std::string input;
	while (std::getline(std::cin, input) && input != "STOP")
	{
		schematic.AppendRow(input);
	}

	// Part 1:
	std::cout << "Sum: " << schematic.SumActiveParts() << std::endl;
}
