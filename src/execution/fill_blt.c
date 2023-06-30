#include "minishell.h"
#include <fcntl.h>

void	exec_built(t_infos *infos, t_command *cmd)
{
	if (!cmd->cmd_argv[0])
		return ;
	if (!compare(cmd->cmd_argv[0], "pwd"))
		cmd_pwd(infos);
	else if (!compare(cmd->cmd_argv[0], "echo"))
		cmd_echo(cmd);
	else if (!compare(cmd->cmd_argv[0], "env"))
		cmd_env(infos);
	else if (!compare(cmd->cmd_argv[0], "getenv"))
		cmd_get_env(infos, cmd->cmd_argv[1]);
	else if (!compare(cmd->cmd_argv[0], "exit"))
		cmd_exit(infos, cmd->cmd_argv);
	else if (!compare(cmd->cmd_argv[0], "cd"))
		cmd_cd(infos, cmd->cmd_argv[1]);
	else if (!compare(cmd->cmd_argv[0], "unset"))
		cmd_unset(infos, cmd);
	else if (!compare(cmd->cmd_argv[0], "export"))
		cmd_export(infos, cmd);
	else
		return ;
}

void	if_builtins(t_command *cmd)
{
	if (!cmd->cmd_argv[0])
		cmd->cmd_is_blt = NOCMD;
	else if (!ft_strncmp("cd", cmd->cmd_argv[0], 3) || \
	!ft_strncmp("exit", cmd->cmd_argv[0], 5) || \
	!ft_strncmp("export", cmd->cmd_argv[0], 7) || \
	!ft_strncmp("unset", cmd->cmd_argv[0], 6))
		cmd->cmd_is_blt = BUILT_PARENT;
	else if (!ft_strncmp("echo", cmd->cmd_argv[0], 5) || \
	!ft_strncmp("env", cmd->cmd_argv[0], 4) || \
	!ft_strncmp("getenv", cmd->cmd_argv[0], 7) || \
	!ft_strncmp("pwd", cmd->cmd_argv[0], 4))
		cmd->cmd_is_blt = BUILT;
	else
		cmd->cmd_is_blt = NOT_BUILT;
}
