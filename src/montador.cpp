#include "montador.h"

void log_error(const std::string message)
{
  std::cout << "[ERROR]: "
  <<  message
  << std::endl;
}

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

Operation::Operation(std::string operation_stringfied)
{
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

int Operation::calculate_operation_size()
{
   int size = 0;

   if (this->get_operador() != "") size++;
   if (this->get_operando1() != "") size++;
   if (this->get_operando2() != "") size++;

   return size;
}

Assembler::Assembler()
{
   VMInstructions ins = VMInstructions("HALT", 0, NOARG, NOARG, 1);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("LOAD", 1, REG, MEM, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("STORE", 2, REG, MEM, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("READ", 3, REG, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("WRITE", 4, REG, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("COPY", 5, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("PUSH", 6, REG, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("POP", 7, REG, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("ADD", 8, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("SUB", 9, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("MULL", 10, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("DIV", 11, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("MOD", 12, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("AND", 13, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("OR", 14, REG, REG, 3);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("NOT", 15, REG, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("JUMP", 16, MEM, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("JZ", 17, MEM, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("JN", 18, MEM, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("CALL", 19, MEM, NOARG, 2);
   this->vm_instructions.push_back(ins);
   ins = VMInstructions("RET", 20, NOARG, NOARG, 1);
   this->vm_instructions.push_back(ins);
}

void Assembler::remove_whitespaces_from_file_input(std::vector<std::string> &input_str)
{
   for (auto &str : input_str)
   {
      std::string line = trim(str);
      str = line;
   }
}

void Assembler::remove_empty_lines_from_file_input(std::vector<std::string> &input_str)
{
   auto it = input_str.begin();

   while (it != input_str.end())
   {
      if (it->length() == 0) input_str.erase(it);
      else ++it;
   }
}

void Assembler::remove_comments_from_file_input(std::vector<std::string> &input_str)
{
   for (auto &str : input_str)
   {
      std::string line = trim(str);

      std::string comment_delimeter = ";";
      std::size_t comment_start_index = line.find(comment_delimeter);
      if (comment_start_index != std::string::npos) {
         line = line.substr(0, comment_start_index);
         str = line;
      }
   }

   Assembler::remove_empty_lines_from_file_input(input_str);
}

std::vector<std::string> Assembler::convert_code(std::vector<Operation> ops)
{
   std::vector<std::string> stringfied_vm_instructions;

   int code_total_size = 0;

   for (auto op : ops)
   {
      std::string vm_instructions_string = "";

      if (op.get_operador() == "END") break;

      if (op.get_operador() == "WORD")
      {
         vm_instructions_string = vm_instructions_string + op.get_operando1();
         stringfied_vm_instructions.push_back(vm_instructions_string);
         code_total_size++;
         continue;
      }

      VMInstructions inst = this->find_instruction_by_symbol(op.get_operador());
      if (inst.symbol != "NOT FOUND")
      {
         code_total_size = code_total_size + inst.size;
         vm_instructions_string = std::to_string(inst.code);

         if (inst.first_arg != NOARG)
         {
            if (inst.first_arg == REG)
            {
               int operando1_code = Assembler::convert_register_to_machine_code(op.get_operando1());
               vm_instructions_string = vm_instructions_string + " " + std::to_string(operando1_code);
            }
            else if (inst.first_arg == MEM)
            {
               int total_size_unitl_label_found = 0;

               for (auto _op : ops)
               {

                  if (_op.get_label() == op.get_operando1())
                  {
                     int diff_indexes = total_size_unitl_label_found - code_total_size;
                     vm_instructions_string = vm_instructions_string + " " + std::to_string(diff_indexes);
                     break;
                  }

                  total_size_unitl_label_found = total_size_unitl_label_found + _op.calculate_operation_size();
               }
            }     
         }

         if (inst.second_arg != NOARG)
         {
            if (inst.second_arg == REG)
            {
               int operando2_code = Assembler::convert_register_to_machine_code(op.get_operando2());
               vm_instructions_string = vm_instructions_string + " " + std::to_string(operando2_code);
            }
            else if (inst.second_arg == MEM)
            {
               int total_size_unitl_label_found = 0;

               for (auto _op : ops)
               {
                  if (_op.get_label() == op.get_operando2())
                  {
                     int diff_indexes = total_size_unitl_label_found - code_total_size;
                     vm_instructions_string = vm_instructions_string + " " + std::to_string(diff_indexes);
                     break;
                  }

                  total_size_unitl_label_found = total_size_unitl_label_found + _op.calculate_operation_size();
               }
            }     
         }
         vm_instructions_string = vm_instructions_string + " ";
         stringfied_vm_instructions.push_back(vm_instructions_string);
      }
      else
      {
         log_error("instruction not found");
         exit(1);
      }
   }

   return stringfied_vm_instructions;
}

int Assembler::convert_register_to_machine_code(std::string registerName)
{
   if (registerName == "R0") return 0;
   else if (registerName == "R1") return 1;
   else if (registerName == "R2") return 2;
   else if (registerName == "R3") return 3;
   else return -1;
}

VMInstructions Assembler::find_instruction_by_symbol(std::string symbol)
{
   for (auto instruction : this->get_vm_instructions())
   {
      if (instruction.symbol == symbol) return instruction;
   }

   return VMInstructions("NOT FOUND", -1, -1, -1, 0);
}