/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:06:54 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/13 15:05:13 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_error_msg(char *token, char *msg)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd(msg, 2);
	get()->exit_status = 1;
}

void	builtin_cd_do(char **token)
{
	if (token[1][0] == '.' && token[1][1] == '.' && token[1][2] == '\0')
	{
		chdir("..");
	}
	else
	{
		if (access(token[1], F_OK) < 0)
		{
			cd_error_msg(token[1], ": No such file or directory");
			return ;
		}
		if (chdir(token[1]) == -1)
		{
			cd_error_msg(token[1], ": Can't access directory");
			return ;
		}
		get()->exit_status = 0;
	}
}

void	builtin_cd(char **token)
{
	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	if (token[0] && !token[1])
		return ;
	if (token[0])
		builtin_cd_do(token);
}
