#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <vector>
#include <fstream> 

Calculator::Calculator():
   memory(0)
{}

void Calculator::store(int val) {
   memory = val;
}

int Calculator::recall() {
   return memory;
}

//se agregan los metodos para agregar variables y recibir variables
void Calculator::addVariable(const string name, const int value){
   variables[name] = value;
}

int Calculator::getVariable(string name){
   return variables[name];
}
//-----------------------------------------------

// Metodos para el manejo de las operaciones de memoría (Implementación)

int Calculator::plus(int pls){
   memory = memory + pls;
   return memory;
}

int Calculator::minus (int min){
   memory = memory - min;
   return memory;
}
//-----------------------------------------------

//Metodos iterativo para controlar las execuciones
//Normal
void Calculator::execution(){
	string expression;
	string line;
	Parser* parser = new Parser(new istringstream(line));
	
	while (expression.compare("<EOF>") != 0){
      try{
	     cout << "> ";
         getline(cin, line);
         if(!line.empty())if(!line.empty())line = line + "\n";
         expression = parser->parse(new istringstream(line), false);
         if(expression.compare("<EOF>") != 0) cout << expression << endl;
      } catch(...){
         cout << "Parser error, program aborted due to exception!" << endl;
      }
	}
	
	delete parser;
}

// Ficheros
void Calculator::executionFicheros(vector<string> ficheros){
	string expression;
	string line;
	Parser* parser;
	ifstream myFile;
	//Antes de abrir los ficheros
	
	for(int position = 0; position < ficheros.size(); position++){
	  line = "";
	  myFile.open(ficheros[position].c_str());
	  parser = new Parser(new istringstream(line));
	
	  while (std::getline(myFile, line)){
        try{
	       if(!line.empty())line = line + "\n";
           expression = parser->parse(new istringstream(line), false);
           if(expression.compare("<EOF>") != 0) cout << expression<<endl;
	    } catch(...){
           cout << "Parser error, program aborted due to exception!" << endl;
        }
	  }
	  
	  myFile.close();
	  delete parser;
	}
}
//----------------------

//Ewe
void Calculator::executionEwe(){
	string expression;
	string line;
	Parser* parser = new Parser(new istringstream(line));
	bool isFirst = true;
	
	int expr = 1;

    try{;
	   ofstream archivo;
	   archivo.open("a.ewe");
	   archivo << "# EWE file:/n" << endl;
	   //antes de las expresiones

	   while (expression.compare("<EOF>") != 0){
         try{
		    cout << "> ";
		    getline(cin, line);
            if(!line.empty())if(!line.empty())line = line + "\n";
            expression = parser->parse(new istringstream(line), true);
			
			if(expression.compare("<EOF>") != 0){			
		      archivo << "# expr" << expr << ":" <<endl;
			  archivo << "# Expresión: " << line <<endl;
		      archivo << "# Instructions before the Abstract Syntax Tree" << endl;
	          archivo << " sp := 1000" << endl;
	          archivo << " one := 1" << endl;
			  archivo << " zero := 0" << endl;
			  
			  if(isFirst){
			    archivo << " memory := zero" << endl;
	            archivo << getStringVar() << endl;//Imprimimos las variables de ambiente que usa el programa
				isFirst = false;
			  }
			  
	          archivo << "# AST route begins" << endl;
			  //antes del código Ewe
			  archivo << expression << endl;
			  //después del código Ewe
		      archivo << "# Write result" << endl;
	          archivo << " operator1 := M[sp+0]" << endl;
	          archivo << " sp := sp - one" << endl;
	          archivo << " writeInt(operator1)" << endl;
			}
			
			parser->getTree()->evaluate();
			expr++;
         } catch(...){
            cout << "Parser error, program aborted due to exception!" << endl;
         }
	   }
	
	   delete parser;
	   //después de las expresiones
	   archivo << "end: halt" << endl;
	   archivo << "equ memory    M[0]" << endl;
	   archivo << "equ one       M[1]" << endl;
	   archivo << "equ zero      M[2]" << endl;
	   archivo << "equ operator1 M[3]" << endl;
	   archivo << "equ operator2 M[4]" << endl;
	   archivo << "equ sp        M[5]" << endl;
	   archivo << calc->getStringEqu() <<//Hacemos los equ de las variables
	   "equ stack     M[1000]" << endl;
	   archivo.close();
    } catch(...){
	   cout << "Program Aborted due to Exception" << endl;	
    }
}

// Ficheros
void Calculator::executionFicherosEwe(vector<string> ficheros){
	string expression;
	string line;
	string name;
	int expr;
	Parser* parser;
	ifstream myFile;
	ofstream archivo;
	bool isFirst;
	//Antes de abrir cada archivo
	
	for(int position = 0; position < ficheros.size(); position++){
	  isFirst = true;
	  myFile.open(ficheros[position].c_str(), std::ifstream::in);
	  line = "";
	  parser = new Parser(new istringstream(line));
	  name = ficheros[position].substr(0, ficheros[position].find(".calc")) + ".ewe";
	  expr = 1;
	  
	  try{;
	     archivo.open(name.c_str());
	     archivo << "#EWE file:\n" << endl;
	     //antes de las lineas
	
	     while (std::getline(myFile, line))
	     {
           try{
	          if(!line.empty())line = line + "\n";
              expression = parser->parse(new istringstream(line), true);
		   
		      archivo << "# expr" << expr << ":" <<endl;
	          archivo << "# Expresión: " << line <<endl;
	          archivo << "# Instructions before the Abstract Syntax Tree" << endl;
	          archivo << " sp := 1000" << endl;
	          archivo << " one := 1" << endl;
		      archivo << " zero := 0" << endl;
			  
			  if(isFirst){
			    archivo << " memory := zero" << endl;
	            archivo << getStringVar() <<endl;//Imprimimos las variables de ambiente que usa el programa
				isFirst = false;
			  }
			  
	          archivo << "# AST route begins" << endl;
		      //Antes del código Ewe
		      archivo << expression << endl;
		      //Después del código Ewe
		      archivo << "# Write result" << endl;
	          archivo << " operator1 := M[sp+0]" << endl;
	          archivo << " sp := sp - one" << endl;
	          archivo << " writeInt(operator1)" << endl;
			  
			  parser->getTree()->evaluate();
			  expr++;
	       } catch(...){
              cout << "Parser error, program aborted due to exception!" << endl;
           }
	     }
		 
		//Después de las lineas
	    archivo << "end: halt" << endl;
	    archivo << "equ memory    M[0]" << endl;
	    archivo << "equ one       M[1]" << endl;
	    archivo << "equ zero      M[2]" << endl;
	    archivo << "equ operator1 M[3]" << endl;
	    archivo << "equ operator2 M[4]" << endl;
	    archivo << "equ sp        M[5]" << endl;
	    archivo << calc->getStringEqu() <<//Hacemos los equ de las variables
	    "equ stack     M[1000]" << endl;
	    archivo.close();
	    myFile.close();
		delete parser;
	  } catch(...){
	     cout << "Program Aborted due to Exception" << endl;	
      }
    }
}
//----------------------
//-----------------------------------------------

// Implementación del metodo para buscar las variables de ambienbte
void Calculator::getEnv (char** env){
   string envVa = "";
   for (char** envs = env; *envs != 0; envs++){
      envVa = *envs;
	  
	  if(envVa.find("CALCVAR_") == 0){
	    int indexEnd = envVa.find("=");
		int indexBegin = envVa.find("_");
	    string name = envVa.substr(indexBegin + 1, indexEnd - indexBegin - 1);
	    int value = atoi(envVa.substr(indexEnd + 1).c_str());
	    addVariable(name, value);
	  }
   }
 }
//-----------------------------------------------

// Metodos que devuelven strings respectivos a los manejos de las variables para ewe
//Varibales
string Calculator::getStringVar(){
   string vars = "";
   ostringstream target;
   map<string, int>::const_iterator iter;
   
   for(iter = variables.begin(); iter != variables.end(); iter++){
	  target << getVariable(iter->first);
	  vars = " " + vars + iter->first + " := " + target.str() + "\n";
	  target.str("");
   }
   
   return vars;
}
//----------------------

//Equs
string Calculator::getStringEqu() {
   string equs = "";
   int I = 6;
   ostringstream target;
   map<string, int>::const_iterator iter;
   
   for(iter = variables.begin(); iter != variables.end(); iter++, I++){
	  target << I;
      equs = equs + "equ " + iter->first + " M[" + target.str() + "] \n";
	  target.str("");
   }  

   return equs;   
}
//----------------------
//-----------------------------------------------

