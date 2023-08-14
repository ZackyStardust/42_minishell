/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:57:34 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 15:53:51 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*rp_util(char *cmd, char *path, char *tmp)
{
	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (is_path(cmd, path))
		return (path);
	return (NULL);
}

char	*absolute_path(char *cmd, char **m_env)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is a directory", 2);
		free(m_env);
		get()->exit_status = 126;
		exit(get()->exit_status);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		free(m_env);
		get()->exit_status = 127;
		exit(get()->exit_status);
	}
	return (cmd);
}

char	*cmd_path(char *cmd, t_list *env, char **m_env)
{
	if (cmd[0] == '/')
		return (absolute_path(cmd, m_env));
	else
		return (relative_path(cmd, env));
}
