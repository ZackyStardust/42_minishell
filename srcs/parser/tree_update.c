/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:34:33 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/11 17:17:02 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**tree_update_array(char **array, char *token)
{
	int		size;
	int		i;
	char	**new;

	new = NULL;
	if (!array)
	{
		new = protect_mem(malloc(2 * sizeof(char *)));
		new[0] = protect_mem(ft_strdup(token));
		new[1] = NULL;
	}
	else
	{
		size = tree_array_size(array);
		new = protect_mem(malloc((size + 2) * sizeof (char *)));
		i = -1;
		while (array[++i])
			new[i] = ft_strdup(array[i]);
		new[i] = ft_strdup(token);
		new[i + 1] = NULL;
		free_array(array);
	}
	return (new);
}

void	tree_update_redir_main(t_tree *node, char *token)
{
	node->token = protect_mem(ft_strdup(token));
}

void	tree_update_cmd(t_tree *node, char *token)
{
	char	**tmp;

	tmp = node->token;
	node->token = tree_update_array(tmp, token);
}

t_tree	*node_update(t_tree *node, char *token)
{
	if (!node || !token)
		return (NULL);
	if (node_is_redir_main(node))
		tree_update_redir_main(node, token);
	else if (node_is_cmd(node))
		tree_update_cmd(node, token);
	return (node);
}
