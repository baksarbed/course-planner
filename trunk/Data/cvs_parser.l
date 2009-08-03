%{


#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

%option noyywrap


/* Define macros for use below */





%%
,				{ return COMMA ; }
\>				{ return START; }
\<				{ return END; }
\"				{ return TEXT; }
\:				{ return COLON; }

[\t\n ]+         { /* ignore white space */
                 }


#.*\n	         { /* ignore comments; text starting with '#' to 
                      the end of the line */
                  }


[a-zA-Z0-9\_.]+			{
					yylval = (char *)strdup(yytext);
					return STRING; 
				}

.                 { 
		     return yytext[0]; 
                  }

<<EOF>>           { 
                    return 0;
                  }

%%

