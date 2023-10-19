#include "ichigos.h"

/**
 *_help_ - Help info for builtin help.
 * Return: no return
 */
void _help_(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "\tChange the working directory.\n ";
	write(STDOUT_FILENO, help, Length_ofString(help));
}
/**
 * help_opt - option for help function
 * Return: no return
*/

void help_opt(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "\tDisplay information about commands.\n ";
	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "Display brief summary of builtin commands.\n";
	write(STDOUT_FILENO, help, Length_ofString(help));
}
/**
 * a_help_opt - same stuff
 * Return: no reurn
*/

void a_help_opt(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, Length_ofString(help));
}


/**
 * HELP - function that retrieves help messages according builtin
 * @dsh: data structure (args and input)
 * Return: Return 0
*/
int HELP(ichigos_shell *dsh)
{

	if (dsh->args[1] == 0)
		gen_h();
	else if (concomp(dsh->args[1], "setenv") == 0)
		h_env_setup_env();
	else if (concomp(dsh->args[1], "env") == 0)
		h_env();
	else if (concomp(dsh->args[1], "unsetenv") == 0)
		h_env_setdown_env();
	else if (concomp(dsh->args[1], "help") == 0)
		help_opt();
	else if (concomp(dsh->args[1], "exit") == 0)
		exit_h();
	else if (concomp(dsh->args[1], "cd") == 0)
		_help_();
	else if (concomp(dsh->args[1], "alias") == 0)
		a_help_opt();
	else
		write(STDERR_FILENO, dsh->args[0],
		      Length_ofString(dsh->args[0]));

	dsh->status = 0;
	return (1);
}
