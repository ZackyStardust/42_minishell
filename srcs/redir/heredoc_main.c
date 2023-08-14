/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:57:51 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 19:26:37 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_no_file(t_tree *node)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strdup(node->token);
	while (1)
	{
		buf = readline("> ");
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buf, ft_strlen(node->token)))
				break ;
			free (buf);
		}
		else
			break ;
	}
	free (tmp);
	free (buf);
}

void	write_to_file(int fd, t_list *env, char *buf)
{
	char	*parser;
	char	*tmp;

	tmp = ft_strjoin(buf, "\n");
	parser = token_treat(tmp, env);
	write(fd, parser, ft_strlen(parser));
	free (buf);
	free (tmp);
}

void	heredoc_file(t_tree *node, int fd, t_list *env)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strdup(node->token);
	while (1)
	{
		buf = readline("> ");
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buf, ft_strlen(node->token)))
				break ;
			write_to_file(fd, env, buf);
		}
		else
			break ;
	}
	free (tmp);
	free (buf);
}

void	heredoc_main(t_tree *node, int i)
{
	int	fd;

	main_call_sigact(SI_HDOC);
	if (i != exe()->in)
	{
		heredoc_no_file(node);
		return ;
	}
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(node);
	heredoc_file(node, fd, exe()->env);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY, 0644);
	if (fd == -1)
		redir_error(node);
	dup2(fd, STDIN_FILENO);
	unlink(".heredoc_tmp");
}
