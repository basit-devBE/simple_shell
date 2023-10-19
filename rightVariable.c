#include "ichigos.h"

/**
 * non_printed_char_swap - swaps | and & for non-printed chars
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *non_printed_char_swap(char *input, int bool)
{
int u;

if (bool == 0)
{
u = 0;
while (input[u])
{
if (input[u] == '|')
{
if (input[u + 1] != '|')
input[u] = 16;
else
u++;
}

if (input[u] == '&')
{
if (input[u + 1] != '&')
input[u] = 12;
else
u++;
}
u++;
}
}
else
{
u = 0;
while (input[u])
{
input[u] = (input[u] == 16 ? '|' : input[u]);
input[u] = (input[u] == 12 ? '&' : input[u]);
u++;
}
}
return (input);
}
/**
 * addSeparators_and_cdLists - add separators and command lines in the lists
 * @hs: head of separator list
 * @hl: head of command lines list
 * @input: input string
 * Return: no return
 */
void addSeparators_and_cdLists(def **hs, dap **hl, char *input)
{
	int u;
	char *line;

	input = non_printed_char_swap(input, 0);

	for (u = 0; input[u]; u++)
	{
		if (input[u] == ';')
			add_node(hs, input[u]);

		if (input[u] == '|' || input[u] == '&')
		{
			add_node(hs, input[u]);
			u++;
		}
	}

	line = split_string(input, ";|&");
	do {
		line = non_printed_char_swap(line, 1);
		end_node(hl, line);
		line = split_string(NULL, ";|&");
	} while (line != NULL);

}
/**
 * nextInLine - go to the next command line stored
 * @l_s: separator list
 * @l_l: command line list
 * @dsh: data structure
 * Return: no return
 */
void nextInLine(def **l_s, dap **l_l, ichigos_shell *dsh)
{
	int loop_sep;
	def *ls_s;
	dap *ls_l;

	loop_sep = 1;
	ls_s = *l_s;
	ls_l = *l_l;

	while (ls_s != NULL && loop_sep)
	{
		if (dsh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*l_s = ls_s;
	*l_l = ls_l;
}


/**
 * splityy - tokenizes the input string
 * @input: input string.
 * Return: string splitted.
 */
char **splityy(char *input)
{
	size_t bs;
	size_t u;
	char **tokens;
	char *token;

	bs = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bs));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = split_string(input, TOK_DELIM);
	tokens[0] = token;

	for (u = 1; token != NULL; u++)
	{
		if (u == bs)
		{
			bs += TOK_BUFSIZE;
			tokens = prmalloc(tokens, u, sizeof(char *) * bs);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = split_string(NULL, TOK_DELIM);
		tokens[u] = token;
	}

	return (tokens);
}
