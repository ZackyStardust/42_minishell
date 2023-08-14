/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:57:57 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 14:47:11 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redir_built_in(t_tree *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->type == E_IN || node->type == E_HDOC)
		{
			if (node->type == E_IN)
			{
				if (open(node->token, O_RDONLY, 0644) == -1)
					redir_error(node);
			}
			else
				heredoc_no_file(node);
		}
	}
}

int	redir_built_out(t_tree *node)
{
	int	i;
	int	fd;
	int	tmp;

	i = exe()->out + 1;
	while (node->left)
	{
		node = node->left;
		if (node->type == E_OUT || node->type == E_APPEND)
		{
			if (node->type == E_OUT)
				tmp = open(node->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				tmp = open(node->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i--;
			if (tmp == -1)
				redir_error(node);
			if (i == exe()->out)
				fd = tmp;
			else
				close(tmp);
		}
	}
	return (fd);
}

int	redir_built(t_tree *node)
{
	main_call_sigact(SI_HDOC);
	redir_counter(node);
	if (exe()->in > 0)
		redir_built_in(node);
	if (exe()->out > 0)
		return (redir_built_out(node));
	else
		return (1);
}

void	redir_error(t_tree *node)
{
	ft_putstr_fd("Error: couldn't open file: ", 2);
	ft_putstr_fd(node->token, 2);
	ft_putstr_fd("\n", 2);
	if (exe()->flag == 1)
	{
		exe()->flag = 2;
		return ;
	}
	exit(1);
}
