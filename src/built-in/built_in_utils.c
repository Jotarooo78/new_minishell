/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:07:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/12 20:47:44 by armosnie         ###   ########.fr       */
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