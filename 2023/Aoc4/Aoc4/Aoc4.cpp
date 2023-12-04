#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>

template<size_t N_WINNER_VALUES, size_t N_PLAYER_VALUES>
struct Card
{
	unsigned int CalculateWinningPoints()
	{
		unsigned int points = 0;

		for (const int play_value : m_PlayingValues)
		{
			if (std::find(std::begin(m_WinningValues), std::end(m_WinningValues), play_value) != std::end(m_WinningValues))
			{
				if (points == 0) ++points;
				else points *= 2;
			}
		}
		return points;
	}

	std::vector<size_t> GetCopiesFromCard()
	{
		size_t n_matches = 0;
		for (const int play_value : m_PlayingValues)
		{
			if (std::find(std::begin(m_WinningValues), std::end(m_WinningValues), play_value) != std::end(m_WinningValues))
			{
				n_matches++;
			}
		}

		std::vector<size_t> copy_indices;
		copy_indices.reserve(n_matches);
		for (size_t i = m_CardNumber + 1; i <= m_CardNumber + n_matches; i++)
		{
			copy_indices.push_back(i);
		}
		return copy_indices;
	}

	int m_CardNumber = -1;
	const std::array<int, N_WINNER_VALUES> m_WinningValues;
	const std::array<int, N_PLAYER_VALUES> m_PlayingValues;
};

template<size_t N_VALUES>
std::array<int, N_VALUES> StringToIntArray(const std::string& str)
{
	std::stringstream stream(str);
	std::array<int, N_VALUES> result{-1};

	int v;
	int ix = 0;
	while (stream >> v && ix < N_VALUES)
	{
		result[ix] = v;
		++ix;
	}
	return result;
}


template<size_t N_WINNER_VALUES, size_t N_PLAYER_VALUES>
Card<N_WINNER_VALUES, N_PLAYER_VALUES> CreateCardFromInput(const std::string& input)
{
	const std::string& split_from_index = input.substr(input.find(':') + 2);
	size_t separator_index = split_from_index.find('|');

	const std::string& winner_row = split_from_index.substr(0, separator_index);
	const std::string& player_row = split_from_index.substr(separator_index + 2);

	const std::array<int, N_WINNER_VALUES> winner_values = StringToIntArray<N_WINNER_VALUES>(winner_row);
	const std::array<int, N_PLAYER_VALUES> player_values = StringToIntArray<N_PLAYER_VALUES>(player_row);
	return Card<N_WINNER_VALUES, N_PLAYER_VALUES> { -1, winner_values, player_values };
}

template<size_t N_WINNER_VALUES, size_t N_PLAYER_VALUES>
Card<N_WINNER_VALUES, N_PLAYER_VALUES> CreateCardFromInputAndCardNumber(const std::string& input, size_t card_number)
{
	Card card = CreateCardFromInput<N_WINNER_VALUES, N_PLAYER_VALUES>(input);
	card.m_CardNumber = card_number;
	return card;
}

int main()
{
	std::string input;
	constexpr static size_t N_WINNER_VALUES = 10;
	constexpr static size_t N_PLAYER_VALUES = 25;

	// Part 1:
	//unsigned int summed_points = 0;
	//while (std::getline(std::cin, input) && input != "STOP")
	//{
	//	Card card = CreateCardFromInput<N_WINNER_VALUES, N_PLAYER_VALUES>(input);
	//	summed_points += card.CalculateWinningPoints();
	//}
	//std::cout << "Results: " << summed_points << "\n";


	// Part 2:
	size_t card_number_counter = 0;
	std::vector<size_t> card_copies;
	while (std::getline(std::cin, input) && input != "STOP")
	{
		Card card = CreateCardFromInputAndCardNumber<N_WINNER_VALUES, N_PLAYER_VALUES>(input, card_number_counter);
		std::vector<size_t> copy_indices = card.GetCopiesFromCard();
		
		size_t n_copies = std::count(card_copies.begin(), card_copies.end(), card_number_counter);
		size_t i = 0;
		do
		{
			card_copies.insert(card_copies.end(), copy_indices.begin(), copy_indices.end());
			i++;
		} while (i <= n_copies);

		card_number_counter++;
	}
	std::cout << "Checked: " << card_number_counter + card_copies.size() << std::endl; // 11024379
}
