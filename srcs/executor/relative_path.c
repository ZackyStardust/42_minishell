/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:15:09 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 21:11:02 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_path(char *str, char *path)
{
	struct stat	buf;

	if (!path)
		return (0);
	ft_memset(&buf, 0, sizeof(buf));
	lstat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" is a directory", 2);
		get()->exit_status = 126;
		exit(get()->exit_status);
	}
	if (access(path, X_OK) >= 0)
		return (1);
	return (0);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (is_path(cmd, tmp))
		{
			free_array(path);
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	free_array(path);
	free(cmd);
	return (NULL);
}

char	*get_path(char *env, char *cmd)
{
	char	**tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (!env)
		return (NULL);
	if (ft_strncmp(env, "PATH=", 5))
		return (NULL);
	tmp = ft_split(env, ':');
	tmp2 = ft_strjoin("/", cmd);
	return (get_cmd_path(tmp, tmp2));
}

void	rlp_error_msg(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
}

char	*relative_path(char *cmd, t_list *env)
{
	char	*path;
	char	*tmp;
	t_list	*tenv;

	path = NULL;
	tenv = env;
	tmp = NULL;
	if (cmd[0] && cmd[0] == '.')
	{
		return (rp_util(cmd, path, tmp));
	}
	free_str(path);
	while (tenv)
	{
		path = get_path(tenv->content, cmd);
		if (is_path(cmd, path))
			return (path);
		free(path);
		tenv = tenv->next;
	}
	rlp_error_msg(cmd);
	return (NULL);
}
