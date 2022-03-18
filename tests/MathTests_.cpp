#include "ann.h"

using namespace NEUROBASE;
using namespace NEUROBASE::L0;
void test_addition(){
	ANN ann;
	unsigned int layers[2] = { 2, 1 };
	nb_type train_cases[10][3] = {
		{0, 0, 0},
		{1, 1, 2},
		{1, 2, 3},
		{10, 05, 15},
		{10, 10, 20},
		{100, 20, 120},
		{90, 70, 160},
		{50, 40, 90},
		{20, 30, 50},
		{12, 13, 25},
	};
	TrainingData train_data(10, 2, 1);
	train_data.setSamplesData((nb_type*)train_cases);
	ann.createStandardArray(2, layers);
	ann.setActivationFunctionOutput(FANN_LINEAR);
	ann.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	ann.trainOnData(train_data, 1000, 100, 0.001f);
	nb_type test_cases[10][3] = {
		{ 1, 3, 0 },
		{ 2, 9, 0 },
		{14, 7, 0 },
		{ 32, 34, 0 },
		{ 95, 32, 0 },
		{ 67, 34, 0 },
		{ 54, 21, 0 },
		{ 43, 54, 0 },
		{ 214, 33, 0 },
		{ 32, 546, 0 },
	};
	TrainingData test_data(10, 2, 1);
	test_data.setSamplesData((nb_type*)test_cases);
	ann.run(test_data);
	test_data.print();
	return;
}

void generate_multiply(TrainingData& train){
	const unsigned int max = 8;
	train.allocateTrainData(max * max, 2, 1);
	for (unsigned int i = 0; i < max; i++){
		for (unsigned int j = 0; j < max; j++){
			train.setSampleInput(i * max + j, 0, (nb_type)i);
			train.setSampleInput(i * max + j, 1, (nb_type)j);
			train.setSampleOutput(i * max + j, 0, ((nb_type)(i*j))/(100));
		}
	}
	return;
}

void generate_multiply_digitized(TrainingData& train){
	train.allocateTrainData(100, 2, 2);
	for (unsigned int i = 0; i < 10; i++){
		for (unsigned int j = 0; j < 10; j++){
			train.setSampleInput(i * 10 + j, 0, (nb_type)i);
			train.setSampleInput(i * 10 + j, 1, (nb_type)j);
			train.setSampleOutput(i * 10 + j, 0, (nb_type)div(i*j, 10).rem);
			train.setSampleOutput(i * 10 + j, 1, (nb_type)div(i*j, 10).quot);
		}
	}
	return;
}

void test_multiplication_non_digitized(){
	ANN ann;
	unsigned int layers[3] = { 2, 15, 1 };
	TrainingData train_data;
	generate_multiply(train_data);
	train_data.print();
	ann.createStandardArray(3, layers);
	ann.setActivationFunctionOutput(FANN_SIGMOID_SYMMETRIC);
	ann.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	ann.trainOnData(train_data, 1000000, 100, 0.00000001f);
	nb_type test_cases[10][3] = {
		{ 1, 3, 0 },
		{ 2, 5, 0 },
		{ 3, 4, 0 },
		{ 5, 5, 0 },
		{ 5, 2, 0 },
		{ 5, 4, 0 },
		{ 3, 3, 0 },
		{ 2, 4, 0 },
		{ 2, 0, 0 },
		{ 3, 1, 0 },
	};
	TrainingData test_data(10, 2, 1);
	test_data.setSamplesData((nb_type*)test_cases);
	ann.run(test_data);
	test_data.print();
	return;
}

void test_multiplication_digitized(){
	ANN ann;
	unsigned int layers[4] = { 2, 20, 20, 2 };
	TrainingData train_data;
	generate_multiply_digitized(train_data);
	train_data.print();
	ann.createStandardArray(4, layers);
	ann.setActivationFunctionOutput(FANN_LINEAR);
	ann.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	ann.trainOnData(train_data, 70000, 100, 0.001f);
	nb_type test_cases[10][4] = {
		{ 1, 3, 0, 0 },
		{ 2, 9, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 9, 2, 0, 0 },
		{ 5, 8, 0, 0 },
		{ 7, 9, 0, 0 },
		{ 6, 9, 0, 0 },
		{ 5, 9, 0, 0 },
		{ 8, 8, 0, 0 },
	};
	TrainingData test_data(10, 2, 2);
	test_data.setSamplesData((nb_type*)test_cases);
	ann.run(test_data);
	test_data.print();
	return;
}
