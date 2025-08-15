/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/15 19:30:01 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// dup puis unset et export

// int	save_pwd_update_oldpwd(t_env *env)
// {
	
// }

void copy_new_path(char *new_path, char **split_path)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (split_path[i + 1])
	{
		k = 0;
		while (split_path[i][k] && new_path[j])
		{
			new_path[j] = split_path[i][k];
			k++;
			j++;
		}
		i++;
	}
	new_path[j] = '\0';
	free_array(split_path);
	printf("end copy new path\n");
}

int update_my_path_and_env(t_env *env, char *target_path)
{
	char *path;
	char **split_path;
	char	*new_path;
	int len;

	// if (save_pwd_update_oldpwd(env) == 1)
	// 	return (1);
	len = ft_strlen(path);
	new_path = malloc(sizeof(char) * len + 1);
	split_path = ft_split(path, '/');
	if (!split_path)
		return (1);
	copy_new_path(new_path, split_path);
	if (get_my_unset_env(&env->env, target_path))
		return (1);
	if (get_my_export_env(&env->env, new_path))
		return (1);
	free(new_path);
	printf("end update_my_path\n");
	return (0);
}

int get_specific_path(t_env *env, char *target_path)
{
	char	*path;
	
	path = find_var(target_path, env->env);
	if (path == NULL)
		return (1);
	printf("path from get_specific_path : %s\n", path);
	get_my_export_env(&env->env, target_path);
	// if (update_my_path_and_env(env, target_path) == 1) // probleme ici
	// 	return (1);
	if (chdir(path) == -1)
		return (1);
	return (0);
}


int	built_in_cd(t_cmd *cmd, t_env *env)
{
	int	len;

	len = count_args(cmd);
	if (ft_strncmp(cmd->name, "cd..", 4) == 0)
		return (printf("minishell: cd..: command not found\n"), 0);
	if (cmd->args)
	{
		if (cmd->args[0][0] == '-' && cmd->args[0][1])
			return (printf("minishell: cd: '-': There is no option allowed\n"), 2);
		if (len == 0 || ((ft_strncmp(cmd->args[0], "~", 1) == 0 && len == 1)))
		{
			if (get_specific_path(env, "HOME=") == 0)
				return (0);
			return (perror("cd: HOME"), 1);
		}
		if ((ft_strncmp(cmd->args[0], "-", 1) == 0 && len == 1))
		{
			if (get_specific_path(env, "OLDPWD=") == 0)
				return (0);
			return (perror("cd: OLDPWD:"), 1);
		}
	}
	return (0);
}


// si il y a pas eu de changement de directory avec cd, oldpwd doit etre NULL

// test a faire : enlever le OLDPWD ou HOME et voir si getenv chope la variable a partir de ma struct env ou du vrai env