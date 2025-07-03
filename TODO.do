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

. When to clear the history
. Need to remove some debug functions
. Can't use realloc in expand/get_arg
. Only norms errors in expanders and debug
. Remove ft_itoa_base from libft, just to passed the project. Will refactor later.
. Need to make small changes in expand_string.c (two lines too long)
. expander2 ?
