#include "ichigos.h"

/**
 * bigups - concatenates the message for cd error
 * @dsh: data relevant (directory)
 * @message: message to print
 * @o: output message
 * @d_s: counter lines
 * Return: error message
 */
char *bigups(ichigos_shell *dsh, char *message, char *o, char *d_s)
{
char *awful_flag;

concpy(o, dsh->ichi[0]);
concat(o, ": ");
concat(o, d_s);
concat(o, ": ");
concat(o, dsh->args[0]);
concat(o, message);
if (dsh->args[1][0] == '-')
{
awful_flag = malloc(3);
awful_flag[0] = '-';
awful_flag[1] = dsh->args[1][1];
awful_flag[2] = '\0';
concat(o, awful_flag);
free(awful_flag);
}
else
{
concat(o, dsh->args[1]);
}

concat(o, "\n");
concat(o, "\0");
return (o);
}

/**
 * error_cd_msg - error message for cd command in get_cd
 * @dsh: data relevant (directory)
 * Return: Error message
 *
 */
char *error_cd_msg(ichigos_shell *dsh)
{
int lathum, lathum_id;
char *o, *d_s, *message;

d_s = int_toString(dsh->counter);
if (dsh->args[1][0] == '-')
{
message = ": Bad option ";
lathum_id = 2;
}
else
{
message = ": There is no such file or directory ";
lathum_id = Length_ofString(dsh->args[1]);
}

lathum = Length_ofString(dsh->ichi[0]) + Length_ofString(dsh->args[0]);
lathum += Length_ofString(d_s) + Length_ofString(message) + lathum_id + 5;
o = malloc(sizeof(char) * (lathum + 1));
if (o == NULL)
{
free(d_s);
return (NULL);
}

o = bigups(dsh, message, o, d_s);

free(d_s);

return (o);
}


/**
 * generic_msg - generic error message for command not found
 * @dsh: data relevant (counter, arguments)
 * Return: Error message
 */
char *generic_msg(ichigos_shell *dsh)
{
int lathum;
char *o;
char *d_s;

d_s = int_toString(dsh->counter);
lathum = Length_ofString(dsh->ichi[0]) + Length_ofString(d_s);
lathum += Length_ofString(dsh->args[0]) + 16;
o = malloc(sizeof(char) * (lathum + 1));
while (o == 0)
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
concat(o, ": not found\n");
concat(o, "\0");
free(d_s);
return (o);
}

/**
 * exit_get - generic error message for exit in get_exit
 * @dsh: data relevant (counter, arguments)
 * Return: Error message
 */
char *exit_get(ichigos_shell *dsh)
{
int lathum;
char *o;
char *d_s;

d_s = int_toString(dsh->counter);
lathum = Length_ofString(dsh->ichi[0]) + Length_ofString(d_s);
lathum += Length_ofString(dsh->args[0]) + Length_ofString(dsh->args[1]) + 23;
o = malloc(sizeof(char) * (lathum + 1));
while (o == 0)
{
free(d_s);
return (NULL);
}
concpy(o, dsh->ichi[0]);
concat(o, ": ");
concat(o, d_s);
concat(o, ": ");
concat(o, dsh->args[0]);
concat(o, ": Bad number: ");
concat(o, dsh->args[1]);
concat(o, "\n\0");
free(d_s);

return (o);
}
