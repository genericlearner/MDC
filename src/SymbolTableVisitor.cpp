#include "SymbolTableVisitor.h"
#include <vector>
#include "SymbolTableHelper.h"
#include <unordered_map>
#include <unordered_set>
#include <functional>
SymbolTableVisitor::SymbolTableVisitor(){

}
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
void SymbolTableVisitor::visit(Not* v) {
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
	std::vector<AST*>childrenAll = v->getChildren();
	std::vector<std::string>duplicateClass;
	std::vector<AST*>children;
	for (AST* child:childrenAll) {
		if (dynamic_cast<ClassDecl*>(child)) {
			children.push_back(child);
		}
		
	}
	//Could use a map for checking duplicates
	for (size_t i = 0; i < children.size(); i++) {
		for (size_t j = 0; j < children.size(); j++) {
			if (i == j) {
				continue;
			}

			if (children[i]->getSymbolRec()->name == children[j]->getSymbolRec()->name) {
				if (std::find(duplicateClass.begin(), duplicateClass.end(), children[i]->getSymbolRec()->name) == duplicateClass.end()) {
					outError("Multiple Classes Declared" + children[i]->getSymbolRec()->name, ((TokenAST*)children[j]->getChild(0))->getToken().getLine());
					duplicateClass.push_back(children[i]->getSymbolRec()->name);
				}
				else {}
			}

		}
	}
	// Collect class declarations and build inheritance map
	std::unordered_map<std::string, std::vector<std::string>> inheritanceMap;
	for (AST* child : childrenAll) {
		if (auto* classDecl = dynamic_cast<ClassDecl*>(child)) {
			inheritanceMap[classDecl->getSymbolRec()->name] = {}; // Initialize map entry
		}
	}

	// Build inheritance map
	for (AST* child : childrenAll) {
		if (auto* classDecl = dynamic_cast<ClassDecl*>(child)) {
			std::vector<ClassEntry*> isaList = classDecl->getSymbolTable()->getClassRec();
			for (ClassEntry* isa : isaList) {
				inheritanceMap[classDecl->getSymbolRec()->name].push_back(isa->name);
			}
		}
	}

	// Detect circular inheritance
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> recStack;

	std::function<bool(const std::string&)> hasCycle = [&](const std::string& className) -> bool {
		if (recStack.count(className)) return true;  // Cycle detected
		if (visited.count(className)) return false; // Already checked

		visited.insert(className);
		recStack.insert(className);

		for (const std::string& parent : inheritanceMap[className]) {
			if (hasCycle(parent)) {
				outError("Circular inheritance detected: " + className + " <-> " + parent, 0);
				return true;
			}
		}

		recStack.erase(className); // Backtrack
		return false;
	};

	// Apply cycle detection on all class declarations
	for (const auto& [className, _] : inheritanceMap) {
		if (!visited.count(className)) {
			hasCycle(className);
		}
	}
	for (AST* classDecl : children) {
		
		std::vector<ClassEntry*>isaList = classDecl->getSymbolTable()->getClassRec();
		for (ClassEntry* isa : isaList) {
			if (classDecl->getSymbolRec()->name == isa->name) {
				outError("self inheritance", ((TokenAST*)classDecl->getChild(0))->getToken().getLine());
			}


			bool isaMatch = false;

			for (AST* classCompare : children) {
				if (classCompare->getSymbolRec()->name == isa->name) {

					if (recStack.count(isa->name)) {
						continue;
					}
					isa->link = classCompare->getSymbolTable();
					isaMatch = true;
				}
			}
			if (!isaMatch) {
				outError("ISA unmatched" + isa->name, ((TokenAST*)classDecl->getChild(0))->getToken().getLine());
			}
		}
	}
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
	v->setSymbolRec(classEntry);
	if (children.size() == 3) {
		classEntry->name = children[0]->getData();

		std::vector<AST*>istList = children[1]->getChildren();

		for (AST* ist : istList) {
			table->insertRec(ist->getSymbolRec());
		}

		std::vector<AST*>classDeclBody = children[2]->getChildren();
		for (AST* visMemberDecl : classDeclBody) {
			table->insertRec(visMemberDecl->getSymbolRec());
		}
	}
	else if (children.size() == 2) {
		classEntry->name = children[0]->getData();

		std::vector<AST*>classDeclBody = children[1]->getChildren();
		for (AST* visMemberDecl : classDeclBody) {
			table->insertRec(visMemberDecl->getChildren().back()->getSymbolRec());
		}
	}


}
void SymbolTableVisitor::visit(ClassList* v) {}
void SymbolTableVisitor::visit(Expr* v) {}
void SymbolTableVisitor::visit(ExtraExpr* v) {}
void SymbolTableVisitor::visit(FuncBody* v) {
	/*
	std::vector<AST*>children = v->getChildren();
	std::vector<AST*>varDeclList;
	if (children[0] != nullptr) {
		std::vector<AST*>localVarDeclchildren = children[0]->getChildren();

		for (size_t i = 0; i < localVarDeclchildren.size(); i++) {
			if (dynamic_cast<VarDecl*>(localVarDeclchildren[i])) {
				varDeclList.push_back(localVarDeclchildren[i]);
			}

		}
		for (AST* varDecl : varDeclList) {
			for (AST* varDeclComp : varDeclList) {
				if (varDecl != varDeclComp && varDecl->getSymbolRec()->name == varDeclComp->getSymbolRec()->name) {
					outError("Muktiple Declared data member" + varDecl->getSymbolRec()->name, 0);
				}
			}
		}
	}*/
}
void SymbolTableVisitor::visit(FuncDecl* v) {
	std::vector<AST*>children = v->getChildren();
	std::vector<AST*>fHeadChildren = children[0]->getChildren();
	FunctionEntry* fEntry = SymbolTableHelper::createSymbolFunctionRec();
	FunctionEntry* fHead = SymbolTableHelper::createSymbolFunctionRec();
	v->setSymbolRec(fEntry);
	
	if (fHeadChildren.size() == 3) {
		fEntry->name = fHeadChildren[0]->getData();
		fEntry->returnType = fHeadChildren[2]->getData();

		for (AST* fParam : fHeadChildren[1]->getChildren()) {
			ParamEntry* param = ((ParamEntry*)fParam->getSymbolRec());
			fEntry->paramList.push_back(std::make_tuple(param->type, param->name, param->arrInd));
		}



	}
}
void SymbolTableVisitor::visit(FuncDef* v) {
	std::vector<AST*>children = v->getChildren();
	FunctionEntry* fEntry = SymbolTableHelper::createSymbolFunctionRec();
	SymbolTable* symbolTable = SymbolTableHelper::createSymbolTable();
	fEntry->link = symbolTable;
	v->setSymbolTable(symbolTable);
	v->setSymbolRec(fEntry);

	if (children.size() == 2) {
		std::vector<AST*>fHeadChildren = children[0]->getChildren();
		std::vector<AST*>localVarDeclOrStatList = children[1]->getChildren();
		std::vector<AST*>varDeclList;

		if (localVarDeclOrStatList.size() > 0) {
			std::vector<AST*>statementOrVar=localVarDeclOrStatList[0]->getChildren();
			for (size_t i = 0; i < statementOrVar.size(); i++) {
				if (dynamic_cast<LocalVarDecl*>(statementOrVar[i])) {
					varDeclList.push_back(statementOrVar[i]->getChild(0));
				}
			}

		}
		if (fHeadChildren.size() == 3) {
			fEntry->name = fHeadChildren[0]->getData();
			fEntry->returnType = fHeadChildren[2]->getData();

			for (AST* fParam : fHeadChildren[1]->getChildren()) {
				symbolTable->insertRec(fParam->getSymbolRec());
				ParamEntry* param = ((ParamEntry*)fParam->getSymbolRec());
				fEntry->paramList.push_back(std::make_tuple(param->type, param->name, param->arrInd));
			}

		}
		else if (fHeadChildren.size() == 2) {
			fEntry->name = fHeadChildren[0]->getData();
			fEntry->returnType = fHeadChildren[1]->getData();
			
		}

		for (AST* stat : varDeclList) {
			symbolTable->insertRec((stat->getSymbolRec()));
		}
	}
	
}
void SymbolTableVisitor::visit(FuncDefList* v) {}
void SymbolTableVisitor::visit(FuncHead* v) {}
void SymbolTableVisitor::visit(IfStat* v) {}
void SymbolTableVisitor::visit(ImplBody* v) {}
void SymbolTableVisitor::visit(ImplDef* v) {
	std::vector<AST*>children = v->getChildren();
	ImplementationEntry* implEntry = SymbolTableHelper::createSymbolImplementationRec();
	SymbolTable* symbolTable = SymbolTableHelper::createSymbolTable();
	implEntry->link = symbolTable;
	v->setSymbolTable(symbolTable);
	v->setSymbolRec(implEntry);

	if (children.size() == 2) {
		implEntry->name = children[0]->getData();

		std::vector<AST*>implBodyChildren = children[1]->getChildren();

		for (AST* funcDef : implBodyChildren) {
			symbolTable->insertRec(funcDef->getSymbolRec());
		}
	}
}
void SymbolTableVisitor::visit(ImplDefList* v) {}
void SymbolTableVisitor::visit(ISA* v) {}
void SymbolTableVisitor::visit(ISAList* v) {
	std::vector<AST*>children = v->getChildren();
	if (children.size() > 0) {
		for (AST* child : children) {
			ClassEntry* classEntry = SymbolTableHelper::createSymbolClassRec();
			classEntry->name = child->getData();
			child->setSymbolRec(classEntry);
		}
	}
}
void SymbolTableVisitor::visit(LocalVarDecl* v) {}
void SymbolTableVisitor::visit(LocalVarDeclList* v) {
	std::vector<AST*>children = v->getChildren();
	std::vector<AST*>varDeclList;
	std::unordered_set<std::string>multi_var;
		for (size_t i = 0; i < children.size(); i++) {
			std::vector<AST*>localVar = children[i]->getChildren();
			if (dynamic_cast<VarDecl*>(localVar[0])) {
				varDeclList.push_back(localVar[0]);
			}

		}
		for (AST* varDecl : varDeclList) {
			for (AST* varDeclComp : varDeclList) {
				if (varDecl != varDeclComp && varDecl->getSymbolRec()->name == varDeclComp->getSymbolRec()->name 
					&& multi_var.count(varDecl->getSymbolRec()->name)==0) {
					multi_var.insert(varDecl->getSymbolRec()->name);
					outError("Multiple Declared data member: " + varDecl->getSymbolRec()->name, ((TokenAST*)varDeclComp->getChild(1))->getToken().getLine());
				}
			}
		}
	

}
void SymbolTableVisitor::visit(MemberList* v) {}
void SymbolTableVisitor::visit(MemDecl* v) {}
void SymbolTableVisitor::visit(Prog* v) {
	std::vector<AST*>children = v->getChildren();

	SymbolTable* progTable = SymbolTableHelper::createSymbolTable();
	v->setSymbolTable(progTable);

	if (children.size() == 1) {
		std::vector<AST*>classImplFuncList = children[0]->getChildren();
		std::vector<AST*>classList;
		std::vector<AST*>implementationList;
		std::vector<AST*>functionList;

		for (AST* classImplFunc : classImplFuncList) {
			if (dynamic_cast<ClassDecl*>(classImplFunc)){
				classList.push_back(classImplFunc);
			}
			else if (dynamic_cast<FuncDef*>(classImplFunc)) {
				functionList.push_back(classImplFunc);
			}
			else if (dynamic_cast<ImplDef*>(classImplFunc)) {
				implementationList.push_back(classImplFunc);
			}
		}
		for (AST* classDecl : classList) {
			progTable->insertRec(classDecl->getSymbolRec());
		}
		
		for (AST* function : functionList) {
			FunctionEntry* functionSymbol = (FunctionEntry*)(function->getSymbolRec());
			//function Overload
			std::vector<FunctionEntry*>res = progTable->findFunctionRec(functionSymbol->name);

			for (FunctionEntry* func : res) {
				//int line = ((TokenAST*)classOrImplOrFunc->getChild(0)->getChild(0)->)
				if (func->compare(functionSymbol)) {
					outError("[ERROR] Redefinition of Function: " + functionSymbol->name, ((TokenAST*)function->getChild(0)->getChild(0))->getToken().getLine());
				}
				else {
					outError("[WARNING] Overloading of Function: " + functionSymbol->name, ((TokenAST*)function->getChild(0)->getChild(0))->getToken().getLine());
				}
			}
			progTable->insertRec(function->getSymbolRec());
		}
			
		for (AST* implementation : implementationList) {
			ImplementationEntry* implementationSymbol = (ImplementationEntry*)(implementation->getSymbolRec());
			if (implementationSymbol) {
				SymbolTable* ImplTable = implementationSymbol->link;

				ClassEntry* classSymbol = progTable->findClassRec(implementationSymbol->name);

				if (classSymbol != nullptr) {
					SymbolTable* classTable = classSymbol->link;

					std::vector<FunctionEntry*>funcDefs = ImplTable->getFuncRec();
					FunctionEntry* tempFunc = nullptr;
					if (funcDefs.size() > 0) {
						for (FunctionEntry* funcDef : funcDefs) {
							tempFunc = funcDef;
							bool matchFound = false;
							std::vector<FunctionEntry*>matchFunc = classTable->findFunctionRec(funcDef->name);
							if (matchFunc.size() > 0) {
								for (FunctionEntry* overloadOrMatch : matchFunc) {
									if (funcDef->compare(overloadOrMatch)) {
										overloadOrMatch->link = funcDef->link;
										matchFound = true;
									}
									funcDef->contClass = classTable;
									implementationSymbol->contClass = classTable;
								}
								if (!matchFound) {
									outError("Function Defined but not Declared" + funcDef->name, 0);
								}
							}
							else {
								outError("Function Defined but not declared" + tempFunc->name, 0);
							}
						}
					}
					else {
						outError("Empty Implementation", 0);
					}
				}
				else {
					outError("Function definition for undeclared class", 0);
				}
				
			}
		}
			
			
		
		
		for (AST* classDecl : classList) {
			std::vector<FunctionEntry*>memberFunctions = classDecl->getSymbolTable()->getFuncRec();

			for (FunctionEntry* memberFunc : memberFunctions) {
				if (memberFunc->link == nullptr) {
					outError("Function Definition Not found: " + classDecl->getSymbolRec()->name + " " + memberFunc->name, ((TokenAST*)classDecl->getChild(0))->getToken().getLine());
				}
			}
			SymbolTable* classSymbolTable = classDecl->getSymbolTable();

			std::vector<ClassEntry*>classRecs = classSymbolTable->getClassRec();
			std::vector<FunctionEntry*>funcRecs = classSymbolTable->getFuncRec();
			std::vector<VariableEntry*>varRecs = classSymbolTable->getVarRec();

			for (ClassEntry* classRecord : classRecs) {
				if (classRecord->link == nullptr) {
					continue;
				}
				for (VariableEntry* varRecord : varRecs) {
					VariableEntry* shadowRec = classRecord->link->findVariableRec(varRecord->name);

					if (shadowRec) {
						outError("Shadow Inherited Member variable: " + classDecl->getSymbolRec()->name + "::" + varRecord->name + "::" + classRecord->name + " " + shadowRec->name, ((TokenAST*)classDecl->getChild(0))->getToken().getLine());
					}
				}
				for (FunctionEntry* funcRecord : funcRecs) {
					std::vector<FunctionEntry*> shadowRec = classRecord->link->findFunctionRec(funcRecord->name);

					for (FunctionEntry* shadow : shadowRec) {
						if (funcRecord->compare(shadow)) {
							outError("Shadow Member Function: " + classDecl->getSymbolRec()->name + " " + funcRecord->name + "Shadows" + classRecord->name + " " + shadow->name, ((TokenAST*)classDecl->getChild(0))->getToken().getLine());
						}
					}
				}
			}

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
		variableRec->name = children[0]->getData();
		variableRec->type = children[1]->getData();
	}
	else if (children.size()== 3) {
		variableRec->name = children[0]->getData();
		variableRec->type = children[1]->getData();

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
	//Temporary Solution, remove ATTRDECL later;
	
	VisibilityEntry* record = nullptr;
	if (children.size() == 2) {
		if (dynamic_cast<AttrDecl*>(children[1])) {
			std::vector<AST*>varDecl = children[1]->getChildren();
			record = (VisibilityEntry*)(varDecl[0]->getSymbolRec());
		}
		else {
			record = (VisibilityEntry*)(children[1]->getSymbolRec());
		}
		record->visibility = children[0]->getData();

	}
	v->setSymbolRec(record);
}
void SymbolTableVisitor::visit(WhileStat* v) {}
void SymbolTableVisitor::visit(WriteStat* v) {}
void SymbolTableVisitor::visit(VisMemberDeclList* v) {
	std::vector<AST*>children = v->getChildren();
	std::vector<AST*>varDeclList;
	std::unordered_set<std::string>multi_var;
	for (size_t i = 0; i < children.size(); i++) {
		std::vector<AST*>attrDecl = children[i]->getChildren();
		std::vector<AST*>varDecl = attrDecl[1]->getChildren();
		if (dynamic_cast<VarDecl*>(varDecl[0])) {
			varDeclList.push_back(varDecl[0]);
		}

	}
	for (AST* varDecl : varDeclList) {
		for (AST* varDeclComp : varDeclList) {
			if (varDecl != varDeclComp && varDecl->getSymbolRec()->name == varDeclComp->getSymbolRec()->name
				&& multi_var.count(varDecl->getSymbolRec()->name) == 0) {
				multi_var.insert(varDecl->getSymbolRec()->name);
				outError("Multiple Declared class member: " + varDecl->getSymbolRec()->name, ((TokenAST*)varDeclComp->getChild(1))->getToken().getLine());
			}
		}
	}
	
}
void SymbolTableVisitor::visit(fParamsList* v) {}
void SymbolTableVisitor::visit(fParams* v) {
	std::vector<AST*>children = v->getChildren();
	ParamEntry* par = SymbolTableHelper::createSymbolParamRec();

	if (children.size() == 2) {
		par->name = children[0]->getData();
		par->type = children[1]->getData();
	}
	else if (children.size() == 3) {
		par->name = children[0]->getData();
		par->type = children[1]->getData();

		std::vector<int>arrDimension;
		std::vector<AST*>indicelist = children[2]->getChildren();

		for (AST* dim : indicelist) {
			std::vector<AST*>indice = dim->getChildren();
			if (indice.size() == 0) {
				arrDimension.push_back(-1);
			}
			else if (indice.size() == 1) {
				arrDimension.push_back(std::stoi(indice[0]->getData()));
			}
		}
		par->arrInd = arrDimension;
	}
	v->setSymbolRec(par);
}
void SymbolTableVisitor::visit(ArraySize* v) {}
void SymbolTableVisitor::visit(ArraySizeList* v) {}
void SymbolTableVisitor::visit(Variable* v) {
	v->setData(v->getChild(0)->getData());
}
void SymbolTableVisitor::visit(AssignStat* v) {}
void SymbolTableVisitor::visit(FuncCall* v) {}
void SymbolTableVisitor::visit(IndiceList* v) {}
void SymbolTableVisitor::visit(Indice* v) {}
void SymbolTableVisitor::visit(Self* v){}