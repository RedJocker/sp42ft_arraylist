/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:50:35 by maurodri          #+#    #+#             */
/*   Updated: 2024/01/28 05:59:47 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arraylist.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
char g_ch;

void assert_str_alst(char *actual_str)
{
	char	expect_str[20];

	snprintf(expect_str, 20, "str_%c", g_ch);
	assert(strcmp(expect_str, actual_str) == 0);
	g_ch++;
}

void test_add()
{
	t_arraylist	alst;
	char *str;
	printf("test_add: ");
	alst = ft_arraylist_new(free);

	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		str = malloc(20);
		snprintf(str, 20, "str_%c", ch);
		alst = ft_arraylist_add(alst, str);
		if (!alst)
		{
			printf("Failed increasing memory for adding");
			exit(1);
		}
	}
	assert(ft_arraylist_len(alst) == 26);
	g_ch = 'a';
	ft_arraylist_foreach(alst, (void (*) (void *)) assert_str_alst);
	g_ch = 'a';
	for (int i = 0; i < 26; i++)
	{
		assert_str_alst(ft_arraylist_get(alst, i));
	}
	ft_arraylist_destroy(alst);
	printf("[OK]\n");
}

void test_replace()
{
	t_arraylist	alst;
	char *str;
	printf("test_replace: ");
	alst = ft_arraylist_new(free);

	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		str = malloc(20);
		snprintf(str, 20, "str_%c", ch);
		alst = ft_arraylist_add(alst, str);
		if (!alst)
		{
			printf("Failed increasing memory for adding");
			exit(1);
		}
	}
	assert(ft_arraylist_len(alst) == 26);
	g_ch = 'a';
	str = malloc(20);
	snprintf(str, 20, "some string");
	ft_arraylist_replace(alst, str, 5);
	assert(strcmp(ft_arraylist_get(alst, 5), "some string") == 0);
	ft_arraylist_destroy(alst);
	printf("[OK]\n");
}

int	main(void)
{
	test_add();
	test_replace();
}
