#ifndef MONTADOR_H
#define MONTADOR_H

#include <vector>
#include <string>
#include <regex>
#include <iostream>

#define NOARG -1
#define REG 0
#define MEM 1

// TODO: structs, classes, e outras definições.


void log_error(const std::string message);

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

typedef struct VMInstructions
{
   std::string symbol;
   int code;
   int first_arg;
   int second_arg;

   VMInstructions(std::string symbol, int code, int first_arg, int second_arg)
   {
      this->symbol = symbol;
      this->code = code;
      this->first_arg = first_arg;
      this->second_arg = second_arg;
   }
} VMInstructions;

class Assembler
{
private:
   std::vector<VMInstructions> vm_instructions;

public:
   Assembler();
   ~Assembler() { };

   std::vector<VMInstructions> get_vm_instructions() const { return this->vm_instructions; }

   std::vector<std::string> convert_code(std::vector<Operation> ops);
   VMInstructions find_instruction_by_symbol(std::string symbol);
   static int convert_register_to_machine_code(std::string registerName);
};

#endif  // MONTADOR_H
