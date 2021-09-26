/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 17:22:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/08 11:22:23 by mvan-wij      ########   odam.nl         */
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

int	ps_atoi(const char *str)
{
	int		offset;
	long	result;
	int		is_neg;

	offset = 0;
	result = 0;
	is_neg = (str[offset] == '-');
	if (is_neg || str[offset] == '+')
		offset++;
	if (str[offset] == '\0')
		ps_protect(NULL);
	while (ft_isdigit(str[offset]))
	{
		result *= 10;
		result -= str[offset] - '0';
		if ((is_neg && result < INT32_MIN) || (!is_neg && result < -INT32_MAX))
			ps_protect(NULL);
		offset++;
	}
	if (str[offset] != '\0')
		ps_protect(NULL);
	if (is_neg)
		return (result);
	return (-result);
}

void	ps_add_to_stack(char **nums, t_list **stack)
{
	long	num;
	int		len;
	t_list	*tmp_stack;

	len = 0;
	while (nums[len] != NULL)
		len++;
	while (len > 0)
	{
		num = ps_atoi(nums[len - 1]);
		tmp_stack = *stack;
		while (tmp_stack != NULL)
		{
			if (tmp_stack->content == (void *)num)
				ps_protect(NULL);
			tmp_stack = tmp_stack->next;
		}
		ft_lstadd_front(stack, ps_protect(ft_lstnew((void *)num)));
		len--;
	}
}

t_list	*ps_init_stack(int size, char **nums)
{
	t_list	*stack;
	char	**num_arr;

	if (size == 0)
		exit(EXIT_SUCCESS);
	stack = NULL;
	while (size > 0)
	{
		num_arr = ps_protect(ft_split(nums[size - 1], ' '));
		ps_protect(num_arr[0]);
		ps_add_to_stack(num_arr, &stack);
		ft_free_arr((void ***)&num_arr);
		size--;
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
		if (stack_a->content > stack_a->next->content)
			return (0);
		stack_a = stack_a->next;
	}
	return (1);
}
