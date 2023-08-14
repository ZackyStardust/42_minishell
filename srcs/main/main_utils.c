/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:18:49 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 16:26:38 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main_skip_quotes(char *str, int *i)
{
	char	c;

	c = str[(*i)++];
	while (str[*i])
	{
		if (str[*i] == c)
			return (0);
		(*i)++;
	}
	return (1);
}

int	main_syntax_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
		return (main_syntax_error(1));
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (main_syntax_error(2));
		else if (ft_strchr("\'\"", str[i]) && main_skip_quotes(str, &i))
			return (main_syntax_error(3));
		i++;
	}
	return (0);
}

int	empty_input(char *str)
{
	int	i;

	if (!str[0])
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!is_match(str[i], WHITE_SPACE))
			return (1);
	}
	return (0);
}

int	main_syntax_error(int i)
{
	if (i != 0)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		if (i == 1 || i == 2)
			ft_putstr_fd("|", STDERR_FILENO);
		else if (i == 3)
			ft_putstr_fd("\"' or `'", STDERR_FILENO);
		else
			ft_putstr_fd("newline", STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		get()->exit_status = 2;
	}
	return (i);
}

void	main_set_enviroment(char **envp)
{
	get()->exit_status = 0;
	get()->flag = 0;
	get_env(envp);
	get()->envp_matriz = NULL;
	if (isatty(STDIN_FILENO) != 1 || !get()->env)
	{
		if (get()->env)
			free_env(get()->env);
		ft_putstr_fd("\001\e[1m\e[35m\002" "MiniShell " "\001\e[1m\e[33m\002", 2);
		perror("attributes setting failed");
		exit(errno);
	}
}
