/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_ops.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/29 11:35:23 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 16:24:22 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "operations.h"
#include <unistd.h>

int	ps_exec(char *cmd, t_list **stack_a, t_list **stack_b)
{
	if (ft_memcmp(cmd, "sa", 3) == 0)
		return (ps_swap(stack_a));
	if (ft_memcmp(cmd, "sb", 3) == 0)
		return (ps_swap(stack_b));
	if (ft_memcmp(cmd, "ss", 3) == 0)
		return (ps_swap2(stack_a, stack_b));
	if (ft_memcmp(cmd, "pa", 3) == 0)
		return (ps_push(stack_a, stack_b));
	if (ft_memcmp(cmd, "pb", 3) == 0)
		return (ps_push(stack_b, stack_a));
	if (ft_memcmp(cmd, "ra", 3) == 0)
		return (ps_rotate(stack_a));
	if (ft_memcmp(cmd, "rb", 3) == 0)
		return (ps_rotate(stack_b));
	if (ft_memcmp(cmd, "rr", 3) == 0)
		return (ps_rotate2(stack_a, stack_b));
	if (ft_memcmp(cmd, "rra", 4) == 0)
		return (ps_reverse_rotate(stack_a));
	if (ft_memcmp(cmd, "rrb", 4) == 0)
		return (ps_reverse_rotate(stack_b));
	if (ft_memcmp(cmd, "rrr", 4) == 0)
		return (ps_reverse_rotate2(stack_a, stack_b));
	ps_protect(NULL);
	return (0);
}

void	ps_exec_print(char *cmd, t_list **stack_a, t_list **stack_b)
{
	ps_exec(cmd, stack_a, stack_b);
	ft_putendl_fd(cmd, STDOUT_FILENO);
}

void	ps_undo(char *cmd, t_list **stack_a, t_list **stack_b)
{
	if (ft_memcmp(cmd, "pb", 3) == 0)
		ps_push(stack_a, stack_b);
	else if (ft_memcmp(cmd, "pa", 3) == 0)
		ps_push(stack_b, stack_a);
	else if (ft_memcmp(cmd, "ra", 3) == 0)
		ps_reverse_rotate(stack_a);
	else if (ft_memcmp(cmd, "rb", 3) == 0)
		ps_reverse_rotate(stack_b);
	else if (ft_memcmp(cmd, "rr", 3) == 0)
		ps_reverse_rotate2(stack_a, stack_b);
	else if (ft_memcmp(cmd, "rra", 4) == 0)
		ps_rotate(stack_a);
	else if (ft_memcmp(cmd, "rrb", 4) == 0)
		ps_rotate(stack_b);
	else if (ft_memcmp(cmd, "rrr", 4) == 0)
		ps_rotate2(stack_a, stack_b);
	else if (ft_memcmp(cmd, "sa", 3) == 0)
		ps_swap(stack_a);
	else if (ft_memcmp(cmd, "sb", 3) == 0)
		ps_swap(stack_b);
	else if (ft_memcmp(cmd, "ss", 3) == 0)
		ps_swap2(stack_a, stack_b);
	else
		ps_protect(NULL);
}
