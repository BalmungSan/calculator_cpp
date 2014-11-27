#pragma once
#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   string parse(istream* in, bool isEwe);
   //Se agregan los metodos para el manejo del arbol (Declaración)
   RootNode* getTree();
   void setTree(RootNode* Tree);
   //--------------------------------------------

 private:
   string Prog(bool isEwe);
   //Modificado la gramatica
   string Stmts(bool isEwe);
   RootNode* Stmt(string variableName);
   //--------------------------------------------
   AST* Expr();
   AST* RestExpr(AST* e);
   AST* Term();
   AST* RestTerm(AST* t);
   AST* Storable();
   
   //Se agrega el metodo para las operaciones de memoria (Declaración)
   AST* MemOperation(AST* f);
   //--------------------------------------------
  
    AST* Factor();
   //Agregamos el metodo para utilizar el parser con varias lineas (Declaración)
   void setScanner(istream* in);
   //--------------------------------------------

   Scanner* scan;
   RootNode* tree; //Se agrega el atributo para el control del arbol
};

