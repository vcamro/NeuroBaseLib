#include "tests_.h"

void MUX3() {
	nb_type truth_table[8][4] = {
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 0, 1 },
		{ 0, 1, 1, 1 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 0 },
		{ 1, 1, 1, 1 }
	};
	TrainingData train_data(8, 3, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[3] = { 3, 2, 1 };
	net.createStandardArray(3, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTM mem;
	mem.createFromFiles("ltm_%s_%d.net");
	// Symbolize
	ProgressiveNSA nsa;
	nsa.setVerbose(true);
	nsa.setMaxTrials(20);
	nsa.setBreakdownFlag(true);
	nsa.setChunkSize(5);
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	//mem.save("ltm_%s_%d.net");

	return;
}

void MUX6() {
	nb_type truth_table[64][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 0 },
		{ 0, 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 1, 1 },
		{ 0, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1 },
		{ 0, 0, 1, 1, 0, 0, 1 },
		{ 0, 0, 1, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 1, 0, 1 },
		{ 0, 0, 1, 1, 1, 1, 1 },

		{ 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 0 },
		{ 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 1, 0, 1, 0, 1, 1 },
		{ 0, 1, 0, 1, 1, 0, 1 },
		{ 0, 1, 0, 1, 1, 1, 1 },
		{ 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 0, 1, 0 },
		{ 0, 1, 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1, 1, 0 },
		{ 0, 1, 1, 1, 0, 0, 1 },
		{ 0, 1, 1, 1, 0, 1, 1 },
		{ 0, 1, 1, 1, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1 },

		{ 1, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 1, 0 },
		{ 1, 0, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 0, 0, 0 },
		{ 1, 0, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 1 },

		{ 1, 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 1, 0, 0 },
		{ 1, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 1, 0, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 0 },
		{ 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
	TrainingData train_data(64, 6, 1);
	train_data.setSamplesData((nb_type*)truth_table);
	ANN net = ANN();
	unsigned int layers[4] = { 6, 8, 8, 1 };
	net.createStandardArray(4, layers);
	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	// Load LTM
	LTM mem;
	mem.createFromFiles("ltm_%s_%d.net");
	// Symbolize
	ProgressiveNSA nsa;
	nsa.setVerbose(true);
	nsa.setProgressiveNSALogDetails(ProgressiveNSA::enum_log_all);
	nsa.setLogDetails(NSA::enum_log_all);
	nsa.setMaxTrials(100);
	nsa.setBreakdownFlag(true);
	nsa.setChunkSize(15);
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	//mem.save("ltm_%s_%d.net");

	return;
}

void MUX11() {
	TrainingData train_data;
	ANN net = ANN();
	train_data.readTrainFromFile("MUX11_FULL.train");

	//unsigned int max_in = 8;
	//unsigned int layers[4] = { 11, 24, 6, 1 };
	//float connection_rates[3] = { (float(max_in) / float(layers[0])), (float(max_in) / float(layers[1])), (float(max_in) / float(layers[2])) };
	//net.createSparseHeterogeneousArray(connection_rates, 4, layers);

	//unsigned int max_in = 4;
	//unsigned int layers[8] = { 11, 2048, 1024, 256, 64, 16, 4, 1 };
	//float connection_rates[7] = { (float(max_in) / float(layers[0])), (float(max_in) / float(layers[1])), (float(max_in) / float(layers[2])), (float(max_in) / float(layers[3])), (float(max_in) / float(layers[4])), (float(max_in) / float(layers[5])), (float(max_in) / float(layers[6])) };
	//net.createSparseHeterogeneousArray(connection_rates, 8, layers);

	//unsigned int max_in = 4;
	//unsigned int layers[4] = { 11, 8, 8, 1 };
	//float connection_rates[3] = { (float(max_in) / float(layers[0])), (float(8) / float(layers[1])), (float(8) / float(layers[2])) };
	//net.createSparseHeterogeneousArray(connection_rates, 4, layers);

	//unsigned int max_in = 4;
	//unsigned int layers[5] = { 11, 16, 8, 4, 1 };
	//float connection_rates[4] = { (float(max_in) / float(layers[0])), (float(max_in) / float(layers[1])), (float(max_in) / float(layers[2])) , (float(max_in) / float(layers[3])) };
	//net.createSparseHeterogeneousArray(connection_rates, 5, layers);

	//unsigned int max_in = 4;
	//unsigned int layers[5] = { 11, 64, 32, 8, 1 };
	//float connection_rates[4] = { (float(max_in) / float(layers[0])), (float(max_in) / float(layers[1])), (float(max_in) / float(layers[2])) , (float(max_in) / float(layers[3])) };
	//net.createSparseHeterogeneousArray(connection_rates, 5, layers);

	unsigned int layers[3] = { 11, 16, 1 };
	net.createStandardArray(3, layers);

	net.setActivationFunctionOutput(FANN_SIGMOID);
	net.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	//unsigned int c = 0;
	//for (unsigned int i = 0; i < net[1].getNumNeurons()-1; i++) {
	//	for (unsigned int j = 0; j < 3; j++)
	//		net[1][i].setConnection(j+1, net[0][j]);
	//	for (unsigned int j = 3; j < max_in; j++, c++) {
	//		c = c % 11;
	//		if (c >= 0 && c <= 2) c = 3;
	//		net[1][i].setConnection(j + 1, net[0][c]);
	//	}
	//}
	//net.save("temp.net");
	// Load LTM
	LTM mem;
	mem.createFromFiles("ltm_%s_%d.net");
	// Symbolize
	ProgressiveNSA nsa;
	nsa.setVerbose(true);
	nsa.setProgressiveNSALogDetails(ProgressiveNSA::enum_log_all);
	nsa.setTrialMaxEpochs(1000);
	nsa.setTrialEpochsBetweenReports(10);
	nsa.setTrialDesiredError(0.0000001f);
	nsa.setLogDetails(NSA::enum_log_all);
	nsa.setMaxTrials(100);
	nsa.setBreakdownFlag(true);
	nsa.setChunkSize(10);
	GlobalTaxonomyScheme btm = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	BooleanModelFormatter formatter(mem.getBusWidth() - 1, btm);
	SymbolicRule rule = nsa.symbolize(mem, net, btm, formatter, train_data);
	//mem.save("ltm_%s_%d.net");

	return;
}