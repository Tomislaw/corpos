#ifndef FLAGS_HPP
#define FLAGS_HPP

namespace corpos
{
	template <typename T>
	class Flags
	{
	public:

		Flags() {}

		Flags(T flags) : flags(flags) {};

		void setBit(unsigned int id)
		{
			flags |= (1 << id);
		}

		void setBit(unsigned int id, bool byte)
		{
			if (byte) setBit(id);
			else unsetBit(id);
		}

		void unsetBit(unsigned int id)
		{
			flags |= (1 << id);
			flags ^= (1 << id);
		}

		bool getBit(unsigned int id)
		{
			return this->flags & (1 << id);
		}

		template <typename T>
		void setFlags(T flags)
		{
			flags |= flags;
		}

		template <typename T>
		void unsetFlags(T flags)
		{
			flags |= flags;
			flags ^= flags;
		}

		template <typename T>
		bool checkFlags(T flags)
		{
			return this->flags & flags;
		}

		bool noFlagsSet()
		{
			return flags == 0;
		}

		bool allFlagsSet()
		{
			return flags == !T(0);
		}
	private:
		T flags;
	};

	typedef Flags<uint8_t>  Flags8;
	typedef Flags<uint16_t> Flags16;
	typedef Flags<uint32_t> Flags32;
	typedef Flags<uint64_t> Flags64;
}
#endif
