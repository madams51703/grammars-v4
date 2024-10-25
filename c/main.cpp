#include <iostream>
#include <fstream>
#include <antlr4-runtime/antlr4-runtime.h>
#include <getopt.h>

#define no_argument 0
#define required_argument 1 
#define optional_argument 2

#include "CLexer.h"
#include "CParser.h"
#include "CWalker.h"
using namespace antlr4;
using namespace std;

int main(int argc, char *argv[]) {
	string line;
        char raw_redo_file[5000]="NONE";
        char input_file[5000]="/dev/stdin";
        int enable_raw_redo=0;
        int print_option=0;
        int column_of_interest=-1;
const struct option longopts[] =
  {
    {"file",     required_argument,  0, 'f'},
    {0,0,0,0},
  };

  int index;
  int iarg=0;

  //turn off getopt error message
  opterr=1; 

  while(iarg != -1)
  {
    iarg = getopt_long(argc, argv, "c:f:r:s:", longopts, &index);

    switch (iarg)
    {

      case 'f':
	strcpy(input_file,optarg);
        break;


    }
  }

	ifstream CParserFile (input_file);
	if (CParserFile.is_open()) {
		ANTLRInputStream input(CParserFile);
		CLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
/*
		tokens.fill();
		for (auto token : tokens.getTokens()) {
			std::cout << token->toString() << std::endl;
		}
*/

		CParser parser(&tokens);



		antlr4::tree::ParseTreeWalker walker;	
		antlr4::ParserRuleContext* c_file = parser.compilationUnit();
 		CWalker * listener = new CWalker();		
  		walker.walk(listener, c_file);
		CParserFile.close();
	}
}
