#include "GenerateLabel.h"

GenerateLabel::GenerateLabel()
{
}

std::string GenerateLabel::genZeroLabel()
{
	return "zero" + std::to_string(zeroLabel++);
}

std::string GenerateLabel::genNonZeroLabel()
{
	return "nonzero" + std::to_string(nonZeroLabel++);
}

std::string GenerateLabel::genEndAndLabel()
{
	return "endand" + std::to_string(endAndLabel++);
}

std::string GenerateLabel::genEndOrLabel()
{
	return "endor" + std::to_string(endOrLabel++);
}

std::string GenerateLabel::genEndNotLabel()
{
	return "endNot" + std::to_string(endNotLabel++);
}

std::string GenerateLabel::genElseLabel()
{
	return "else" + std::to_string(endNotLabel++);
}

std::string GenerateLabel::genEndIfLabel()
{
	return "endif" + std::to_string(endIfLabel++);
}

std::string GenerateLabel::genGoWhileLabel()
{
	return "gowhile" + std::to_string(goWhileLabel++);
}

std::string GenerateLabel::genEndWhileLabel()
{
	return "endwhile" + std::to_string(endWhileLabel++);
}

std::string GenerateLabel::genGetStrLabel()
{
	return "getstr" + std::to_string(getStrLabel++);
}

std::string GenerateLabel::genEndGetLabel()
{
	return "endget" + std::to_string(endGetLabel++);
}
