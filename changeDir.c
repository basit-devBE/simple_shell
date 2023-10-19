#include "ichigos.h"
/**
 * Change_Dir - changes to the parent directory
 * @dsh: the data relevant (environ)
 * Return: no return
 */
void Change_Dir(ichigos_shell *dsh)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = Stardom(pwd);
	set_envV("OLDPWD", cp_pwd, dsh);
	d = dsh->args[1];
	if (concomp(".", d) == 0)
	{
		set_envV("PWD", cp_pwd, dsh);
		free(cp_pwd);
		return;
	}
	if (concomp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	ReverseString(cp_strtok_pwd);
	cp_strtok_pwd = split_string(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = split_string(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			ReverseString(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_envV("PWD", cp_strtok_pwd, dsh);
	}
	else
	{
		chdir("/");
		set_envV("PWD", "/", dsh);
	}
	dsh->status = 0;
	free(cp_pwd);
}

/**
 * ChaneDir_usr - changes to a dir given by user
 * @dsh: data relevant (directories)
 * Return: no return
 */
void ChaneDir_usr(ichigos_shell *dsh)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	d = dsh->args[1];
	if (chdir(d) == -1)
	{
		G_ERROR(dsh, 2);
		return;
	}

	cp_pwd = Stardom(pwd);
	set_envV("OLDPWD", cp_pwd, dsh);

	cp_dir = Stardom(d);
	set_envV("PWD", cp_dir, dsh);

	free(cp_pwd);
	free(cp_dir);

	dsh->status = 0;

	chdir(d);
}
/**
 * changeDir_prev - changes to the previous directory
 * @dsh: data relevant (environ)
 * Return: no return
 */
void changeDir_prev(ichigos_shell *dsh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = Stardom(pwd);

	p_oldpwd = obtainenv("OLDPWD", dsh->env_variable);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = Stardom(p_oldpwd);

	set_envV("OLDPWD", cp_pwd, dsh);

	if (chdir(cp_oldpwd) == -1)
		set_envV("PWD", cp_pwd, dsh);
	else
		set_envV("PWD", cp_oldpwd, dsh);

	p_pwd = obtainenv("PWD", dsh->env_variable);

	write(STDOUT_FILENO, p_pwd, Length_ofString(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dsh->status = 0;

	chdir(p_pwd);
}

/**
 * changeDir_ - changes to home directory
 * @dsh: data relevant (environ)
 * Return: no return
 */
void changeDir_(ichigos_shell *dsh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = Stardom(pwd);

	home = obtainenv("HOME", dsh->env_variable);

	if (home == NULL)
	{
		set_envV("OLDPWD", p_pwd, dsh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		G_ERROR(dsh, 2);
		free(p_pwd);
		return;
	}

	set_envV("OLDPWD", p_pwd, dsh);
	set_envV("PWD", home, dsh);
	free(p_pwd);
	dsh->status = 0;
}
