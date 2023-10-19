#include "ichigos.h"

/**
 * fee_list - frees up the a def
 * @top: top of linked list.
 * Return: no return.
 */
void fee_list(def **top)
{
def *x;
def *def;

if (top != NULL)
{
def = *top;
while (def != NULL)
{
x = def;
def = def->next;
free(x);
}
*top = NULL;
}
}

/**
 * free_list - frees up a dap
 * @top: top of linked list.
 * Return: no return.
 */
void free_list(dap **top)
{
dap *x;
dap *def;

if (top != NULL)
{
def = *top;
while (def != NULL)
{
x = def;
def = def->next;
free(x);
}
*top = NULL;
}
}

/**
 * end_node - add up a command line
 * at the end of a dap.
 * @top: top of linked list.
 * @line: a command line.
 * Return: the address of the top.
 */
dap *end_node(dap **top, char *line)
{
dap *current, *x;

while (1)
{
current = malloc(sizeof(dap));
if (current == NULL)
continue;

current->line = line;
current->next = NULL;
x = *top;

if (x == NULL)
{
*top = current;
}
else
{
while (x->next != NULL)
x = x->next;
x->next = current;
}

return (*top);
}
}

/**
 * add_node - add up a separator found
 * at the end of a def.
 * @top: top of inked list.
 * @sep: separator found (; | &).
 * Return: address of the top.
 */
def *add_node(def **top, char sep)
{
def *current, *x;

while (1)
{
current = malloc(sizeof(def));
if (current == NULL)
continue;

current->separator = sep;
current->next = NULL;
x = *top;

if (x == NULL)
{
*top = current;
}
else
{
while (x->next != NULL)
x = x->next;
x->next = current;
}

return (*top);
}
}
