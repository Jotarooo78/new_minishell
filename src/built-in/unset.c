/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:20:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/15 13:31:28 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	copy_and_replace_env_pt2(char **env, char **new_env, int i, int j)
{
	new_env[j] = ft_strdup(env[i]);
	if (!new_env[j])
	{
		free_array(new_env);
		return (1);
	}
	return (0);
}
int	copy_and_replace_env(t_env *env, int var_pos)
{
	int		env_size;
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	j = 0;
	env_size = env_len(env->env);
	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (0);
	while (env->env[++i] && i <= env_size)
	{
		if (i == var_pos)
			j--;
		else if (copy_and_replace_env_pt2(env->env, new_env, i, j) == 1)
			return (1);
		j++;
	}
	new_env[j] = NULL;
	if (env->is_cpy)
		free_array(env->env);
	env->env = new_env;
	return (0);
}

int	unset_var(t_env *env, char *target_var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(target_var);
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], target_var, len) == 0
			&& env->env[i][len] == '=')
		{
			if (copy_and_replace_env(env, i) == 1)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	built_in_unset(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args && invalid_option(cmd->args, "unset"))
		return (printf("minishell: unset: '-': There is no option allowed\n"),
			2);
	while (cmd->args[i])
	{
		if (unset_var(env, cmd->args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
