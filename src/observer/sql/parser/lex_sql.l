%{
#include<string.h>
#include<stdio.h>

struct ParserContext;

#include "yacc_sql.tab.h"
extern int atoi();
extern double atof();

#if YYDEBUG > 0
#define debug_printf  printf
#else
#define debug_printf(...)
#endif // YYDEBUG

#define RETURN_TOKEN(token) debug_printf("%s\n",#token);return token
%}

/* Prevent the need for linking with -lfl */
%option noyywrap
%option bison-bridge
%option reentrant

WHITE_SAPCE      [\ \t\b\f]
DIGIT            [0-9]+

ID               [A-Za-z_]+[A-Za-z0-9_]*
DOT              \.
QUOTE            [\'\"]

DATES 			 [0-9]{4}\-[0-9]{1,2}\-[0-9]{1,2}
          
%x STR

%%

{WHITE_SAPCE}                           // ignore whitespace
\n																						 ;

{QUOTE}{DATES}{QUOTE}	     								yylval->date=strdup(yytext); RETURN_TOKEN(DATE);
[\-]?{DIGIT}+					                   yylval->number=atoi(yytext); RETURN_TOKEN(NUMBER);
[\-]?{DIGIT}+{DOT}{DIGIT}+				       yylval->floats=(float)(atof(yytext)); RETURN_TOKEN(FLOAT);

";"                 	 				           RETURN_TOKEN(SEMICOLON);
{DOT}                 					         RETURN_TOKEN(DOT);
"*"                   					         RETURN_TOKEN(STAR);
[Ee][Xx][Ii][Tt]						             RETURN_TOKEN(EXIT);
[Hh][Ee][Ll][Pp]                    	   RETURN_TOKEN(HELP);
[Dd][Ee][Ss][Cc]                         RETURN_TOKEN(DESC);
[Cc][Rr][Ee][Aa][Tt][Ee]                 RETURN_TOKEN(CREATE);
[Dd][Rr][Oo][Pp]                    	   RETURN_TOKEN(DROP);
[Tt][Aa][Bb][Ll][Ee]					           RETURN_TOKEN(TABLE);
[Tt][Aa][Bb][Ll][Ee][Ss]			           RETURN_TOKEN(TABLES);
[Ii][Nn][Dd][Ee][Xx]                  	 RETURN_TOKEN(INDEX);
[Oo][Nn]								                 RETURN_TOKEN(ON);
[Ss][Hh][Oo][Ww]                         RETURN_TOKEN(SHOW);
[Ss][Yy][Nn][Cc]                         RETURN_TOKEN(SYNC);
[Ss][Ee][Ll][Ee][Cc][Tt]                 RETURN_TOKEN(SELECT);
[Cc][Oo][Uu][Nn][Tt]                 yylval->string=strdup(yytext); RETURN_TOKEN(POLYKEY);
[Mm][Aa][Xx]                		yylval->string=strdup(yytext);	RETURN_TOKEN(POLYKEY);
[Mm][Ii][Nn]                		yylval->string=strdup(yytext);	RETURN_TOKEN(POLYKEY);
[Aa][Vv][Gg]						yylval->string=strdup(yytext);	RETURN_TOKEN(POLYKEY);
[Ff][Rr][Oo][Mm]                      	 RETURN_TOKEN(FROM);
[Ww][Hh][Ee][Rr][Ee]                  	 RETURN_TOKEN(WHERE);
[Aa][Nn][Dd]                             RETURN_TOKEN(AND);
[Oo][Rr][Dd][Ee][Rr][ ][Bb][Yy]		 		RETURN_TOKEN(ORDERBY);
[Gg][Rr][Oo][Uu][Pp][ ][Bb][Yy]				RETURN_TOKEN(GROUPBY);
[Aa][Ss][Cc]							 	RETURN_TOKEN(ASC);
[Ii][Nn][Nn][Ee][Rr][ ][Jj][Oo][Ii][Nn]		RETURN_TOKEN(INNERJOIN);
[Uu][Nn][Ii][Qq][Uu][Ee]				RETURN_TOKEN(UNIQUE);
[Nn][Uu][Ll][Ll][Aa][Bb][Ll][Ee]		RETURN_TOKEN(NULLABLE);
[Nn][Oo][Tt][ ][][Nn][Uu][Ll][Ll]		RETURN_TOKEN(NOTNULL);
[Ii][Ss]								RETURN_TOKEN(IS);
[Ii][Nn][Ss][Ee][rR][tT]                 RETURN_TOKEN(INSERT);
[Ii][Nn][Tt][Oo]					 	             RETURN_TOKEN(INTO);
[Vv][Aa][Ll][Uu][Ee][Ss]                 RETURN_TOKEN(VALUES);
[Dd][Ee][Ll][Ee][Tt][Ee]                 RETURN_TOKEN(DELETE);
[Uu][Pp][Dd][Aa][Tt][Ee]                 RETURN_TOKEN(UPDATE);
[Ss][Ee][Tt]							               RETURN_TOKEN(SET);
[Bb][Ee][Gg][Ii][Nn]                     RETURN_TOKEN(TRX_BEGIN);
[Cc][Oo][Mm][Mm][Ii][Tt]                 RETURN_TOKEN(TRX_COMMIT);
[Rr][Oo][Ll][Ll][Bb][Aa][Cc][Kk]         RETURN_TOKEN(TRX_ROLLBACK);
[Ii][Nn][Tt]					                   RETURN_TOKEN(INT_T);
[Cc][Hh][Aa][Rr]				                 RETURN_TOKEN(STRING_T);
[Ff][Ll][Oo][Aa][Tt]			               RETURN_TOKEN(FLOAT_T);
[Dd][Aa][Tt][Ee]							RETURN_TOKEN(DATE_T);
[Nn][Uu][Ll][Ll]						RETURN_TOKEN(NULL_T);
[Tt][Ee][Xx][Tt]							RETURN_TOKEN(TEXT_T);
[Ll][Oo][Aa][Dd]			                   RETURN_TOKEN(LOAD);
[Dd][Aa][Tt][Aa]	                       RETURN_TOKEN(DATA);
[Ii][Nn][Ff][Ii][Ll][Ee]                 RETURN_TOKEN(INFILE);
[Ii][Nn]				 													RETURN_TOKEN(IN);
[Nn][Oo][Tt][ ][Ii][Nn]										RETURN_TOKEN(NOTIN);


{ID}							                       yylval->string=strdup(yytext); RETURN_TOKEN(ID);
"("								                       RETURN_TOKEN(LBRACE);
")"								                       RETURN_TOKEN(RBRACE);
","                                      RETURN_TOKEN(COMMA);
"="                                      RETURN_TOKEN(EQ);
"<="                                     RETURN_TOKEN(LE);
"<>"                                     RETURN_TOKEN(NE);
"<"                                      RETURN_TOKEN(LT);
">="                                     RETURN_TOKEN(GE);
">"                                      RETURN_TOKEN(GT);
"+"								                       RETURN_TOKEN(PLUS);
"-"								                       RETURN_TOKEN(MINUS);
"/"								                       RETURN_TOKEN(DIVE);

{QUOTE}[\40\42\47A-Za-z0-9_/\.\-]*{QUOTE}	     yylval->string=strdup(yytext); RETURN_TOKEN(SSS);


.						                             printf("Unknown character [%c]\n",yytext[0]); return yytext[0];
%%

void scan_string(const char *str, yyscan_t scanner) {
	yy_switch_to_buffer(yy_scan_string(str, scanner), scanner);
}