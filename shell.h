#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Define buffer sizes for read and write operations */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUFFER_FLUSH -1

/* Constants for command chaining types */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND	2
#define CMD_CHAIN	3

/* Constants for number conversion */
#define CONVERT_LOW	1
#define CONVERT_UNSIGNED	2

/* Configuration flags for getline and strtok usage */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* History file settings */
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list structure.
 * @num: Integer number field.
 * @str: Pointer to a string.
 * @next: Pointer to the next node in the list.
 */
typedef struct liststr
{
	int num; /* Numeric value */
	char *str; /* String value */
	struct liststr *next; /* Pointer to next node */
} list_str;

/**
 * struct passinfo - contains pseudo-arguments
 * for uniform function call interface.
 * @arg: String from getline containing arguments.
 * @argv: Array of argument strings.
 * @path: String path for the current command.
 * @argc: Argument count.
 * @error_count: Error count.
 * @error_code: Error code for exit().
 * @count_line: Flag for counting this line of input.
 * @fname: Program filename.
 * @env: Linked list as a local copy of the environment.
 * @environ: Custom modified copy of the environment.
 * @history: History list node.
 * @alias: Alias list node.
 * @env_change: Flag indicating change in environment.
 * @status: Return status of the last executed command.
 * @cmd_buf: Address of pointer to command chain buffer.
 * @cmd_buf_type: Type of command chaining.
 * @readfd: File descriptor for reading line input.
 * @history_count: History line count.
 */
typedef struct passinfo
{
	char *arg; /* String of arguments */
	char **argv; /* Array of argument strings */
	char *path; /* Command path */
	int argc; /* Argument count */
	unsigned int error_count; /* Error count */
	int error_code; /* Error code for exit */
	int count_line; /* Line count indicator */
	char *fname; /* Program filename */
	list_str *env; /* Local copy of environment */
	list_str *history; /* History list */
	list_str *alias; /* Alias list */
	char **environ; /* Modified copy of environment */
	int env_change; /* Environment change indicator */
	int status; /* Last command's return status */
	char **cmd_buf; /* Pointer to command chain buffer */
	int cmd_buf_type; /* Command chaining type */
	int readfd; /* File descriptor for input */
	int history_count; /* History line count */
} info_passed;

/* Initial values for info_passed structure */
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - represents a built-in shell command.
 * @type: String representing the type of built-in command.
 * @func: Function pointer to the built-in command function.
 */
typedef struct builtin
{
	char *type; /* Command type */
	int (*func)(info_passed *); /* Function pointer */
} shell_builtin;

/* Function prototypes for various shell components */

/* Main shell loop */
int hshell(info_passed *, char **);
int builtin_search(info_passed *);
void cmd_search(info_passed *);
void shell_fork(info_passed *);

/* Parsing functions */
int is_executable(info_passed *, char *);
char *make_dup(char *, int, int);
char *pathfinder(info_passed *, char *, char *);

/* Error handling functions */
void print_str(char *);
int write_char(char);
int write_fd(char c, int fd);
int writes_fd(char *str, int fd);

/* String manipulation functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *hay_checker(const char *, const char *);
char *_strcat(char *, char *);

/* More string manipulation functions */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Functions for string exits */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Tokenizer functions */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Reallocation functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Memory management functions */
int free_n_null(void **);

/* Atoi and related functions */
int is_interactive(info_passed *);
int is_delim(char, char *);
int is_alpha(int);
int _atoi(char *);

/* More error handling functions */
int _erratoi(char *);
void print_error(info_passed *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Built-in command functions */
int shell_exit(info_passed *);
int shell_cd(info_passed *);
int shell_help(info_passed *);

/* More built-in command functions */
int shell_history(info_passed *);
int shell_alias(info_passed *);

/* Getline functions */
ssize_t get_input(info_passed *);
int _getline(info_passed *, char **, size_t *);
void signal_handler(int);

/* Functions for information handling */
void info_start(info_passed *);
void set_info(info_passed *, char **);
void info_end(info_passed *, int);

/* Environment manipulation functions */
char *shell_get_env(info_passed *, const char *);
int shell_env(info_passed *);
int shell_setenv(info_passed *);
int shell_unsetenv(info_passed *);
int populate_envlist(info_passed *);

/* More environment functions */
char **get_env(info_passed *);
int unset_env(info_passed *, char *);
int set_env(info_passed *, char *, char *);

/* History management functions */
char *get_history_file(info_passed *info);
int write_history(info_passed *info);
int read_history(info_passed *info);
int build_history_list(info_passed *info, char *buf, int linecount);
int order_history(info_passed *info);

/* List manipulation functions */
list_str *add_node(list_str **, const char *, int);
list_str *add_node_end(list_str **, const char *, int);
size_t print_list_str(const list_str *);
int delete_node(list_str **, unsigned int);
void free_list(list_str **);

/* More list functions */
size_t list_len(const list_str *);
char **list_to_strings(list_str *);
size_t print_list(const list_str *);
list_str *prefix_start(list_str *, char *, char);
ssize_t get_index(list_str *, list_str *);

/* Variable handling functions */
int is_chain(info_passed *, char *, size_t *);
void check_chain(info_passed *, char *, size_t *, size_t, size_t);
int replace_alias(info_passed *);
int replace_vars(info_passed *);
int replace_string(char **, char *);

#endif
