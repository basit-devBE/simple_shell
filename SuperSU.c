#include "ichigos.h"
/**
 * check_dir - checks ":" if is in the current directory.
 * @path: the type char pointer char.
 * @m: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int check_dir(char *path, int *m)
{
	if (path[*m] == ':')
		return (1);

	while (path[*m] != ':' && path[*m])
	{
		*m += 1;
	}

	if (path[*m])
		*m += 1;

	return (0);
}
/**
 * w_command - locates a command
 * @cmd: command name
 * @env_variable: environment variable
 * Return: location of the command.
 */
char *w_command(char *cmd, char **env_variable)
{
	char *path, *ptr_path, *token_path, *d;
	int len_dir, len_cmd, u;
	struct stat st;

	path = obtainenv("PATH", env_variable);
	if (path)
	{
		ptr_path = Stardom(path);
		len_cmd = Length_ofString(cmd);
		token_path = split_string(ptr_path, ":");
		u = 0;
		while (token_path != NULL)
		{
			if (check_dir(path, &u))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = Length_ofString(token_path);
			d = malloc(len_dir + len_cmd + 2);
			concpy(d, token_path);
			concat(d, "/");
			concat(d, cmd);
			concat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ptr_path);
				return (d);
			}
			free(d);
			token_path = split_string(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * check_e - determines if is an executable
 * @dsh: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int check_e(ichigos_shell *dsh)
{
	struct stat st;
	int u;
	char *input;

	input = dsh->args[0];
	for (u = 0; input[u]; u++)
	{
		if (input[u] == '.')
		{
			if (input[u + 1] == '.')
				return (0);
			if (input[u + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[u] == '/' && u != 0)
		{
			if (input[u + 1] == '.')
				continue;
			u++;
			break;
		}
		else
			break;
	}
	if (u == 0)
		return (0);

	if (stat(input + u, &st) == 0)
	{
		return (u);
	}
	G_ERROR(dsh, 127);
	return (-1);
}
/**
 * check_SU_permission_cmd - verifies if user has permissions to access
 * @d: destination directory
 * @dsh: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_SU_permission_cmd(char *d, ichigos_shell *dsh)
{
	if (d == NULL)
	{
		G_ERROR(dsh, 127);
		return (1);
	}

	if (concomp(dsh->args[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			G_ERROR(dsh, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(dsh->args[0], X_OK) == -1)
		{
			G_ERROR(dsh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 * @dsh: data relevant
 * Return: 1 on success.
 */
int exec_cmd(ichigos_shell *dsh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int executable;
	char *d;
	(void) wpd;

	executable = check_e(dsh);
	if (executable == -1)
		return (1);
	if (executable == 0)
	{
		d = w_command(dsh->args[0], dsh->env_variable);
		if (check_SU_permission_cmd(d, dsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (executable == 0)
			d = w_command(dsh->args[0], dsh->env_variable);
		else
			d = dsh->args[0];
		execve(d + executable, dsh->args, dsh->env_variable);
	}
	else if (pd < 0)
	{
		perror(dsh->ichi[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	dsh->status = state / 256;
	return (1);
}
