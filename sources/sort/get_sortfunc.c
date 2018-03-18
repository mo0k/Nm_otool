/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sortfunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:08 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 15:27:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

t_sfunc						get_sortfunc(uint32_t options)
{
	//if (!options || options->nosort)
	//	return (NULL);
	if (GET_BIT(options, BIT(1))) //letter p => no_sort
		return (NULL);
	if (GET_BIT(options, BIT(32))) //no letter
		return (&sort_ascii);
	else
		return (NULL);
}
