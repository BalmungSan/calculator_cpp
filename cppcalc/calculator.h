#pragma once
#include <string>
#include <map>
#include <stdlib.h>
#include <vector>
#include <fstream> 

using namespace std;


class Calculator {
 public:
   Calculator();
   void store(int val);
   string ewe(string expr);
   int recall();
   
   //se añade metodos para el manejo variables (Declaración)
   void addVariable(const string name, const int value);
   int getVariable(string name);
   //--------------------------------------------
   
   //Metodos para el manejo de las operaciones de memoria (Declaración)
   int plus(int pls);
   int minus(int min);
   //--------------------------------------------
   
   //Metodos para manejar la ejecución de varias entradas (Declaración)
   //Normal
   void execution();
   void executionFicheros(vector<string> ficheros);//Manejo de ficheros
   //-------------------
   
   //Ewe
   void executionEwe();
   void executionFicherosEwe(vector<string> ficheros);//Manejo de ficheros
   //-------------------
   //--------------------------------------------
   
   //Metodo para buscar las variables de ambiente
   void getEnv (char** env); 
   //--------------------------------------------
   
   //Metodos para recorrer las variables para ewe (Declaración)
   string getStringVar();//get variables
   string getStringEqu();//get Equs
   //--------------------------------------------
   
 private:
   int memory;
   map <string,int> variables; //se añade el map "mapa" (atributo) para manejo de las variables
};

extern Calculator* calc;

