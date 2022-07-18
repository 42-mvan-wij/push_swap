/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 12:05:48 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/18 13:06:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

void	print_error(void)
{
	static char	*error_text[] = {
	[OK] = "lol, get prankt!",
	[E_MALLOC] = "Error",
	[E_EXPECTED_INT] = "Error",
	[E_TOO_DEEP] = "Error",
	[E_DUPLICATE] = "Error",
	[E_INVALID_CMD] = "Error",
	[E_GNL] = "Error",
	};

	ft_putendl_fd(error_text[ps_get_error()], STDERR_FILENO);
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
