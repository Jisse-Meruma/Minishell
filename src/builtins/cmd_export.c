#include "minishell.h"

// print the add var such as var=value as input
//execution is export A=VALUE

int	get_end(char *str, char c)
{
	int	i;
	int	end;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (i != ft_strlen(str))
		end = 2;
	else
		end = 1;
	return (end);
}

char	**ft_split_first(char *str, char c)
{
	int		i;
	char	**str2d;
	int		end;

	end = get_end(str, c);
	str2d = (char **)calloc(end + 1, sizeof(char *));
	str2d[end] = NULL;
	if (end == 1)
	{
		str2d[0] = ft_strdup(str);
		return (str2d);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			str2d[0] = ft_substr(str, 0, i);
			++i;
			break ;
		}
		++i;
	}
	if (str[i] && str[i] == c)
		++i;
	if (ft_strlen(str) != i)
		str2d[1] = ft_substr(str, i, (ft_strlen(str) - i));
	return (str2d);
}

void	show_declare(t_infos *infos, int fd)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(current->name, fd);
		if (current->type != EMPTY)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			if (current->type == FULL)
				ft_putstr_fd(current->data, fd);
			ft_putstr_fd("\"", fd);
		}
		write(fd, "\n", 1);
		current = current->next;
	}
}

void	node_type(char **function, t_node *new_node, char *str)
{
	if ((ft_2d_arrlen(function) == 1) && !ft_strchr(str, '='))
		new_node->type = EMPTY;
	else if ((ft_2d_arrlen(function) == 1) && ft_strchr(str, '='))
		new_node->type = NO_VALUE;
	else
		new_node->type = FULL;
}

void	create_node_export(t_node *new, char **function, t_infos *infos, t_node *current)
{
	new->name = function[0];
	if ((ft_2d_arrlen(function) > 1))
		new->data = function[1];
	else
		new->data = NULL;
	new->next = NULL;
	current = infos->head;
	if (current == NULL)
		infos->head = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	change_env_type(t_infos *infos, t_env_data type, char *env_name)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (!ft_strncmp(env_name, current->name, ft_strlen(env_name)))
		{
			current->type = type;
			return ;
		}
		current = current->next;
	}
}

//theres leaks in this functions
void	exec_export(t_infos *infos, char *str)
{
	t_node	*new_node;
	char	**function;

	if (!str[0])
		return (not_valid_id(str, "export"));
	new_node = (t_node *) malloc(sizeof(t_node));
	if (!new_node)
		return (void_ret_error("Malloc fail", 2));
	function = ft_split_first(str, '=');
	if (!function)
		return (free(new_node));
	node_type(function, new_node, str);
	if (cmd_check_env_exist(infos, function[0]))
	{
		if (new_node->type > 0)
			change_env_type(infos, new_node->type, function[0]);
		change_env_data(infos, function[0], function[1]);
		ft_2dfree(function);
	}
	else
		create_node_export(new_node, function, infos, NULL);
}

void	cmd_export(t_infos *infos, t_command *cmd)
{
	int arg;

	arg = 1;
	g_glo.error = 0;
	if (!cmd->cmd_argv[arg])
		return (show_declare(infos, 1));
	while (cmd->cmd_argv[arg])
	{
		exec_export(infos, cmd->cmd_argv[arg]);
		++arg;
	}
}
