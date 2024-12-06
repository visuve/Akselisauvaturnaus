#pragma once

namespace Ast
{
	class Player;

	struct Strategy
	{
		virtual char Apply(const Player& self, const Player& opponent, size_t round, size_t left) = 0;
		virtual const char* Name() const = 0;
	};

	namespace Strategies
	{
		struct Self : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Nice : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Evil : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Random : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Tit4Tat : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Alternator : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Grumpy : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};

		struct Shubik : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
			size_t RetaliationMax = 0;
			size_t RetaliationCur = 0;
		};

		struct Tideman : Shubik
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
			size_t SinceLastReset = 0;
			bool Reset = false;
		};

		struct Friedman : Strategy
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
			bool Mad = false;
		};

		struct Davis : Friedman
		{
			char Apply(const Player&, const Player&, size_t, size_t) override;
			const char* Name() const override;
		};
	}

	std::ostream& operator << (std::ostream&, const Strategy&);
}