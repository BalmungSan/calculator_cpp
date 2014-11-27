#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "calculator.h"
using namespace std;

//Archivo calc.C, en este archivo se programan las funcionalidades de la calculadora, la calculadora de variables y la calculadora que genera un codigo EWE.

Calculator* calc;

int main(int argc, char* argv[], char* env[]) {
  bool isCompilator = false;
  bool isFichero = false;
  vector<string> ficheros;
  calc = new Calculator();
  calc->getEnv(env);
  
  for(int a=1; a<argc; a++){
    string word = argv[a];
	
    if(word.compare("-c") == 0){
	  //Código para poner la calculadora en modo compilador
      isCompilator = true;
    }
	
	if(word.compare("-v") == 0){
	   //Código para leer variables
	   a++;
	   string var = argv[a];
	   int index = var.find("=");
	   string name = var.substr(0, index);
	   int value = atoi(var.substr(index + 1).c_str());
	   calc->addVariable(name, value);
	}
	
	if(word.find(".calc") != -1){
	   //Código para leer ficheros
	   isFichero = true;
	   ficheros.push_back(word);
	}
  }

  //Modo normal, calculadora con manejo de variables
  if(isCompilator == false){
    cout << "=======VARIABLE CALCULATOR=======" << endl;
    cout << "Input any expression with variables; to finish the execution of the program press '$'" << endl;
    cout << "==================================" << endl;
    
	if(isFichero){
	  calc->executionFicheros(ficheros);
	} else {
	  calc->execution();
	}
	
	delete calc;
	cout << "Ended execution; it was a pleasure :)"<<endl; 
  } else {
    //Modo calculadora de EWE, genera código de EWE
    cout << "========EWE CALCULATOR===========" << endl;
    cout << "You have switched to the EWE calculator, enter an operation and the computer will produce an EWE code of said operation" << endl;
	cout << "to finish the execution of the program press '$'" << endl;
    cout << "=================================" << endl;
	
    if(isFichero){
	  calc->executionFicherosEwe(ficheros);
	} else {
	  calc->executionEwe();
	}
	
	delete calc;
	cout << "Ended execution, the result code is store in the file(s) '*.ewe'; it was a pleasure :)"<<endl;
  }
}

