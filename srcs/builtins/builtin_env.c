/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:21:45 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/13 14:37:03 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(t_list *head, int fd)
{
	t_list	*current;

	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	current = head;
	while (current && current->content)
	{
		if (ft_strchr(current->content, '=') != 0)
			ft_putendl_fd(current->content, fd);
		current = current->next;
	}
}
