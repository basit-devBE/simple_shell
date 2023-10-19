#include "ichigos.h"
/**
 * theLIne - assigns the line var for get_line
 * @lptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @i: the size of line
 * @k: size of buffer
 */
void theLIne(char **lptr, size_t *i, char *buffer, size_t k)
{

	if (*lptr == NULL)
	{
		if  (k > BUFSIZE)
			*i = k;

		else
			*i = BUFSIZE;
		*lptr = buffer;
	}
	else if (*i < k)
	{
		if (k > BUFSIZE)
			*i = k;
		else
			*i = BUFSIZE;
		*lptr = buffer;
	}
	else
	{
		concpy(*lptr, buffer);
		free(buffer);
	}
}
/**
 * CD - changes current directory
 * @dsh: data relevant
 * Return: 1 on success
 */
int CD(ichigos_shell *dsh)
{
	char *d;
	int ie, i2, ih;

	d = dsh->args[1];

	if (d != NULL)
	{
		ie = concomp("$HOME", d);
		i2 = concomp("~", d);
		ih = concomp("--", d);
	}

	if (d == NULL || !ie || !i2 || !ih)
	{
		changeDir_(dsh);
		return (1);
	}

	if (concomp("-", d) == 0)
	{
		changeDir_prev(dsh);
		return (1);
	}

	if (concomp(".", d) == 0 || concomp("..", d) == 0)
	{
		Change_Dir(dsh);
		return (1);
	}

	Change_Dir(dsh);

	return (1);
}


/**
 * gettheLIne - Read inpt from stream
 * @lptr: buffer that stores the input
 * @i: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t gettheLIne(char **lptr, size_t *i, FILE *stream)
{
	int n;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		n = read(STDIN_FILENO, &t, 1);
		if (n == -1 || (n == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (n == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = prrealloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	theLIne(lptr, i, buffer, input);
	retval = input;
	if (n != 0)
		input = 0;
	return (retval);
}



/**
 * lefshell - exits the shell
 * @dsh: data relevant (status and args)
 * Return: 0 on success.
 */
int lefshell(ichigos_shell *dsh)
{
	unsigned int x;
	int jiggy;
	int sterling;
	int big_num;

	if (dsh->args[1] != NULL)
	{
		x = string_toInt(dsh->args[1]);
		jiggy = check_if_int(dsh->args[1]);
		sterling = Length_ofString(dsh->args[1]);
		big_num = x > (unsigned int)INT_MAX;
		if (!jiggy || sterling > 10 || big_num)
		{
			G_ERROR(dsh, 2);
			dsh->status = 2;
			return (1);
		}
		dsh->status = (x % 256);
	}
	return (0);

}
