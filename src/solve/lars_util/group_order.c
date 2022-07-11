/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_order.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 17:30:12 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:30:23 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lars_util.h"

t_3_order	get_group_order_3(t_list *stack)
{
	if (stack->content < stack->next->content)
	{
		if (stack->content > stack->next->next->content)
			return (O_231);
		if (stack->next->content < stack->next->next->content)
			return (O_123);
		return (O_132);
	}
	if (stack->content < stack->next->next->content)
		return (O_213);
	if (stack->next->content < stack->next->next->content)
		return (O_312);
	return (O_321);
}
