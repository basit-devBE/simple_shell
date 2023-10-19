#include "ichigos.h"
/**
 * right_var - checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void right_var(dame **h, char *in, ichigos_shell *data)
{
	int row, chr, k, lval;
	char **_envr;

	_envr = data->env_variable;
	for (row = 0; _envr[row]; row++)
	{
		for (k = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = Length_ofString(_envr[row] + chr + 1);
				AddVariable(h, k, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[k] == _envr[row][chr])
				k++;
			else
				break;
		}
	}

	for (k = 0; in[k]; k++)
	{
		if (in[k] == ' ' || in[k] == '\t' || in[k] == ';' || in[k] == '\n')
			break;
	}

	AddVariable(h, k, NULL, 0);
}
/**
 * more_money - check if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int more_money(dame **h, char *in, char *st, ichigos_shell *data)
{
	int x, lst, lpd;

	lst = Length_ofString(st);
	lpd = Length_ofString(data->process_id);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				AddVariable(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				AddVariable(h, 2, data->process_id, lpd), x++;
			else if (in[x + 1] == '\n')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == '\0')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == ' ')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == '\t')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == ';')
				AddVariable(h, 0, NULL, 0);
			else
				right_var(h, in + x, data);
		}
	}

	return (x);
}

/**
 * rep_i - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *rep_i(dame **head, char *input, char *new_input, int nlen)
{
	dame *indx;
	int x, y, z;

	indx = *head;
	x = y = 0;
	while (y < nlen)
	{
		if (input[y] == '$')
		{
			if (!(indx->Length_of_variable) && !(indx->Length_of_value))
			{
				new_input[x] = input[y];
				y++;
			}
			else if (indx->Length_of_variable && !(indx->Length_of_value))
			{
				for (z = 0; z < indx->Length_of_variable; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < indx->Length_of_value; z++)
				{
					new_input[x] = indx->val[z];
					x++;
				}
				y += (indx->Length_of_variable);
				x--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[x] = input[y];
			y++;
		}
	}

	return (new_input);
}
/**
 * replace_variable - calls functions to replace string into vars
 * @input: input string
 * @dsh: data structure
 * Return: replaced string
 */
char *replace_variable(char *input, ichigos_shell *dsh)
{
	dame *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = int_toString(dsh->status);
	head = NULL;

	olen = more_money(&head, input, status, dsh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->Length_of_value - indx->Length_of_variable);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = rep_i(&head, input, new_input, nlen);

	free(input);
	free(status);
	FreeVariable(&head);

	return (new_input);
}
