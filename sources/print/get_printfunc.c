/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 21:30:20 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

t_pfunc						get_printfunc(uint32_t options)
{
	if (GET_BIT(options, OPT_X)) //letter x
		return (&print_option_x);
	else if (GET_BIT(options, OPT_J))
		return (&print_option_j);
	else if (GET_BIT(options, OPT_M))
		return (&print_option_m);
	else
		//default a changer
		return (&print_option_none);
}