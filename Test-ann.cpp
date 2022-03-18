#include "tests\tests.h"

void test1(){
	ANN net = ANN();
	unsigned int layers[3] = { 2, 2, 1 };
	net.createStandardArray(3, layers);
	if (net.getNumLayers() == 3)
		printf("Test 1 ................. [PASSED] \n");
	else
		printf("Test 1 ................. [FAILED] \n");
	if (net[0].getNumNeurons() == 3)
		printf("Test 2 ................. [PASSED] \n");
	else
		printf("Test 2 ................. [FAILED] \n");
	if (net[1].getNumNeurons() == 3)
		printf("Test 3 ................. [PASSED] \n");
	else
		printf("Test 3 ................. [FAILED] \n");
	if (net[2].getNumNeurons() == 2)
		printf("Test 4 ................. [PASSED] \n");
	else
		printf("Test 4 ................. [FAILED] \n");
	if (net[0][0].getNumConnections() == 0)
		printf("Test 5 ................. [PASSED] \n");
	else
		printf("Test 5 ................. [FAILED] \n");
	if (net[0][1].getNumConnections() == 0)
		printf("Test 6 ................. [PASSED] \n");
	else
		printf("Test 6 ................. [FAILED] \n");
	if (net[0][2].getNumConnections() == 0)
		printf("Test 7 ................. [PASSED] \n");
	else
		printf("Test 7 ................. [FAILED] \n");
	if (net[1][0].getNumConnections() == 3)
		printf("Test 8 ................. [PASSED] \n");
	else
		printf("Test 8 ................. [FAILED] \n");
	if (net[1][1].getNumConnections() == 3)
		printf("Test 9 ................. [PASSED] \n");
	else
		printf("Test 9 ................. [FAILED] \n");
	if (net[1][2].getNumConnections() == 0)
		printf("Test 10 ................. [PASSED] \n");
	else
		printf("Test 10 ................. [FAILED] \n");
	if (net[2][0].getNumConnections() == 3)
		printf("Test 11 ................. [PASSED] \n");
	else
		printf("Test 11 ................. [FAILED] \n");
	if (net[2][1].getNumConnections() == 0)
		printf("Test 12 ................. [PASSED] \n");
	else
		printf("Test 12 ................. [FAILED] \n");
	if (net[2][0].getConnection(0).getNumConnections() == 3)
		printf("Test 13 ................. [PASSED] \n");
	else
		printf("Test 13 ................. [FAILED] \n");
	return;
}
void test2(){//XOR - Without breakdown
	nb_type truth_table[4][3] = {
		{ 0, 0, 0 },
		{ 0, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 0 } };
	TrainingData train_data(4, 2, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 2, 2, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTMSegment mem;
	mem.createFromFiles("ltm_alpha_0.net", "ltm_beta_0.net");
	// Symbolize
	NSA nsa;
	nsa.setVerbose(true);
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);

	return;
}

void test6(){// (a0 and a1) or (a2 and a3) without breakdown
	nb_type truth_table[16][5] = {
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1 },
	};
	TrainingData train_data(16, 4, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 4, 2, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTMSegment mem;
	mem.createFromFiles("ltm_alpha_0.net", "ltm_beta_0.net");
	// Symbolize
	NSA nsa;
	nsa.setVerbose(true);
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);

	return;
}

void test7(){	//XOR with breakdown
	nb_type truth_table[4][3] = {
		{ 0, 0, 0 },
		{ 0, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 0 } };
	TrainingData train_data(4, 2, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 2, 2, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTM mem;
	mem.createFromFiles("ltm_%s_%d.net");
	// Symbolize
	ProgressiveNSA nsa;
	nsa.setVerbose(true);
	nsa.setMaxTrials(10);
	nsa.setBreakdownFlag(true);
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem[0].getBusWidth() - 1, btm);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	return;
}

void test13(){// (a0 and a1) or (a2 and a3) with breakdown
	nb_type truth_table[16][5] = {
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1 },
	};
	TrainingData train_data(16, 4, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 4, 3, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTM mem;
	mem.createFromFiles("ltm_%s_%d.net");
	// Symbolize
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	ProgressiveNSA nsa;
	nsa.setVerbose(true);
	nsa.setMaxBreakdownTrials(7);
	nsa.setMaxTrials(20);
	nsa.setBreakdownFlag(true);
	nsa.setChunkSize(16);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	mem.save("ltm_%s_%d.net");

	return;
}

void test14(){// (a0 and a1) or (a2 and a3) or (a4 and a5)
	nb_type truth_table[64][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 0, 0, 1 },
		{ 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 1, 0, 0 },
		{ 1, 1, 0, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1, 0, 0 },
		{ 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 1, 0, 0 },
		{ 1, 0, 0, 1, 1, 0, 0 },
		{ 0, 1, 0, 1, 1, 0, 0 },
		{ 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 0, 0, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 1, 0 },
		{ 0, 1, 1, 0, 0, 1, 0 },
		{ 1, 1, 1, 0, 0, 1, 1 },
		{ 0, 0, 0, 1, 0, 1, 0 },
		{ 1, 0, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0 },
		{ 1, 1, 0, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 0, 1, 1 },
		{ 1, 0, 1, 1, 0, 1, 1 },
		{ 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1 },
		{ 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 1 },
		{ 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1 },
		{ 0, 0, 0, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1 },
		{ 0, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
	TrainingData train_data(64, 6, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 6, 5, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	//net[1].setActivationFunction(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTM mem;
	mem.createFromFiles("ltm_%s_%d.net");
	// Symbolize
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	ProgressiveNSA nsa;
	nsa.setVerbose(true);
	nsa.setMaxBreakdownTrials(7);
	nsa.setMaxTrials(100);
	nsa.setBreakdownFlag(true);
	nsa.setChunkSize(16);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	mem.save("ltm_%s_%d.net");
	//nsa.setBreakdownFlag(false);
	//SymbolicRule rule1 = nsa.symbolize(mem, net, btm, formatter, train_data);

	return;
}

void test15(){ // Majority On
	nb_type truth_table[16][5] = {
		//{ 0, 0, 0, 0, 0 },
		//{ 1, 0, 0, 0, 0 },
		//{ 0, 1, 0, 0, 0 },
		//{ 1, 1, 0, 0, 1 },
		//{ 0, 0, 1, 0, 0 },
		//{ 1, 0, 1, 0, 1 },
		//{ 0, 1, 1, 0, 1 },
		//{ 1, 1, 1, 0, 1 },
		//{ 0, 0, 0, 1, 0 },
		//{ 1, 0, 0, 1, 1 },
		//{ 0, 1, 0, 1, 1 },
		//{ 1, 1, 0, 1, 1 },
		//{ 0, 0, 1, 1, 1 },
		//{ 1, 0, 1, 1, 1 },
		//{ 0, 1, 1, 1, 1 },
		//{ 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 1 },
		{ 0, 1, 1, 0, 1 },
		{ 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 1, 1 },
		{ 0, 1, 0, 1, 1 },
		{ 1, 1, 0, 1, 0 },
		{ 0, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 0 },
		{ 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1 },
	};
	TrainingData train_data(16, 4, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 4, 8, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	//net[1].setActivationFunction(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	//LTM mem;
	//mem.createFromFiles("ltm_%s_%d.net");
	LTMSegment mem;
	mem.createFromFiles("ltm_alpha_0.net", "ltm_beta_0.net");
	// Symbolize
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	NSA nsa;
	//ProgressiveNSA nsa;
	nsa.setVerbose(true);
	//nsa.setMaxBreakdownTrials(7);
	nsa.setMaxTrials(100);
	//nsa.setBreakdownFlag(true);
	//nsa.setChunkSize(16);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	//mem.save("ltm_%s_%d.net");
	//nsa.setBreakdownFlag(false);
	//SymbolicRule rule1 = nsa.symbolize(mem, net, btm, formatter, train_data);

	return;
}

void test_a(){
	nb_type truth_table[8][4] = {
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 1 },
		{ 0, 0, 1, 1 },
		{ 1, 0, 1, 0 },
		{ 0, 1, 1, 1 },
		{ 1, 1, 1, 1 },
	};
	TrainingData data(8, 3, 1);
	data.setSamplesData((nb_type*)truth_table);
	ANN net;
	unsigned int layers[2] = { 3, 1 };
	net.createStandardArray(2, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	net.trainOnData(data, 100000, 100, 0.001f);
	return;
}

void test_a1(){
	nb_type truth_table[8][4] = {
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 1, 0 },
	};
	TrainingData data(8, 3, 1);
	data.setSamplesData((nb_type*)truth_table);
	ANN net;
	unsigned int layers[2] = { 3, 1 };
	net.createStandardArray(2, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	net[1][0].setWeight(0, 0.4f);
	net[1][0].setWeight(1, 0.4f);
	net[1][0].setWeight(2, 0.6f);
	net[1][0].setWeight(3, -0.5f);
	net.run(data);
	data.print();
}

void test_b(){
	nb_type truth_table[16][5] = {
		{ 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 0, 1, 0, 0, 1 },
		{ 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 1, 1, 0, 1, 0 },
		{ 0, 0, 1, 1, 0 },
		{ 1, 0, 1, 1, 0 },
		{ 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 0 },
	};
	TrainingData data(16, 4, 1);
	data.setSamplesData((nb_type*)truth_table);
	ANN net;
	unsigned int layers[2] = { 4, 1 };
	net.createStandardArray(2, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	net.trainOnData(data, 100000, 100, 0.001f);
	return;
}

void train_LTM_Series(){
	TrainingData alphaData;
	TrainingData betaData;
	for (unsigned int i = 0; i <= 6; i++){
		std::string alphaPath = ".\\scalability_test\\ltm_alpha_" + std::to_string(i) + "_0.train";
		std::string betaPath = ".\\scalability_test\\ltm_beta_" + std::to_string(i) + "_0.train";
		std::string alphaANNPath = ".\\scalability_test\\ltm_alpha_" + std::to_string(i) + "_0.net";
		std::string betaANNPath = ".\\scalability_test\\ltm_beta_" + std::to_string(i) + "_0.net";
		alphaData.readTrainFromFile(alphaPath);
		betaData.readTrainFromFile(betaPath);
		LTMSegment segment;
		if (!segment.createFromFiles(alphaANNPath, betaANNPath)){
			ANN alpha, beta;
			unsigned int alpha_layers[3], beta_layers[3];
			alpha_layers[0] = alphaData.numInput(); alpha_layers[1] = 300; alpha_layers[2] = alphaData.numOutput();
			beta_layers[0] = betaData.numInput(); beta_layers[1] = 300; beta_layers[2] = betaData.numOutput();
			alpha.createStandardArray(3, alpha_layers);
			alpha.setActivationFunctionOutput(FANN_SIGMOID);
			alpha.setTrainingAlgorithm(FANN_TRAIN_RPROP);
			beta.createStandardArray(3, beta_layers);
			beta.setActivationFunctionOutput(FANN_LINEAR);
			beta.setTrainingAlgorithm(FANN_TRAIN_RPROP);
			alpha.trainOnData(alphaData, 1000, 100, 0.001f);
			beta.trainOnData(betaData, 1000, 100, 0.1f);
			alpha.save(alphaANNPath);
			beta.save(betaANNPath);
		}
	}
}

void test_gt() {
	ANN net = ANN();
	unsigned int layers[2] = { 2, 1 };
	net.createStandardArray(2, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	nb_type samples[5][3] = {
		{5, 10, 0},
		{5, 1, 1},
		{10, 15, 0},
		{10, 1, 1},
		{10, 7, 1}
	};
	TrainingData data(3, 2, 1);
	data.setSamplesData((nb_type*)samples);
	net.trainOnData(data, 10000, 1000, 0.001f);
	if(net.getMSE() <= 0.001)
		printf("Trained successfully \n");
	else
		printf("Training failed \n");
}

void main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	unsigned int sead = 0;
	if (argc > 1)
		sead = atoi(argv[1]);
	srand(sead);
	//train_LTM_Series();
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	///test9();
	//test10();
	//test11();
	//test12();
	//test13();
	//test14();
	//test15();
	//test_a();
	//test_a1();
	//test_b();
	//test_addition();
	//test_multiplication_digitized();
	//test_multiplication_non_digitized();
	//test_gt();
	//true_mux_3();
	MUX6();
	//test_demux6();
	//test_demux11();
	//test_demux20();
	//test_demux37();
	//test_demux70();
	//test_demux135();
}