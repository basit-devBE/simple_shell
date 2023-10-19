#include "ichigos.h"
/**
 * PGLA - copies info to create
 * a fresh env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: fresh env or alias.
 */
char *PGLA(char *name, char *value)
{
	char *fresh;
	int len_name, Length_of_valueue, len;

	len_name = Length_ofString(name);
	Length_of_valueue = Length_ofString(value);
	len = len_name + Length_of_valueue + 2;
	fresh = malloc(sizeof(char) * (len));
	concpy(fresh, name);
	concat(fresh, "=");
	concat(fresh, value);
	concat(fresh, "\0");

	return (fresh);
}
/**
 * set_envV - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @dsh: data structure (environ)
 * Return: no return
 */
void set_envV(char *name, char *value, ichigos_shell *dsh)
{
	int u;
	char *var_env, *name_env;

	for (u = 0; dsh->env_variable[u]; u++)
	{
		var_env = Stardom(dsh->env_variable[u]);
		name_env = split_string(var_env, "=");
		if (concomp(name_env, name) == 0)
		{
			free(dsh->env_variable[u]);
			dsh->env_variable[u] = PGLA(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dsh->env_variable = prmalloc(dsh->env_variable, u, sizeof(char *) * (u + 2));
	dsh->env_variable[u] = PGLA(name, value);
	dsh->env_variable[u + 1] = NULL;
}

/**
 * compa_env_names - compares env variables names
 * with the name passed.
 * @dsh: data relevant (env name and env value)
 * Return: 1 on success.
 */
int compa_env_names(ichigos_shell *dsh)
{

	if (dsh->args[1] == NULL || dsh->args[2] == NULL)
	{
		G_ERROR(dsh, -1);
		return (1);
	}

	set_envV(dsh->args[1], dsh->args[2], dsh);

	return (1);
}

/**
 * del_env - deletes a environment variable
 * @dsh: data relevant (env name)
 * Return: 1 on success.
 */
int del_env(ichigos_shell *dsh)
{
	char **reallocenv_variable;
	char *var_env, *name_env;
	int i, j, k;

	if (dsh->args[1] == NULL)
	{
		G_ERROR(dsh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; dsh->env_variable[i]; i++)
	{
		var_env = Stardom(dsh->env_variable[i]);
		name_env = split_string(var_env, "=");
		if (concomp(name_env, dsh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		G_ERROR(dsh, -1);
		return (1);
	}
	reallocenv_variable = malloc(sizeof(char *) * (i));
	for (i = j = 0; dsh->env_variable[i]; i++)
	{
		if (i != k)
		{
			reallocenv_variable[j] = dsh->env_variable[i];
			j++;
		}
	}
	reallocenv_variable[j] = NULL;
	free(dsh->env_variable[k]);
	free(dsh->env_variable);
	dsh->env_variable = reallocenv_variable;
	return (1);
}
