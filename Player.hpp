#pragma once

#include "Strategy.hpp"

namespace Ast
{
	struct IStrategy;

	class Player
	{
	public:
		Player(IStrategy*, size_t rounds, size_t competitions = 1);
		virtual ~Player();

		static Player* Clone(const Player* other);

		char Play(const Player* other, size_t round, size_t left);

		operator bool() const;
		Player& operator++();

		const char* History() const;
		char History(size_t i) const;
		char& History(size_t i);

		size_t Cooperations() const;
		size_t Defections() const;

		size_t Score() const;
		size_t& Score();

		friend std::ostream& operator << (std::ostream&, const Player&);

	private:
		IStrategy* _strategy;
		char** _history = nullptr;
		size_t* _score = 0;

		const size_t _rounds = 0;
		const size_t _competitionCount = 0;
		size_t _competitionIndex = 0;
	};

	std::ostream& operator << (std::ostream&, const Player&);
};