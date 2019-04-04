/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:53:02 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/04 13:37:57 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_main.h"
#include "assert.h"

t_unit_tester_args		*failsafe_args_recover;

/* ----------------------------------------------------------------------------
** Initializer for unit testing args
** --------------------------------------------------------------------------*/
static void		init_args(t_unit_tester_args *args, char *prefix,
					int from, int to, t_unit_tester_func f)
{
	char	*pattern;

	if (prefix != NULL)
	{
		//Append a * onto pattern so we don't have to modify the piscine's ft_match
		size_t len = strlen(prefix) + 2;
		pattern = (char *)malloc(len);
		pattern[len - 1] = '\0';
		for (size_t i = 0; i < len - 2; i++)
			pattern[i] = prefix[i];
		pattern[len - 2] = '*';
	}
	else
	{
		pattern = NULL;
	}

	args->pattern = pattern;
	args->from = from;
	args->to = to;
	args->current = from;
	args->num_fails = 0;
	args->num_run = 0;
	args->run = f;
	//Back up stdout
	args->fd_stdout_dup = dup(fileno(stdout));
}

/* ----------------------------------------------------------------------------
** Entry main
** --------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	unit_testing(argc, argv);
	return (0);
}

/* ----------------------------------------------------------------------------
** Dispatch function for all unit testing from main
** --------------------------------------------------------------------------*/
void		unit_testing(int argc, char **argv)
{
	t_unit_tester_args		args;
	failsafe_args_recover = &args;
	int from, to;

	if (argc > 1)
	{
		if ((argv[1][0] == '*') || (argv[1][0] >= 'a' && argv[1][0] <= 'z')
				|| (argv[1][0] >= 'A' && argv[1][0] <= 'Z'))
		{
			//Search pattern
			init_args(&args, argv[1], 0, 2147483647, run_search_tests);
			run_search_tests(&args);
		}
		else
		{
			from = atoi(argv[1]);
			if (argc > 2)
				to = atoi(argv[2]);
			else
				to = 2147483647;
			init_args(&args, NULL, from, to, run_test_range);
			run_test_range(&args);
		}
	}
	else
	{
		//No arguments. Run all tests
		from = 0;
		to = 2147483647;
		init_args(&args, NULL, from, to, run_test_range);
		run_test_range(&args);
	}
}

/* ----------------------------------------------------------------------------
** Logs a failed test to the test results file
** --------------------------------------------------------------------------*/
void	log_failed_test(int test_number, char *signal_terminated)
{
	char	buff[TEST_BUFF_SIZE + 1];
	buff[TEST_BUFF_SIZE] = '\0';

	//Open files
	int fout = open(TEST_OUTPUT_FILENAME, O_CREAT | O_WRONLY | O_APPEND,
				S_IRWXU | S_IRWXG | S_IRWXO);
	if (fout < 0) return;

	//Write to test results file
	snprintf(buff, TEST_BUFF_SIZE, 
			"Test %3i (%s) : FAILED.\n",
			test_number, g_unit_test_names[test_number]);
	write(fout, buff, strlen(buff));

	t_assertresult	*r = get_results();
	if (!signal_terminated)
	{
		//Get all the asserts from the test
		int assertion_number = get_list_size(r);
		while (r)
		{
			if (r->completed == 0)
			{
				snprintf(buff, TEST_BUFF_SIZE, 
						"     Assertion %i exited without completing.\n",
						assertion_number);
				write(fout, buff, strlen(buff));
			}
			else if (r->result == AR_FAIL)
			{
				snprintf(buff, TEST_BUFF_SIZE,
						"     Assertion %i: Expected {%s}\n",
						assertion_number, r->expected);
				write(fout, buff, strlen(buff));
				snprintf(buff, TEST_BUFF_SIZE,
						"     Assertion %i: Actual   {%s}\n",
						assertion_number, r->actual);
				write(fout, buff, strlen(buff));
			}
			else if (r->result == AR_PASS)
			{
				snprintf(buff, TEST_BUFF_SIZE, 
						"     Assertion %i passed.\n",
						assertion_number);
				write(fout, buff, strlen(buff));
			}
			else
			{
				snprintf(buff, TEST_BUFF_SIZE, 
						"     Assertion %i has undefined state. Please notify gfielder.\n",
						assertion_number);
				write(fout, buff, strlen(buff));
			}
			assertion_number--;
			r = r->next;
		}
	}
	else
	{
		snprintf(buff, TEST_BUFF_SIZE,
				"     Signal: %s\n", signal_terminated);
		write(fout, buff, strlen(buff));
	}
	//close files)
	close(fout);
}

/* ----------------------------------------------------------------------------
** Signal Handlers for segfault, bus error, etc.
** --------------------------------------------------------------------------*/
static void failsafe_recover(void)
{
	//Go to the next test
	failsafe_args_recover->current++;
	failsafe_args_recover->num_fails++;
	failsafe_args_recover->num_run++;
	//Cleanup stdout
	fflush(stdout);
	fflush(stderr);
	//Recover stdout from the args failsafe
	dup2(failsafe_args_recover->fd_stdout_dup, fileno(stdout));
}
static void	handle_sigsegv(int sigval)
{
	(void)sigval;
	log_failed_test(failsafe_args_recover->current, "Segmentation fault");
	failsafe_recover();
	printf(FAULT "SEGFAULT" RESET "]\n");
	failsafe_args_recover->run(failsafe_args_recover);
}
static void	handle_sigbus(int sigval)
{
	(void)sigval;
	log_failed_test(failsafe_args_recover->current, "Bus error");
	failsafe_recover();
	printf(FAULT "BUSERROR" RESET "]\n");
	failsafe_args_recover->run(failsafe_args_recover);
}
static void handle_sigabrt(int sigval)
{
	(void)sigval;
	log_failed_test(failsafe_args_recover->current, "Abort signal received");
	failsafe_recover();
	printf(FAULT "SIGABRT" RESET "]\n");
	failsafe_args_recover->run(failsafe_args_recover);
}

/* ----------------------------------------------------------------------------
** Runs a specific test
** --------------------------------------------------------------------------*/
static int		run_test(int test_number)
{
	int				failed = 0;

	signal(SIGSEGV, handle_sigsegv);
	signal(SIGBUS, handle_sigbus);
	signal(SIGABRT, handle_sigabrt);

	printf("Test %4i:  %-42s [",test_number, g_unit_test_names[test_number]);

	//Run test
	failed = g_unit_tests[test_number]();

	//If the test was a nocrash_ test, then it passed
	if (strncmp(g_unit_test_names[test_number], "nocrash_", 8) == 0)
		failed = 0;

	if (failed)
	{
		log_failed_test(test_number, NULL);
		printf(RED "FAIL" RESET);
	}
	else
	{
		printf(GRN "PASS" RESET);
	}
	printf("]\n");

	flush_results();

	return failed;
}

/* ----------------------------------------------------------------------------
** Prints a message at the end of all the tests
** --------------------------------------------------------------------------*/
static void	print_end_test_message(int num_tests, int num_passed)
{
	printf("Tests completed. %i/%i tests passed.\n",
			num_passed, num_tests);
	if (num_passed != num_tests)
		printf("See %s for details.\n", TEST_OUTPUT_FILENAME);
}

/* ----------------------------------------------------------------------------
** The ft_match function is used for wildcard-based searches
** s2 has an indeterminate number of *, s1 is the function name to test.
** --------------------------------------------------------------------------*/
static int	ft_match(const char *s1, char *s2);
static int	ft_match_helper(const char *s1, char *s2)
{
	int		i;
	char	next;
	int		found;

	i = 0;
	next = *(s2 + 1);
	found = 0;
	if (next == '\0')
		return (1);
	if (next == '*')
		return (ft_match(s1, s2 + 1));
	while (1)
	{
		if (s1[i] == next)
			found = (ft_match(s1 + i, s2 + 1));
		if (found)
			return (found);
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (-1);
}
static int	ft_match(const char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	if (*s2 != '*' && (*s1 != *s2))
		return (0);
	if (*s2 == '*')
		return (ft_match_helper(s1, s2));
	else if (*s1 == *s2)
		return (ft_match(s1 + 1, s2 + 1));
	return (-1);
}

/* ----------------------------------------------------------------------------
** Runs all the tests that match the search pattern
** --------------------------------------------------------------------------*/
void	run_search_tests(t_unit_tester_args *args)
{
	int fail = 0;
	
	//Search tests
	while (g_unit_tests[args->current] != NULL)
	{
		if (ft_match(g_unit_test_names[args->current], args->pattern))
		{
			fail = run_test(args->current);
			args->num_fails += fail;
			args->num_run++;
		}
		args->current++;
	}
	print_end_test_message(args->num_run, args->num_run - args->num_fails);
	free(args->pattern);
	exit(0); //needed in case a test segfaulted
}

/* ----------------------------------------------------------------------------
** Runs a range of tests
** --------------------------------------------------------------------------*/
void	run_test_range(t_unit_tester_args *args)
{
	int	fail = 0;

	while (args->current <= args->to && g_unit_tests[args->current] != NULL)
	{
		fail = run_test(args->current);
		args->num_fails += fail;
		args->num_run++;
		args->current++;
	}
	print_end_test_message(args->num_run, args->num_run - args->num_fails);
	exit(0); //needed in case a test segfaulted
}
