/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:28:30 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 15:01:52 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo_token_print(char **token, int fd, int i)
{
	if (!token[i])
		return ;
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putstr_fd(token[i], fd);
}

void	echo_token_print_nl(char **token, int fd, int i)
{
	if (!token[i])
		return (ft_putchar_fd('\n', fd));
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putendl_fd(token[i], fd);
}

int	echo_token_check(char	**token)
{
	int	i;

	i = 0;
	if (token[1])
	{
		if (token[1][0] == '-' && token[1][1] == 'n')
		{
			while (token[1][++i])
				if (token[1][i] != 'n')
					return (0);
			return (1);
		}
	}
	return (0);
}

void	builtin_echo(t_tree *node, int fd)
{
	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	if (echo_token_check((char **)node->token))
		echo_token_print(((char **)(node->token)), fd, 2);
	else
		echo_token_print_nl(((char **)(node->token)), fd, 1);
	get()->exit_status = 0;
}
