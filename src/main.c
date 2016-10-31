/*
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
#define DOT_NUMBER		30
#define TRAINING_NUMBER 8
#define TEST_NUMBER		4

/* All training sets is 6x5 grid.
 * Each dot can be 1 or -1. 1 means dark, -1 means light. */
static const int training_set[TRAINING_NUMBER][DOT_NUMBER] = {
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
static const int training_answer[TRAINING_NUMBER] = { -1, 1, 1, -1, -1, 1, 1, -1 };

/* All testing sets. */
static const int test_set[TEST_NUMBER][DOT_NUMBER] = {
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

static const int test_answer[TEST_NUMBER] = { -1, 1, 1, 1 };

struct neuron {
	double weight[DOT_NUMBER];
	double bias;
	double learning_rate;
};

int linear_function(double input)
{
	return input >= 0 ? 1 : -1;
}

/*
 * Initialize neuron weight, biase, and return address.
 */
struct neuron *init_neuron(void)
{
	int i;
	struct neuron *ne;

	ne = malloc(sizeof(*ne));
	if (ne == NULL) {
		fprintf(stderr, "No memory space availible.\n");
		exit(1);
	}

	ne->bias = 0;
	ne->learning_rate = 0.5;
	for (i = 0; i < DOT_NUMBER; i++) {
		/* Weight is random number between 0 and 1. */
		srand(time(NULL));
		ne->weight[i] = (double)rand() / (double)RAND_MAX;
	}

	return ne;
}

void train_neuron(struct neuron *ne)
{
	int i, j;
	double sum, output;

	/* iterate all training set. */
	for (i = 0; i < TRAINING_NUMBER; i++) {
		/* Get sum from weight and input. */
		sum = 0;
		for (j = 0; j < DOT_NUMBER; j++) {
			sum += ne->weight[j] * training_set[i][j];
		}

		/* Get output value. */
		output = linear_function(sum - ne->bias);

		/* Update weights. */
		for (j = 0; j < DOT_NUMBER; j++) {
			ne->weight[j] = ne->learning_rate * \
					(training_answer[i] - output) * training_set[i][j];
		}
	}

	return;
}

/*
 * This function only return 1 or -1.
 */
int predict(struct neuron *ne, const int *array)
{
	int i;
	int sum;
	int predict_output;

	sum = 0;
	for (i = 0; i < DOT_NUMBER; i++) {
		sum += ne->weight[i] * array[i];
	}

	predict_output = linear_function(sum - ne->bias);

	return predict_output;
}

void test_neuron(struct neuron *ne)
{
	int i;
	int predict_output;

	for (i = 0; i < TRAINING_NUMBER; i++) {
		predict_output = predict(ne, training_set[i]);
		printf("predict: %d, answer:  %d\n", predict_output, training_answer[i]);
	}

	printf("\n\n");

	for (i = 0; i < TEST_NUMBER; i++) {
		predict_output = predict(ne, test_set[i]);
		printf("predict: %d, answer:  %d\n", predict_output, test_answer[i]);
	}
}

void free_neuron(struct neuron *ne)
{
	free(ne);
}

int main(void)
{
	/* Windrow_holf increnment and batch version. */
	struct neuron *whi, *whb;

	whi = init_neuron();
	whb = init_neuron();

	train_neuron(whi);
	train_neuron(whb);

	test_neuron(whi);
	/* test_neuron(whb); */

	/* Free memoru space. */
	free_neuron(whi);
	free_neuron(whb);

	return 0;
}

