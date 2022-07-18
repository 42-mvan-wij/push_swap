/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 11:59:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/18 13:07:11 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "operations.h"
#include "utils.h"

t_cmd	get_command(char *str)
{
	if (ft_strncmp(str, "sa", 3) == 0)
		return (SA);
	if (ft_strncmp(str, "sb", 3) == 0)
		return (SB);
	if (ft_strncmp(str, "ss", 3) == 0)
		return (SS);
	if (ft_strncmp(str, "pa", 3) == 0)
		return (PA);
	if (ft_strncmp(str, "pb", 3) == 0)
		return (PB);
	if (ft_strncmp(str, "ra", 3) == 0)
		return (RA);
	if (ft_strncmp(str, "rr", 3) == 0)
		return (RR);
	if (ft_strncmp(str, "rra", 3) == 0)
		return (RRA);
	if (ft_strncmp(str, "rrb", 3) == 0)
		return (RRB);
	if (ft_strncmp(str, "rrr", 3) == 0)
		return (RRR);
	ps_set_error(E_INVALID_CMD);
	return (NONE);
}

void	*malloc_fail_check(void *ptr)
{
	if (ptr == NULL)
		ps_set_error(E_MALLOC);
	return (ptr);
}

t_status	add_cmd(t_list **cmds, char *cmd_str)
{
	t_cmd	cmd;

	cmd = get_command(cmd_str);
	if (cmd == NONE)
	{
		ft_lstclear(cmds, NULL);
		return (ps_set_error(E_INVALID_CMD));
	}
	if (ft_lstnew_front((void *)cmd, cmds) == NULL)
	{
		ft_lstclear(cmds, NULL);
		return (ps_set_error(E_MALLOC));
	}
	return (OK);
}

t_status	read_cmds(t_list **cmds)
{
	int		res;
	char	*cmd_str;

	res = 1;
	while (res == 1)
	{
		res = get_next_line(STDIN_FILENO, &cmd_str);
		if (res == -1)
		{
			ft_lstclear(cmds, NULL);
			return (ps_set_error(E_GNL));
		}
		if (cmd_str[0] == '\0' && res == 0)
		{
			free(cmd_str);
			break ;
		}
		add_cmd(cmds, cmd_str);
		free(cmd_str);
		if (ps_get_error() != OK)
			return (ps_get_error());
	}
	ft_lstreverse(cmds);
	return (ps_set_error(OK));
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*cmds;

	cmds = NULL;
	stack_b = NULL;
	if (ps_init_stack(argc - 1, &argv[1], &stack_a) != OK
		|| read_cmds(&cmds) != OK)
	{
		ft_lstclear(&stack_a, NULL);
		print_error();
		return (EXIT_FAILURE);
	}
	while (cmds != NULL)
	{
		ps_exec((t_cmd)cmds->content, &stack_a, &stack_b);
		ft_lstnext(&cmds, NULL);
	}
	if (ps_is_sorted(stack_a, stack_b))
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
	ft_lstclear(&stack_a, NULL);
	ft_lstclear(&stack_b, NULL);
	return (EXIT_SUCCESS);
}
