#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* 6x5 grid. */
#define DOT_NUMBER      30
#define TRAINING_NUMBER 8
#define TEST_NUMBER     4
#define MY_TEST_NUMBER  4

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
	}, /* -1 */
	{
		-1, -1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, 1, -1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
		-1, -1, 1, -1, -1,
	}, /* 1 */
};

static const int test_answer[TEST_NUMBER] = { -1, 1, -1, 1 };

struct neuron {
	double weight[DOT_NUMBER];
	double bias;
};

struct neuron *init_neuron(void);
void free_neuron(struct neuron *ne);
void print_neuron(struct neuron *ne);
void train_neuron(struct neuron *ne, double learning_rate, int epochs);
int predict(struct neuron *ne, const int *array);

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

	/* generate random weight between 0 to 1. */
	srand(time(NULL));
	for (i = 0; i < DOT_NUMBER; i++) {
		ne->weight[i] = (double)rand() / (double)RAND_MAX;
	}

	return ne;
}

void free_neuron(struct neuron *ne)
{
	free(ne);
}

void print_neuron(struct neuron *ne)
{
	int i;

	printf("* Show all weights and bias in this trained neuron.\n");
	printf("bias: %f\n", ne->bias);

	for (i = 0; i < DOT_NUMBER; i++)
		printf("weight %d: %f\n", i + 1, ne->weight[i]);

	printf("\n\n");
}

void train_neuron(struct neuron *ne, double learning_rate, int epochs)
{
	int i, j;
	int count; /* epochs count. */
	double eps; /* mean squared error (MSE) */
	double update;
	double diff;

	eps = 1;
	count = 0;

	while (eps > 0.000001 && count < epochs) {
		eps = 0;
		/* iterate all training set. */
		for (i = 0; i < TRAINING_NUMBER; i++) {
			diff = training_answer[i] - predict(ne, training_set[i]);
			eps += pow(diff, 2);

			update = learning_rate * diff;

			/* Update weights. */
			for (j = 0; j < DOT_NUMBER; j++)
				ne->weight[j] += update * training_set[i][j];
			ne->bias += update;
		}

		eps /= TRAINING_NUMBER;

		count++;
	}

	print_neuron(ne);

	printf("* Learning rate: %f\n", learning_rate);
	printf("* total %d generations.\n", count);

	if (count == epochs) {
		printf("Stop training because reach max generation iteration.\n");
		printf("This may cause predict not correctly.\n");
		printf("Please change learning rate and try again.\n");
	} else {
		printf("Stop training because Mean Squared Error(MSE) < 0.000001\n");
	}

	printf("\n");
}

/*
 * This function only return 1 or -1.
 */
int predict(struct neuron *ne, const int *array)
{
	int i;
	int sum, output, predict;

	sum = 0;
	for (i = 0; i < DOT_NUMBER; i++)
		sum += ne->weight[i] * array[i];

	output = sum - ne->bias;
	predict = output >= 0 ? 1 : -1;

	return predict;
}

void test_neuron(struct neuron *ne)
{
	int i;
	int count;
	int predict_output;

	printf("* all training set predict:\n");
	count = 0;
	for (i = 0; i < TRAINING_NUMBER; i++) {
		predict_output = predict(ne, training_set[i]);
		printf("answer: %d, predict:  %d\n", training_answer[i], predict_output);
		if (training_answer[i] == predict_output)
			count++;
	}
	printf("* accuracy: %d of %d correct.\n\n", count, TRAINING_NUMBER);

	printf("* all test set predict:\n");
	count = 0;
	for (i = 0; i < TEST_NUMBER; i++) {
		predict_output = predict(ne, test_set[i]);
		printf("answer: %d, predict:  %d\n", test_answer[i], predict_output);
		if (test_answer[i] == predict_output)
			count++;
	}
	printf("* accuracy: %d of %d correct.\n\n", count, TEST_NUMBER);
}

int main(void)
{
	/* Windrow_holf increnment and batch version. */
	struct neuron *ne_1, *ne_2;

	ne_1 = init_neuron();
	ne_2 = init_neuron();

	train_neuron(ne_1, 0.00001, 1000);
	test_neuron(ne_1);

	train_neuron(ne_2, 0.1, 1000);
	test_neuron(ne_2);

	free_neuron(ne_1);
	free_neuron(ne_2);

	return 0;
}

