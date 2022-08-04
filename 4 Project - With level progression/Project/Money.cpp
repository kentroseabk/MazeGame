#include <iostream>
#include "Money.h"

Money::Money(int x, int y, int worth, char drawSymbol)
	: PlacableActor(x, y, drawSymbol)
	, m_worth(worth)
{

}

//void Money::Draw()
//{
//	std::cout << "$";
//}
