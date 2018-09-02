/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol_sect_nofound.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:34:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 23:50:28 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char 		*get_symbol_sect_nofound(char *buf, t_info *info,
													int colomn, int is_external)
{
	if (!(buf = ft_strcpy(buf, colomn == SECTNAME ? (char*)info->sectname 
													: "s")))
		return (NULL);
	if (colomn == SYMBOL_CHAR && is_external)
		buf[0] -= 32;
	return (buf);
}
