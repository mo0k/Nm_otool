/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 22:59:54 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 09:56:59 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void corrupted(char *str)
{
	//free all mem
	ft_printf("corrupted: %s\n", str);
	exit(EXIT_FAILURE);
}
