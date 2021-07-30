#include <iostream>

#include "montador.h"

int main()
{
   std::cout << std::endl;
   std::cout << "###############################################" << std::endl;
   std::cout << "#############  ! RUNNING TESTS !  #############" << std::endl;
   std::cout << "###############################################" << std::endl;
   std::cout << std::endl;

   std::vector<std::string> mock_instructions;

   mock_instructions.push_back(";;;;;;;;;;");
   mock_instructions.push_back("READ R0    ; comentario de testes");
   mock_instructions.push_back("LOAD R1 const100");
   mock_instructions.push_back("ADD R0 R1 ; comentario de testes");
   mock_instructions.push_back("WRITE R0"              );
   mock_instructions.push_back("HALT");
   mock_instructions.push_back("const100: WORD 100");
   mock_instructions.push_back("              ");
   mock_instructions.push_back("END");


   Assembler::remove_empty_lines_from_file_input(mock_instructions);
   Assembler::remove_whitespaces_from_file_input(mock_instructions);
   Assembler::remove_comments_from_file_input(mock_instructions);

   std::vector<Operation> mock_operations;

   for (auto instruction : mock_instructions)
   {
      Operation *op = new Operation(instruction);
      mock_operations.push_back(*op);
   }

   int index_of_operation = 0;

   std::cout << "******** IMPRIMINDO OPERAÇÕES ********" << std::endl;

   for (auto op : mock_operations)
   {
      std::cout << ">> OPERATION " << index_of_operation << std::endl;
      std::cout << "label: " << op.get_label() << std::endl;
      std::cout << "operador: " << op.get_operador() << std::endl;
      std::cout << "operando1: " << op.get_operando1() << std::endl;
      std::cout << "operando2: " << op.get_operando2() << std::endl;
      index_of_operation++;
   }

   Assembler *assembler = new Assembler();

   std::vector<std::string> converted = assembler->convert_code(mock_operations);

   std::cout << std::endl;
   std::cout << "******** CONVERTENDO PARA VM INSTR. ********" << std::endl;

   for (auto string_vm_inst : converted)
   {
      std::cout << string_vm_inst;
   }

   std::cout << std::endl;

   return 0;
}