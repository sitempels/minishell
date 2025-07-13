Check leaks for more advanced commands
Need to make small changes in expand_string.c (one line too long)
MAYBE WE CAN FIND A GOOD FRIEND THAT CAN TRY SOME COMMANDS AND CHECK IF EVERYTHING WORKS LIKE EXPECTED

-------------------------------------------------------------------------------

. Need to remove some debug functions
. Need to remove ft_itoa_base from libft just to pass the eval
. expander2 ? main_parser ? main_lexer ?
. Delete misc, .vscode folders. !keep misc/valgrind.suppress

-------------------------------------------------------------------------------

LEXER OUTPUT: 

TOKEN_TYPE: 11	<<
TOKEN_TYPE: 0	end
TOKEN_TYPE: 0	cat
TOKEN_TYPE: 8	EOL

==39321== Warning: noted but unhandled ioctl 0x5412 with no size/direction hints.
==39321==    This could cause spurious value errors to appear.
==39321==    See README_MISSING_SYSCALL_OR_IOCTL for guidance on writing a proper wrapper.

PROBLEM WITH SIGNAL SIGINT (TRY TO SET SIGNAL ELSEWHERE)

-------------------------------------------------------------------------------

EXIT/RETURN STATUS FIXED

verify the value returned in evvery case.
Some off them may not be the correct one.

-------------------------------------------------------------------------------

check ft_error

-------------------------------------------------------------------------------

MOSTLY WORK, DETAILS ON ctrl+\ TO DO AND CHECK CORRECTNESS OF THE OTHERS SIGNALS

SIG:
on empty prompt:	ctr+C: ok
			ctrl+D: ok
			ctr+\: ok

on non_empty prompt:	ctr+C: ok
			ctrl+D: ok
			ctr+\: okeyish (they say it need to quit the shell, but bash does nothing)
				=> my guess, it's actually to make it easier to implement. We could as (see below ->pt3)

blocking cmd with:	ctrl+C: work but display multiple prompt
			ctrl+D: work
			ctr+\c: doesn't work

pt3: For ctrl+\, I guess we could implement the following behaviour:	if prompt empty, does nothing.
									if prompt non empty, quit.
