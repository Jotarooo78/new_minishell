/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:58 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/13 19:24:05 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// int	check_quotes(char *var)
// {
// 	int	quotes;
// 	int	double_quotes;
// 	int	i;

// 	i = 0;
// 	quotes = 0;
// 	double_quotes = 0;
// 	while (var[i])
// 	{
// 		if (var[i] == 34)
// 			double_quotes++;
// 		if (var[i] == 39)
// 			quotes++;
// 		i++;
// 	}
// 	if (quotes % 2 != 0)
// 		return (1);
// 	if (double_quotes % 2 != 0)
// 		return (1);
// 	return (0);
// }

int	check_is_var_exist(t_env *env, char *var)
{
	int	i;
	int	len_env_var;
	int len_new_var;

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
	i++;
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

int	add_and_replace_env_pt2(char **env, char **new_env, int i, int j)
{
	new_env[j] = ft_strdup(env[i]);
	if (!new_env[j])
	{
		free_array(new_env);
		return (1);
	}
	return (0);
}

int	add_and_replace_env(t_env *env, char *var)
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

int	built_in_export(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args && invalid_option(cmd, "export"))
		return (printf("minishell: unset: '-': There is no option allowed\n"),
			2);
	while (cmd->args && cmd->args[i])
	{
		if (check_export_format(cmd->args[i]) != 0)
			return (printf("minishell: export: %s: not a valid identifier\n",
					cmd->args[i]), 1);
		if (check_is_var_exist(env, cmd->args[i]) != 0)
			return (1);
		if ()
		i++;
	}
	return (0);
}

// int	print_export_env(char **env)
// {
// 	char **export_env;
// 	int env_size;
// 	int i;

// 	i = 0;
// 	env_size = env_len(env);
// 	export_env = copy_env(env);
// 	if (!export_env)
// 		return (1);
// 	sort_env(env);
// 	while (i <= env_size)
// 	{
// 		printf("declare -x ");
// 		print_format_export_env(env);
// 		i++;
// 	}
// 	return (0);
// }
