/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:10:57 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/04 01:16:37 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define FAULT "\x1B[0;31;43m"

#define TEST_BUFF_SIZE 256

typedef struct s_unit_tester_args t_unit_tester_args;

typedef void (*t_unit_tester_func) (t_unit_tester_args *);

struct s_unit_tester_args
{
	char	*pattern;
	int		from;
	int		to;
	int		current;
	int		num_fails;
	int		num_run;
	t_unit_tester_func	run;
	int		fd_stdout_dup;
};

extern t_unit_tester_args  *failsafe_args_recover;

typedef	int					(* t_unit_test) (void);
typedef int					(*printf_func) (const char *, ...);

extern const t_unit_test	g_unit_tests[];
extern const char 			*g_unit_test_names[];

void						run_test_range(t_unit_tester_args *args);
void						run_search_tests(t_unit_tester_args *args);

void						unit_testing(int argc, char **argv);

#endif
