#ifndef _ichigos_h_
#define _ichigos_h_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

typedef struct data
{
    char **ichi;
    char *input;
    char **args;
    int status;
    int counter;
    char **env_variable;
    char *process_id;
} ichigos_shell;

typedef struct def_s
{
    char separator;
    struct def_s *next;
} def;

typedef struct dap_s
{
    char *line;
    struct dap_s *next;
} dap;

typedef struct dame_list
{
    int Length_of_variable;
    char *val;
    int Length_of_value;
    struct dame_list *next;
} dame;

typedef struct builtin_s
{
    char *name;
    int (*f)(ichigos_shell *dsh);
} builtin_t;

char *bigups(ichigos_shell *dsh, char *message, char *o, char *d_s);
char *error_cd_msg(ichigos_shell *dsh);
char *generic_msg(ichigos_shell *dsh);
char *exit_get(ichigos_shell *dsh);

char *Stardom(const char *s);
int Length_ofString(const char *s);
int comp_char(char string[], const char *delim);
char *split_string(char string[], const char *delim);
int check_if_int(const char *s);

void ReverseString(char *s);

void Change_Dir(ichigos_shell *dsh);
void ChaneDir_usr(ichigos_shell *dsh);
void changeDir_prev(ichigos_shell *dsh);
void changeDir_(ichigos_shell *dsh);

int CD(ichigos_shell *dsh);

int count_repchar(char *input, int u);
int syntax_err(char *input, int u, char last);
int index_char(char *input, int *u);
void error_message(ichigos_shell *dsh, char *input, int u, int bool);
int case_intfunc(ichigos_shell *dsh, char *input);

int kano(ichigos_shell *dsh);

int lefshell(ichigos_shell *dsh);

int (*builtINFunctions(char *cmd))(ichigos_shell *);

int G_ERROR(ichigos_shell *dsh, int eva);

int HELP(ichigos_shell *dsh);

void theLIne(char **lptr, size_t *i, char *buffer, size_t k);
ssize_t gettheLIne(char **lptr, size_t *i, FILE *stream);

void sing_line(int sig);
char *READLINE(int *dub);

char *del_COMMENT(char *in);
void shell_loop(ichigos_shell *dsh);

char *non_printed_char_swap(char *input, int bool);
void addSeparators_and_cdLists(def **hs, dap **hl, char *input);
void nextInLine(def **l_s, dap **l_l, ichigos_shell *dsh);
int split(ichigos_shell *dsh, char *input);
char **splityy(char *input);

void h_env(void);
void h_env_setup_env(void);
void h_env_setdown_env(void);
void gen_h(void);
void exit_h(void);

void help_opt(void);
void a_help_opt(void);
void _help_(void);

def *add_node(def **top, char sep);
void fee_list(def **top);
dap *end_node(dap **top, char *line);
void free_list(dap **top);

dame *AddVariable(dame **head, int lvar, char *val, int lval);
void FreeVariable(dame **head);

void copy_s(void *newptr, const void *ptr, unsigned int size);
void *prrealloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **prmalloc(char **ptr, unsigned int old_size, unsigned int new_size);

int getInt_length(int n);
char *int_toString(int n);
int string_toInt(char *s);

char *concat(char *dest, const char *src);
char *concpy(char *dest, char *src);
int concomp(char *s1, char *s2);
char *loc_String(char *s, char c);
int acq_String(char *s, char *accept);

void right_var(dame **h, char *in, ichigos_shell *data);
int more_money(dame **h, char *in, char *st, ichigos_shell *data);
char *rep_i(dame **head, char *input, char *new_input, int nlen);
char *replace_variable(char *input, ichigos_shell *dsh);

char *PGLA(char *name, char *value);
void set_envV(char *name, char *value, ichigos_shell *dsh);
int compa_env_names(ichigos_shell *dsh);
int del_env(ichigos_shell *dsh);

int compare_envnames(const char *nenv, const char *name);
char *obtainenv(const char *name, char **env_variable);
int print_env(ichigos_shell *dsh);

int check_dir(char *path, int *m);
char *w_command(char *cmd, char **env_variable);
int check_e(ichigos_shell *dsh);
int check_SU_permission_cmd(char *d, ichigos_shell *dsh);
int exec_cmd(ichigos_shell *dsh);

char *error_info(ichigos_shell *dsh);
char *path_error_info(ichigos_shell *dsh);

#endif
