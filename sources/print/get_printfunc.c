/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 15:28:35 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

t_pfunc						get_printfunc(uint32_t options)
{
	if (GET_BIT(options, BIT(4))) //letter p 
		return (&print_hexa);
	else if (GET_BIT(options, BIT(3)))
		return (&print_just_symbol_names);
	else
		//default a changer
		return (&prinf_default);
}