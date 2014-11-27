#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <sstream>

// for debug information uncomment
//#define debug

//Clase AST.C, acá se inicializan e instancian las variables de los operadores y diferentes nodos, para las diferentes funciones de la calculadora
//se agregaron las funciones EWE para cuando la calculadora esté en modo EWE

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
  AST(),
  leftTree(left),
  rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
  cout << "In BinaryNode destructor" << endl;
#endif

  try {
    delete leftTree;
  } catch (...) {}

  try {
    delete rightTree;
  } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
  return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
  return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
  AST(),
  subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
  cout << "In UnaryNode destructor" << endl;
#endif

  try {
    delete subTree;
  } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
  return subTree;
}

AddNode::AddNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int AddNode::evaluate() {
  return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

string AddNode::ewe(){
  return getLeftSubTree()->ewe() + getRightSubTree()->ewe() + "# Add\n operator2 := M[sp+0]\n operator1 := M[sp+1]\n operator1 := operator1 + operator2\n sp := sp + one\n M[sp+0] := operator1\n";
}

TimesNode::TimesNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int TimesNode::evaluate() {
  return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
} 

string TimesNode::ewe(){
  return getLeftSubTree()->ewe() + getRightSubTree()->ewe() + "# Times\n operator2 := M[sp+0]\n operator1 := M[sp+1]\n operator1 := operator1 * operator2\n sp := sp + one\n M[sp+0] := operator1\n";
}

SubNode::SubNode(AST* left, AST* right):
BinaryNode(left,right)
{}

int SubNode::evaluate() {
  return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

string SubNode::ewe(){
  return getLeftSubTree()->ewe() + getRightSubTree()->ewe() + "# Sub\n operator2 := M[sp+0]\n operator1 := M[sp+1]\n operator1 := operator1 - operator2\n sp := sp + one\n M[sp+0] := operator1\n";
}

DivideNode::DivideNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int DivideNode::evaluate(){
  //Agregamos la corrección para atrapar una división por cero "0"
  try {
    int leftSon = getLeftSubTree()->evaluate();
	int rightSon = getRightSubTree()->evaluate();
	
	if (rightSon != 0) {
	  return leftSon / rightSon;
	} else {
	  throw 0;
	}
  } catch (...) {
    cout << "Math error, divide by zero is not defined" << endl;
	return 0;
  }
}

string DivideNode::ewe(){
  return getLeftSubTree()->ewe() + getRightSubTree()->ewe() + "# Divide\n operator2 := M[sp+0]\n operator1 := M[sp+1]\n operator1 := operator1 / operator2\n sp := sp + one\n M[sp+0] := operator1\n";
}

//Código para realizar la operación modulo "%" (Implementación)
ModNode::ModNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int ModNode::evaluate(){
  return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

string ModNode::ewe(){
  return getLeftSubTree()->ewe() + getRightSubTree()->ewe() + "# Mod\n operator2 := M[sp+0]\n operator1 := M[sp+1]\n operator1 := operator1 % operator2\n sp := sp + one\n M[sp+0] := operator1\n";
}
//-----------------------------------------------

NumNode::NumNode(int n) :
  AST(),
  val(n)
{}

int NumNode::evaluate() {
  return val;
}

string NumNode::ewe(){  
  ostringstream PushNode;
  PushNode << "#Push(" << val << ")" << endl
           << "sp := sp - one" << endl
           << "operator1 := " << val << endl
           << "M[sp+0] := operator1" << endl;
  return PushNode.str();
}

StoreNode::StoreNode(AST* sub) : UnaryNode(sub) {} 

int StoreNode::evaluate() {
  int ret = getSubTree()->evaluate();
  calc->store(ret);
  return ret;
}

string StoreNode::ewe(){
  return getSubTree()->ewe() + "# Store\n memory := M[sp+0]\n";
}

RecallNode::RecallNode(){}

int RecallNode::evaluate(){
  
  return calc->recall(); 
}
 
string RecallNode::ewe(){
  return "# Recall\n sp:= sp - one\n M[sp+0] := memory\n";
}

// Se agregan las nuevas clases de Minus, Plus, y clear memory
MinusMemoryNode::MinusMemoryNode(AST *sub) : UnaryNode(sub){}

int MinusMemoryNode::evaluate(){
  int minus = getSubTree()->evaluate();
  return calc->minus(minus);
}

string MinusMemoryNode::ewe(){
  return getSubTree()->ewe() + "# Memory Minus \n operator2:= M[sp+0] \n memory := memory - operator2 \n M[sp+0] := memory \n";
}

PlusMemoryNode::PlusMemoryNode(AST *sub) : UnaryNode(sub){}

int PlusMemoryNode::evaluate(){
  int plus = getSubTree()->evaluate();
  return calc->plus(plus);
}

string PlusMemoryNode::ewe(){
  return getSubTree()->ewe() + "# Memory Plus \n operator2:= M[sp+0] \n memory := memory + operator2 \n M[sp+0] := memory \n";
}

ClearMemoryNode::ClearMemoryNode(){}

int ClearMemoryNode::evaluate(){
  calc->store(0);
  return 0;
}

string ClearMemoryNode::ewe(){
  return "# Clear Memory \n memory := zero \n sp := sp - one \n M[sp+0] := memory";
}
//-----------------------------------------------

// Nodo para el manejo de variables (Implementación)
VariableNode::VariableNode(string name) : name(name){}

int VariableNode::evaluate(){
  return calc->getVariable(name);
}

string VariableNode::ewe(){
  calc->getVariable(name);
  ostringstream PushNodeVar;
  PushNodeVar << "#Push(" << name << ")" << endl
              << "sp := sp - one" << endl
              << "operator1 := " << name << endl
              << "M[sp+0] := operator1" << endl;
  return PushNodeVar.str();
}

string VariableNode::getName(){
  return name;
}

void VariableNode::setName(int value){
   calc->addVariable(name, value);
}
//-----------------------------------------------

//Código para la clase RootNode (Implementación)
RootNode::RootNode(VariableNode* left, AST* right):
  AST(),
  leftTree(left),
  rightTree(right)
{}

RootNode::~RootNode() {
#ifdef debug
  cout << "In BinaryNode destructor" << endl;
#endif

  try {
    delete leftTree;
  } catch (...) {}

  try {
    delete rightTree;
  } catch(...) {}
}
   
VariableNode* RootNode::getLeftSubTree() const {
  return leftTree;
}

AST* RootNode::getRightSubTree() const {
  return rightTree;
}
//-----------------------------------------------

//Se agregan las nuevas clases de nodos de variables
EqualsNode::EqualsNode(VariableNode* left, AST* right) : RootNode(left, right){}

int EqualsNode::evaluate(){
  int value = getRightSubTree()->evaluate();
  getLeftSubTree()->setName(value);
  return value;
}

string EqualsNode::printResult(){
  ostringstream target;
  target << evaluate();
  string rightString = target.str();
  return "= " + getLeftSubTree()->getName() + " <- " + rightString;
}

string EqualsNode::ewe(){
  return getRightSubTree()->ewe() + "# Assign \n " + getLeftSubTree()->getName() + " := M[sp+0]\n";
}
//-----------------------------------------------

