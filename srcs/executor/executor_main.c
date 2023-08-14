/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:57:28 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 16:43:03 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	executor_main(t_tree **root, int c)
{
	t_tree		*tree;

	tree = *root;
	main_call_sigact(SI_DFL);
	if (!tree->parent && tree->type == E_HDOC)
		heredoc_no_file(tree);
	else if (!tree->parent && tree->type == E_BUILT)
	{
		exe()->flag = 1;
		builtin_main(tree, redir_built(tree));
	}
	else
	{
		execute_first_command(tree);
		while (tree->parent)
		{
			execute_command(tree->parent->right);
			tree = tree->parent;
			exe()->c--;
		}
		wait_cmds(exe()->pid, c);
	}
}

void	execute_first_command(t_tree *tree)
{
	if (tree->type == E_PIPE)
	{
		execute_command(tree->left);
		exe()->c--;
		execute_command(tree->right);
		exe()->c--;
	}
	else
		execute_command(tree);
}

void	execute_command(t_tree *tree)
{
	if (pipe(tree->p) == -1)
		ft_putendl_fd("Error: Pipe failed", 2);
	exe()->pid = fork();
	if (exe()->pid < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (exe()->pid == 0)
		execute_in_process(tree);
	if (exe()->c != 1)
	{
		if (exe()->fd > 0)
			close(exe()->fd);
		close(tree->p[1]);
		exe()->fd = tree->p[0];
	}
	else
	{
		close(tree->p[0]);
		close(tree->p[1]);
		if (exe()->fd > 0)
			close(exe()->fd);
	}
}

void	execute_in_process(t_tree *tree)
{
	char	*path;

	path = NULL;
	get()->envp_matriz = execute_env_array(get()->env);
	if (tree->type == E_HDOC)
		return (heredoc_no_file(tree));
	if (tree->type == E_CMD || tree->type == E_BUILT)
		path = cmd_path(((char **)tree->token)[0],
				get()->env, get()->envp_matriz);
	close(tree->p[0]);
	redir_main(tree);
	rl_clear_history();
	if (tree->type == E_BUILT)
		execute_builtin(tree);
	if (path)
		execve(path, tree->token, get()->envp_matriz);
	free(get()->envp_matriz);
	close(tree->p[1]);
	close(tree->p[0]);
	close(exe()->fd);
	if (exe()->doc == 1)
		unlink(".heredoc_tmp");
	exit(127);
}

char	**execute_env_array(t_list *env)
{
	int		size;
	int		i;
	char	**matrix;
	t_list	*tmp;

	i = 0;
	tmp = env;
	size = ft_lstsize(env);
	matrix = malloc(sizeof(char *) * (size + 1));
	while (tmp->next != NULL)
	{
		matrix[i++] = tmp->content;
		tmp = tmp->next;
	}
	matrix[i] = tmp->content;
	matrix[++i] = NULL;
	return (matrix);
}
