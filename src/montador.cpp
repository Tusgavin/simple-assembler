#include "montador.h"

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
      this->label(label);
      operation_stringfied = operation_stringfied.substr(label_end_index + 1);
   }
   else
   {
      this->label("");
   }

   operation_stringfied = trim(operation_stringfied);

   // Operador
   std::string whitespace_delimiter = " ";
   std::size_t operator_end_index = operation_stringfied.find(whitespace_delimiter);
   if (operator_end_index != std::string::npos)
   {
      std::string operador = operation_stringfied.substr(0, operator_end_index);
      this->operador(operador);
      operation_stringfied = operation_stringfied.substr(operator_end_index + 1);
   }
   else
   {
      if (operation_stringfied.length() != 0)
         this->operador(operation_stringfied);
         this->operando1("");
         this->operando2("");
         operation_stringfied = "";
         return;
   }

   operation_stringfied = trim(operation_stringfied);

   // Operando1 - first check if there is any Operando
   if (operation_stringfied.length() != 0)
   {
      std::size_t operand1_end_index = operation_stringfied.find(whitespace_delimiter);
      if (operator_end_index != std::string::npos)
      {
         std::string operando1 = operation_stringfied.substr(0, operand1_end_index);
         this->operando1(operando1);
         operation_stringfied = operation_stringfied.substr(operand1_end_index + 1);
      }
      else
      {
         if (operation_stringfied.length() != 0)
            this->operando1(operation_stringfied);
            this->operando2("");
            operation_stringfied = "";
            return;
      }
   }

   operation_stringfied = trim(operation_stringfied);

   // Operando2 - first check if there is any Operando
   if (operation_stringfied.length() != 0)
   {
      this->operando2(operation_stringfied);
      operation_stringfied = "";
   }
}