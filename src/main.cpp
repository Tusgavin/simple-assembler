#include <iostream>
#include <fstream>
#include <string>

#include "montador.h"

#define DEBUG 1

void log_error(const std::string message)
{
#if DEBUG 1
  std::cout << "[ERROR]: "
  <<  message
  << " - in file "
  << __FILE__
  << " at line "
  << __LINE__
  << std::endl;
#endif
}

int main(int argc, char *argv[]) {
  /*
  * Ler arquivo texto e separar cada instrução por linhas => 
  * gerar um std::vector<std::string> com cada posição sendo uma instrução  
  */

  if (argc <= 1) {
    log_error("argc insufficient - need filename");
    exit(EXIT_FAILURE);
  }

  std::vector<std::string> instructions_in_file;

  const std::string assembly_file_name = std::string(argv[1]);

  std::ifstream assembly_file_pointer(assembly_file_name);

  if (assembly_file_pointer.is_open())
  {
    std::string file_line;

    while(std::getline(assembly_file_pointer, file_line))
    {
      instructions_in_file.push_back(file_line);
    }
    assembly_file_pointer.close();
  }
  else
  {
    log_error("unable to open file " + assembly_file_name);
    exit(EXIT_FAILURE);
  }

  return 0;
}