#include "../../includes/minishell.h"

void	echo_builtin(const char *str, bool newline)
{
	if (newline)
		printf("%s\n", str);
	else
		printf("%s", str);
}
