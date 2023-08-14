/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_frees.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:35:01 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/01 15:35:01 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	if (str)
		free(str);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free_str(array[i]);
	free (array);
}

void	free_node(t_tree *node)
{
	if (node_is_redir_main(node))
	{
		if (node->token)
			free_str(node->token);
	}
	else if (node_is_cmd(node))
	{
		if (node->token)
			free_array(node->token);
	}
	free(node);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free_node(tree);
}

void	free_env(t_list *env)
{
	if (env)
		list_clear(env);
}
