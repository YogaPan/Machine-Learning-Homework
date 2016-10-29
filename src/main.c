/*
 * Problem:
 * ==================
 *
 * Implement both incremental and batch versions of Widrow-Holf
 * learning rule to classify 0 and 1.
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
#include <time.h>

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
	struct windrow_holf_learner *whl;

	init_windrow_holf_learner(whl);
	train_windorw_holf_learner(whl);

	return 0;
}

struct windrow_holf_learner {
	double weight[DOT_NUMBER];
	double biase;
	double leaning_rate;
};

void init_winrow_holf_learner(struct windrow_holf_learner *whl)
{
	int i;

	whl = malloc(sizeof(*whl));
	if (whl == NULL)
		return;

	whl->biase = 0;
	for (i = 0; i < DOT_NUMBER; i++) {
		srand(time(NULL));
		whl->weight[i] = (double)rand() / (double)RAND_MAX;
	}
}

void train_widrow_holf(struct windrow_holf_learner *whl)
{
	int i, j;
	double sum, output;

	/* iterate all training set. */
	for (i = 0; i < 8; i++) {

		/* Get sum from weight and input. */
		sum = 0;
		for (j = 0; j < DOT_NUMBER; j++) {
			sum += whl->weight[j] * training_set[i][j];
		}

		/* Get output value. */
		output = sum - whl->baise;
		if (output < 0)
			output = -1;
		if (output >= 0)
			output = 1;

		/* Update weights. */
		for (j = 0; j < DOT_NUMBER; j++) {
			whl->weight[j] = whl->leaning_rate * (target - output) * training_set[i][j];
		}
	}

	return;
}
