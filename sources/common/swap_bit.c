/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 20:32:46 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 22:26:37 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include<stdio.h>
uint32_t		swap_bit(uint32_t value)
{
	uint32_t	result = 0x0;

	//printf("value:  0x%08x\n", value); 
	result |= (value >> 24);
	result |= (value >> 8) & 0xFF00;
	result |= (value << 8) & 0xFF0000;
	result |= (value << 24) & 0xFF000000;

	//printf("result: 0x%08x\n", result); 
	return (result);
}