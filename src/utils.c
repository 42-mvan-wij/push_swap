/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 17:22:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/24 17:19:20 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	*ps_protect(void *ptr)
{
	if (ptr == NULL)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

t_list	*ps_init_stack(int size, char **nums)
{
	t_list	*stack;
	int		num;
	bool	had_overflow;

	if (size == 0)
		exit(EXIT_SUCCESS);
	stack = NULL;
	while (size > 0)
	{
		size--;
		if (!ft_atoi_strict(nums[size], &num, &had_overflow) || had_overflow)
		{
			ft_lstclear(&stack, NULL);
			ps_protect(NULL);
		}
		ps_protect(ft_lstnew_front((void *)(long)num, &stack));
	}
	return (stack);
}

int	ps_is_sorted(t_list *stack_a, t_list *stack_b)
{
	if (stack_b != NULL)
		return (0);
	if (stack_a == NULL)
		return (1);
	while (stack_a->next != NULL)
	{
		if ((long)stack_a->content > (long)stack_a->next->content)
			return (0);
		stack_a = stack_a->next;
	}
	return (1);
}
