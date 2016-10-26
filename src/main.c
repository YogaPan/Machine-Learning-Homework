/*
 * Problem:
 * ==================
 *
 * Implement both incremental and batch versions of Widrow-Holf
 * learning rule to classify 0 and 1.
 *
 * Tips:
 * ==================
 *
 * Use a Single Neuron with 30 inputs in the recognition system.
 *
 * Input Example:
 * ===================
 * P = [-1 1 1 1 1 -1 1 -1 -1 -1 -1 1 1 -1 -1 -1 -1 1 1 -1 -1 -1 -1 1 -1 1 1 1 1 -1].
 *
 * Output:
 * ===================
 *
 * Display the stop conditon, the adjusted bias and weight values,
 * the training accuracy and testing accuracy.
 *
 * Testing Case:
 * =============
 *
 * Run both incremental and batch versions of the Widrow-Hoff learning rule with
 * same parameter settings, training/testing sets, and compare their performance.
 *
 * Try different learning rates and initial weights when you run the same
 * training/testing sets and see any difference among the results.
 *
 * Create your own training and testing sets and repeat the process.
 *
 * Discussion:
 * ===============
 *
 * - Compare the performance of both versions of the Widrow-Hoff learning rule.
 * - Compare the performance of different learning rates and initial weights.
 * - Compare the performance of different training/testing sets.
 * - Everything else you consider it is important.
 */

#include <stdio.h>
#include <stdlib.h>

/* 6x5 grid. */
#define DOT_NUMBER 30

int main(void)
{
	/* All training sets is 6x5 grid.
	 * Each dot can be 1 or -1. 1 means dark, -1 means light. */
	const int p1[DOT_NUMBER] = {
		1, 1,  1,  1,  1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, 1,  1,  1,  1
	}; /* -1 */
	const int p2[DOT_NUMBER] = {
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1
	}; /* 1 */
	const int p3[DOT_NUMBER] = {
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1
	}; /* 1 */
	const int p4[DOT_NUMBER] = {
		1,  1,  1,  1, -1,
		1,  -1, -1, 1, -1,
		1,  -1, -1, 1, -1,
		1,  -1, -1, 1, -1,
		1,  -1, -1, 1, -1,
		-1, 1,  1,  1, -1
	}; /* 0 */
	const int p5[DOT_NUMBER] = {
		-1, 1, 1,  1,  -1,
		-1, 1, -1, -1, 1,
		-1, 1, -1, -1, 1,
		-1, 1, -1, -1, 1,
		-1, 1, -1, -1, 1,
		-1, 1, 1,  1,  1
	}; /* -1 */
	const int p6[DOT_NUMBER] = {
		-1, -1, -1, -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, -1, -1, -1
	}; /* 1 */
	const int p7[DOT_NUMBER] = {
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, 1, -1,  -1, -1,
		-1, 1, -1,  -1, -1,
		-1, -1, -1, -1, -1 
	}; /* 1 */
	const int p8[DOT_NUMBER] = {
		-1, 1,  1,  1,  -1,
		-1, -1, -1, -1, 1,
		1,  -1, -1, -1, 1,
		1,  -1, -1, -1, 1,
		1,  -1, -1, -1, 1,
		-1, 1,  1,  1,  -1 
	}; /* -1 */

	/* All testing sets. */
	const int t1[DOT_NUMBER] = {
		1,  1, 1,  1, -1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		-1, 1, 1,  1,  1
	};
	const int t2[DOT_NUMBER] = {
		-1, -1, -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, -1, -1, -1, -1,
	};
	const int t3[DOT_NUMBER] = {
		-1, 1, 1, 1, -1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		-1, 1, 1, 1, -1
	};
	const int t4[DOT_NUMBER] = {
		-1, -1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
	};

	return 0;
}

void widrow_holf(void)
{
	return;
}

void incremental(void)
{
	return;
}
