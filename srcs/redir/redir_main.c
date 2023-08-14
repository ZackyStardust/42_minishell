/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:16:40 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 13:17:34 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redir_counter(t_tree *node)
{
	exe()->in = 0;
	exe()->out = 0;
	while (node)
	{
		if (node->type == E_IN || node->type == E_HDOC)
			exe()->in++;
		if (node->type == E_OUT || node->type == E_APPEND)
			exe()->out++;
		node = node->left;
	}
}

void	redir_in_doc(t_tree *node, int i)
{
	int	fd;

	fd = open(((char *)node->token), O_RDONLY, 0644);
	if (fd == -1)
		redir_error(node);
	if (i != exe()->in)
		close(fd);
	else
		dup2(fd, STDIN_FILENO);
}

void	redir_in(t_tree *node)
{
	int	i;

	i = exe()->in + 1;
	if (exe()->fd)
		close (exe()->fd);
	while (node)
	{
		if (node->type == E_IN || node->type == E_HDOC)
		{
			i--;
			if (node->type == E_IN)
				redir_in_doc(node, i);
			else
				heredoc_main(node, i);
		}
		node = node->left;
	}
}

void	redir_out(t_tree *node)
{
	int	i;
	int	fd;

	i = exe()->out + 1;
	close(node->p[1]);
	while (node)
	{
		if (node->type == E_OUT || node->type == E_APPEND)
		{
			if (node->type == E_OUT)
				fd = open(node->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(node->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i--;
			if (fd == -1)
				redir_error(node);
			if (i == exe()->out)
				dup2(fd, STDOUT_FILENO);
			else
				close(fd);
		}
		node = node->left;
	}
}

void	redir_main(t_tree *node)
{
	main_call_sigact(SI_HDOC);
	redir_counter(node);
	if (exe()->in)
		redir_in(node);
	else
		dup2(exe()->fd, STDIN_FILENO);
	if (exe()->out)
		redir_out(node);
	else if (exe()->c > 1)
	{
		dup2(node->p[1], STDOUT_FILENO);
		close(node->p[1]);
	}
	else
		close(node->p[1]);
}
