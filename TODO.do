BUILTIN:

GEN.:

OPT-SIMON. move the here_doc gestion from lexer to parser (if time)

NORME, LEAK and TRIM UNEEDED file !!!

-------------------------------------------------------------------------------

Selim's Note:

Check your leaks
Need to make small changes in expand_string.c (one line too long)

------    TO DO BEFORE EVAL -------

. Need to remove some debug functions
. Need to remove ft_itoa_base from libft just to pass the eval
. expander2 ? main_parser ? main_lexer ?
. Delete misc, .vscode folders. !keep misc/valgrind.suppress


THIS SOULD WORKS
📁 ~/projects/minishell $ export LS="ls -la"
📁 ~/projects/4_circle/minishell $ <<end cat

LEXER OUTPUT: 

TOKEN_TYPE: 11	<<
TOKEN_TYPE: 0	end
TOKEN_TYPE: 0	cat
TOKEN_TYPE: 8	EOL

==39321== Warning: noted but unhandled ioctl 0x5412 with no size/direction hints.
==39321==    This could cause spurious value errors to appear.
==39321==    See README_MISSING_SYSCALL_OR_IOCTL for guidance on writing a proper wrapper.
📁 ~/projects/minishell $ $LS
