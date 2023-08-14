/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 21:14:29 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/11 15:52:45 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export_list_is_alpha_sort(t_list *head)
{
	t_list	*current;

	current = head;
	while (current->next)
	{
		if (ft_strcmp(current->content, current->next->content) > 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	export_list_print(t_list *head, int fd)
{
	t_list	*current;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	current = head;
	while (current && current->content)
	{
		ft_putstr_fd("declare -x ", fd);
		while (current && current->content && current->content[i])
		{
			if (i > 0 && current && current->content[i - 1] == '=')
			{
				ft_putstr_fd("\"", fd);
				flag = 1;
			}
			ft_putchar_fd(current->content[i], 1);
			i++;
		}
		export_list_print_end(flag, fd);
		i = 0;
		flag = 0;
		current = current->next;
	}
}

void	export_list_print_end(int flag, int fd)
{
	if (flag == 1)
		ft_putendl_fd("\"", fd);
	else
		ft_putendl_fd("", fd);
}
