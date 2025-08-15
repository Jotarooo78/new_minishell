/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:58 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/15 13:52:06 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	check_head_var(char *var)
{
	int	i;

	i = 0;
	if ((var[0] != '_' && ft_isalpha(var[0]) == 0) || var[0] == '=')
		return (-1);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (-1);
		i++;
	}
	if (var[i] == '=')
		return (i);
	return (-1);
}

int	check_export_format(char *var)
{
	int	sign;
	int	i;

	sign = 0;
	i = check_head_var(var);
	if (i == -1)
		return (1);
	i++;
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_' && var[i] != '/'
			&& var[i] != ' ' && var[i] != '-' && var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**copy_and_replace_my_env(char **env, char *var)
{
	int i;
	char **tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * env_len(env) + 1);
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (check_is_same_var(env[i], var))
			tmp[i] = ft_strdup(var);
		else
			tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
		{
			free_array(tmp);
			return (NULL);
		}
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**copy_and_add_my_env(char **env, char *var)
{
	int i;
	char **tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * env_len(env) + 2);
	printf("size : %d\n", env_len(env));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
		{
			free_array(tmp);
			return (NULL);
		}
		i++;
	}
	printf("i : %d\n", i);
	printf("tmp : %s\n", tmp[i]);
	tmp[i] = ft_strdup(var);
	printf("tmp : %s\n", tmp[i]);
	printf("i : %d\n", i);
	if (!tmp[i])
	{
			free_array(tmp);
			return (NULL);
	}
	tmp[i + 1] = NULL;
	printf("tmp : %s\n", tmp[i]);
	printf("i : %d\n", i);
	return (tmp);
}

int	get_my_env(char ***env, char *new_var)
{
	char **tmp;
	int i;

	i = 0;
	while ((*env)[i])
	{
		if (check_is_same_var((*env)[i], new_var))
		{
			tmp = copy_and_replace_my_env(*env, new_var);
			if (!tmp)
				return (1);
			free_array(*env);
			*env = tmp;
			return (0);
		}
		i++;
	}
	tmp = copy_and_add_my_env(*env, new_var);
	if (!tmp)
		return (1);
	free_array(*env);
	*env = tmp;
	return (0);
}

int	built_in_export(t_cmd *cmd, t_env *env, int code_error)
{
	int	i;

	i = -1;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args && invalid_option(cmd->args, "export"))
		return (printf("minishell: unset: '-': There is no option allowed\n"),
			2);
	while (cmd->args && cmd->args[++i])
	{
		while (cmd->args[i] && check_export_format(cmd->args[i]) == 1)
		{
			if (check_export_format(cmd->args[i]) != 0)
			{
				printf("minishell: export: %s: not a valid identifier\n",
					cmd->args[i]);
				code_error = 1;
			}
			i++;
		}
		if (cmd->args && cmd->args[i] && get_my_env(&(env->env), cmd->args[i]) == 1)
			return (1);
	}
	return (code_error);
}
