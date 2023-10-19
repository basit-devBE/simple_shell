#include "ichigos.h"

/**
 * print_env - prints the evironment variables
 * @dsh: data relevant.
 * Return: 1 on success.
 */
int print_env(ichigos_shell *dsh)
{
	int g, h;

	for (g = 0; dsh->env_variable[g]; g++)
	{

		for (h = 0; dsh->env_variable[g][h]; h++)
			;

		write(STDOUT_FILENO, dsh->env_variable[g], h);
		write(STDOUT_FILENO, "\n", 1);
	}
	dsh->status = 0;

	return (1);
}
/**
 * compare_envnames - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_envnames(const char *nenv, const char *name)
{
	int m;

	for (m = 0; nenv[m] != '='; m++)
	{
		if (nenv[m] != name[m])
		{
			return (0);
		}
	}

	return (m + 1);
}
/**
 * obtainenv - get an environment variable
 * @name: name of the environment variable
 * @env_variable: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *obtainenv(const char *name, char **env_variable)
{
	char *ptr_env;
	int n, mov;

	ptr_env = NULL;
	mov = 0;

	for (n = 0; env_variable[n]; n++)
	{
		mov = compare_envnames(env_variable[n], name);
		if (mov)
		{
			ptr_env = env_variable[n];
			break;
		}
	}

	return (ptr_env + mov);
}


/**
 * check_if_int - defines if string passed is a number
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int check_if_int(const char *s)
{
unsigned int u;

u = 0;
while (s[u])
{
if (s[u] < 48 || s[u] > 57)
return (0);
u++;
}
return (1);
}

/**
 * ReverseString - reverses a stribg.
 * @s: input string.
 * Return: no return.
 */
void ReverseString(char *s)
{
int count = 0, a, b;
char *string, x;

for (count = 0; s[count] != '\0'; count++)
{
string = s;
}

a = 0;
while (a < count - 1)
{
b = a + 1;
while (b > 0)
{
x = *(string + b);
*(string + b) = *(string + (b - 1));
*(string + (b - 1)) = x;
b--;
}
a++;
}
}
