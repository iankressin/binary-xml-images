#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "include/parser.h"
#include <stdexcept>

using namespace std;
static char BASE_PATH[] = "assets/";

int main (int argc, char *argv[]) {
  char * file_name = argv[1];
  char * full_path = strcat(BASE_PATH, file_name);
  ifstream file(full_path);

  if(!file.is_open()) {
    printf("ERROR: Unable to open file %s", full_path);
    exit(1);
  }

  stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  Parser parser(buffer.str());

  bool valid = parser.parse();

  if (!valid) printf("Not valid\n");
  else printf("Valid\n");

  return 0;
}
