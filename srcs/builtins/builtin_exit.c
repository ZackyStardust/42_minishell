/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:30:56 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/14 09:45:27 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_exit_is_num(char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (!trigger)
			trigger = 1;
		i++;
	}
	if (!str[i] && trigger)
		return (1);
	return (0);
}

void	builtin_exit_errors(char **token, int arg)
{
	if (arg && token[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		get()->exit_status = 1;
		exit(get()->exit_status);
	}
	ft_putstr_fd("exit\nshell: exit ", 2);
	ft_putstr_fd(token[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	rl_clear_history();
	free_tree(get()->tree);
	ft_lstclear(&get()->env, free);
	exit(2);
	return ;
}

void	builtin_exit_do(int arg, char **token)
{
	ft_putstr_fd("exit\n", 1);
	if (arg)
	{
		get()->exit_status = ft_atoi(token[1]);
		rl_clear_history();
		ft_lstclear(&get()->env, free);
		free_tree(get()->tree);
		exit(get()->exit_status);
	}
	rl_clear_history();
	ft_lstclear(&get()->env, free);
	free_tree(get()->tree);
	exit(get()->exit_status);
}

void	builtin_exit(char **token)
{
	int	arg;

	arg = 0;
	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	if (token[1] && builtin_exit_is_num(token[1]))
		arg = 1;
	if ((arg && !token[2]) || !token[1])
		builtin_exit_do(arg, token);
	return (builtin_exit_errors(token, arg));
}
