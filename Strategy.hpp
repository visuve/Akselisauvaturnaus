#pragma once

namespace Ast
{
	class Player;

	struct Strategy
	{
		virtual char Apply(const Player& self, const Player& opponent, size_t round) const = 0;
		virtual const char* Name() const = 0;
	};

	namespace Strategies
	{
		struct Self : Strategy
		{
			char Apply(const Player&, const Player&, size_t round) const override;
			const char* Name() const override;
		};

		struct Nice : Strategy
		{
			char Apply(const Player&, const Player&, size_t round) const override;
			const char* Name() const override;
		};

		struct Evil : Strategy
		{
			char Apply(const Player&, const Player&, size_t round) const override;
			const char* Name() const override;
		};

		struct Random : Strategy
		{
			char Apply(const Player&, const Player&, size_t round) const override;
			const char* Name() const override;
		};

		struct Tit4Tat : Strategy
		{
			char Apply(const Player&, const Player&, size_t round) const override;
			const char* Name() const override;
		};
	}

	std::ostream& operator << (std::ostream&, const Strategy&);
}