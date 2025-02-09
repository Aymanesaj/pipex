/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:10:02 by asajed            #+#    #+#             */
/*   Updated: 2024/11/06 10:52:28 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	t_list	*linker;

	head = NULL;
	linker = NULL;
	while (lst)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		node->content = f(lst->content);
		node->next = NULL;
		if (!head)
			head = node;
		else
			linker->next = node;
		linker = node;
		lst = lst->next;
	}
	return (head);
}
// #include <stdio.h>
// void *aymane(void *s)
// {
// 	char *s1 = (char *)s;
// 	char *result = (char *)malloc(ft_strlen(s1) + 1);
// 	int i = 0;
// 	if (!result)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		result[i] = ft_toupper(s1[i]);
// 		i++;
// 	}
// 	result[i] = '\0';
// 	return result;
// }
// void delete(void *s)
// {
// }
// int main()
// {
// 	t_list *lst = ft_lstnew("aymane");
// 	lst->next = ft_lstnew("said");
// 	lst->next->next = ft_lstnew("othman");
// 	lst->next->next->next = ft_lstnew("hamzaa");
// 	t_list *new_lst = ft_lstmap(lst, aymane, delete);
// 	while (new_lst)
// 	{
// 		printf("%s\n", (char *)new_lst->content);
// 		new_lst = new_lst->next;
// 	}
// 	return 0;
// }