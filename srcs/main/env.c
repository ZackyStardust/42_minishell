/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:57:03 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/14 10:09:38 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(char **envp)
{
	int	i;

	i = 0;
	if (envp && envp[0] == NULL)
	{
		get()->env = ft_lstnew(envp[0]);
		return ;
	}
	get()->env = list_new(envp[i]);
	i++;
	while (envp[i])
	{
		list_add_back(get()->env, list_new(envp[i]));
		i++;
	}
}
/*
void	get_env(char **envp)
{
	int	i;

	i = 0;
	if (envp && envp[0] && envp[0][0])
		get()->env = list_new(ft_strdup(envp[i]));
	else
	{
		get()->env = ft_lstnew(NULL);
		return ;
	}
	i++;
	while (envp[i])
	{
		list_add_back(get()->env, list_new(ft_strdup(envp[i])));
		i++;
	}
}
*/