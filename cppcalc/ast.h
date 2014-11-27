#pragma once
#include <iostream>


using namespace std;

class AST {
 public:
   AST();
   virtual ~AST() = 0;
   virtual int evaluate() = 0;
   virtual string ewe() = 0;
};

class BinaryNode : public AST {
 public:
   BinaryNode(AST* left, AST* right);
   ~BinaryNode();

   AST* getLeftSubTree() const;
   AST* getRightSubTree() const;

 private:
   AST* leftTree;
   AST* rightTree;
};

class UnaryNode : public AST {
 public:
   UnaryNode(AST* sub);
   ~UnaryNode();

   AST* getSubTree() const;

 private:
   AST* subTree;
};

class AddNode : public BinaryNode {
 public:
   AddNode(AST* left, AST* right);
   
   int evaluate();
   string ewe();
};

class TimesNode: public BinaryNode {
 public:
  TimesNode(AST* left, AST* right);

  int evaluate();
  string ewe();
};

class SubNode : public BinaryNode {
 public:
   SubNode(AST* left, AST* right);

   int evaluate();
   string ewe();
};

class DivideNode: public BinaryNode {
 public:
  DivideNode(AST* left, AST* right);
  
  int evaluate();
  string ewe();
};

//Se Agrega la clase ModNode para manejar la operación modulo "%" (Declaración)
class ModNode: public BinaryNode{
 public:
  ModNode(AST* left, AST* right);
  
  int evaluate();
  string ewe();
};
//-----------------------------------------------

class NumNode : public AST {
 public:
   NumNode(int n);

   int evaluate();
   string ewe();
   int val;
};

class StoreNode : public UnaryNode {
 public:
  StoreNode(AST* sub);
  int evaluate();
  string ewe();
};

class RecallNode: public AST {
 public:
  RecallNode();
  int evaluate();
  string ewe();
};

// Nodos para Minus, Plus y Clear Memory
class MinusMemoryNode: public UnaryNode{
 public:
  MinusMemoryNode(AST* sub);
  int evaluate();
  string ewe();
};

class PlusMemoryNode: public UnaryNode{
 public:
  PlusMemoryNode(AST* sub);
  int evaluate();
  string ewe();
};

class ClearMemoryNode: public AST{
 public:
  ClearMemoryNode();
  int evaluate();
  string ewe();
};
//-----------------------------------------------

// Agregamos la clase VariableNode para manejar las variables (Declaración)
class VariableNode: public AST{
 public:
  VariableNode(string name);
  int evaluate();
  string ewe();
  string getName();
  void setName(int value);
 private:
  string name;
};
//-----------------------------------------------

//Agregamos la clase RootNode necesaría para distiguir la raiz de los nodos normales (Declaración)
class RootNode : public AST {
 public:
   RootNode(VariableNode* left, AST* right);
   ~RootNode();

   VariableNode* getLeftSubTree() const;
   AST* getRightSubTree() const;
   virtual string printResult() = 0;

 private:
   VariableNode* leftTree;
   AST* rightTree;
};
//----------------------------------------------- 

// Agregar Nodos de las variables

class EqualsNode: public RootNode{
 public:
  EqualsNode(VariableNode* left, AST* right);
  int evaluate();
  string ewe();
  string printResult();
};
//-----------------------------------------------

