/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:57:20 by fpereira          #+#    #+#             */
/*   Updated: 2023/07/12 13:57:20 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tree_add_top(t_tree **tree, t_tree *node)
{
	t_tree	*first;

	first = *tree;
	if (!first)
		first = node;
	else
	{
		node->left = first;
		first->parent = node;
		first = node;
	}
	*tree = first;
}

void	tree_add_right(t_tree *node, t_tree *new_node)
{
	if (!node || !new_node)
		return ;
	if (node->right)
	{
		new_node->left = node->right;
		node->right->parent = new_node;
	}
	node->right = new_node;
	new_node->parent = node;
}

void	tree_add_left(t_tree *current, t_tree *new_node)
{
	if (!current || !new_node)
		return ;
	if (current->left)
	{
		new_node->left = current->left;
		current->left->parent = new_node;
	}
	current->left = new_node;
	new_node->parent = current;
}

void	tree_add_cmd(t_tree **tree, t_tree *node)
{
	t_tree	*first;

	first = *tree;
	if (!first || node_is_redir_main(first))
		tree_add_top(tree, node);
	else if (node_is_pipe(first))
		tree_add_right(first, node);
}

void	tree_add_redir_main(t_tree **tree, t_tree *node)
{
	t_tree	*first;
	t_tree	*next;

	if (!tree)
		return ;
	first = *tree;
	if (!first)
		tree_add_top(tree, node);
	else if (node_is_cmd(first) || node_is_redir_main(first))
		tree_add_left(first, node);
	else if (node_is_pipe(first))
	{
		next = first->right;
		if (!next || node_is_redir_main(next))
			tree_add_right(first, node);
		else
			tree_add_left(next, node);
	}
}
