#include "My_Defines.h"

Vec2 MyFunction::getUnitVec2(Vec2 vec)
{
	Vec2 temp;
	float size;

	size = sqrt(vec.x * vec.x + vec.y * vec.y);

	temp.x = vec.x / size;
	temp.y = vec.y / size;

	return temp;
}
std::string MyFunction::toString(float value)
{
	std::ostringstream convStream;
	convStream << value;

	return convStream.str();
}