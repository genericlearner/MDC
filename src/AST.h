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

	virtual void accept();


};