/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:46:24 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/14 10:12:31 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset_list_remove(t_list *head, t_list *remove)
{
	t_list	*before;
	t_list	*current;

	current = head;
	if (current == remove)
	{
		get()->env = get()->env->next;
		ft_lstdelone(current, free);
		return ;
	}
	while (current && current != remove)
	{
		before = current;
		current = current->next;
	}
	if (current && !current->next)
		before->next = NULL;
	else if (current && current->next)
		before->next = current->next;
	ft_lstdelone(current, free);
}

void	builtin_unset(char **token)
{
	t_list	*current;

	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	if (token[1] && !token[2])
	{
		current = export_string_search(token[1]);
		if (current)
			unset_list_remove(get()->env, current);
	}
}
