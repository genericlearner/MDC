#include "ASTFactory.h"
#include "addFactorList.h"
#include "addOp.h"
#include "addTermArithExpr.h"
#include "addTermList.h"
#include "arithExpr.h"
#include "attrDecl.h"
#include "classDecl.h"
#include "classList.h"
#include "expr.h"
#include "extraExpr.h"
#include "factor.h"
#include "floatLit.h"
#include "funcBody.h"
#include "funcDecl.h"
#include "funcDef.h"
#include "funcDefList.h"
#include "funcHead.h"
#include "ifStat.h"
#include "implBody.h"
#include "implDef.h"
#include "implDeflist.h"
#include "intLit.h"
#include "isa.h"
#include "isaList.h"
#include "localVarDecl.h"
#include "localVarDeclList.h"
#include "memberList.h"
#include "memDecl.h"
#include "multOp.h"
#include "notFactor.h"
#include "prog.h"
#include "readStat.h"
#include "recFactor.h"
#include "relExpr.h"
#include "relOp.h"
#include "returnStat.h"
#include "sign.h"
#include "signFactor.h"
#include "statBlock.h"
#include "statement.h"
#include "statementlist.h"
#include "term.h"
#include "varDecl.h"
#include "visibility.h"
#include "visMemberDecl.h"
#include "whileStat.h"
#include "writeStat.h"
#include "IntegerID.h"
#include "FloatID.h"
#include "Public.h"
#include "Private.h"
#include "intLit.h"
#include "floatLit.h"
#include "tokenAST.h"
#include "compositeConcept.h"
#include "Add.h"
#include "addFactorList.h"
#include "addOp.h"
#include "addTermArithExpr.h"
#include "addTermList.h"
#include "And.h"
#include "arithExpr.h"
#include "attrDecl.h"
#include "classDecl.h"
#include "classList.h"
#include "EQTO.h"
#include "expr.h"
#include "Divide.h"
#include "extraExpr.h"
#include "factor.h"
#include "funcBody.h"
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
#include "isa.h"
#include "isaList.h"
#include "LessThan.h"
#include "LessThanOrEQTO.h"
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
#include "parserUtility.h"
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
#include "statBlock.h"
#include "statement.h"
#include "statementlist.h"
#include "Subt.h"
#include "term.h"
#include "varDecl.h"
#include "visibility.h"
#include "visMemberDecl.h"
#include "Void.h"
#include "whileStat.h"
#include "writeStat.h"
#include "APaaramsList.h"
#include "Start.h"

std::vector<AST*>treesProduced;

AST* ASTFactory::makeNode(Token token) {
	switch (token.getType()) {
		case TokenType::INTEGER_VAL:
			treesProduced.push_back(new IntLit(token));
			break;

		case TokenType::FLOAT_VAL:
			treesProduced.push_back(new FloatLit(token));
			break;

		case TokenType::FLOAT_T:
			treesProduced.push_back(new FloatID(token));
			break;
		case TokenType::INT_T:
			treesProduced.push_back(new IntegerID(token));
			break;
		case TokenType::ID:
			treesProduced.push_back(new ID(token));
			break;
		case TokenType::VOID:
			treesProduced.push_back(new Void(token));
			break;
		case TokenType::PUBLIC:
			treesProduced.push_back(new Public(token));
			break;
		case TokenType::PRIVATE:
			treesProduced.push_back(new Private(token));
			break;
		case TokenType::EQ:
			treesProduced.push_back(new EqTo(token));
		case TokenType::NOTEQ:
			treesProduced.push_back(new NotEqTo(token));
			break;
		case TokenType::LT:
			treesProduced.push_back(new LessThan(token));
			break;
		case TokenType::LTEQ:
			treesProduced.push_back(new LessThanOrEqTo(token));
			break;
		case TokenType::GT:
			treesProduced.push_back(new GreaterThan(token));
			break;
		case TokenType::GTEQ:
			treesProduced.push_back(new GreaterThanOrEqTo(token));
			break;
		
		case TokenType::ADD:
			treesProduced.push_back(new Add(token));
			break;
		case TokenType::SUBT:
			treesProduced.push_back(new Subt(token));
			break;
		case TokenType::MULT:
			treesProduced.push_back(new Multiply(token));
			break;
		case TokenType::DIV:
			treesProduced.push_back(new Divide(token));
			break;
		case TokenType::OR:
			treesProduced.push_back(new Or(token));
			break;
		case TokenType::AND:
			treesProduced.push_back(new And(token));
			break;
		case TokenType::DOT:
			treesProduced.push_back(new Period(token));
			break;

	}
	return treesProduced.back();
}

AST* ASTFactory::makeNode(compositeConcept cc)
{
	switch (cc) {
	case compositeConcept::START:
		treesProduced.push_back(new Start(cc));
		break;
	case compositeConcept::ADDOP:
		treesProduced.push_back(new addOp(cc));
		break;
	case compositeConcept::ADDTERMLIST:
		treesProduced.push_back(new addTermList(cc));
		break;
	case compositeConcept::APARAMSLIST:
		treesProduced.push_back(new AParamsList(cc));
		break;
	case compositeConcept::ARITHEXPR:
		treesProduced.push_back(new ArithExpr(cc));
		break;
	case compositeConcept::ATTRDECL:
		treesProduced.push_back(new AttrDecl(cc));
		break;
	case compositeConcept::CLASSDECL:
		treesProduced.push_back(new ClassDecl(cc));
		break;
	case compositeConcept::CLASSLIST:
		treesProduced.push_back(new ClassList(cc));
		break;
	case compositeConcept::EXPR:
		treesProduced.push_back(new Expr(cc));
		break;
	case compositeConcept::EXPR2:
		treesProduced.push_back(new ExtraExpr(cc));
		break;
	case compositeConcept::FUNCBODY:
		treesProduced.push_back(new FuncBody(cc));
		break;
	case compositeConcept::FUNCDECL:
		treesProduced.push_back(new FuncDecl(cc));
		break;
	case compositeConcept::FUNCDEF:
		treesProduced.push_back(new FuncDef(cc));
		break;
	case compositeConcept::FUNCDEFLIST:
		treesProduced.push_back(new FuncDefList(cc));
		break;
	case compositeConcept::FUNCHEAD:
		treesProduced.push_back(new FuncHead(cc));
		break;
	case compositeConcept::IFSTAT:
		treesProduced.push_back(new IfStat(cc));
		break;
	case compositeConcept::IMPLBODY:
		treesProduced.push_back(new ImplBody(cc));
		break;
	case compositeConcept::IMPLDEF:
		treesProduced.push_back(new ImplDef(cc));
		break;
	case compositeConcept::IMPLDEFLIST:
		treesProduced.push_back(new ImplDefList(cc));
	case compositeConcept::ISA:
		treesProduced.push_back(new ISA(cc));
		break;
	case compositeConcept::ISALIST:
		treesProduced.push_back(new ISAList(cc));
		break;
	case compositeConcept::LOCALVARDECL:
		treesProduced.push_back(new LocalVarDecl(cc));
		break;
	case compositeConcept::LOCALVARDECLLIST:
		treesProduced.push_back(new LocalVarDeclList(cc));
		break;
	case compositeConcept::MEMBERLIST:
		treesProduced.push_back(new MemberList(cc));
		break;
	case compositeConcept::MEMDECL:
		treesProduced.push_back(new MemDecl(cc));
		break;
	case compositeConcept::NOTFACTOR:
		treesProduced.push_back(new NotFactor(cc));
		break;
	case compositeConcept::PROG:
		treesProduced.push_back(new Prog(cc));
		break;
	case compositeConcept::READSTAT:
		treesProduced.push_back(new ReadStat(cc));
		break;
	case compositeConcept::RETURNSTAT:
		treesProduced.push_back(new ReturnStat(cc));
		break;
	case compositeConcept::SIGNFACTOR:
		treesProduced.push_back(new SignFactor(cc));
		break;
	case compositeConcept::SIGN:
		treesProduced.push_back(new Sign(cc));
		break;
	case compositeConcept::STATBLOCK:
		treesProduced.push_back(new StatBlock(cc));
		break;
	case compositeConcept::STATEMENT:
		treesProduced.push_back(new Statement(cc));
		break;
	case compositeConcept::STATEMENTLIST:
		treesProduced.push_back(new StatementList(cc));
		break;
	case compositeConcept::TERM:
		treesProduced.push_back(new Term(cc));
		break;
	case compositeConcept::VARDECL:
		treesProduced.push_back(new VarDecl(cc));
		break;
	case compositeConcept::VISIBILITY:
		treesProduced.push_back(new Visibility(cc));
		break;
	case compositeConcept::VISMEMBERDECL:
		treesProduced.push_back(new VisMemberDecl(cc));
		break;
	case compositeConcept::WHILESTAT:
		treesProduced.push_back(new WhileStat(cc));
		break;
	case compositeConcept::WRITESTAT:
		treesProduced.push_back(new WriteStat(cc));
		break;
		/*
	case compositeConcept::VISMEMBERDECLLIST:
		treesProduced.push_back(new VisMemberDeclList(cc));
		break;
			
	case compositeConcept::FACTOR2:
		treesProduced.push_back(new factor2(cc);
		break;
		
	case compositeConcept::FPARAMSLIST:
		treesProduced.push_back(new fparamslist(cc));
		break;
		*/

	}
}

AST* ASTFactory::makeFamily(compositeConcept cc, std::vector<AST*> children) {
	AST* par = makeNode(cc);
	makeFamily(par, children);

	return par;

}
void ASTFactory::makeFamily(AST* par, std::vector<AST*>children) {
	AST* firstChild = nullptr;

	for (AST* child : children) {
		if (child) {
			if (!firstChild) {
				firstChild = child;
				continue;
			}
			firstChild->makeSiblings(child);
		}
	}

	if (firstChild) {
		par->adoptChild(firstChild);
	}
}