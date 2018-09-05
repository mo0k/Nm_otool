/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printfunc32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/05 23:14:31 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

t_pfunc						get_printfunc_arch32(uint32_t options)
{
	if (GET_BIT(options, OPT_j) || GET_BIT(options, OPT_u))
		return (&print_option_j_arch32);
	else if (GET_BIT(options, OPT_x))
		return (&print_option_x_arch32);
	else
		return (&print_option_none_arch32);
}
