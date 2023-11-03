// AoC2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

enum class ERps
{
    E_INVALID = 0,
    E_ROCK,
    E_PAPER,
    E_SCISSORS
};

class Move
{
public:
    Move(char c)
    {
        switch (c)
        {
        case 'A':
            m_MoveType = ERps::E_ROCK;
            m_OpponentMove = true;
            break;
		case 'B':
			m_MoveType = ERps::E_PAPER;
            m_OpponentMove = true;
			break;
		case 'C':
			m_MoveType = ERps::E_SCISSORS;
            m_OpponentMove = true;
			break;
		case 'X':
			m_MoveType = ERps::E_ROCK;
            m_OpponentMove = false;
			break;
		case 'Y':
			m_MoveType = ERps::E_PAPER;
            m_OpponentMove = false;
			break;
		case 'Z':
			m_MoveType = ERps::E_SCISSORS;
            m_OpponentMove = false;
			break;
        default:
            break;
        }
    }

    int RoundScore(const Move opponent_move) const
    {
        ERps opponent_move_type = opponent_move.GetMoveType();
        if (m_MoveType == opponent_move_type) return 3;
        else if (WinsAgainst(opponent_move_type)) return 6;
        return 0; // Otherwise we lose.
    }

    bool WinsAgainst(const ERps opponent_move_type) const
    {
        switch (m_MoveType)
        {
        case ERps::E_ROCK:
            return opponent_move_type == ERps::E_SCISSORS;
        case ERps::E_PAPER:
            return opponent_move_type == ERps::E_ROCK;
        case ERps::E_SCISSORS:
            return opponent_move_type == ERps::E_PAPER;
        case ERps::E_INVALID:
        default:
            return false;
        }
    }

    bool IsOponentMove() const
    {
        return m_OpponentMove;
    }

    ERps GetMoveType() const
    {
        return m_MoveType;
    }

private:
    // Development / Debug
    std::ostream& write(std::ostream& os) const
    {
        const char* opp_str = m_OpponentMove ? "(OPPONENT)" : "(YOURS)";
        switch (m_MoveType)
        {
        case ERps::E_ROCK:
            os << "ROCK " << opp_str;
            break;
        case ERps::E_PAPER:
            os << "PAPER " << opp_str;
            break;
        case ERps::E_SCISSORS:
            os << "SCISSORS " << opp_str;
            break;
        case ERps::E_INVALID:
            os << "";
            break;
        default:
            os << "";
            break;
        }
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Move& m)
    {
        return m.write(os);
    }
	ERps m_MoveType = ERps::E_INVALID;
	bool m_OpponentMove = false;
};

class Battle
{
public:
    Battle(Move m1, Move m2) : m_Move1(m1), m_Move2(m2) {}
	int Run() const
	{
		const Move opponent_move = m_Move1.IsOponentMove() ? m_Move1 : m_Move2;
		const Move your_move = m_Move1.IsOponentMove() ? m_Move2 : m_Move1;

		int score_sum = 0;
		int move_score = 0;
		switch (your_move.GetMoveType())
		{
		case ERps::E_INVALID:
			break;
		case ERps::E_ROCK:
			move_score = 1;
			break;
		case ERps::E_PAPER:
			move_score = 2;
			break;
		case ERps::E_SCISSORS:
			move_score = 3;
			break;
		default:
			break;
		}
		score_sum += move_score;
		score_sum += your_move.RoundScore(opponent_move);
		return score_sum;
	}

private:
    Move m_Move1;
    Move m_Move2;
};

int main()
{
    std::vector<Battle> battles;
    bool opponent_move = true;

    char opp_char;
    char your_char;
    char c;

    std::cout << "Input moves: " << std::endl;
    while (std::cin >> c)
    {
        if (opponent_move)
        {
            opp_char = c;
        }
        else
        {
            your_char = c;
            battles.emplace_back(Move(opp_char), Move(your_char));
        }
        opponent_move = !opponent_move;
    }

    unsigned int total_score = 0;
    for (const Battle& b : battles)
    {
        total_score += b.Run();
    }

    std::cout << "YOUR SCORE: " << total_score;
}
