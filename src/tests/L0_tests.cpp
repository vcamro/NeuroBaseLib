#ifndef __L0_TESTS_CPP
#define __L0_TESTS_CPP

#include "L0_tests.h"

ANN create_ann() {
	ANN net = ANN();
	unsigned int layers[3] = { 2, 2, 1 };
	net.createStandardArray(3, layers);
	net.randomizeWeights(-10, 10);
	return net;
}

ANN create_ann_big() {
	ANN net = ANN();
	unsigned int layers[3] = { 10, 2, 1 };
	net.createStandardArray(3, layers);
	net.randomizeWeights(-10, 10);
	return net;
}

void test_ann_navigation(ANN& net) {
	printf("Testing ANN class navigation functions ... \n");
	if (net.getNumLayers() == 3)
		printf("ANN::getNumLayers ................. [PASSED] \n");
	else
		printf("ANN::getNumLayers ................. [FAILED] \n");
}

void test_layer_navigation(ANN& net) {
	printf("\n\n");
	printf("Testing Layer class navigation functions ... \n");
	printf("Testing Layer::getNumNeurons ... \n");
	if (net[0].getNumNeurons() == 3)
		printf("Test 1 ................. [PASSED] \n");
	else
		printf("Test 1 ................. [FAILED] \n");
	if (net[1].getNumNeurons() == 3)
		printf("Test 2 ................. [PASSED] \n");
	else
		printf("Test 2 ................. [FAILED] \n");
	if (net[2].getNumNeurons() == 2)
		printf("Test 3 ................. [PASSED] \n");
	else
		printf("Test 3 ................. [FAILED] \n");

	printf("\n");
	printf("Testing Layer::getNumNodes ... \n");
	if (net[0].getNumNodes() == 0)
		printf("Test 1 ................. [PASSED] \n");
	else
		printf("Test 1 ................. [FAILED] \n");
	if (net[1].getNumNodes() == 2)
		printf("Test 2 ................. [PASSED] \n");
	else
		printf("Test 2 ................. [FAILED] \n");
	if (net[2].getNumNodes() == 1)
		printf("Test 3 ................. [PASSED] \n");
	else
		printf("Test 3 ................. [FAILED] \n");

	printf("\n");
	printf("Testing Layer::getLayerIndex ... \n");
	if (net[0].getLayerIndex() == 0)
		printf("Test 1 ................. [PASSED] \n");
	else
		printf("Test 1 ................. [FAILED] \n");
	if (net[1].getLayerIndex() == 1)
		printf("Test 2 ................. [PASSED] \n");
	else
		printf("Test 2 ................. [FAILED] \n");
	if (net[2].getLayerIndex() == 2)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");

	printf("\n");
	printf("Testing Layer::getNumInputs ... \n");
	if (net[0].getNumInputs() == 2)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[1].getNumInputs() == 2)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[2].getNumInputs() == 2)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
}

void test_neuron_navigation(ANN& net) {
	printf("\n\n");
	printf("Testing Neuron class navigation functions ... \n");
	printf("Testing Neuron::getNumConnections ... \n");
	if (net[0][0].getNumConnections() == 0)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[0][1].getNumConnections() == 0)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[0][2].getNumConnections() == 0)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net[1][0].getNumConnections() == 3)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (net[1][1].getNumConnections() == 3)
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (net[1][2].getNumConnections() == 0)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (net[2][0].getNumConnections() == 3)
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (net[2][1].getNumConnections() == 0)
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");

	printf("\n");
	printf("Testing Neuron::getIndexInLayer and Neuron::getLayerIndex ... \n");
	if (net[0][0].getIndexInLayer() == 0 && net[0][0].getLayerIndex() == 0)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[0][1].getIndexInLayer() == 1 && net[0][1].getLayerIndex() == 0)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[0][2].getIndexInLayer() == 2 && net[0][2].getLayerIndex() == 0)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net[1][0].getIndexInLayer() == 0 && net[1][0].getLayerIndex() == 1)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (net[1][1].getIndexInLayer() == 1 && net[1][1].getLayerIndex() == 1)
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (net[1][2].getIndexInLayer() == 2 && net[1][2].getLayerIndex() == 1)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (net[2][0].getIndexInLayer() == 0 && net[2][0].getLayerIndex() == 2)
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (net[2][1].getIndexInLayer() == 1 && net[2][1].getLayerIndex() == 2)
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");

	printf("\n");
	printf("Testing Neuron::getConnection ... \n");
	if (net[2][0].getConnection(0).getNumConnections() == 3)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");

	printf("\n");
	printf("Testing Neuron::isNode ... \n");
	if (net[0][0].isNode() == false)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[0][2].isNode() == false)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[1][0].isNode() == true)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net[1][2].isNode() == false)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (net[2][0].isNode() == true)
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (net[2][1].isNode() == false)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");

	printf("\n");
	printf("Testing Neuron::isNode ... \n");
	if (net[0][0].isBias() == false)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[0][2].isBias() == true)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[1][0].isBias() == false)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net[1][2].isBias() == true)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (net[2][0].isBias() == false)
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (net[2][1].isBias() == true)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
}

void test_neuron_isolate(ANN& net) {
	printf("\n\n");
	printf("Testing Neuron::isolate ... \n");
	ANN isolated = net[1][0].isolate();
	if (net[1][0].getWeight(0) == isolated[1][0].getWeight(0))
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[1][0].getWeight(1) == isolated[1][0].getWeight(1))
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[1][0].getWeight(2) == isolated[1][0].getWeight(2))
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net[1][0].getActivationFunction() == isolated[1][0].getActivationFunction())
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (net.getTrainingAlgorithm() == isolated.getTrainingAlgorithm())
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
}

void test_neuron_isolate_mask(ANN& net) {
	printf("\n\n");
	printf("Testing Neuron::isolate with mask... \n");
	printf("Case1 inactive mask... \n");
	ANN isolated1 = net[1][0].isolate(std::vector<bool>({ false, false }));
	if (net[1][0].getWeight(0) == isolated1[1][0].getWeight(0))
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[1][0].getWeight(1) == isolated1[1][0].getWeight(1))
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[1][0].getWeight(2) == isolated1[1][0].getWeight(2))
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net[1][0].getActivationFunction() == isolated1[1][0].getActivationFunction())
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (net.getTrainingAlgorithm() == isolated1.getTrainingAlgorithm())
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");

	printf("\n");
	printf("Case2 single masked input ... \n");
	ANN isolated2 = net[1][0].isolate(std::vector<bool>({ false, true }));
	if (net[1][0].getWeight(0) == isolated2[1][0].getWeight(0))
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[1][0].getWeight(2) == isolated2[1][0].getWeight(1))
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[1][0].getActivationFunction() == isolated2[1][0].getActivationFunction())
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net.getTrainingAlgorithm() == isolated2.getTrainingAlgorithm())
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");

	printf("\n");
	printf("Case3 single masked input ... \n");
	ANN isolated3 = net[1][0].isolate(std::vector<bool>({ true, false }));
	if (net[1][0].getWeight(1) == isolated3[1][0].getWeight(0))
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (net[1][0].getWeight(2) == isolated3[1][0].getWeight(1))
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (net[1][0].getActivationFunction() == isolated3[1][0].getActivationFunction())
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (net.getTrainingAlgorithm() == isolated3.getTrainingAlgorithm())
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
}

void test_training_data() {
	printf("\n\n");
	printf("Testing TrainingData class ... \n");
	printf("Test Get length, number of inputs and outputs... \n");
	TrainingData samples(4, 2, 1);
	nb_type data[12] = { 0, 0, 0,
		0, 1, 1,
		1, 0, 1,
		1, 1, 0 };
	samples.setSamplesData(data);
	if (samples.numInput() == 2)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (samples.numOutput() == 1)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (samples.length() == 4)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");


	printf("\n");
	printf("Test TrainingData::getInputs ... \n");
	if (samples.getInputs()[0][0] == 0)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (samples.getInputs()[0][1] == 0)
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (samples.getInputs()[0][1] == 0)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (samples.getInputs()[1][0] == 0)
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (samples.getInputs()[1][1] == 1)
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");

	printf("\n");
	printf("Test TrainingData::getOutputs ... \n");
	if (samples.getOutputs()[0][0] == 0)
		printf("Test 9 ................ [PASSED] \n");
	else
		printf("Test 9 ................ [FAILED] \n");
	if (samples.getOutputs()[1][0] == 1)
		printf("Test 10 ................ [PASSED] \n");
	else
		printf("Test 10 ................ [FAILED] \n");
}

void test_L0() {
	printf("\n\n");
	printf("Testing Abstraction Layer Zero of neural cuircuits ... \n");
	ANN net = create_ann();
	test_ann_navigation(net);
	test_layer_navigation(net);
	test_neuron_navigation(net);
	test_neuron_isolate(net);
	test_neuron_isolate_mask(net);
	test_training_data();

	return;
}

#endif