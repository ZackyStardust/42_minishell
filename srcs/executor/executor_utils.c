/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:41:38 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 16:43:12 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_builtin(t_tree *tree)
{
	builtin_main(tree, 1);
	free(get()->envp_matriz);
	exit(get()->exit_status);
}
