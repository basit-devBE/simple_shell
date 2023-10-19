#include "ichigos.h"

/**
 * count_repchar - counts the repetitions of a char
 * @input: input string
 * @u: the index
 * Return: repetitions
 */
int count_repchar(char *input, int u)
{
	if (*(input - 1) == *input)
		return (count_repchar(input - 1, u + 1));

	return (u);
}
/**
 * syntax_err - finds syntax errors
 * @input: input string
 * @u: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int syntax_err(char *input, int u, char last)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syntax_err(input + 1, u + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (u);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (u);

		if (last == '|')
		{
			c = count_repchar(input, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (u);

		if (last == '&')
		{
			c = count_repchar(input, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	return (syntax_err(input + 1, u + 1, *input));
}
/**
 * index_char - finds index of the first char
 * @input: input string
 * @u: index
 * Return: 1 if there is an error. 0 in other case.
 */
int index_char(char *input, int *u)
{
	for (*u = 0; input[*u]; *u += 1)
	{
		if (input[*u] == ' ' || input[*u] == '\t')
			continue;

		if (input[*u] == ';' || input[*u] == '|' || input[*u] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * split - splits command lines according to
 * the separators ;, | and &, and executes them
 * @dsh: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split(ichigos_shell *dsh, char *input)
{

	def *x, *l_s;
	dap *y, *l_l;
	int loop;

	x = NULL;
	y = NULL;

	addSeparators_and_cdLists(&x, &y, input);

	l_s = x;
	l_l = y;

	while (l_l != NULL)
	{
		dsh->input = l_l->line;
		dsh->args = splityy(dsh->input);
		loop = kano(dsh);
		free(dsh->args);

		if (loop == 0)
			break;

		nextInLine(&l_s, &l_l, dsh);

		if (l_l != NULL)
			l_l = l_l->next;
	}

	fee_list(&x);
	free_list(&y);

	if (loop == 0)
		return (0);
	return (1);
}
/**
 * error_message- prints when a syntax error is found
 * @dsh: data structure
 * @input: input string
 * @u: index of the error
 * @bool: to control mg error
 * Return: no return
 */
void error_message(ichigos_shell *dsh, char *input, int u, int bool)
{
	char *mg, *mg2, *mg3, *e, *counter;
	int lth;

	if (input[u] == ';')
	{
		if (bool == 0)
			mg = (input[u + 1] == ';' ? ";;" : ";");
		else
			mg = (input[u - 1] == ';' ? ";;" : ";");
	}

	if (input[u] == '|')
		mg = (input[u + 1] == '|' ? "||" : "|");

	if (input[u] == '&')
		mg = (input[u + 1] == '&' ? "&&" : "&");

	mg2 = ": Syntax error: \"";
	mg3 = "\" unexpected\n";
	counter = int_toString(dsh->counter);
	lth = Length_ofString(dsh->ichi[0]) + Length_ofString(counter);
	lth += Length_ofString(mg) + Length_ofString(mg2) + Length_ofString(mg3) + 2;

	e = malloc(sizeof(char) * (lth + 1));
	if (e == 0)
	{
		free(counter);
		return;
	}
	concpy(e, dsh->ichi[0]);
	concat(e, ": ");
	concat(e, counter);
	concat(e, mg2);
	concat(e, mg);
	concat(e, mg3);
	concat(e, "\0");

	write(STDERR_FILENO, e, lth);
	free(e);
	free(counter);
}
