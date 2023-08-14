/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:25:17 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/07 16:36:14 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*node_make(int id)
{
	t_tree	*node;

	node = protect_mem(malloc(sizeof(t_tree)));
	if (!node)
		return (0);
	node->type = id;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->token = NULL;
	return (node);
}

t_tree	*tree_check_update(t_tree *tree)
{
	t_tree	*cursor;
	t_tree	*next;

	if (!tree)
		return (NULL);
	if (node_is_pipe(tree))
		cursor = tree->right;
	else
		cursor = tree;
	if (!cursor)
		return (NULL);
	next = cursor->left;
	if (node_is_redir_main(cursor) && !(cursor->token))
		return (cursor);
	else if (next && node_is_redir_main(next) && !(next->token))
		return (next);
	else if (node_is_cmd(cursor))
		return (cursor);
	return (NULL);
}

void	tree_make(char *token, int id, t_tree **tree)
{
	t_tree	*node;

	if (id == E_WORD)
	{
		node = tree_check_update(*tree);
		if (node)
			node = node_update(node, token);
		else
		{
			id = tree_check_builtin(token);
			node_add_new(tree, node_update(node_make(id), token));
		}
	}
	else
		node_add_new(tree, node_make(id));
	free_str(token);
}

void	node_add_new(t_tree **tree, t_tree *node)
{
	if (node_is_redir_main(node))
		tree_add_redir_main(tree, node);
	else if (node_is_cmd(node))
		tree_add_cmd(tree, node);
	else if (node_is_pipe(node))
		tree_add_top(tree, node);
}
