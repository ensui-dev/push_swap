/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:12:57 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/24 17:28:19 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tp;

	if (!lst)
		return (0);
	tp = lst;
	i = 0;
	while (tp)
	{
		tp = tp->next;
		i++;
	}
	return (i);
}
