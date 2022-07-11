/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 11:59:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/06 14:02:45 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "operations.h"
#include "utils.h"

t_status	read_cmds(t_list **cmds)
{
	int		res;
	char	*cmd;

	res = get_next_line(STDIN_FILENO, &cmd);
	while (res == 1)
	{
		if (ft_lstnew_front(cmd, cmds) == NULL)
		{
			ft_lstclear(cmds, NULL);
			return (ps_set_error(E_MALLOC));
		}
		res = get_next_line(STDIN_FILENO, &cmd);
	}
	if (res == -1)
	{
		ft_lstclear(cmds, NULL);
		return (ps_set_error(E_GNL));
	}
	ft_lstreverse(cmds);
	return (OK);
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
		write(STDOUT_FILENO, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	while (cmds != NULL)
	{
		ps_exec(cmds->content, &stack_a, &stack_b);
		free(cmds->content);
		cmds = cmds->next;
	}
	if (ps_is_sorted(stack_a, stack_b))
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
	return (EXIT_SUCCESS);
}
