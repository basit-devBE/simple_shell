#include "ichigos.h"
/**
 * G_ERROR - calls the error according the builtin, syntax or permission
 * @dsh: data structure that contains arguments
 * @eva: the error value
 * Return: error
 */
int G_ERROR(ichigos_shell *dsh, int eva)
{
	char *e;

	switch (eva)
	{
	case -1:
		e = error_info(dsh);
		break;
	case 126:
		e = path_error_info(dsh);
		break;
	case 127:
		e = generic_msg(dsh);
		break;
	case 2:
		if (concomp("exit", dsh->args[0]) == 0)
			e = exit_get(dsh);
		else if (concomp("cd", dsh->args[0]) == 0)
			e = error_cd_msg(dsh);
		break;
	}

	if (e)
	{
		write(STDERR_FILENO, e, Length_ofString(e));
		free(e);
	}

	dsh->status = eva;
	return (eva);
}
/**
 * sing_line - Handle crtl + c call in prompt
 * @sig: Signal handler
 */
void sing_line(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
/**
 * READLINE- reads the input string.
 * @dub: return value of getline function
 * Return: input string
 */

char *READLINE(int *dub)
{
	char *input = NULL;
	size_t bufsize = 0;

	*dub = getline(&input, &bufsize, stdin);

	return (input);
}

/**
 * kano - finds builtins and commands
 * @dsh: data relevant (args)
 * Return: 1 on success.
 */
int kano(ichigos_shell *dsh)
{
	int (*builtin)(ichigos_shell *dsh);

	if (dsh->args[0] == NULL)
		return (1);

	builtin = builtINFunctions(dsh->args[0]);

	if (builtin != NULL)
		return (builtin(dsh));

	return (exec_cmd(dsh));
}
