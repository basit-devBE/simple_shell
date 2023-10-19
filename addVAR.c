#include "ichigos.h"

/**
 * add_rvar_node - adds up a variable
 * at the end of a dame list.
 * @head: head of linked list.
 * @lvar: the length of variable.
 * @val: the value of variable.
 * @lval:the length of value.
 * Return: the address of the head.
 */
dame *AddVariable(dame **head, int lvar, char *val, int lval)
{
	dame *fresh, *x;

	fresh = malloc(sizeof(dame));
	if (fresh == NULL)
		return (NULL);

	fresh->Length_of_variable = lvar;
	fresh->val = val;
	fresh->Length_of_value = lval;

	fresh->next = NULL;
	x = *head;

	if (x == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (x->next != NULL)
			x = x->next;
		x->next = fresh;
	}

	return (*head);
}

/**
 * FreeVariable - frees up a dame list
 * @head: head of linked list.
 * Return: no return.
 */
void FreeVariable(dame **head)
{
	dame *x;
	dame *curl;

	if (head != NULL)
	{
		curl = *head;
		while ((x = curl) != NULL)
		{
			curl = curl->next;
			free(x);
		}
		*head = NULL;
	}
}

/**
 * path_error_info - the error info for env in get_env.
 * @dsh: data relevant (counter, arguments)
 * Return: an error message.
 */


char *path_error_info(ichigos_shell *dsh)
{
	int lathum;
	char *d_s;
	char *o;

	d_s = int_toString(dsh->counter);
	lathum = Length_ofString(dsh->ichi[0]) + Length_ofString(d_s);
	lathum += Length_ofString(dsh->args[0]) + 24;
	o = malloc(sizeof(char) * (lathum + 1));
	if (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}
	concpy(o, dsh->ichi[0]);
	concat(o, ": ");
	concat(o, d_s);
	concat(o, ": ");
	concat(o, dsh->args[0]);
	concat(o, ": insufficient permission\n");
	concat(o, "\0");
	free(d_s);
	return (o);
}
/**
 * error_info - error info for path and failure denied permission.
 * @dsh: data relevant (counter, arguments).
 * Return: error string.
 */

char *error_info(ichigos_shell *dsh)
{
	int lathum;
	char *o;
	char *d_s;
	char *message;

	d_s = int_toString(dsh->counter);
	message = ": Cannot add or Remove environment\n";
	lathum = Length_ofString(dsh->ichi[0]) + Length_ofString(d_s);
	lathum += Length_ofString(dsh->args[0]) + Length_ofString(message) + 4;
	o = malloc(sizeof(char) * (lathum + 1));
	if (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}

	concpy(o, dsh->ichi[0]);
	concat(o, ": ");
	concat(o, d_s);
	concat(o, ": ");
	concat(o, dsh->args[0]);
	concat(o, message);
	concat(o, "\0");
	free(d_s);

	return (o);
}


