#pragma once
#include <string>

class GenerateLabel {

	int zeroLabel = 0;
	int nonZeroLabel = 0;
	int endAndLabel = 0;
	int endOrLabel = 0;
	int endNotLabel = 0;
	int elseLabel = 0;
	int endIfLabel = 0;
	int goWhileLabel = 0;
	int endWhileLabel = 0;
	int getStrLabel = 0;
	int endGetLabel = 0;
public:
	GenerateLabel();

	std::string genZeroLabel();
	std::string genNonZeroLabel();
	std::string genEndAndLabel();
	std::string genEndOrLabel();
	std::string genEndNotLabel();
	std::string genElseLabel();
	std::string genEndIfLabel();
	std::string genGoWhileLabel();
	std::string genEndWhileLabel();
	std::string genGetStrLabel();
	std::string genEndGetLabel();
};