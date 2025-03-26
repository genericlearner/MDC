#include "SymbolTableVisitor.h"
#include <vector>
#include "SymbolTableHelper.h"

SymbolTableVisitor::SymbolTableVisitor(){}
void SymbolTableVisitor::visit(CompositeConceptAST* v) {}

void SymbolTableVisitor::visit(IntLit* v) {
	return;
}
void SymbolTableVisitor::visit(FloatLit* v) {
	return;
}
void SymbolTableVisitor::visit(FloatID* v) {
	return;
}
void SymbolTableVisitor::visit(IntegerID* v) {
	return;
}
void SymbolTableVisitor::visit(ID* v) {
	return;
}
void SymbolTableVisitor::visit(Void* v) {
	return;
}
void SymbolTableVisitor::visit(Public* v) {
	return;
}
void SymbolTableVisitor::visit(Private* v) {
	return;
}
void SymbolTableVisitor::visit(EqTo* v) {
	return;
}
void SymbolTableVisitor::visit(NotEqTo* v) {
	return;
}
void SymbolTableVisitor::visit(LessThan* v) {
	return;
}
void SymbolTableVisitor::visit(LessThanOrEqTo* v) {
	return;
}
void SymbolTableVisitor::visit(GreaterThan* v) {
	return;
}
void SymbolTableVisitor::visit(GreaterThanOrEqTo* v) {
	return;
}
void SymbolTableVisitor::visit(Add* v) {
	return;
}
void SymbolTableVisitor::visit(Subt* v) {
	return;
}
void SymbolTableVisitor::visit(Multiply* v) {
	return;
}
void SymbolTableVisitor::visit(Divide* v) {
	return;
}
void SymbolTableVisitor::visit(Or* v) {
	return;
}
void SymbolTableVisitor::visit(And* v) {
	return;
}
void SymbolTableVisitor::visit(Period* v) {
	return;
}
void SymbolTableVisitor::visit(Assign* v) {
	return;
}
void SymbolTableVisitor::visit(Start* v) {
	return;
}
void SymbolTableVisitor::visit(ClassImplFunc* v) {
	
}
void SymbolTableVisitor::visit(ClassImplFuncList* v) {
	return;
}
void SymbolTableVisitor::visit(addOp* v) {
	return;
}
void SymbolTableVisitor::visit(addTermList* v) {
	return;
}
void SymbolTableVisitor::visit(AParamsList* v) {
	return;
}
void SymbolTableVisitor::visit(ArithExpr* v) {
	return;
}
void SymbolTableVisitor::visit(AttrDecl* v) {}
void SymbolTableVisitor::visit(ClassDecl* v) {
	std::vector<AST*>children = v->getChildren();

	SymbolTable* table = SymbolTableHelper::createSymbolTable();
	v->setSymbolTable(table);

	ClassEntry* classEntry = SymbolTableHelper::createSymbolClassRec();

	classEntry->link = table;

	if (children.size() == 3) {
		classEntry->name = children[0]->getData();

		std::vector<AST*>istList = children[1]->getChildren();

		for (AST* ist : istList) {
			table->insertRec(ist->getSymbolRec());
		}

		std::vector<AST*>classDeclBody = children[2]->getChildren();
		for (AST* visMemberDecl : classDeclBody) {
			table->insertRec(visMemberDecl->getChildren().back()->getSymbolRec());
		}
	}


}
void SymbolTableVisitor::visit(ClassList* v) {}
void SymbolTableVisitor::visit(Expr* v) {}
void SymbolTableVisitor::visit(ExtraExpr* v) {}
void SymbolTableVisitor::visit(FuncBody* v) {}
void SymbolTableVisitor::visit(FuncDecl* v) {}
void SymbolTableVisitor::visit(FuncDef* v) {}
void SymbolTableVisitor::visit(FuncDefList* v) {}
void SymbolTableVisitor::visit(FuncHead* v) {}
void SymbolTableVisitor::visit(IfStat* v) {}
void SymbolTableVisitor::visit(ImplBody* v) {}
void SymbolTableVisitor::visit(ImplDef* v) {}
void SymbolTableVisitor::visit(ImplDefList* v) {}
void SymbolTableVisitor::visit(ISA* v) {}
void SymbolTableVisitor::visit(ISAList* v) {
	std::vector<AST*>children = v->getChildren();

	for (AST* child : children) {
		ClassEntry* classEntry = SymbolTableHelper::createSymbolClassRec();
		classEntry->name = child->getData();
		child->setSymbolRec(classEntry);
	}
}
void SymbolTableVisitor::visit(LocalVarDecl* v) {}
void SymbolTableVisitor::visit(LocalVarDeclList* v) {}
void SymbolTableVisitor::visit(MemberList* v) {}
void SymbolTableVisitor::visit(MemDecl* v) {}
void SymbolTableVisitor::visit(Prog* v) {
	std::vector<AST*>children = v->getChildren();

	SymbolTable* progTable = SymbolTableHelper::createSymbolTable();
	v->setSymbolTable(progTable);

	if (children.size() == 1) {
		std::vector<AST*>classImplFuncList = children[0]->getChildren();

		for (AST* classImplFunc : classImplFuncList) {

			if()
		}
	}

}
void SymbolTableVisitor::visit(ReadStat* v) {}
void SymbolTableVisitor::visit(ReturnStat* v) {}
void SymbolTableVisitor::visit(SignFactor* v) {}
void SymbolTableVisitor::visit(Sign* v) {}
void SymbolTableVisitor::visit(StatBlock* v) {}
void SymbolTableVisitor::visit(Statement* v) {}
void SymbolTableVisitor::visit(StatementList* v) {}
void SymbolTableVisitor::visit(Term* v) {}
void SymbolTableVisitor::visit(VarDecl* v) {
	std::vector<AST*>children = v->getChildren();

	VariableEntry* variableRec = SymbolTableHelper::createSymbolVariableRec();

	v->setSymbolRec(variableRec);
	
	if (children.size() == 2) {
		variableRec->type = children[0]->getData();
		variableRec->name = children[1]->getData();
	}
	else if (children.size()== 3) {
		variableRec->type = children[0]->getData();
		variableRec->name = children[1]->getData();

		std::vector<int>indices;
		std::vector<AST*>arrayDim = children[2]->getChildren();

		for (AST* dim : arrayDim) {
			std::vector<AST*> index = dim->getChildren();

			if (index.size()== 1) {
				indices.push_back(std::stoi(index[0]->getData()));
			}
			else {
				indices.push_back(-1);
			}
		}
		variableRec->arrayDimension = indices;

	}

}
void SymbolTableVisitor::visit(Visibility* v) {}
void SymbolTableVisitor::visit(VisMemberDecl* v) {
	std::vector<AST*>children = v->getChildren();

	VisibilityEntry* record = nullptr;
	if (children.size() == 2) {
		record = (VisibilityEntry*)(children[1]->getSymbolRec());
		record->visibility = children[0]->getData();

	}
	v->setSymbolRec(record);
}
void SymbolTableVisitor::visit(WhileStat* v) {}
void SymbolTableVisitor::visit(WriteStat* v) {}
void SymbolTableVisitor::visit(VisMemberDeclList* v) {
	

}
void SymbolTableVisitor::visit(fParamsList* v) {}
void SymbolTableVisitor::visit(fParams* v) {}
void SymbolTableVisitor::visit(ArraySize* v) {}
void SymbolTableVisitor::visit(ArraySizeList* v) {}
void SymbolTableVisitor::visit(Variable* v) {}
void SymbolTableVisitor::visit(AssignStat* v) {}
void SymbolTableVisitor::visit(FuncCall* v) {}
void SymbolTableVisitor::visit(IndiceList* v) {}
void SymbolTableVisitor::visit(Indice* v) {}