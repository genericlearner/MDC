#include "CreateTempVariablesVisitor.h"
#include "SymbolTableHelper.h"

std::string CreateTempVariablesVisitor::generateTempVariableName() {
	return 't' + std::to_string(tempVariableCount++);
}
void CreateTempVariablesVisitor::visit(CompositeConceptAST* v) {}

void CreateTempVariablesVisitor::visit(IntLit* v) {}
void CreateTempVariablesVisitor::visit(FloatLit* v) {}
void CreateTempVariablesVisitor::visit(FloatID* v) {}
void CreateTempVariablesVisitor::visit(IntegerID* v) {}
void CreateTempVariablesVisitor::visit(ID* v) {}
void CreateTempVariablesVisitor::visit(Void* v) {}
void CreateTempVariablesVisitor::visit(Public* v) {}
void CreateTempVariablesVisitor::visit(Private* v) {}
void CreateTempVariablesVisitor::visit(EqTo* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(NotEqTo* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Not* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(LessThan* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(LessThanOrEqTo* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(GreaterThan* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(GreaterThanOrEqTo* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Add* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Subt* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Multiply* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Divide* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Or* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(And* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(Period* v) {}
void CreateTempVariablesVisitor::visit(Assign* v) {}
void CreateTempVariablesVisitor::visit(Start* v) {}
void CreateTempVariablesVisitor::visit(ClassImplFunc* v) {}
void CreateTempVariablesVisitor::visit(ClassImplFuncList* v) {}
void CreateTempVariablesVisitor::visit(addOp* v) {}
void CreateTempVariablesVisitor::visit(addTermList* v) {}
void CreateTempVariablesVisitor::visit(AParamsList* v) {}
void CreateTempVariablesVisitor::visit(ArithExpr* v) {}
void CreateTempVariablesVisitor::visit(AttrDecl* v) {}
void CreateTempVariablesVisitor::visit(ClassDecl* v) {}
void CreateTempVariablesVisitor::visit(ClassList* v) {}
void CreateTempVariablesVisitor::visit(Expr* v) {}
void CreateTempVariablesVisitor::visit(ExtraExpr* v) {}
void CreateTempVariablesVisitor::visit(FuncBody* v) {}
void CreateTempVariablesVisitor::visit(FuncDecl* v) {}
void CreateTempVariablesVisitor::visit(FuncDef* v) {}
void CreateTempVariablesVisitor::visit(FuncDefList* v) {}
void CreateTempVariablesVisitor::visit(FuncHead* v) {}
void CreateTempVariablesVisitor::visit(IfStat* v) {}
void CreateTempVariablesVisitor::visit(ImplBody* v) {}
void CreateTempVariablesVisitor::visit(ImplDef* v) {}
void CreateTempVariablesVisitor::visit(ImplDefList* v) {}
void CreateTempVariablesVisitor::visit(ISA* v) {}
void CreateTempVariablesVisitor::visit(ISAList* v) {}
void CreateTempVariablesVisitor::visit(LocalVarDecl* v) {}
void CreateTempVariablesVisitor::visit(LocalVarDeclList* v) {}
void CreateTempVariablesVisitor::visit(MemberList* v) {}
void CreateTempVariablesVisitor::visit(MemDecl* v) {}
void CreateTempVariablesVisitor::visit(Prog* v) {}
void CreateTempVariablesVisitor::visit(ReadStat* v) {}
void CreateTempVariablesVisitor::visit(ReturnStat* v) {}
void CreateTempVariablesVisitor::visit(SignFactor* v) {}
void CreateTempVariablesVisitor::visit(Sign* v) {}
void CreateTempVariablesVisitor::visit(StatBlock* v) {}
void CreateTempVariablesVisitor::visit(Statement* v) {}
void CreateTempVariablesVisitor::visit(StatementList* v) {}
void CreateTempVariablesVisitor::visit(Term* v) {}
void CreateTempVariablesVisitor::visit(VarDecl* v) {}
void CreateTempVariablesVisitor::visit(Visibility* v) {}
void CreateTempVariablesVisitor::visit(VisMemberDecl* v) {}
void CreateTempVariablesVisitor::visit(WhileStat* v) {}
void CreateTempVariablesVisitor::visit(WriteStat* v) {}
void CreateTempVariablesVisitor::visit(VisMemberDeclList* v) {}
void CreateTempVariablesVisitor::visit(fParamsList* v) {}
void CreateTempVariablesVisitor::visit(fParams* v) {}
void CreateTempVariablesVisitor::visit(ArraySize* v) {}
void CreateTempVariablesVisitor::visit(ArraySizeList* v) {}
void CreateTempVariablesVisitor::visit(Variable* v) {}
void CreateTempVariablesVisitor::visit(AssignStat* v) {}
void CreateTempVariablesVisitor::visit(FuncCall* v) {
	std::string tempVarName = generateTempVariableName();
	v->setAssemblyData(tempVarName);

	TempEntry* tempEntry = SymbolTableHelper::createSymbolTempRec();
	tempEntry->name = tempVarName;
	v->setType("int");
	tempEntry->type = v->getType();

	v->insertIntoTable(tempEntry);
}
void CreateTempVariablesVisitor::visit(IndiceList* v) {}
void CreateTempVariablesVisitor::visit(Indice* v) {}
void CreateTempVariablesVisitor::visit(Self* v) {}