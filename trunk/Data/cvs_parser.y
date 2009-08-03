%{
/**
 * @file
 * @brief parses cvs courses
 *
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE *fp;
char buff[100];

#define convert_day(m) \
	if( strcmp(m,"Mon") == 0 ) printf("monday,"); \
	else if( strcmp(m,"Tue") == 0 ) printf("tuesday,");\
	else if( strcmp(m,"Wed") == 0 ) printf("wednesday,");\
	else if( strcmp(m,"Thu") == 0 ) printf("thursday,");\
	else if( strcmp(m,"Fri") == 0 ) printf("friday,");\
	else{\
		printf("Error: invalid day");\
		exit(0);\
	}

%}


%token STRING
%token COMMA START END COLON TEXT

%%

course_info:
	course_info course_row1 course_row2 course_row3
   	|
	course_row1 course_row2 course_row3
	;

course_row1:
	TEXT STRING TEXT COMMA TEXT STRING STRING TEXT COMMA TEXT STRING TEXT COMMA STRING COLON STRING COLON STRING COMMA STRING COLON STRING COLON STRING COMMA TEXT STRING COMMA STRING TEXT COMMA TEXT STRING TEXT
	{
		printf("course_name,%s,course_id,%s,\ncourse_professor,%s,\ncourse_section,%s,\ncourse_type,%s,\n",$33,$2,$27,$7,$6);
		int h1= atoi($14); // get first time
		int h2= atoi($20); // get second time
	
		printf("course_time,");
		convert_day($11)
		printf("_%d_%d,\n",h1>12?h1-12:h1,h2>12?h2-12:h2);
	}
;
	
course_row2:
	TEXT STRING TEXT COMMA TEXT STRING STRING TEXT COMMA TEXT STRING TEXT COMMA STRING COLON STRING COLON STRING COMMA STRING COLON STRING COLON STRING COMMA TEXT STRING COMMA STRING TEXT COMMA
	{
	
		int h1= atoi($14); // get first time
		int h2= atoi($20); // get second time
	
		printf("course_time,");
		convert_day($11)
		printf("_%d_%d,\n",h1>12?h1-12:h1,h2>12?h2-12:h2);

	}
;

course_row3:
	TEXT STRING TEXT COMMA TEXT STRING STRING TEXT COMMA TEXT STRING TEXT COMMA STRING COLON STRING COLON STRING COMMA STRING COLON STRING COLON STRING COMMA TEXT STRING COMMA STRING TEXT COMMA
	{
		int h1= atoi($14); // get first time
		int h2= atoi($20); // get second time
	
		printf("course_time,");
		convert_day($11)
		printf("_%d_%d,\n<\n",h1>12?h1-12:h1,h2>12?h2-12:h2);

	}
;



  
%%

yyerror(char *e){
  fprintf(stderr,"%s.\n",e);
}

int main () {

/*	fp=fopen("test.txt","r");
	if( fp == NULL )
		printf("Error opening output file\n");
*/	
	yyparse();

}

