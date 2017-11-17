#include "My_Utils.h"


std::string MyFunction::FloatToString(float value)
{
	std::ostringstream convStream;
	convStream << value;

	return convStream.str();
}