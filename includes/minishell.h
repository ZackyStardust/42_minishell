/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:31:05 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 21:08:16 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <errno.h>
# include <libft.h>

# define OPERATORS		"<>|"
# define WHITE_SPACE	" \t\r\n\v\f"

typedef enum e_type
{
	E_WORD,
	E_CMD,
	E_PIPE,
	E_IN,
	E_OUT,
	E_APPEND,
	E_HDOC,
	E_BUILT,
	E_FLAG
}	t_type;

typedef enum e_sigtype
{
	SI_IGN,
	SI_HDOC,
	SI_RLINE,
	SI_DFL
}	t_sigtype;

typedef struct s_tree
{
	void			*token;
	int				type;
	int				p[2];
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*parent;
}	t_tree;

typedef struct s_data
{
	t_list				*env;
	t_tree				*tree;
	t_tree				*tree_head;
	struct termios		term;
	struct termios		termbase;
	int					exit_status;
	char				**envp_matriz;
	int					last_pipe;
	int					atual_pipe[2];
	int					flag;
}	t_data;

typedef struct s_exec
{
	int		n_c;
	int		c;
	int		fd;
	int		pid;
	int		in;
	int		out;
	int		doc;
	int		flag;
	t_list	*env;
}					t_exec;

////\\\\// FOLDER-> MAIN ////\\\\////\\\\////\\\\////\\\\//
//// Main ////
t_data	*get(void);
t_exec	*exe(void);
int		empty_input(char *str);
int		main_syntax_check(char *str);
int		main_skip_quotes(char *str, int *i);
int		main_syntax_error(int i);
void	main_set_enviroment(char **envp);
//// Main uitls ////
int		main_skip_quotes(char *str, int *i);
int		main_syntax_check(char *str);
int		empty_input(char *str);
int		main_syntax_error(int i);
void	main_set_enviroment(char **envp);
//// Main Signals ////
void	main_set_termios(struct termios *term, struct termios *termbase);
char	*main_rdl_signals(struct termios *term, struct termios *termbase);
void	main_handle_ctrlc(int sig, siginfo_t *info, void *ucontext);
void	main_heredoc_file(int sig, siginfo_t *info, void *ucontext);
void	main_get_signal(struct sigaction *act, char si_mode);
void	main_call_sigact(char act_choice);
void	main_attr_setting(struct termios *term);
//// Main Signals 2 ////
void	main_call_sigact(char act_choice);
void	main_attr_setting(struct termios *term);
//// Main list utils ////
t_list	*list_new(char *newdata);
void	list_add_back(t_list *head, t_list *new);
void	list_print(t_list *head, int fd);
void	list_free(t_list *head);
t_list	*list_copy(t_list *head);
void	list_clear(t_list *env);
//// env ////
void	get_env(char **envp);
//char	**env_array(t_list *env);
//// Main frees ////
void	free_str(char *str);
void	free_array(char **array);
void	free_node(t_tree *node);
void	free_tree(t_tree *tree);
void	free_env(t_list *env);
////\\\\// FOLDER-> EXECUTOR ////\\\\////\\\\////\\\\////\\\\//
//// Executor main ////
void	executor_main(t_tree **root, int c);
void	execute_first_command(t_tree *tree);
void	execute_command(t_tree *tree);
void	execute_in_process(t_tree *tree);
char	**execute_env_array(t_list *env);
/// Executor utils ///
void	execute_builtin(t_tree *tree);
//// Relative path  ////
char	*relative_path(char *cmd, t_list *env);
char	*get_cmd_path(char **path, char *cmd);
char	*get_path(char *env, char *cmd);
int		is_path(char *str, char *path);
void	rlp_error_msg(char *cmd);
//// Path utils ////
char	*rp_util(char *cmd, char *path, char *tmp);
char	*absolute_path(char *cmd, char **m_env);
char	*cmd_path(char *cmd, t_list *env, char **m_env);
//// Wait cmds ////
void	wait_cmds(int last_pid, int n_cmds);
void	wait_missing_cmds(int n_cmds);
void	wait_last_cmd(int pid);
////\\\\// FOLDER-> BUILTINS ////\\\\////\\\\////\\\\////\\\\//
//// Builtin_env.c ////
void	builtin_env(t_list *head, int fd);
//// Builtin_main.c ////
void	builtin_main(t_tree *node, int fd);
void	builtin_special_case(void);
//// Builtin_cd.c ////
void	builtin_cd(char **token);
void	cd_error_msg(char *token, char *msg);
void	builtin_cd_do(char **token);
//// Builtin_echo.c ////
void	builtin_echo(t_tree *node, int fd);
int		echo_token_check(char	**token);
void	echo_token_print(char **token, int fd, int i);
void	echo_token_print_nl(char **token, int fd, int i);
//// Builtin_exit.c ////
void	builtin_exit(char **token);
void	builtin_exit_errors(char **token, int arg);
int		builtin_exit_is_num(char *str);
void	builtin_exit_do(int arg, char **token);
//// Builtin_export_utils.c ////
int		export_list_is_alpha_sort(t_list *head);
void	export_list_print(t_list *head, int fd);
void	export_list_print_end(int flag, int fd);
//// Builtin_export.c ////
void	builtin_export(char **token, int fd);
void	export_string_build(char *str, t_list *current);
void	export_list_sort(t_list *list, int fd);
t_list	*export_string_search(char *str);
//// Builtin_pwd.c ////
void	builtin_pwd(int fd);
//// Builtin_unset.c ////
void	builtin_unset(char **token);
void	unset_list_remove(t_list *head, t_list *remove);
////\\\\// FOLDER-> PARSER ////\\\\////\\\\////\\\\////\\\\//
//// Expander home ////
char	*home_expansion(char *token, int size, t_list *env);
char	*home_expand(char *token, t_list *env);
//// expander main////
int		exp_word_size(char *s);
int		exp_var_name(char c, int i);
int		exp_var_size(char *s);
char	*expand_var(char *s, char *token, int *i, t_list *env);
char	*expand_var_else(char *s, char *token, int *i, t_list *env);
char	*expand_str(char *s, t_list *env);
char	*expand_str_loop(int size, char *s, int i, char *token);
int		ft_strccmp(const char *s1, const char *s2, size_t n);
//// Parser main ////
t_tree	*parser_main(char *str, t_list *env);
char	*parser_get_token(char *str, int reset);
int		parser_get_id(char *token);
char	*parser_get_operator(char *str, int *i);
char	*parser_get_word(char *str, int *i);
int		parser_count_inquote(char *str, char c);
//// Parser utils ////
int		is_match(char c, char *str);
char	*exist_in_env(char	*elem, t_list *env);
void	*protect_mem(void *p);
char	*token_join(char *t1, char *t2, int trigger);
char	*join_char(char *str, char c);
//// Syntax errors ////
int		syntax_error(t_tree *tree, char *token);
int		syntax_check_node(t_tree *node);
int		syntax_analysis(t_tree *tree, char *token);
void	syntax_error_msg(char *token);
//// Token treat////
char	*token_treat(char *token, t_list *env);
int		token_need_treat(char *token);
//// Token update////
int		token_get_unquoted(char *s);
int		token_get_quoted(char *s);
int		token_get_size(char *s);
char	*token_update(char *token, char *new_token, int *index, t_list *env);
//// Tree add ////
void	tree_add_top(t_tree **tree, t_tree *node);
void	tree_add_right(t_tree *node, t_tree *new_node);
void	tree_add_left(t_tree *current, t_tree *new_node);
void	tree_add_cmd(t_tree **tree, t_tree *node);
void	tree_add_redir_main(t_tree **tree, t_tree *node);
//// Tree update ////
char	**tree_update_array(char **array, char *token);
void	tree_update_redir_main(t_tree *node, char *token);
void	tree_update_cmd(t_tree *node, char *token);
t_tree	*node_update(t_tree *node, char *token);
//// Tree utils ////
int		tree_check_builtin(char *token);
int		node_is_redir_main(t_tree *node);
int		node_is_pipe(t_tree *node);
int		node_is_cmd(t_tree *node);
int		tree_array_size(char **array);
//// Tree main ////
void	tree_make(char *token, int id, t_tree **tree);
t_tree	*node_make(int id);
void	node_add_new(t_tree **tree, t_tree *node);
t_tree	*tree_check_update(t_tree *tree);
////\\\\// FOLDER-> REDIR ////\\\\////\\\\////\\\\////\\\\//
//// heredoc_main ////
void	heredoc_main(t_tree *node, int i);
void	heredoc_no_file(t_tree *node);
void	write_to_file(int fd, t_list *env, char *buf);
void	heredoc_file(t_tree *node, int fd, t_list *env);
//// redir main////
void	redir_counter(t_tree *node);
void	redir_in_doc(t_tree *node, int i);
void	redir_in(t_tree *node);
void	redir_out(t_tree *node);
void	redir_main(t_tree *node);
//// redir built ////
void	redir_built_in(t_tree *node);
int		redir_built_out(t_tree *node);
int		redir_built(t_tree *node);
void	redir_error(t_tree *node);
//// END ////
#endif
