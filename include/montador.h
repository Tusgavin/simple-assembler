#ifndef MONTADOR_H
#define MONTADOR_H

#include <vector>
#include <string>
#include <regex>
#include <iostream>

// TODO: structs, classes, e outras definições.

std::string left_trim(const std::string &str);

std::string right_trim(const std::string &str);

// Remove unecessary whitespaces in the beggining and end of string
std::string trim(const std::string &str);

class Operation
{
private:
   std::string label;
   std::string operador;
   std::string operando1;
   std::string operando2;

public:
   Operation(std::string operation_stringfied);
   ~Operation() { };

   // GET
   std::string get_label() const { return this->label; }
   std::string get_operador() const { return this->operador; }
   std::string get_operando1() const { return this->operando1; }
   std::string get_operando2() const { return this->operando2; }

   // SET
   void set_label(std::string label) { this->label = label; }
   void set_operador(std::string operador) { this->operador = operador; }
   void set_operando1(std::string operando1) { this->operando1 = operando1; }
   void set_operando2(std::string operando2) { this->operando2 = operando2; }
};

// class Assembler
// {
// private:
//    std::vector<Operation> vm_instructions;

// public:
//    Assembler();
//    ~Assembler();

//    Operation findBySymbol(std::string symbol);
//    std::vector<Operation> get_instructions_per_string(std::vector<std::string> instrucions_string);
//    std::string convert_code(std::vector<Operation> ops);
// };

#endif  // MONTADOR_H
