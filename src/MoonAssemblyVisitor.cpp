#include "MoonAssemblyVisitor.h"
#include "SymbolTableHelper.h"

#include <iostream>


int MoonAssemblyVisitor::getStackOffset(SymbolTable* table) {
	return table->compOffset() + 4;
}

std::string MoonAssemblyVisitor::getRegister() {
	std::string res = registers.top();
	registers.pop();
	return res;
}

std::string MoonAssemblyVisitor::loadVariable(AST* node, SymbolTable* table) {
	std::string reg = getRegister();

	if (Variable* varCallNode = dynamic_cast<Variable*>(node)) {
		SymbolTableEntry* var = table->findVarOrParRec(varCallNode->getData());

		//need to implement classes
		if (var == nullptr) {
			return zeroReg;
		}
		std::vector<AST*>children = varCallNode->getChildren();

		int offset = 0;

		if (children.size() == 2) {
			std::vector<int>arraySize;
			std::string type;

			if (VariableEntry* varRecEntry = dynamic_cast<VariableEntry*>(var)) {
				arraySize = varRecEntry->arrayDimension;
				type = varRecEntry->type;
			}
			else if (ParamEntry* parRecEntry = dynamic_cast<ParamEntry*>(var)) {
				arraySize = parRecEntry->arrInd;
				type = varRecEntry->type;
			}
			int tSize = 0;
			if (type == "int") {
				tSize = 4;
			}
			else if (type == "float") {
				tSize = 8;
			}
			else {
				//class type
			}

			std::vector<AST*>indiceChildren = children[1]->getChildren();

			for (size_t i = 0; i < indiceChildren.size(); i++) {
				if (i == arraySize.size() - 1) {
					offset += std::stoi(indiceChildren[i]->getData()) * tSize;
				}
				else {
					offset += std::stoi(indiceChildren[i]->getData()) * (arraySize[i] + 1) * tSize;
				}
			}
		}
		codeOps.push_back("\tlw " + reg + "," + std::to_string(var->getOffset() - offset) + "(" + stackFramePointerReg + ")");
	}

	if (FuncCall* funcCallNode = dynamic_cast<FuncCall*>(node)) {
		TempEntry* tempEntry = table->findTempRec(funcCallNode->getAssemblyData());

		codeOps.push_back("\tlw " + reg + "," + std::to_string(tempEntry->getOffset()) + "(" + stackFramePointerReg + ")");
	}
	else if (CompositeConceptTokenAST* opType = dynamic_cast<CompositeConceptTokenAST*>(node)) {
		SymbolTableEntry* tempEentry = table->findTempRec(opType->getAssemblyData());

		codeOps.push_back("\tlw " + reg + "," + std::to_string(tempEentry->getOffset()) + "(" + stackFramePointerReg + ")");
	}
	else if (TokenAST* specType = dynamic_cast<TokenAST*>(node)) {
		codeOps.push_back("\taddi " + reg + "," + zeroReg + "," + specType->getAssemblyData());
	}
	return reg;
}

void MoonAssemblyVisitor::visitChildren(AST* parent) {
	AST* child = parent->leftMostChild;
	while (child != nullptr) {
		child->accept(this, false);
		child = child->rightSibling;
	}
}


MoonAssemblyVisitor::MoonAssemblyVisitor() {
	zeroReg = "r0";

	stackFramePointerReg = "r14";

	returnAddrReg = "r15";

	registers.push("r1");
	registers.push("r2");
	registers.push("r3");
	registers.push("r4");
	registers.push("r5");
	registers.push("r6");
	registers.push("r7");
	registers.push("r8");
	registers.push("r9");
	registers.push("r10");
	registers.push("r11");
	registers.push("r12");
	//registers.push("r13");

}

std::vector<std::string>MoonAssemblyVisitor::getCode() {
	std::vector<std::string>constr;

	for (std::deque<std::string>func : functions) {
		while (func.size() != 0) {
			constr.push_back(func.front());
			func.pop_front();
		}
	}
	constr.insert(constr.end(), reserveOps.begin(), reserveOps.end());
	return constr;
}

void MoonAssemblyVisitor:: visit(CompositeConceptAST* v) {visitChildren(v);}

void MoonAssemblyVisitor:: visit(IntLit* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(FloatLit* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(FloatID* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(IntegerID* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ID* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Void* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Public* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Private* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(EqTo* v) {
	visitChildren(v);
	codeOps.push_back("% equal operation compare");
	std::vector<std::string>registersUsed;

	SymbolTable* table = v->getClosestTable();

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tceq " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin(); 
		reg != registersUsed.rend(); 
		++reg) {

		registers.push(*reg);
	}

}
void MoonAssemblyVisitor:: visit(NotEqTo* v) {
	visitChildren(v);
	codeOps.push_back("% Not equal operation compare");
	std::vector<std::string>registersUsed;

	SymbolTable* table = v->getClosestTable();

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tcne " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(Not* v) {
	visitChildren(v);

	codeOps.push_back("% NOT  operation");

	SymbolTable* table = v->getClosestTable();

	std::string opReg = loadVariable(v->getChild(0), table);

	std::string zeroLabel = gl.genZeroLabel();
	std::string endNotLabel = gl.genEndOrLabel();

	TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
	
	codeOps.push_back("\tbnz " + opReg + "," + zeroLabel);
	codeOps.push_back("\taddi " + opReg + "," + zeroReg + ",1");
	codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + opReg);

	codeOps.push_back("\tj " + endNotLabel);

	codeOps.push_back(zeroLabel + "\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + zeroReg);

	registers.push(opReg);
}
void MoonAssemblyVisitor:: visit(LessThan* v) {
	visitChildren(v);
	codeOps.push_back("% Less than operation compare");
	std::vector<std::string>registersUsed;

	SymbolTable* table = v->getClosestTable();

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tclt " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(LessThanOrEqTo* v) {
	visitChildren(v);
	codeOps.push_back("% Less than or equal to operation compare");
	std::vector<std::string>registersUsed;

	SymbolTable* table = v->getClosestTable();

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tcle " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(GreaterThan* v) {
	visitChildren(v);
	codeOps.push_back("% Greater than operation compare");
	std::vector<std::string>registersUsed;

	SymbolTable* table = v->getClosestTable();

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tcgt " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(GreaterThanOrEqTo* v) {
	visitChildren(v);
	codeOps.push_back("% Greater than or equal to operation compare");
	std::vector<std::string>registersUsed;

	SymbolTable* table = v->getClosestTable();

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tcge " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(Add* v) {
	visitChildren(v);

	codeOps.push_back("% add operation");

	SymbolTable* table = v->getClosestTable();

	std::vector<std::string>registersUsed;


	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tadd " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}

}
void MoonAssemblyVisitor:: visit(Subt* v) {
	visitChildren(v);

	codeOps.push_back("% Subtraction operation");

	SymbolTable* table = v->getClosestTable();

	std::vector<std::string>registersUsed;

	

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tsub " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(Multiply* v) {
	visitChildren(v);

	codeOps.push_back("% Multiplication operation");

	SymbolTable* table = v->getClosestTable();

	std::vector<std::string>registersUsed;

	

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tmul " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(Divide* v) {
	visitChildren(v);

	codeOps.push_back("% Division operation");

	SymbolTable* table = v->getClosestTable();

	std::vector<std::string>registersUsed;

	registersUsed.push_back(loadVariable(v->getChild(0), table));
	//check this with the ast tree
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();
		registersUsed.push_back(res);

		codeOps.push_back("\tdiv " + res + "," + registersUsed[0] + "," + registersUsed[1]);

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back("\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}
	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(Or* v) {
	visitChildren(v);

	codeOps.push_back("% OR operation");

	SymbolTable* table = v->getClosestTable();

	std::vector<std::string>registersUsed;
	registersUsed.push_back(loadVariable(v->getChild(0), table));
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();

		registersUsed.push_back(res);

		std::string notZeroLabel = gl.genZeroLabel();
		std::string endOrLabel = gl.genEndOrLabel();

		codeOps.push_back("\tbnz " + registersUsed[0] + "," + notZeroLabel);
		codeOps.push_back("\tbnz " + registersUsed[1] + "," + notZeroLabel);

		codeOps.push_back("\taddi " + res + "," + zeroReg + ",1");
		codeOps.push_back("\tj " + endOrLabel);

		codeOps.push_back(notZeroLabel + "\taddi " + res + "," + zeroReg + ",1");

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back(endOrLabel + "\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}

	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}

}
void MoonAssemblyVisitor:: visit(And* v) {
	visitChildren(v);

	codeOps.push_back("% AND operation");

	SymbolTable* table = v->getClosestTable();

	std::vector<std::string>registersUsed;
	registersUsed.push_back(loadVariable(v->getChild(0), table));
	registersUsed.push_back(loadVariable(v->getChild(1), table));

	if (registersUsed.size() == 2) {
		std::string res = getRegister();

		registersUsed.push_back(res);

		std::string notZeroLabel = gl.genZeroLabel();
		std::string endAndLabel = gl.genEndAndLabel();

		codeOps.push_back("\tbz " + registersUsed[0] + "," + notZeroLabel);
		codeOps.push_back("\tbz " + registersUsed[1] + "," + notZeroLabel);

		codeOps.push_back("\taddi " + res + "," + zeroReg + ",0");
		codeOps.push_back("\tj " + endAndLabel);

		codeOps.push_back(notZeroLabel + "\taddi " + res + "," + zeroReg + ",0");

		TempEntry* tempRec = table->findTempRec(v->getAssemblyData());
		codeOps.push_back(endAndLabel + "\tsw " + std::to_string(tempRec->getOffset()) + "(" + stackFramePointerReg + ")," + res);
	}

	for (std::vector<std::string>::reverse_iterator reg = registersUsed.rbegin();
		reg != registersUsed.rend();
		++reg) {

		registers.push(*reg);
	}
}
void MoonAssemblyVisitor:: visit(Period* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Assign* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Start* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ClassImplFunc* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ClassImplFuncList* v) {
	//implement ts
	
	visitChildren(v);
	/* 
	if (Prog* progParent = dynamic_cast<Prog*>(v->parent)) {
		if (codeOps.size() != 0) {
			functions.push_back(codeOps);
			codeOps = std::deque<std::string>();
		}
	}*/

}
void MoonAssemblyVisitor:: visit(addOp* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(addTermList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(AParamsList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ArithExpr* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(AttrDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ClassDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ClassList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Expr* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ExtraExpr* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(FuncBody* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(FuncDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(FuncDef* v) {
	visitChildren(v);
	if (FunctionEntry* fEntry = dynamic_cast<FunctionEntry*>(v->getSymbolRec())) {
		// Function prologue
		codeOps.push_front(fEntry->name);

		// Return to caller
		codeOps.push_back("\tjr " + returnAddrReg);

		functions.push_back(codeOps);
		codeOps = std::deque<std::string>();
	}

}
void MoonAssemblyVisitor:: visit(FuncDefList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(FuncHead* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(IfStat* v) {
	v->getChild(0)->accept(this, false);

	SymbolTable* table = v->getClosestTable();
	std::string relExpr = loadVariable(v->getChild(0), table);

	if (v->getChild(2)) {
		codeOps.push_back("%ifelse statment");

		std::string elseLabel = gl.genElseLabel();
		std::string endIfLabel = gl.genEndIfLabel();

		codeOps.push_back("\tbz " + relExpr + "," + elseLabel);

		v->getChild(1)->accept(this, false);
		codeOps.push_back("\tj " + endIfLabel);

		codeOps.push_back(elseLabel + "\tnop");
		v->getChild(2)->accept(this, false);

		codeOps.push_back(endIfLabel + "\tnop");
	}
	else {
		codeOps.push_back("% if statement");

		std::string endIfLabel = gl.genEndIfLabel();

		codeOps.push_back("\tbz " + relExpr + "," + endIfLabel);

		v->getChild(1)->accept(this, false);

		codeOps.push_back(endIfLabel + "\tnop");
	}
	registers.push(relExpr);


}
void MoonAssemblyVisitor:: visit(ImplBody* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ImplDef* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ImplDefList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ISA* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ISAList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(LocalVarDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(LocalVarDeclList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(MemberList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(MemDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Prog* v) {
	visitChildren(v);
	bool hasMain = false;
	if (SymbolTable* table = v->getSymbolTable()) {
		for (auto func : table->findFunctionRec("main")) {
			if (func->name == "main") {
				hasMain = true;
				break;
			}
		}
		// Program entry point and initialization
		codeOps.push_front("MAIN");
		codeOps.push_front("\tsubi " + stackFramePointerReg + "," + stackFramePointerReg + ",4");
		codeOps.push_front("\tsub " + zeroReg + "," + zeroReg + "," + zeroReg);
		codeOps.push_front("\taddi " + stackFramePointerReg + "," + zeroReg + ",topaddr");
		codeOps.push_front("\tentry");

		if (hasMain) {
			codeOps.push_back("\tjl " + returnAddrReg + ",main");
		}
		// Add comment indicating program start
		codeOps.push_front("% Program start");		

		// Set up buffering for I/O operations
		reserveOps.push_back("\t% buffer for output");
		reserveOps.push_back("buf\tres 20");

		// Call main function if necessary
		// If your language requires an explicit call to main, add it here
		// codeOps.push_back("\tjl " + returnAddrReg + ",main");

		// Halt the program when execution completes
		codeOps.push_back("\thlt");

		// Add the main program code to the functions list
		functions.push_back(codeOps);
	}


}
void MoonAssemblyVisitor:: visit(ReadStat* v) {
	SymbolTable* table = v->getClosestTable();

	codeOps.push_back("% read");

	std::string bufferReg = getRegister();
	std::string getStrLabel = gl.genGetStrLabel();
	std::string endGetLabel = gl.genEndGetLabel();

	codeOps.push_back("\taddi " + bufferReg + ',' + zeroReg + ",buf");
	codeOps.push_back("\tsw -8(" + stackFramePointerReg + ")," + bufferReg);

	codeOps.push_back("\tsw " + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")," + returnAddrReg);

	std::string charReg = getRegister();

	codeOps.push_back("\taddi " + charReg + "," + zeroReg + ",10");
	codeOps.push_back("\tputc " + charReg);
	codeOps.push_back("\taddi " + charReg + "," + zeroReg + ",63");
	codeOps.push_back("\tputc " + charReg);
	codeOps.push_back("\taddi " + charReg + "," + zeroReg + ",58");
	codeOps.push_back("\tputc " + charReg);

	// Read string from console
	codeOps.push_back("\tjl " + returnAddrReg + ",getstr");

	// restore jump register state
	codeOps.push_back("\tlw " + returnAddrReg + "," + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")");


	// save jump register state
	codeOps.push_back("\tsw " + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")," + returnAddrReg);

	// Convert string to integer
	codeOps.push_back("\tjl " + returnAddrReg + ",strint");

	// restore jump register state
	codeOps.push_back("\tlw " + returnAddrReg + "," + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")");

	VariableEntry* tempRecord = table->findVariableRec(v->getChild(0)->getAssemblyData());
	codeOps.push_back("\tsw " + std::to_string(tempRecord->getOffset()) + "(" + stackFramePointerReg + "),r13");

	registers.push(charReg);
	registers.push(bufferReg);

}
void MoonAssemblyVisitor:: visit(ReturnStat* v) {
	visitChildren(v);

	SymbolTable* table = v->getClosestTable();

	std::string returnReg = loadVariable(v->getChild(0), table);

	codeOps.push_back("\tsw " + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")," + returnReg);
	//TODO work on handling array and aggregate types + add jump statement to actually exit the function
	registers.push(returnReg);
}
void MoonAssemblyVisitor:: visit(SignFactor* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Sign* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(StatBlock* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Statement* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(StatementList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Term* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(VarDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Visibility* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(VisMemberDecl* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(WhileStat* v) {
	codeOps.push_back("% while loop");

	SymbolTable* table = v->getClosestTable();
	std::string whileLabel = gl.genGoWhileLabel();
	std::string endwhileLabel = gl.genEndWhileLabel();

	codeOps.push_back(whileLabel + "\tnop");

	v->getChild(0)->accept(this, false);

	std::string whileReg = loadVariable(v->getChild(0), table);

	codeOps.push_back("\tbz " + whileReg + "," + endwhileLabel);

	if (AST* statementList = v->getChild(1)) {
		statementList->accept(this, false);
	}

	codeOps.push_back("\tj " + whileLabel);

	codeOps.push_back(endwhileLabel + "\tnop");

	registers.push(whileReg);
}
void MoonAssemblyVisitor:: visit(WriteStat* v) {
	
	SymbolTable* table = v->getClosestTable();
	visitChildren(v);

	codeOps.push_back("% write Statement");

	std::string writeReg = loadVariable(v->getChild(0), table);

	codeOps.push_back("\tsw " + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")," + returnAddrReg);

	codeOps.push_back("\taddi " + stackFramePointerReg + "," + stackFramePointerReg + "," + std::to_string(table->compOffset() - 4));


	codeOps.push_back("\tsw -8(" + stackFramePointerReg + ")," + writeReg);

	codeOps.push_back("\taddi " + writeReg + "," + zeroReg + ",buf");
	codeOps.push_back("\tsw -12(" + stackFramePointerReg + ")," + writeReg);

	codeOps.push_back("\tjl " + returnAddrReg + ",intstr");

	codeOps.push_back("\tsw -8(" + stackFramePointerReg + "), r13");

	codeOps.push_back("\tjl r15, putstr");

	codeOps.push_back("\tsubi " + stackFramePointerReg + "," + stackFramePointerReg + "," + std::to_string(table->compOffset() - 4));

	codeOps.push_back("\tlw " + returnAddrReg + "," + std::to_string(table->compOffset()) + "(" + stackFramePointerReg + ")");

	registers.push(writeReg);


}
void MoonAssemblyVisitor:: visit(VisMemberDeclList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(fParamsList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(fParams* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ArraySize* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(ArraySizeList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Variable* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(AssignStat* v) {
	visitChildren(v);

	codeOps.push_back("% assignment operation");

	AST* leftOp = v->getChild(0);
	AST* rightOp = v->getChild(2);

	SymbolTable* table = v->getClosestTable();

	SymbolTableEntry* varAssign = nullptr;
	int leftVarArrOffset = 0;

	VariableEntry* varRec = table->findVariableRec(leftOp->getData());
	ParamEntry* parRec = table->findParRec(leftOp->getData());

	std::string type;

	std::vector<int>leftVarArrSize;

	if (varRec != nullptr) {
		varAssign = varRec;
		type = varRec->type;
		leftVarArrSize = varRec->arrayDimension;
	}
	else if (parRec != nullptr) {
		varAssign = parRec;
		type = parRec->type;
		leftVarArrSize = parRec->arrInd;
	}
	
	if (varAssign == nullptr) {
		//class;
		return;
	}

	int leftVarOffset = 0;
	int leftVarTypeSize = 0;

	if (leftVarArrSize.size() > 0) {
		if (type == "int") {
			leftVarTypeSize = 4;
		}
		else if (type == "float") {
			leftVarTypeSize = 8;
		}
		else {
			//class
		}

		std::vector<AST*>leftVarIndices = leftOp->getChildren()[1]->getChildren();

		for (size_t i = 0; i < leftVarIndices.size(); i++) {
			if (i == leftVarArrSize.size() - 1) {
				leftVarOffset += std::stoi(leftVarIndices[i]->getData()) * leftVarTypeSize;
			}
			else {
				leftVarOffset += std::stoi(leftVarIndices[i]->getData()) * (leftVarArrSize[i] + 1) * leftVarTypeSize;
			}
		}


	}

	if (Variable* varCallNode = dynamic_cast<Variable*>(rightOp)) {
		SymbolTableEntry* rightVarRec = table->findVariableRec(varCallNode->getData());

		if (rightVarRec == nullptr) {
			rightVarRec = table->findImplementationRec(varCallNode->getData());
		}
		std::vector<AST*>children = varCallNode->getChildren();

		int rightVarOffset = 0;

		if (children.size() == 2) {
			std::vector<int>rightVarArrSize;

			if (VariableEntry* rightVarRec = dynamic_cast<VariableEntry*>(rightVarRec)) {
				rightVarArrSize = rightVarRec->arrayDimension;
			}
			else if (ParamEntry* rightVarRec = dynamic_cast<ParamEntry*>(rightVarRec)) {
				rightVarArrSize = rightVarRec->arrInd;
			}
			int rightVarTypeSize = 0;
			if (type == "int") {
				rightVarTypeSize = 4;
			}
			else if (type == "float") {
				rightVarTypeSize = 8;
			}
			else {
				//class
			}

			std::vector<AST*>rightVarIndices = children[1]->getChildren();

			for (size_t i = 0; i < rightVarIndices.size(); i++) {
				if (i == rightVarArrSize.size() - 1) {
					rightVarOffset += std::stoi(rightVarIndices[i]->getData()) * rightVarTypeSize;
				}
				else {
					rightVarOffset += std::stoi(rightVarIndices[i]->getData()) * (rightVarArrSize[i] + 1) * rightVarTypeSize;
				}
			}
		}

		std::string reg = registers.top(); registers.pop();

		codeOps.push_back("\tlw " + reg + "," + std::to_string(rightVarRec->getOffset() - rightVarOffset) + "(" + stackFramePointerReg + ")");

		codeOps.push_back("\tsw " + std::to_string(varAssign->getOffset() - leftVarOffset) + "(" + stackFramePointerReg + ")" + "," + reg);

		registers.push(reg);
	}

	if (FuncCall* funcCallNode = dynamic_cast<FuncCall*>(rightOp)) {
		TempEntry* tempRec = table->findTempRec(funcCallNode->getAssemblyData());

		std::string reg = registers.top(); registers.pop();
		codeOps.push_back("\tlw " + reg + "," + std::to_string(varAssign->getOffset()) + "(" + stackFramePointerReg + ")");

		codeOps.push_back("\tsw "  + std::to_string(varAssign->getOffset() - leftVarOffset) + "(" + stackFramePointerReg + ")" + "," + reg);

		registers.push(reg);
	}
	else if (CompositeConceptTokenAST* operationType = dynamic_cast<CompositeConceptTokenAST*>(rightOp)) {
		SymbolTableEntry* rightVarAssign = table->findTempRec(operationType->getAssemblyData());

		std::string reg = registers.top(); registers.pop();

		codeOps.push_back("\tlw " + reg + "," + std::to_string(rightVarAssign->getOffset()) + "(" + stackFramePointerReg + ")");

		codeOps.push_back("\tsw " + std::to_string(varAssign->getOffset() - leftVarOffset) + "(" + stackFramePointerReg + ")" + "," + reg);

		registers.push(reg);
	}
	else if (TokenAST* specType = dynamic_cast<TokenAST*>(rightOp)) {
		std::string reg = registers.top(); registers.pop();

		codeOps.push_back("\tsub " + reg + "," + reg + "," + reg);

		codeOps.push_back("\taddi " + reg + "," + reg + "," + specType->getData());

		codeOps.push_back("\tsw " + std::to_string(varAssign->getOffset() - leftVarOffset) + "(" + stackFramePointerReg + ")" + "," + reg);

		registers.push(reg);
	}

	//array assignments

}
void MoonAssemblyVisitor:: visit(FuncCall* v) {
	visitChildren(v);

	if (Period* period = dynamic_cast<Period*>(v->parent)) {
		return;
	}
	AST* functionName = v->getChild(0);
	SymbolTable* table = v->getClosestTable();
	int tableOffset = table->compOffset();

	if (functionName != nullptr && table != nullptr) {
		FunctionEntry* fEntry = nullptr;

		std::vector<FunctionEntry*>entries = v->searchFunction(functionName->getData());
		if(entries.size() != 0) {
			fEntry = entries[0];
		}

		codeOps.push_back("% Function call to" + functionName->getData());

		int funcOffset = fEntry->link->compOffset();

		// 1. Set up parameter passing
		if (AST* aParamList = v->getChild(1)) {
			std::vector<AST*> params = aParamList->getChildren();

			// Pass parameters in reverse order (last parameter first)
			for (int i = params.size() - 1; i >= 0; i--) {
				codeOps.push_back("\t% Parameter " + std::to_string(i + 1));
				std::string paramReg = loadVariable(params[i], table);

				// Store parameter at the appropriate offset in the new stack frame
				// Parameters are typically stored at positive offsets from the frame pointer
				int paramOffset = (tableOffset - 4) - 4 * i;
				codeOps.push_back("\tsw " + std::to_string(paramOffset) + "(" + stackFramePointerReg + ")," + paramReg);

				registers.push(paramReg);
			}
		}

		// 2. Save return address
		codeOps.push_back("\t% Save return address");
		codeOps.push_back("\tsw " + std::to_string(tableOffset) + "(" + stackFramePointerReg + ")," + returnAddrReg);

		// 3. Adjust stack pointer to create new frame
		codeOps.push_back("\t% Create new stack frame");
		codeOps.push_back("\taddi " + stackFramePointerReg + "," + stackFramePointerReg + "," + std::to_string(tableOffset - 4));

		// 4. Call the function
		codeOps.push_back("\t% Call function");
		codeOps.push_back("\tjl " + returnAddrReg + "," + fEntry->name);

		// 5. Restore stack frame (undo the adjustment we made)
		codeOps.push_back("\t% Restore original stack frame");
		codeOps.push_back("\tsubi " + stackFramePointerReg + "," + stackFramePointerReg + "," + std::to_string(tableOffset - 4));

		// 6. Restore return address
		codeOps.push_back("\t% Restore return address");
		codeOps.push_back("\tlw " + returnAddrReg + "," + std::to_string(tableOffset) + "(" + stackFramePointerReg + ")");

		// 7. Handle return value if the function returns something
		if (v->getType() != "void") {
			codeOps.push_back("\t% Handle return value");
			std::string returnReg = getRegister();

			// Load return value from where the function stored it
			// Return values are typically placed at a fixed offset from the frame pointer
			codeOps.push_back("\tlw " + returnReg + "," + std::to_string(tableOffset - 4 + funcOffset) + "(" + stackFramePointerReg + ")");

			// Store the return value in the temp location for this function call
			TempEntry* tempReturn = table->findTempRec(v->getAssemblyData());
			codeOps.push_back("\tsw " + std::to_string(tempReturn->getOffset()) + "(" + stackFramePointerReg + ")," + returnReg);

			registers.push(returnReg);
		}
	}

}
void MoonAssemblyVisitor:: visit(IndiceList* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Indice* v) {visitChildren(v);}
void MoonAssemblyVisitor:: visit(Self* v) {visitChildren(v);}