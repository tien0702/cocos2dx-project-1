#ifndef __BITMASK_H__
#define __BITMASK_H__

class Bitmask
{
public:
	static const int None = 0x0000;
	static const int All = 0x000F;
	static const int Player = 0x0001;
	static const int Enemy = 0x0002;
	static const int Projectile = 0x0003;
	static const int Wall = 0x0004;
};

#endif // !__BITMASK_H__
