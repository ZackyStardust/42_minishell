/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:55:13 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/13 14:36:42 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_list_sort(t_list *list, int fd)
{
	t_list	*temp;
	t_list	*temp_head;
	char	*str;

	temp = list_copy(list);
	temp_head = temp;
	while (export_list_is_alpha_sort(temp_head))
	{
		while (temp->next)
		{
			if (ft_strcmp(temp->content, temp->next->content) > 0)
			{
				str = temp->content;
				temp->content = temp->next->content;
				temp->next->content = str;
			}
			else
				temp = temp->next;
		}
		temp = temp_head;
	}
	export_list_print (temp_head, fd);
	free_env(temp);
}

t_list	*export_string_search(char *str)
{
	int		i;
	t_list	*current;

	i = 0;
	current = get()->env;
	while (str[i] != '=' && str[i])
		i++;
	while (current)
	{
		if (ft_strncmp(str, current->content, i) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	export_string_build(char *str, t_list *current)
{
	char	*new_str;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new_str = (char *)ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	while (str && str[i])
	{
		if (str && (str[i] == '\"' || str[i] == '\''))
			i++;
		new_str[y] = str[i];
		i++;
		y++;
	}
	if (!current)
		ft_lstadd_back(&get()->env, ft_lstnew(new_str));
	else
	{
		free(current->content);
		current->content = new_str;
	}
}

void	builtin_export(char **token, int fd)
{
	int	i;

	i = 0;
	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	if (!token && (!token[1] || !token[2]))
	{
		printf("export din't received a valid token ERROR\n");
		return ;
	}
	if (!token[1])
		export_list_sort(get()->env, fd);
	while (token[++i])
	{
		export_string_build(token[i], export_string_search(token[i]));
	}
}
