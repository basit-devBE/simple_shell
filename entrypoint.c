#include "ichigos.h"
/**
 * f_data - frees data struct
 * @dsh: data struct
 * Return: no return
 **********************************/
void f_data(ichigos_shell *dsh)
{
unsigned int u = 0;
while (dsh->env_variable[u])
{
free(dsh->env_variable[u]);
u++;
}

free(dsh->env_variable);
free(dsh->process_id);
}
/**
 * s_data - Initialize data struct
 * @dsh: data struct
 * @ichi: arg vector
 * Return: no return
 **********************************/
void s_data(ichigos_shell *dsh, char **ichi)
{
unsigned int u = 0;

dsh->ichi = ichi;
dsh->input = NULL;
dsh->args = NULL;
dsh->status = 0;
dsh->counter = 1;

for (u = 0; environ[u]; u++)
;

dsh->env_variable = malloc(sizeof(char *) * (u + 1));

for (u = 0; environ[u]; u++)
{
dsh->env_variable[u] = Stardom(environ[u]);
}

dsh->env_variable[u] = NULL;
dsh->process_id = int_toString(getpid());
}



/**
 * main - Entry point
 * @ac: argument count
 * @ichi: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **ichi)
{
	ichigos_shell dsh;
	(void) ac;

	signal(SIGINT, sing_line);
	s_data(&dsh, ichi);
	shell_loop(&dsh);
	f_data(&dsh);
	if (dsh.status < 0)
		return (255);
	return (dsh.status);
}
