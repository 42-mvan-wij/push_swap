/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 11:59:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/07 20:09:00 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "operations.h"
#include "utils.h"

void	ps_print_sorted(t_list *stack_a, t_list *stack_b)
{
	if (stack_b != NULL)
	{
		write(STDOUT_FILENO, "KO\n", 3);
		return ;
	}
	if (stack_a == NULL)
	{
		write(STDOUT_FILENO, "OK\n", 3);
		return ;
	}
	while (stack_a->next != NULL)
	{
		if (stack_a->content > stack_a->next->content)
		{
			write(STDOUT_FILENO, "KO\n", 3);
			return ;
		}
		stack_a = stack_a->next;
	}
	write(STDOUT_FILENO, "OK\n", 3);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*cmds;
	int		res;
	char	*line;

	stack_a = ps_init_stack(argc - 1, &argv[1]);
	stack_b = NULL;
	cmds = NULL;
	res = get_next_line(STDIN_FILENO, &line);
	while (res == 1)
	{
		ft_lstadd_back(&cmds, ps_protect(ft_lstnew(line)));
		res = get_next_line(STDIN_FILENO, &line);
	}
	if (res == -1)
		ps_protect(NULL);
	while (cmds != NULL)
	{
		ps_exec(cmds->content, &stack_a, &stack_b);
		free(cmds->content);
		cmds = cmds->next;
	}
	ps_print_sorted(stack_a, stack_b);
	return (EXIT_SUCCESS);
}
