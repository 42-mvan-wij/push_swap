/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 11:59:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 14:09:33 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "operations.h"
#include "utils.h"

void	read_cmds(t_list **cmds)
{
	int		res;
	char	*cmd;

	res = get_next_line(STDIN_FILENO, &cmd);
	while (res == 1)
	{
		ft_lstadd_back(cmds, ps_protect(ft_lstnew(cmd)));
		res = get_next_line(STDIN_FILENO, &cmd);
	}
	if (res == -1)
		ps_protect(NULL);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*cmds;

	stack_a = ps_init_stack(argc - 1, &argv[1]);
	stack_b = NULL;
	cmds = NULL;
	read_cmds(&cmds);
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
