#pragma once
#include "Add.h"
#include "addFactorList.h"
#include "addOp.h"
#include "addTermArithExpr.h"
#include "addTermList.h"
#include "And.h"
#include "APaaramsList.h"
#include "arithExpr.h"
#include "ArraySize.h"
#include "ArraySizeList.h"
#include "Assign.h"
#include "AssignStat.h"
#include "AST.h"
#include "ASTFactory.h"
#include "attrDecl.h"
#include "classDecl.h"
#include "ClassImplFunc.h"
#include "ClassImplFuncList.h"
#include "classList.h"
#include "compositeConcept.h"
#include "compositeConceptToken.h"
#include "Divide.h"
#include "EQTO.h"
#include "expr.h"
#include "extraExpr.h"
#include "factor.h"
#include "floatID.h"
#include "floatLit.h"
#include "fParams.h"
#include "fParamsList.h"
#include "funcBody.h"
#include "FuncCall.h"
#include "funcDecl.h"
#include "funcDef.h"
#include "funcDefList.h"
#include "funcHead.h"
#include "GreaterThan.h"
#include "GreaterThanOrEQTO.h"
#include "ID.h"
#include "ifStat.h"
#include "implBody.h"
#include "implDef.h"
#include "implDeflist.h"
#include "Indice.h"
#include "IndiceList.h"
#include "IntegerID.h"
#include "intLit.h"
#include "isa.h"
#include "isaList.h"
#include "LessThan.h"
#include "LessthanOrEQTO.h"
#include "localVarDecl.h"
#include "localVarDeclList.h"
#include "memberList.h"
#include "memDecl.h"
#include "Multiply.h"
#include "multOp.h"
#include "Not.h"
#include "NotEQTO.h"
#include "notFactor.h"
#include "Or.h"
#include "Period.h"
#include "Private.h"
#include "prog.h"
#include "Public.h"
#include "readStat.h"
#include "recFactor.h"
#include "relExpr.h"
#include "relOp.h"
#include "returnStat.h"
#include "Self.h"
#include "sign.h"
#include "signFactor.h"
#include "Start.h"
#include "statBlock.h"
#include "statement.h"
#include "statementlist.h"
#include "Subt.h"
#include "term.h"
#include "tokenAST.h"
#include "varDecl.h"
#include "Variable.h"
#include "visibility.h"
#include "visMemberDecl.h"
#include "visMemberDeclList.h"
#include "Void.h"
#include "whileStat.h"
#include "writeStat.h"

#include <string>
#include <vector>
class Visitor {
	std::vector<std::string> errors;

	
public:
	virtual void visit(CompositeConceptAST* v) = 0;

	virtual void visit(IntLit* v) = 0;
	virtual void visit(FloatLit* v) = 0;
	virtual void visit(FloatID* v) = 0;
	virtual void visit(IntegerID* v) = 0;
	virtual void visit(ID* v) = 0;
	virtual void visit(Void* v) = 0;
	virtual void visit(Public* v) = 0;
	virtual void visit(Private* v) = 0;
	virtual void visit(EqTo* v) = 0;
	virtual void visit(NotEqTo* v) = 0;
	virtual void visit(LessThan* v) = 0;
	virtual void visit(LessThanOrEqTo* v) = 0;
	virtual void visit(GreaterThan* v) = 0;
	virtual void visit(GreaterThanOrEqTo* v) = 0;
	virtual void visit(Add* v) = 0;
	virtual void visit(Subt* v) = 0;
	virtual void visit(Multiply* v) = 0;
	virtual void visit(Divide* v) = 0;
	virtual void visit(Or* v) = 0;
	virtual void visit(And* v) = 0;
	virtual void visit(Period* v) = 0;
	virtual void visit(Assign* v) = 0;
	virtual void visit(Start* v) = 0;
	virtual void visit(ClassImplFunc* v) = 0;
	virtual void visit(ClassImplFuncList* v) = 0;
	virtual void visit(addOp* v) = 0;
	virtual void visit(addTermList* v) = 0;
	virtual void visit(AParamsList* v) = 0;
	virtual void visit(ArithExpr* v) = 0;
	virtual void visit(AttrDecl* v) = 0;
	virtual void visit(ClassDecl* v) = 0;
	virtual void visit(ClassList* v) = 0;
	virtual void visit(Expr* v) = 0;
	virtual void visit(ExtraExpr* v) = 0;
	virtual void visit(FuncBody* v) = 0;
	virtual void visit(FuncDecl* v) = 0;
	virtual void visit(FuncDef* v) = 0;
	virtual void visit(FuncDefList* v) = 0;
	virtual void visit(FuncHead* v) = 0;
	virtual void visit(IfStat* v) = 0;
	virtual void visit(ImplBody* v) = 0;
	virtual void visit(ImplDef* v) = 0;
	virtual void visit(ImplDefList* v) = 0;
	virtual void visit(ISA* v) = 0;
	virtual void visit(ISAList* v) = 0;
	virtual void visit(LocalVarDecl* v) = 0;
	virtual void visit(LocalVarDeclList* v) = 0;
	virtual void visit(MemberList* v) = 0;
	virtual void visit(MemDecl* v) = 0;
	virtual void visit(Prog* v) = 0;
	virtual void visit(ReadStat* v) = 0;
	virtual void visit(ReturnStat* v) = 0;
	virtual void visit(SignFactor* v) = 0;
	virtual void visit(Sign* v) = 0;
	virtual void visit(StatBlock* v) = 0;
	virtual void visit(Statement* v) = 0;
	virtual void visit(StatementList* v) = 0;
	virtual void visit(Term* v) = 0;
	virtual void visit(VarDecl* v) = 0;
	virtual void visit(Visibility* v) = 0;
	virtual void visit(VisMemberDecl* v) = 0;
	virtual void visit(WhileStat* v) = 0;
	virtual void visit(WriteStat* v) = 0;
	virtual void visit(VisMemberDeclList* v) = 0;
	virtual void visit(fParamsList* v) = 0;
	virtual void visit(fParams* v) = 0;
	virtual void visit(ArraySize* v) = 0;
	virtual void visit(ArraySizeList* v) = 0;
	virtual void visit(Variable* v) = 0;
	virtual void visit(AssignStat* v) = 0;
	virtual void visit(FuncCall* v) = 0;
	virtual void visit(IndiceList* v) = 0;
	virtual void visit(Indice* v) = 0;

	void outError(std::string err, int line);
	std::vector<std::string> getError() { return errors; }
};