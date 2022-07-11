/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 17:22:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/06 14:03:24 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"

t_status	ps_init_stack(int size, char **nums, t_list **stack)
{
	int		num;
	bool	had_overflow;

	if (size == 0)
		exit(EXIT_SUCCESS);
	*stack = NULL;
	while (size > 0)
	{
		size--;
		if (!ft_atoi_strict(nums[size], &num, &had_overflow) || had_overflow)
		{
			ft_lstclear(stack, NULL);
			return (ps_set_error(E_EXPECTED_INT));
		}
		if (ft_lstnew_front((void *)(long)num, stack) == NULL)
		{
			ft_lstclear(stack, NULL);
			return (ps_set_error(E_MALLOC));
		}
	}
	return (OK);
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

static t_status	*get_error_ptr(void)
{
	static t_status	error = OK;

	return (&error);
}

t_status	ps_get_error(void)
{
	return (*get_error_ptr());
}

t_status	ps_set_error(t_status status)
{
	*get_error_ptr() = status;
	return (status);
}
