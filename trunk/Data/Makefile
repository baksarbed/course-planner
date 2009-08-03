all: clean parser

parser:	
	lex cvs_parser.l
	yacc -d cvs_parser.y
	cc lex.yy.c y.tab.c -o parser

clean: 
	rm -rf *~ *.o lex.yy.c y.tab.* parser
