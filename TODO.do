BUILTIN:

. export: need to export empty value/without = variable (only when export)

. cd doesn't create OLDPWD when program was started without environnement.

GEN.:

. protect the shell against segfault when current directory get deleted.

. move the here_doc gestion from lexer to parser (if time)

. correct readline graphic glitch


NORME, LEAK and TRIM UNEEDED file !!!

-------------------------------------------------------------------------------

Selim's Note:

!!! Handle cd when current dir is deleted

if launch without env, when first cd, create oldpwd in env

Fixing the here_doc

. When to clear the history
. Need to make small changes in expand_string.c (one line too long)
. Need to remove some debug functions
. expander2 ? main_parser ? main_lexer ?
. Delete misc, .vscode folders.
