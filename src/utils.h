/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 17:41:46 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/07 15:53:50 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

typedef enum e_status
{
	OK,
	E_MALLOC,
	E_EXPECTED_INT,
	E_TOO_DEEP,
	E_DUPLICATE,
	E_GNL,
}	t_status;

int			ps_atoi(char *num);
t_status	ps_init_stack(int size, char **nums, t_list **stack);
int			ps_is_sorted(t_list *stack_a, t_list *stack_b);

t_status	ps_get_error(void);
t_status	ps_set_error(t_status status);

#endif
