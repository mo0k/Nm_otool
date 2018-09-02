/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sortfunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:27:08 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/03 00:02:43 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

t_sfunc						get_sortfunc(uint32_t options, enum e_archtype type)
{
	//if (!options || options->nosort)
	//	return (NULL);
	if (GET_BIT(options, OPT_p)) //letter p => no_sort
		return (NULL);
	if (GET_BIT(options, OPT_ASCII)) //no letter
		return (type == ARCH32 ? &sort_ascii32 : &sort_ascii64);
	else
		return (NULL);
}
