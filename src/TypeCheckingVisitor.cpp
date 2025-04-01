#include "TypeCheckingVisitor.h"
#include "SymbolTableHelper.h"


TypeCheckingVisitor::TypeCheckingVisitor() {

}
void TypeCheckingVisitor::visit(CompositeConceptAST* v) {}

void TypeCheckingVisitor::visit(IntLit* v) {
	v->setType("int");
}
void TypeCheckingVisitor::visit(FloatLit* v) {
	v->setType("float");
}
void TypeCheckingVisitor::visit(FloatID* v) {}
void TypeCheckingVisitor::visit(IntegerID* v) {}
void TypeCheckingVisitor::visit(ID* v) {
	std::vector<VariableEntry*>variables = v->searchVariabe(v->getData());
	std::vector<ParamEntry*>params = v->searchParam(v->getData());
	if (variables.size() > 0) {

		v->setType(variables[0]->type);
	}
	else if (params.size() > 0) {
		v->setType(params[0]->type);
	}
	

}
void TypeCheckingVisitor::visit(Void* v) {}
void TypeCheckingVisitor::visit(Public* v) {}
void TypeCheckingVisitor::visit(Private* v) {}
void TypeCheckingVisitor::visit(EqTo* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for == \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType("int");
		}
	}
}
void TypeCheckingVisitor::visit(NotEqTo* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for <> \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType("int");
		}
	}
}
void TypeCheckingVisitor::visit(Not* v){}
void TypeCheckingVisitor::visit(LessThan* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for < \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType("int");
		}
	}
}
void TypeCheckingVisitor::visit(LessThanOrEqTo* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for <= \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType("int");
		}
	}
}
void TypeCheckingVisitor::visit(GreaterThan* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for > \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType("int");
		}
	}
}
void TypeCheckingVisitor::visit(GreaterThanOrEqTo* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for >= \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType("int");
		}
	}
}
void TypeCheckingVisitor::visit(Add* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for Addition \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType(operands[0]->getType());
		}
	}
}
void TypeCheckingVisitor::visit(Subt* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for Subtraction \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType(operands[0]->getType());
		}
	}
}
void TypeCheckingVisitor::visit(Multiply* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for Multiplication \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType(operands[0]->getType());
		}
	}
}
void TypeCheckingVisitor::visit(Divide* v) {
	std::vector<AST*>operands = v->getChildren();

	if (operands.size() == 2) {
		if (operands[0]->getType() != operands[1]->getType()) {
			outError("Incompatible operand type for Division \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), v->getToken().getLine());
		}
		else {
			v->setType(operands[0]->getType());
		}
	}
}
void TypeCheckingVisitor::visit(Or* v) {}
void TypeCheckingVisitor::visit(And* v) {}
void TypeCheckingVisitor::visit(Period* v) {
	std::vector<AST*>children = v->getChildren();

	if (children.size() == 2) {
		std::vector<VariableEntry*>res = v->searchVariabe(children[0]->getData());

		if (res.size() > 0) {
			ClassEntry* classRec = v->searchClass(res[0]->type);

			if (!classRec && (res[0]->type == "float" || res[0]->type == "int")) {
				outError("dot operator used on non class type" + res[0]->name, v->getToken().getLine());
			}
			else {
				v->setType(children[1]->getType());
			}
		}
	}
}
void TypeCheckingVisitor::visit(Assign* v) {
	
}
void TypeCheckingVisitor::visit(Start* v) {}
void TypeCheckingVisitor::visit(ClassImplFunc* v) {}
void TypeCheckingVisitor::visit(ClassImplFuncList* v) {}
void TypeCheckingVisitor::visit(addOp* v) {}
void TypeCheckingVisitor::visit(addTermList* v) {}
void TypeCheckingVisitor::visit(AParamsList* v) {}
void TypeCheckingVisitor::visit(ArithExpr* v) {}
void TypeCheckingVisitor::visit(AttrDecl* v) {}
void TypeCheckingVisitor::visit(ClassDecl* v) {}
void TypeCheckingVisitor::visit(ClassList* v) {}
void TypeCheckingVisitor::visit(Expr* v) {}
void TypeCheckingVisitor::visit(ExtraExpr* v) {}
void TypeCheckingVisitor::visit(FuncBody* v) {}
void TypeCheckingVisitor::visit(FuncDecl* v) {}
void TypeCheckingVisitor::visit(FuncDef* v) {}
void TypeCheckingVisitor::visit(FuncDefList* v) {}
void TypeCheckingVisitor::visit(FuncHead* v) {}
void TypeCheckingVisitor::visit(IfStat* v) {}
void TypeCheckingVisitor::visit(ImplBody* v) {}
void TypeCheckingVisitor::visit(ImplDef* v) {}
void TypeCheckingVisitor::visit(ImplDefList* v) {}
void TypeCheckingVisitor::visit(ISA* v) {}
void TypeCheckingVisitor::visit(ISAList* v) {}
void TypeCheckingVisitor::visit(LocalVarDecl* v) {}
void TypeCheckingVisitor::visit(LocalVarDeclList* v) {}
void TypeCheckingVisitor::visit(MemberList* v) {}
void TypeCheckingVisitor::visit(MemDecl* v) {}
void TypeCheckingVisitor::visit(Prog* v) {}
void TypeCheckingVisitor::visit(ReadStat* v) {}
void TypeCheckingVisitor::visit(ReturnStat* v) {
	
	if (FunctionEntry* function = (FunctionEntry*)v->getClosestTable()->getNode()->getSymbolRec()) {
		if (v->getChild(0)->getType() != function->returnType) {
			outError("return statement does not match return type declared by function: " + function->name, ((TokenAST*)v->getChild(0))->getToken().getLine());
		}
	}
}
void TypeCheckingVisitor::visit(SignFactor* v) {}
void TypeCheckingVisitor::visit(Sign* v) {}
void TypeCheckingVisitor::visit(StatBlock* v) {}
void TypeCheckingVisitor::visit(Statement* v) {}
void TypeCheckingVisitor::visit(StatementList* v) {}
void TypeCheckingVisitor::visit(Term* v) {}
void TypeCheckingVisitor::visit(VarDecl* v) {
	if (VariableEntry* varRec = (VariableEntry*)v->getSymbolRec()) {
		ClassEntry* classRec = v->searchClass(varRec->type);
		if (!classRec &&(varRec->type != "int" && varRec->type != "float")) {
			outError("Use of undeclared class" + varRec->type, ((TokenAST*)v->getChild(1))->getToken().getLine());
		}
	}

	if (VariableEntry* varRec = (VariableEntry*)v->getSymbolRec()) {

	}
	/*
	VariableEntry* varRec = (VariableEntry*)v->getSymbolRec();
	if (ClassEntry* classRec = v->getClosestTable()->findClassRec(varRec->type)) {
		varRec->link = classRec->link;
	}*/
}
void TypeCheckingVisitor::visit(Visibility* v) {}
void TypeCheckingVisitor::visit(VisMemberDecl* v) {}
void TypeCheckingVisitor::visit(WhileStat* v) {}
void TypeCheckingVisitor::visit(WriteStat* v) {}
void TypeCheckingVisitor::visit(VisMemberDeclList* v) {}
void TypeCheckingVisitor::visit(fParamsList* v) {}
void TypeCheckingVisitor::visit(fParams* v) {
	std::vector<ParamEntry*>params = v->searchParam(v->getData());

	if (params.size() > 0) {
		v->setType(params[0]->type);
	}
}
void TypeCheckingVisitor::visit(ArraySize* v) {}
void TypeCheckingVisitor::visit(ArraySizeList* v) {}
void TypeCheckingVisitor::visit(Variable* v) {
	vector<AST*>children = v->getChildren();

	if (TokenAST* id = (TokenAST*)children[0]) {

		std::vector<VariableEntry*>varRes = v->searchVariabe(id->getData());
		std::vector<ParamEntry*>paramRes = v->searchParam(id->getData());

		if (varRes.size() > 0) {
			VariableEntry* varRec = varRes[0];
			v->setType(varRec->type);

			if (children.size() == 2) {
				std::vector<AST*>indices = children[1]->getChildren();
				if (indices.size() == varRec->arrayDimension.size()) {
					for (size_t i = 0; i < indices.size(); i++) {

						AST* ind = indices[i];

						if (ind->getType() != "int") {
							outError("Array Indice" + std::to_string(i) + "is not int type" + id->getData(), id->getToken().getLine());

						}
					}
				}
				else {
					outError("Wrong number of indices in the array: " + id->getData(), id->getToken().getLine());

				}
			}
		}

		else if (paramRes.size()) {
			ParamEntry* parRec = paramRes[0];
			v->setType(parRec->type);

			if (children.size() == 2) {
				std::vector<AST*>indices = children[1]->getChildren();
				if (indices.size() == parRec->arrInd.size()) {
					for (size_t i = 0; i < indices.size(); i++) {

						AST* ind = indices[i];

						if (ind->getType() != "int") {
							outError("Array Indice" + std::to_string(i) + "is not int type" + id->getData(), id->getToken().getLine());

						}
					}
				}
				else {
					outError("Wrong number of indices in the array: " + id->getData(), id->getToken().getLine());
				}
			}
		}
		else {
			outError("Use of undeclared variable: " + id->getData(), id->getToken().getLine());
		}
	}
}
void TypeCheckingVisitor::visit(AssignStat* v) {
	std::vector<AST*>operands = v->getChildren();


	if (operands.size() == 3) {
		if (operands[0]->getType() != operands[2]->getType()) {
			outError("Incompatible operand type for Assignment \"" + operands[0]->getType() + "\"and right operand \"" + operands[1]->getType(), 0);
		}
		else {
			v->setType(operands[0]->getType());
		}
	}
}
void TypeCheckingVisitor::visit(FuncCall* v) {
	
	if (!dynamic_cast<Period*>(v->parent)) {
		std::string fName = v->getChild(0)->getData();

		AST* paramListNode = v->getChild(1);
		std::vector<AST*>paramList;

		if (paramListNode) {
			paramList = paramListNode->getChildren();
		}
		std::vector<FunctionEntry*>correspondingFunction = v->searchFunction(fName);

		if (correspondingFunction.size() == 0) {
			outError("Function not found: " + fName, ((TokenAST*)v->getChild(0))->getToken().getLine());
			return;
		}

		bool isSameParamList = false;
		bool isSameNumParamList = false;

		for (FunctionEntry* f : correspondingFunction) {
			if (paramList.size() == f->paramList.size()) {
				isSameNumParamList = true;
				bool paramMatch = true;

				for (size_t i = 0; i < f->paramList.size(); i++) {
					AST* aParam = paramList[i];

					if (paramList[i]->getType() != std::get<0>(f->paramList[i])) {
						paramMatch = false;
					}
				}
				if (paramMatch) {
					v->setType(f->returnType);
					isSameParamList = true;
				}
			}
		}

		if (!isSameNumParamList) {
			outError("[ERROR]Function Call With Wrong Number Of Parameters: " + fName, ((TokenAST*)v->getChild(0))->getToken().getLine());
		}
		if (!isSameParamList) {
			outError("[ERROR]Function Call With Wrong Parameters: " + fName, ((TokenAST*)v->getChild(0))->getToken().getLine());
		}
		


	}

}
void TypeCheckingVisitor::visit(IndiceList* v) {}
void TypeCheckingVisitor::visit(Indice* v) {}
void TypeCheckingVisitor::visit(Self* v){}