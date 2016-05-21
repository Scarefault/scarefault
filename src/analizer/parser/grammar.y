%scanner                  ../scanner/Scanner.h
%scanner-token-function   d_scanner.lex()
%baseclass-preinclude     ParserPreinclude.h

%stype std::string
%start startrule

%include spec/tokens.y

%%

startrule:
  // Empty Rule.
|
  startrule content
;

%include newspec/content.y

//%include spec/values.y
//%include spec/types_modifiers.y
//%include spec/expr_stmt.y
//%include spec/variable_stmt.y
//%include spec/method_stmt.y
//%include spec/control_structure_stmt.y
//%include spec/oop_stmt.y
//%include spec/content_stmt.y
//%include spec/content.y
