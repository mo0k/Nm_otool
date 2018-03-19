/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/19 15:29:07 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

t_pfunc						get_printfunc(uint32_t options)
{
	if (GET_BIT(options, OPT_J))
		return (&print_option_j);
	else if (GET_BIT(options, OPT_X))
		return (&print_option_x);
	else if (GET_BIT(options, OPT_M))
		return (&print_option_m);
	else
		return (&print_option_none);
}