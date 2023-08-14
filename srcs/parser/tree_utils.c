/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:28:24 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/11 17:27:58 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tree_check_builtin(char *token)
{
	if (token)
	{
		if (!ft_strncmp(token, "echo", 5))
			return (E_BUILT);
		if (!ft_strncmp(token, "cd", 3))
			return (E_BUILT);
		if (!ft_strncmp(token, "pwd", 4))
			return (E_BUILT);
		if (!ft_strncmp(token, "export", 7))
			return (E_BUILT);
		if (!ft_strncmp(token, "unset", 6))
			return (E_BUILT);
		if (!ft_strncmp(token, "env", 4))
			return (E_BUILT);
		if (!ft_strncmp(token, "exit", 5))
			return (E_BUILT);
	}
	return (E_CMD);
}

int	node_is_redir_main(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type >= E_IN && node->type <= E_HDOC)
		return (1);
	return (0);
}

int	node_is_pipe(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type == E_PIPE)
		return (1);
	return (0);
}

int	node_is_cmd(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type == E_CMD || node->type == E_BUILT)
		return (1);
	return (0);
}

int	tree_array_size(char **array)
{
	int	i;

	i = 0;
	if (!array || !array[i])
		return (0);
	while (array[i])
		i++;
	return (i);
}
