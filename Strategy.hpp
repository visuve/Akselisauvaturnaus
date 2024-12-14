#pragma once

namespace Ast
{
	class Player;

	struct IStrategy
	{
		virtual char Apply(const Player* self, const Player* opponent, size_t round, size_t left) = 0;
		virtual const char* Name() const = 0;
		virtual IStrategy* Clone() const = 0;

		static IStrategy* Clone(const IStrategy* strategy);
	};

	namespace Strategies
	{
		struct Self : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Random : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Tit4Tat : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Shubik : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;

			size_t RetaliationMax = 0;
			size_t RetaliationCur = 0;
		};

		struct Tideman : Shubik
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;

			size_t SinceLastForgive = 0;
			bool Forgive = false;
		};

		// A.k.a. Grim
		struct Friedman : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Davis : Friedman
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Grofman : Tit4Tat
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Nydegger : Tit4Tat
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct SteinRapoport : Tit4Tat
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;

			bool OpponentAppearsRandom = false;
		};

		struct Graaskamp : Tit4Tat
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;

			size_t NextDefectTurn = 0;
		};

		struct Downing : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;

			float Good = 1.0f;
			float Bad = 0.0f;
			size_t CooperateResponses = 0;
			size_t DefectResponses = 0;
		};

		struct Downing2nd : Downing
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Feld : Tit4Tat
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;

			float CooperationProbability = 1.0f;
		};

		struct Joss : Tit4Tat
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Tullock : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Unnamed : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		// Extras

		struct Nice : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Evil : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Alternator : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};

		struct Grumpy : IStrategy
		{
			char Apply(const Player*, const Player*, size_t, size_t) override;
			const char* Name() const override;
			IStrategy* Clone() const override;
		};
	}

	std::ostream& operator << (std::ostream&, const IStrategy&);
}