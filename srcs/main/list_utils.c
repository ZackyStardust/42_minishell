/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:17:00 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/13 14:40:00 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*list_new(char *newdata)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	new->content = ft_strdup(newdata);
	new->next = NULL;
	return (new);
}

t_list	*list_copy(t_list *head)
{
	t_list	*new_list;
	t_list	*current;

	current = head;
	new_list = list_new(current->content);
	current = current->next;
	while (current)
	{
		list_add_back(new_list, list_new(current->content));
		current = current->next;
	}
	return (new_list);
}

void	list_add_back(t_list *head, t_list *new)
{
	t_list	*current;

	current = head;
	while (current->next)
		current = current->next;
	current->next = new;
	new->next = NULL;
}

void	list_print(t_list *head, int fd)
{
	t_list	*current;

	current = head;
	while (current)
	{
		ft_putendl_fd(current->content, fd);
		current = current->next;
	}
}

void	list_free(t_list *head)
{
	t_list	*temp;

	temp = head;
	while (head)
	{
		temp = head;
		if (head->next)
			head = head->next;
		free(temp);
	}
}
