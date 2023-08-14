/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:57:38 by fpereira          #+#    #+#             */
/*   Updated: 2023/07/12 13:57:38 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_error_msg(char *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int	syntax_analysis(t_tree *tree, char *token)
{
	t_tree	*node;

	if (!token && node_is_pipe(tree) && !tree->right)
	{
		syntax_error_msg(token);
		return (1);
	}
	if (node_is_pipe(tree))
		node = tree->right;
	else
		node = tree;
	if (syntax_check_node(node))
	{
		syntax_error_msg(token);
		return (1);
	}
	return (0);
}

int	syntax_check_node(t_tree *node)
{
	while (node)
	{
		if (!(node->token))
			return (1);
		node = node->left;
	}
	return (0);
}

int	syntax_error(t_tree *tree, char *token)
{
	int	status;

	status = 0;
	if (!token || parser_get_id(token) != E_WORD)
		status = syntax_analysis(tree, token);
	if (status)
	{
		free_tree(tree);
		free_str(token);
		return (2);
	}
	return (0);
}
