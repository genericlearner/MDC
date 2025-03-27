#include "TypeCheckingVisitor.h"
#include "SymbolTableHelper.h"


TypeCheckingVisitor::TypeCheckingVisitor() {

}
void TypeCheckingVisitor::visit(CompositeConceptAST* v) {}

void TypeCheckingVisitor::visit(IntLit* v) {}
void TypeCheckingVisitor::visit(FloatLit* v) {}
void TypeCheckingVisitor::visit(FloatID* v) {}
void TypeCheckingVisitor::visit(IntegerID* v) {}
void TypeCheckingVisitor::visit(ID* v) {}
void TypeCheckingVisitor::visit(Void* v) {}
void TypeCheckingVisitor::visit(Public* v) {}
void TypeCheckingVisitor::visit(Private* v) {}
void TypeCheckingVisitor::visit(EqTo* v) {}
void TypeCheckingVisitor::visit(NotEqTo* v) {}
void TypeCheckingVisitor::visit(Not* v){}
void TypeCheckingVisitor::visit(LessThan* v) {}
void TypeCheckingVisitor::visit(LessThanOrEqTo* v) {}
void TypeCheckingVisitor::visit(GreaterThan* v) {}
void TypeCheckingVisitor::visit(GreaterThanOrEqTo* v) {}
void TypeCheckingVisitor::visit(Add* v) {}
void TypeCheckingVisitor::visit(Subt* v) {}
void TypeCheckingVisitor::visit(Multiply* v) {}
void TypeCheckingVisitor::visit(Divide* v) {}
void TypeCheckingVisitor::visit(Or* v) {}
void TypeCheckingVisitor::visit(And* v) {}
void TypeCheckingVisitor::visit(Period* v) {}
void TypeCheckingVisitor::visit(Assign* v) {}
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
void TypeCheckingVisitor::visit(ReturnStat* v) {}
void TypeCheckingVisitor::visit(SignFactor* v) {}
void TypeCheckingVisitor::visit(Sign* v) {}
void TypeCheckingVisitor::visit(StatBlock* v) {}
void TypeCheckingVisitor::visit(Statement* v) {}
void TypeCheckingVisitor::visit(StatementList* v) {}
void TypeCheckingVisitor::visit(Term* v) {}
void TypeCheckingVisitor::visit(VarDecl* v) {}
void TypeCheckingVisitor::visit(Visibility* v) {}
void TypeCheckingVisitor::visit(VisMemberDecl* v) {}
void TypeCheckingVisitor::visit(WhileStat* v) {}
void TypeCheckingVisitor::visit(WriteStat* v) {}
void TypeCheckingVisitor::visit(VisMemberDeclList* v) {}
void TypeCheckingVisitor::visit(fParamsList* v) {}
void TypeCheckingVisitor::visit(fParams* v) {}
void TypeCheckingVisitor::visit(ArraySize* v) {}
void TypeCheckingVisitor::visit(ArraySizeList* v) {}
void TypeCheckingVisitor::visit(Variable* v) {}
void TypeCheckingVisitor::visit(AssignStat* v) {}
void TypeCheckingVisitor::visit(FuncCall* v) {}
void TypeCheckingVisitor::visit(IndiceList* v) {}
void TypeCheckingVisitor::visit(Indice* v) {}
void TypeCheckingVisitor::visit(Self* v){}