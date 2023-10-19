#include "ichigos.h"

/**
 * builtINFunctions - builtin that passes the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*builtINFunctions(char *cmd))(ichigos_shell *)
{
	builtin_t builtIN[] = {
		{ "env", print_env },
		{ "exit", lefshell },
		{ "setenv", compa_env_names },
		{ "unsetenv", del_env },
		{ "cd", CD },
		{ "help", HELP },
		{ NULL, NULL }
	};
	int u;

	for (u = 0; builtIN[u].name; u++)
	{
		while (concomp(builtIN[u].name, cmd) == 0)
			break;
	}

	return (builtIN[u].f);
}


/**
 * string_toInt - changes a string to an integer.
 * @s: the input string.
 * Return: an integer.
 */
int string_toInt(char *s)
{
	unsigned int total = 0, size = 0, oi = 0, pn = 1, m = 1, r;

	while (*(s + total) != '\0')
	{
		if (size > 0 && (*(s + total) < '0' || *(s + total) > '9'))
			break;

		if (*(s + total) == '-')
			pn *= -1;

		if ((*(s + total) >= '0') && (*(s + total) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		total++;
	}

	for (r = total - size; r < total; r++)
	{
		oi = oi + ((*(s + r) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}


/**
 *getInt_length - Get the lenght of the number.
 * @n: the type int number.
 * Return: the lenght of the number.
 */
int getInt_length(int n)
{
	unsigned int x;
	int y = 1;

	if (n < 0)
	{
		y++;
		x = n * -1;
	}
	else
	{
		x = n;
	}
	while (x > 9)
	{
		y++;
		x = x / 10;
	}

	return (y);
}

/**
 * int_toString - function changes int to string.
 * @n: the type int number
 * Return: a String.
 */
char *int_toString(int n)
{
	unsigned int x;
	int y = getInt_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (y + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + y) = '\0';

	if (n < 0)
	{
		x = n * -1;
		buffer[0] = '-';
	}
	else
	{
		x = n;
	}

	y--;
	do {
		*(buffer + y) = (x % 10) + '0';
		x = x / 10;
		y--;
	}
	while (x > 0)
		;
	return (buffer);
}

/**
 * case_intfunc - intermediate function to
 * find and print a syntax error
 * @dsh: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int case_intfunc(ichigos_shell *dsh, char *input)
{
	int b = 0;
	int f_char = 0;
	int i = 0;

	f_char = index_char(input, &b);
	if (f_char == -1)
	{
		error_message(dsh, input, b, 0);
		return (1);
	}

	i = syntax_err(input + b, 0, *(input + b));
	if (i != 0)
	{
		error_message(dsh, input, b + i, 1);
		return (1);
	}

	return (0);
}

