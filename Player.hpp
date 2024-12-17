#pragma once

#include "Strategy.hpp"

namespace Ast
{
	struct IStrategy;

	class Player
	{
	public:
		Player(IStrategy*, size_t rounds, size_t competitions = 1, size_t competitionIndex = 0);
		virtual ~Player();
		Player* Clone(bool shallow = true) const;

		char Play(const Player* other, size_t round, size_t left);

		operator bool() const;
		Player& operator++();

		const char* History() const;
		char History(size_t i) const;
		char& History(size_t i);
		const char* CompetitionHistory(size_t i) const;

		size_t Cooperations() const;
		size_t Defections() const;

		size_t Score() const;
		size_t& Score();
		size_t CompetitionScore(size_t i) const;

		const char* Name() const;

	private:
		IStrategy* _strategy;
		char** _history = nullptr;
		size_t* _score = 0;

		const size_t _rounds = 0;
		const size_t _competitionCount = 0;
		size_t _competitionIndex = 0;
	};
};