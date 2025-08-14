/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:07:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/14 20:02:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	invalid_option(t_cmd *cmd, char *str)
{
	if (cmd->args)
	{
		if ((cmd->args[0][0] == '-' && cmd->args[0][1])
			|| (cmd->args[0][0] == '-' && !cmd->args[0][1]))
		{
			if (ft_strncmp(str, "env", 3) == 0)
				return (2);
			if (ft_strncmp(str, "pwd", 3) == 0)
				return (2);
			if (ft_strncmp(str, "export", 6) == 0)
				return (2);
			if (ft_strncmp(str, "unset", 5) == 0)
				return (2);
			if (ft_strncmp(str, "exit", 4) == 0)
				return (2);
		}
	}
	return (0);
}

int	env_len(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = envp;
	while (tmp[i])
		i++;
	return (i);
}

char *find_var(char *target_var, char *env)
{
	int	i;
	int len;

	i = 0;
	while (env[len] && env[len] != '=')
		len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], target_var, len) == 0)
			return (env);
		i++;
	}
	return (NULL);
}

int	check_is_var_exist(t_env *env, char *var)
{
	int	i;
	int	len_env_var;
	int	len_new_var;

	i = 0;
	while (env->env[i])
	{
		len_env_var = ft_strlen(env->env[i]);
		len_new_var = ft_strlen(var);
		if (ft_strncmp(env->env[i], var, len_new_var) == 0
			&& len_env_var == len_new_var)
			return (1);
		i++;
	}
	return (0);
}
