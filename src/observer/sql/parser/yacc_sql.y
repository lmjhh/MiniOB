
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length; //Select 栈的深度
  size_t condition_length;
  size_t from_length;
  size_t value_length;

	//做一个快照
  size_t condition_length_tmp[5];
  size_t from_length_tmp[5];
  size_t value_length_tmp[5];
	CompOp comp_tmp[5];

  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  int order_by_type;
  int nullable;
  Exp exp[2];
  int exp_length;
	Selects selects[3];

	int selects_tmp_pool_length;
	Selects selects_tmp_pool[5];
	Exp exp_pool[6];
	int exp_pool_length;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->exp_length = 0;
  context->ssql->sstr.insertion.tuple_num = 0;
  printf(". error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
		DATE_T
        STRING_T
        FLOAT_T
		NULL_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
		MAX
		MIN
		COUNT
		AVG
		ORDERBY
		ASC
		INNERJOIN
		UNIQUE
		NULLABLE
		NOTNULL
		IS
		GROUPBY
		IN
		NOTIN
		PLUS
		MINUS
		DIVE

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  char *date;
  int number;
  float floats;
  int isNULL;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <date> DATE

%token <string> SSS
%token <string> STAR
%token <string> STRING_V
%token <string> POLYKEY
//非终结符

%left  PLUS MINUS
%left  STAR DIVE
%nonassoc UMINUS

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $7);
		}
	| CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $8);			
		}
    ;
id_list:
/* empty */
| COMMA ID id_list {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,$2);
}
;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type null LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $5, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type null
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;

null:
	/* empty */{
		CONTEXT->nullable = 0;
	}
	| NOTNULL {
		CONTEXT->nullable = 0;
	}
	| NULLABLE {
		CONTEXT->nullable = 1;
	}
	;

number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
	   | DATE_T { $$=DATES; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
	   | NULL_T {$$=NULLS;}
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list  SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
	  		//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
			CONTEXT->value_length=0;
    }
	;
	
values_list:
/* empty */
| COMMA LBRACE value value_list RBRACE values_list{
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
;

value_list:
    /* empty */ {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
	DATE {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|NULL_T {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
	}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;

select:				/*  select 语句的语法解析树*/
    SELECT select_mix FROM ID rel_list inner_join where group_by order_by SEMICOLON 
		{

			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $4);
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions,0, CONTEXT->condition_length);
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length];
			CONTEXT->ssql->flag = SCF_SELECT;
			
			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length = 0;
			CONTEXT->value_length = 0;
			CONTEXT->order_by_type = 0;
			CONTEXT->selects_tmp_pool_length=0;
	}

	| left_brace SELECT select_mix FROM ID rel_list inner_join where group_by order_by RBRACE
	{
			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $5);
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions, CONTEXT->condition_length_tmp[CONTEXT->select_length - 1], CONTEXT->condition_length);
			
			//临时变量退栈
			CONTEXT->select_length--;
			CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
			CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
			CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

			if(CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub == 0){
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub = 1;


				selects_swap_with_other(&CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length], &CONTEXT->selects[CONTEXT->select_length + 1]);
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length];
				CONTEXT->selects_tmp_pool_length++;
			}else{
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_left_sub = 1;
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub = 1;

				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].left_sub_select = CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select;	

				selects_swap_with_other(&CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length], &CONTEXT->selects[CONTEXT->select_length + 1]);
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length];			
				CONTEXT->selects_tmp_pool_length++;
			}

			CONTEXT->selects_tmp_pool_length = CONTEXT->selects_tmp_pool_length % (5);
	}
	;

left_brace:
	LBRACE {
		CONTEXT->condition_length_tmp[CONTEXT->select_length] = CONTEXT->condition_length;
		CONTEXT->value_length_tmp[CONTEXT->select_length] = CONTEXT->value_length;
		CONTEXT->from_length_tmp[CONTEXT->select_length] = CONTEXT->from_length;
		CONTEXT->select_length++;
	}
	;

select_mix:
	STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
    | ID  mix_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
	| ID DOT ID mix_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
	| ID DOT STAR mix_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
	| POLYKEY LBRACE poly_value RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
	| POLYKEY LBRACE STAR RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| POLYKEY LBRACE ID RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $3);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
	| POLYKEY LBRACE ID DOT ID RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $3, $5);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
	| POLYKEY LBRACE ID DOT STAR RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $3, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
  ;


mix_list:
	/* empty */
	| COMMA ID  mix_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
	| COMMA ID DOT ID mix_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
	| COMMA ID DOT STAR mix_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
	| COMMA POLYKEY LBRACE poly_value RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
	| COMMA POLYKEY LBRACE STAR RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| COMMA POLYKEY LBRACE ID RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $4);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
	| COMMA POLYKEY LBRACE ID DOT ID RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $4, $6);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
	| COMMA POLYKEY LBRACE ID DOT STAR RBRACE mix_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $4, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
  ;


select_attr:
    STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
    | ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
  	| ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
	| ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
    ;


poly_key:
	POLYKEY{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);

	}
	;

select_poly:
	POLYKEY LBRACE poly_value RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");

	}
	|	POLYKEY LBRACE STAR RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| 	POLYKEY LBRACE ID RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $3);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| 	POLYKEY LBRACE ID DOT ID RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $3, $5);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| POLYKEY LBRACE ID DOT STAR RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $1);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $3, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	;


poly_list:
	/* empty */
	| COMMA POLYKEY LBRACE poly_value RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");

	}
	| COMMA	POLYKEY LBRACE STAR RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| COMMA	POLYKEY LBRACE ID RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $4);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| COMMA	POLYKEY LBRACE ID DOT ID RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $4, $6);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	| COMMA POLYKEY LBRACE ID DOT STAR RBRACE poly_list{
		Poly poly_tmp;
		poly_init(&poly_tmp, $2);
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, $4, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
	;


poly_value:
    NUMBER{	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, $1);
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, $1);
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, $1);
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	
    ;

select_attr_poly:
	poly_value{  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			// selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
	| STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			// selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
    | ID attr_list_poly {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			// selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
  	| ID DOT ID attr_list_poly {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			// selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
	| ID DOT STAR attr_list_poly {
			RelAttr attr;
			relation_attr_init(&attr, $1, "*");
			// selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
	;

attr_list:
    /* empty */
    | COMMA ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
    | COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
  	;

attr_list_poly:
    /* empty */
  	;


rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $2);
		  }
    ;

inner_join:
	/* empty */
	| INNERJOIN ID inner_join_on condition condition_list inner_join {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $2);
	}
	;
inner_join_on:
	ON {
		Condition condition;
		condition_init_with_comp(&condition, NO_OP);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;	
	}
	;
where:
    /* empty */ 
    | where_key condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
where_key:
		WHERE{
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
		;

condition_list:
    /* empty */
    | and_key condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
and_key:
		AND {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
		;

expression:
	expression PLUS expression{ 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "+");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1+$3; 
		}
    | expression MINUS expression  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1-$3; 
		}
    | expression STAR expression  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "*");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1*$3; 
		}
    | expression DIVE expression {
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "/");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
        }
    | LBRACE expression RBRACE {
		//$$=$2; 
		}
    | value { 
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		ExpNode expnode;
		expnode_init(&expnode, 1, value, NULL, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1; 
		}
	| ID {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

	}
    ;


condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);

			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|value comOp value 
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
	| expression comOp expression {
		exp_swap_with_other(&CONTEXT->exp_pool[CONTEXT->exp_pool_length], &CONTEXT->exp[0]);
		CONTEXT->exp_pool_length++ ;
		exp_swap_with_other(&CONTEXT->exp_pool[CONTEXT->exp_pool_length], &CONTEXT->exp[1]);

		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &CONTEXT->exp_pool[CONTEXT->exp_pool_length-1], 1, &CONTEXT->exp_pool[CONTEXT->exp_pool_length]);
		CONTEXT->exp_pool_length = CONTEXT->exp_pool_length % MAX_NUM;
		// 将临时变量清空
		 exp_destroy(&CONTEXT->exp[0]);
		 exp_destroy(&CONTEXT->exp[1]);
		CONTEXT->exp_length = 0;
	}
	| value IS NULL_T {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
	| value IS NOTNULL {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, left_value, 0, NULL, &right_value);
	} 
	| ID IS NULL_T {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
	| ID IS NOTNULL {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
	| ID DOT ID IS NULL_T {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);

	}
	| ID DOT ID IS NOTNULL {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		Value right_value;	
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
	| NULL_T IS value{
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 0, NULL, right_value);
	}

	| NULL_T IS ID {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}

	| NULL_T IS ID DOT ID{
		RelAttr right_attr;
		relation_attr_init(&right_attr, $3, $5);
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}

	| NULL_T IS NOTNULL {
		Value left_value;
		value_init_null(&left_value, 0);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, &left_value, 0, NULL, &right_value);
	}

	| ID in_or_not_in select {

		// //临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = 	left_attr;
	}

	| ID DOT ID in_or_not_in select{

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = 	left_attr;
	}

	| ID comOp select{

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
	}

	| ID DOT ID comOp select{

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
	}

	| select comOp ID{		//放 condition 左边了 改一下符号

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		switch(CONTEXT->comp_tmp[CONTEXT->select_length]){
			case LESS_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN;
			break;
			case LESS_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL;
			break;
			case GREAT_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN;
			break;
			case GREAT_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL;
			break;
			default:
			break;
		}

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $3);	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;

	}

	| select comOp ID DOT ID {

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		//放 condition 左边了 改一下符号
		switch(CONTEXT->comp_tmp[CONTEXT->select_length]){
			case LESS_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN;
			break;
			case LESS_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL;
			break;
			case GREAT_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN;
			break;
			case GREAT_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL;
			break;
			default:
			break;
		}

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, $3, $5);	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
	}

	| select comOp select{
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
	}
  ;

in_or_not_in:
	IN {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_IN;
	}
	| NOTIN {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_NO_IN;
	}
	;

comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; CONTEXT->exp_length++; CONTEXT->comp_tmp[CONTEXT->select_length] = NOT_EQUAL; }
    ;


order_by:
	/* empty */
	| ORDERBY order_by_attr order_by_list {
		
	}
	;
	order_by_list:
	/* empty */
	| COMMA order_by_attr order_by_list {
			
	}
	;

	order_by_attr:
	ID order_by_type {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
	| ID DOT ID order_by_type {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
	;
	order_by_type:
	/* empty */{
		CONTEXT->order_by_type = 0;
	}
	| ASC {
		CONTEXT->order_by_type = 0;
	}
	| DESC {
		CONTEXT->order_by_type = 1;
	}
	;

group_by:
	/* empty */
	| GROUPBY group_by_attr group_by_list {

	}
	;
	group_by_list:
	/* empty */
	| COMMA group_by_attr group_by_list {
			
	}
	;

	group_by_attr:
	ID order_by_type {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
	| ID DOT ID order_by_type {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
	;	


load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
	printf("context size = %d B\n",sizeof(context));
	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
