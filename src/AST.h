#pragma once
#include <string>
#include <vector>

class AST {
private:
	std::string data;
	std::string type;

public:
	AST* leftMostSibling;
	AST* leftMostChild;
	AST* rightSibling;
	AST* parent;

	AST();
	~AST();

	std::vector<AST*> getChildren();

	AST* getChild(int c);

	AST* makeSiblings(AST* y);
	void adoptChild(AST* y);

	virtual std::string toString() = 0;
	std::string dotConvert();
	//virtual void accept();


};