/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:20:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/13 11:48:05 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	copy_and_replace_env(t_env *env, int var_pos)
{
	int env_size;
	char **new_env;
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	env_size = (env_len(env->env) - 1);
	printf("size : %d\n", env_size);
	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (0);
	while (i <= env_size)
	{
		if (i == var_pos)
			j--;
		else
		{
			new_env[j] = ft_strdup(env->env[i]);
			if (!new_env[j])
			{
				free_array(new_env);
				return (1);
			}
		}
		j++;
		i++;
	}
	new_env[i] = NULL;
	// print_array(new_env);
	if (env->is_cpy)
		free_my_env(env);
	env->env = new_env;
	return(0);
}

int unset_var(t_env *env, char *target_var)
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
			printf("FOUND IT\n");
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
	if (cmd->args && invalid_option(cmd, "unset"))
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

// int	new_env(char ***envp, int target)
// {
// 	int		i;
//     int     j;
// 	int		len;
// 	char	**new_env;

// 	i = 0;
//     j = 0;
// 	len = env_len(env->env));
// 	new_env = malloc(sizeof(char *) * len);
// 	if (!new_env)
// 		return (1);
// 	while (env->env)[i])
// 	{
// 		if (i == target)
// 			i++;
// 		new_env[j] = ft_strdup(env->env)[i]);
// 		if (new_env[j] == NULL)
// 			return (1);
// 		i++;
//         j++;
// 	}
// 	new_env[j] = NULL;
// 	free_arrayenv->env);
// 	*envp = new_env;
// 	return (0);
// }

// int	find_var(t_cmd *cmd, char ***envp)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	while (cmd->args && cmd->args[i])
// 	{
// 		len = ft_strlen(cmd->args[i]);
// 		j = 0;
// 		while (env->env)[j])
// 		{
// 			if (ft_strncmp(env->env)[j], cmd->args[i], len - 1) == 0
// 				&& env->env)[j][len] == '=')
// 			{
// 				printf("FOUND IT\n");
// 				if (new_env(envp, j) == 1)
// 					return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }