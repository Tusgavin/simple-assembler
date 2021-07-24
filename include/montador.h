#ifndef MONTADOR_H
#define MONTADOR_H

#include <vector>
#include <string>
#include <regex>

// TODO: structs, classes, e outras definições.

std::string left_trim(const std::string &str)
{
   return std::regex_replace(str, std::regex("^\\s+"), std::string(""));
}

std::string right_trim(const std::string &str)
{
   return std::regex_replace(str, std::regex("\\s+$"), std::string(""));
}

// Remove unecessary whitespaces in the beggining and end of string
std::string trim(const std::string &str)
{
   return right_trim(left_trim(str));
}

class Operation
{
private:
   std::string label;
   std::string operador;
   std::string operando1;
   std::string operando2;

public:
   Operation(std::string operation_stringfied);
   ~Operation();

   // GET
   std::string label() { return label; }
   std::string operador() { return operador; }
   std::string operando1() { return operando1; }
   std::string operando2() { return operando2; }

   // SET
   void label(std::string label) { this->label = label; }
   void operador(std::string operador) { this->operador = operador; }
   void operando1(std::string operando1) { this->operando1 = operando1; }
   void operando2(std::string operando2) { this->operando1 = operando2; }
};

class Assembler
{
private:
   std::vector<Operation> vm_instructions;

public:
   Assembler();
   ~Assembler();

   Operation findBySymbol(std::string symbol);
   std::vector<Operation> get_instructions_per_string(std::vector<std::string> instrucions_string);
   std::string convert_code(std::vector<Operation> ops);
};

#endif  // MONTADOR_H
