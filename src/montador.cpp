#include "montador.h"

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

// TODO: implementação do montador
Operation::Operation(std::string operation_stringfied)
{
   operation_stringfied = trim(operation_stringfied);

   // Comments - delete every character after comment delimiter is found
   std::string comment_delimeter = ";";
   std::size_t comment_start_index = operation_stringfied.find(comment_delimeter);
   if (comment_start_index != std::string::npos) 
      operation_stringfied = operation_stringfied.substr(0, comment_start_index);

   operation_stringfied = trim(operation_stringfied);

   // Label
   std::string label_delimiter = ":";
   std::size_t label_end_index = operation_stringfied.find(label_delimiter);
   if (label_end_index != std::string::npos)
   {
      std::string label = operation_stringfied.substr(0, label_end_index);
      this->set_label(label);
      operation_stringfied = operation_stringfied.substr(label_end_index + 1);
   }
   else
   {
      this->set_label("");
   }

   operation_stringfied = trim(operation_stringfied);

   // Operador
   std::string whitespace_delimiter = " ";
   std::size_t operator_end_index = operation_stringfied.find(whitespace_delimiter);
   if (operator_end_index != std::string::npos)
   {
      std::string operador = operation_stringfied.substr(0, operator_end_index);
      this->set_operador(operador);
      operation_stringfied = operation_stringfied.substr(operator_end_index + 1);
   }
   else if (operation_stringfied.length() != 0)
   {
      this->set_operador(operation_stringfied);
      this->set_operando1("");
      this->set_operando2("");
      operation_stringfied = "";
      return;
   }

   operation_stringfied = trim(operation_stringfied);

   // Operando1 - first check if there is any Operando
   if (operation_stringfied.length() != 0)
   {
      std::size_t operand1_end_index = operation_stringfied.find(whitespace_delimiter);
      if (operand1_end_index != std::string::npos)
      {
         std::string operando1 = operation_stringfied.substr(0, operand1_end_index);
         this->set_operando1(operando1);
         operation_stringfied = operation_stringfied.substr(operand1_end_index + 1);
      }
      else
      {
         this->set_operando1(operation_stringfied);
         this->set_operando2("");
         operation_stringfied = "";
         return;
      }
   }

   operation_stringfied = trim(operation_stringfied);

   // Operando2 - first check if there is any Operando
   if (operation_stringfied.length() != 0)
   {
      this->set_operando2(operation_stringfied);
      operation_stringfied = "";
   }
   else
   {
      this->set_operando2("");
   }
}

Assembler::Assembler()
{
   VMInstructions ins = VMInstructions("HALT", 0, NOARG, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("LOAD", 1, REG, MEM);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("STORE", 2, REG, MEM);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("READ", 3, REG, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("WRITE", 4, REG, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("COPY", 5, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("PUSH", 6, REG, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("POP", 7, REG, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("ADD", 8, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("SUB", 9, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("MULL", 10, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("DIV", 11, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("MOD", 12, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("AND", 13, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("OR", 14, REG, REG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("NOT", 15, REG, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("JUMP", 16, MEM, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("JZ", 17, MEM, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("JN", 18, MEM, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("CALL", 19, MEM, NOARG);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("RET", 20, NOARG, NOARG);
   this->vm_instructions.push_back(ins);
}

std::vector<std::string> Assembler::convert_code(std::vector<Operation> ops)
{
   for (auto op : ops)
   {
      
   }
}
