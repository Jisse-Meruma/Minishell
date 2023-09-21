/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_invalid_id.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:15:34 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 16:23:37 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_cmd(t_command *cmd)
{
	int	i;

	i = 1;
	if (cmd->cmd_argv[1])
	{
		free(cmd->cmd_argv[0]);
		while (cmd->cmd_argv[i])
		{
			cmd->cmd_argv[i - 1] = cmd->cmd_argv[i];
			++i;
		}
		cmd->cmd_argv[i - 1] = NULL;
	}
}

void	fix_cmd(t_command *cmd, t_infos *infos, int *ex)
{
	if (cmd->cmd_argv[1])
	{
		while (!cmd->cmd_argv[0][0] && cmd->cmd_argv[1])
			move_cmd(cmd);
	}
	else
	{
		infos->error = 0;
		*ex = 0;
	}
}

void	skip(const char *str, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	while (str[*i] == ' ' || str[*i] == '\f' || str[*i] == '\n' || \
	str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\v')
		(*i)++;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

int	ft_atoi64_overflow(const char *str, int64_t *numb)
{
	int	i;
	int	sign;
	int	digit;

	*numb = 0;
	if (!str)
		return (1);
	skip(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (*numb > INT64_MAX / 10 || (*numb == INT64_MAX / 10 && \
		digit > INT64_MAX % 10))
		{
			if (sign == 1)
				*numb = INT64_MAX;
			else
				*numb = INT64_MIN;
			return (1);
		}
		*numb = *numb * 10 + digit;
		i++;
	}
	*numb *= sign;
	return (0);
}

int	check_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i])
	{
		if (ft_isspace(str[i]) || \
		(str[i] >= 32 && str[i] <= 47) || \
		(str[i] >= 58 && str[i] <= 60) || \
		(str[i] >= 62 && str[i] <= 64) || \
		(str[i] >= 91 && str[i] <= 94) || \
		(str[i] == 96) || \
		(str[i] >= 123 && str[i] <= 126))
			return (0);
		if (str[i] == '=')
			return (1);
		++i;
	}
	return (1);
}
