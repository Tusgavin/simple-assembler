#include "montador.h"

// TODO: implementação do montador
Operation::Operation(std::string operation_stringfied)
{
   operation_stringfied = trim(operation_stringfied);

   // Comments
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


   // Operando1

   // Operando2
}