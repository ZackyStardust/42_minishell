/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:46:06 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/09 17:28:57 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_main(t_tree *node, int fd)
{
	if (!ft_strncmp(((char **)(node->token))[0], "echo", 5))
		builtin_echo(node, fd);
	else if (!ft_strncmp(((char **)(node->token))[0], "cd", 3))
		builtin_cd(node->token);
	else if (!ft_strncmp(((char **)(node->token))[0], "pwd", 4))
		builtin_pwd(fd);
	else if (!ft_strncmp(((char **)(node->token))[0], "export", 7))
		builtin_export(node->token, fd);
	else if (!ft_strncmp(((char **)(node->token))[0], "unset", 6))
		builtin_unset(node->token);
	else if (!ft_strncmp(((char **)(node->token))[0], "env", 4))
		builtin_env(get()->env, fd);
	else if (!ft_strncmp(((char **)(node->token))[0], "exit", 5))
		builtin_exit(node->token);
}
