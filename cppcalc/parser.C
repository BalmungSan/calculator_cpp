#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
	  delete tree;
   } catch (...) {}
}

string Parser::parse(istream* in, bool isEwe) {
   setScanner(in);
   return Prog(isEwe);
}

string Parser::Prog(bool isEwe) {
   string result = Stmts(isEwe);
   
   if (result.empty()){
      Token* t = scan->getToken();
	  
      if (t->getType() != eof) {
         cout << "Syntax Error: Expected '<EOF>', found token at column " << t->getCol() << endl;
         throw ParseError;
      }
	  
	  result = "<EOF>";
   }

   return result;
}

// Código para la gramatica módificada (Stmts, Stmt)
string Parser::Stmts(bool isEwe){
   Token* t = scan->getToken();
   string result = "";
   
   if (t->getType() == identifier){
      RootNode* Tree = Stmt(t->getLex());
	  setTree(Tree);
	  
	  if(isEwe){
	    result = Tree->ewe();
	  } else {
	    result = Tree->printResult();
	  }
   } else {
      scan->putBackToken();
   }
   
   return result;
}

RootNode* Parser::Stmt(string variableName){
   Token* t = scan->getToken();
   
   if (t->getType() == equals){
     RootNode* raiz = new EqualsNode(new VariableNode(variableName), Expr());
     Token* t = scan->getToken();
		 
     if (t->getType() == eoe){
       Token* t = scan->getToken();
		 
       if (t->getType() != eol){
	     cout << "Syntax Error: Expected '<eol>' "
	          << "found: " << t->getType()
	          << " at col: " << t->getCol()
	          << endl;
	     throw ParseError;
       }
     } else {
       cout << "Syntax Error: Expected '<eoe>' "
	    << "found: " << t->getType()
	    << " at col: " << t->getCol()
	    << endl;
       throw ParseError;
     }
	  
     return raiz;
   } else { 
     cout << "Syntax Error: Expected '=' "
	  << "found: " << t->getType()
	  << " at col: " << t->getCol()
	  << endl;
		   
     throw ParseError;
   }
}
//-----------------------------------------------
   
AST* Parser::Expr() {
   return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == add) {
      return RestExpr(new AddNode(e,Term()));
   }

   if (t->getType() == sub)
      return RestExpr(new SubNode(e,Term()));

   scan->putBackToken();

   return e;
}

AST* Parser::Term(){
  return RestTerm(Storable());
}

AST* Parser::RestTerm(AST* e) {
  Token* t = scan->getToken();

   if (t->getType() == times) {
      return RestTerm(new TimesNode(e,Storable()));
   }

   if (t->getType() == divide)
     return RestTerm(new DivideNode(e,Storable()));


   if (t->getType() == mod) {
     return RestTerm(new ModNode(e,Storable()));
   }
  
   scan->putBackToken();

   return e;
}

AST* Parser::Storable() {
  return MemOperation(Factor());
}

//Se agrega el metodo MemOperation (Implementación)
AST* Parser::MemOperation(AST* f){
   Token *t = scan->getToken();
   
   if (t->getType() == keyword)
   {
      if (t->getLex().compare("S") == 0) {
	     return new StoreNode(f);
	  } else if (t->getLex().compare("M") == 0) {
	     return new MinusMemoryNode(f);
	  } else if (t->getLex().compare("P") == 0) {
	     return new PlusMemoryNode(f);
	  } else {
	     cout << "Expected '<MemOperation>' " 
	       << "found: " << t->getType()
	       << " at col: " << t->getCol()
	       << endl;
		 throw ParseError;
	  }
   }
   
   scan->putBackToken();
   return f;
}
//-----------------------------------------------

AST* Parser::Factor() {
  Token *t = scan->getToken();
  
  if (t->getType() == number) {
     istringstream in(t->getLex());
     int val;
     in >> val;
     return new NumNode(val);
  }
  
  if (t->getType() == identifier){
     istringstream in(t->getLex());
     string var;
     in >> var;
	 return new VariableNode(var);
  }
  
  if(t->getType() == keyword){

    if(t->getLex().compare("R") == 0){
      return new RecallNode();
    } else if (t->getLex().compare("C") == 0){
	  return new ClearMemoryNode();
	} else{
      cout << "Expected 'R' or 'C' " 
	       << "found: " << t->getType()
	       << " at col: " << t->getCol()
	       << endl;
      throw ParseError;
    }
  }
  
  if(t->getType() == lparen){
    AST *result = Expr();
    t = scan->getToken();
    
    if(t->getType() == rparen){
      return result;
    }
    else{
      cout << "Expected ) " 
	   << "found: " << t->getType()
	   << " at col: " << t->getCol()
	   << endl;
      throw ParseError;
    }
	
	scan->putBackToken();
  }
  
  scan->putBackToken();
  cout << "Expected '<Factor>' " 
       << "found: " << t->getType()
       << " at col: " << t->getCol()
       << endl;
  throw ParseError;
}

//Metodo para cambiar el scaner por la nueva linea (Implementación)
void Parser::setScanner (istream* in){
   scan = new Scanner(in);
}
//-----------------------------------------------

//Se agregan los metodos para el manejo del arbol (Implementación)
void Parser::setTree(RootNode* Tree){
   tree = Tree;
}

RootNode* Parser::getTree(){
   return tree;
}
//-----------------------------------------------

