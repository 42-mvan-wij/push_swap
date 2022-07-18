/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 12:10:04 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/14 12:47:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_status
{
	OK,
	E_MALLOC,
	E_EXPECTED_INT,
	E_TOO_DEEP,
	E_DUPLICATE,
	E_INVALID_CMD,
	E_GNL,
}	t_status;

void		print_error(void);
t_status	ps_get_error(void);
t_status	ps_set_error(t_status status);

#endif
