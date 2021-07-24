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
