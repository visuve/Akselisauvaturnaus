#include "Tournament.hpp"

namespace Ast
{
	Tournament::Tournament(Player** players, size_t playerCount, size_t rounds) :
		_players(players),
		_playerCount(playerCount),
		_competitions(new Competition*[playerCount * playerCount]),
		_competitionCount(playerCount* playerCount),
		_competitionIndex(0)
	{
		for (size_t y = 0; y < playerCount; ++y)
		{
			for (size_t x = 0; x < playerCount; ++x)
			{
				const size_t competitionIdx = y * _playerCount + x;
				_competitions[competitionIdx] = new Competition(players[y], players[x], rounds);
			}
		}
	}

	Tournament::~Tournament()
	{
		if (_competitions)
		{
			for (size_t i = 0; i < _competitionCount; ++i)
			{
				delete _competitions[i];
			}

			delete[] _competitions;
		}
	}

	Tournament::operator bool() const
	{
		return _competitionIndex < _competitionCount;
	}

	Tournament& Tournament::operator++()
	{
		Competition& competition = *_competitions[_competitionIndex];

		while (competition)
		{
			++competition;
		}

		for (size_t i = 0; i < _playerCount; ++i)
		{
			Player& player = *_players[i];
			++player;
		}

		++_competitionIndex;
		return *this;
	}

	void Tournament::PrintMatrix(std::ostream& os) const
	{
		constexpr size_t None = std::numeric_limits<size_t>::max();

		for (size_t y = None; y != _playerCount; ++y)
		{
			if (y == None)
			{
				os << "Akselisauvaturnaus";
			}
			else
			{
				os << std::setw(ConsolePadding) << _players[y]->Name();
			}

			for (size_t x = 0; x < _playerCount; ++x)
			{
				if (y == None)
				{
					os << std::setw(ConsolePadding) << _players[x]->Name();
				}
				else
				{
					const size_t competitionIdx = y * _playerCount + x;
					os << std::setw(ConsolePadding) << _players[x]->Result(competitionIdx)->Score;
				}
			}

			os << '\n';
		}
	}

	void Tournament::PrintTable(std::ostream& os) const
	{
		for (size_t y = 0; y != _playerCount; ++y)
		{
			for (size_t x = 0; x < _playerCount; ++x)
			{
				Player* arthur = _players[y];
				Player* bertha = _players[x];

				os << arthur->Name() << " vs " << bertha->Name() << "\t->\t";

				const size_t competitionIdx = y * _playerCount + x;

				size_t arthurScore = arthur->Result(competitionIdx)->Score;
				size_t berthaScore = bertha->Result(competitionIdx)->Score;

				os << arthur->Name() << '=' << arthurScore << '\t';
				os << bertha->Name() << '=' << berthaScore << "\t->\t";

				if (arthurScore > berthaScore)
				{
					os << arthur->Name() << " Wins!";
				}
				else if (arthurScore < berthaScore)
				{
					os << bertha->Name() << " Wins!";
				}
				else
				{
					os << " Draw.";
				}

				os << '\n';
			}
		}
	}
}