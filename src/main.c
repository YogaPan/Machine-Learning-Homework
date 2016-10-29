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

/* All training sets is 6x5 grid.
 * Each dot can be 1 or -1. 1 means dark, -1 means light. */
static const int training_set[8][DOT_NUMBER] = {
	{
		1, 1,  1,  1,  1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, 1,  1,  1,  1,
	}, /* -1 */
	{
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
	}, /* 1 */
	{
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
	}, /* 1 */
	{
		1,  1,  1,  1, -1,
		1,  -1, -1, 1, -1,
		1,  -1, -1, 1, -1,
		1,  -1, -1, 1, -1,
		1,  -1, -1, 1, -1,
		-1, 1,  1,  1, -1,
	}, /* -1 */
	{
		-1, 1, 1,  1,  -1,
		-1, 1, -1, -1, 1,
		-1, 1, -1, -1, 1,
		-1, 1, -1, -1, 1,
		-1, 1, -1, -1, 1,
		-1, 1, 1,  1,  1,
	}, /* -1 */
	{
		-1, -1, -1, -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, -1, -1, -1,
	}, /* 1 */
	{
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, -1, 1,  -1, -1,
		-1, 1, -1,  -1, -1,
		-1, 1, -1,  -1, -1,
		-1, -1, -1, -1, -1,
	}, /* 1 */
	{
		-1, 1,  1,  1,  -1,
		-1, -1, -1, -1, 1,
		1,  -1, -1, -1, 1,
		1,  -1, -1, -1, 1,
		1,  -1, -1, -1, 1,
		-1, 1,  1,  1,  -1,
	}, /* -1 */
};

/* training set answer */
static const int training_answer[8] = {-1, 1, 1, -1, -1, 1, 1, -1};

/* All testing sets. */
static const int test_set[4][DOT_NUMBER] = {
	{
		1,  1, 1,  1, -1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		-1, 1, 1,  1,  1,
	}, /* -1 */
	{
		-1, -1, -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, 1,  -1, -1, -1,
		-1, -1, -1, -1, -1,
	}, /* 1 */
	{
		-1, 1, 1, 1, -1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		-1, 1, 1, 1, -1,
	}, /* 1 */
	{
		-1, -1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
	}, /* 1 */
};

int main(void)
{

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
