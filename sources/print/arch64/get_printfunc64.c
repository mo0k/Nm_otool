/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printfunc64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/01 19:39:08 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

t_pfunc						get_printfunc_arch64(uint32_t options)
{
	if (GET_BIT(options, OPT_J) || (GET_BIT(options, OPT_u) && !GET_BIT(options, OPT_M)))
		return (&print_option_j_arch64);
	else if (GET_BIT(options, OPT_X))
		return (&print_option_x_arch64);
	else if (GET_BIT(options, OPT_M))
		return (&print_option_m_arch64);
	else
		return (&print_option_none_arch64);
}