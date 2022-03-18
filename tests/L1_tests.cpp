#ifndef __L1_TESTS_CPP
#define __L1_TESTS_CPP

#include "L0_tests.h"
#include "L1_tests.h"

void test_global_taxonomy_scheme() {
	printf("Testing global taxonomy scheme structure ...\n");
	TaxonomyScheme taxonomy = GlobalTaxonomyScheme::createBooleanTaxonomyModel();
	if (taxonomy[0].getName() == GlobalTaxonomyScheme::STR_TAXONOMY_INPUT_STATES && taxonomy[0].getType() == Taxonomy::InputTaxonomy)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (taxonomy[1].getName() == GlobalTaxonomyScheme::STR_TAXONOMY_PAIRED_OPERATOR && taxonomy[1].getType() == Taxonomy::RelationTaxonomy)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (taxonomy[2].getName() == GlobalTaxonomyScheme::STR_TAXONOMY_TERM_TYPE && taxonomy[2].getType() == Taxonomy::InputTaxonomy)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (taxonomy[3].getName() == GlobalTaxonomyScheme::STR_TAXONOMY_PART_TYPE && taxonomy[3].getType() == Taxonomy::InputTaxonomy)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");

	printf("Testing input states taxonomy structure ...\n");
	if (taxonomy[0][0].getName() == GlobalTaxonomyScheme::STR_CLASS_INACTIVE)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (taxonomy[0][1].getName() == GlobalTaxonomyScheme::STR_CLASS_TRANSFERED)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (taxonomy[0][2].getName() == GlobalTaxonomyScheme::STR_CLASS_INVERTED)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");

	printf("Testing paired relations taxonomy structure ...\n");
	if (taxonomy[1][0].getName() == GlobalTaxonomyScheme::STR_CLASS_R1)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (taxonomy[1][1].getName() == GlobalTaxonomyScheme::STR_CLASS_R2)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");

	printf("Testing term type taxonomy structure ...\n");
	if (taxonomy[2][0].getName() == GlobalTaxonomyScheme::STR_CLASS_SIMPLE)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (taxonomy[2][1].getName() == GlobalTaxonomyScheme::STR_CLASS_COMPOUND)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (taxonomy[2][2].getName() == GlobalTaxonomyScheme::STR_CLASS_BOTH)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");

	printf("Testing part type taxonomy structure ...\n");
	if (taxonomy[3][0].getName() == GlobalTaxonomyScheme::STR_CLASS_PRIMARY)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (taxonomy[3][1].getName() == GlobalTaxonomyScheme::STR_CLASS_SECONDERY)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (taxonomy[3][2].getName() == GlobalTaxonomyScheme::STR_CLASS_BOTH)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
}

void test_neuron_topology_model(ANN net) {
	printf("\n\n");
	printf("Testing topology model class ...\n");
	NeuronTopologyModel Neuron1Topology(net[1][0]);
	if (Neuron1Topology.iLayer == 1 && Neuron1Topology.InputsMap[0] == 0 && Neuron1Topology.InputsMap[1] == 1)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");

	NeuronTopologyModel Neuron2Topology(net[1][1]);
	if (Neuron2Topology.iLayer == 1 && Neuron2Topology.InputsMap[0] == 0 && Neuron2Topology.InputsMap[1] == 1)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");

	NeuronTopologyModel Neuron3Topology(net[2][0]);
	if (Neuron3Topology.iLayer == 2 && Neuron3Topology.InputsMap[0] == 0 && Neuron3Topology.InputsMap[1] == 1)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
}

void test_connection_ignore_mask() {
	printf("\n\n");
	printf("Testing connection ignore mask class ...\n");
	printf("Case1 neuron with connections less than buswidth ... \n");
	ANN net1 = create_ann();
	net1[1][0].setWeight(0, -0.1f);
	net1[1][0].setWeight(1, 0.2f);
	net1[1][0].setWeight(2, 0.01f);
	ConnectionsIgnoreMask mask1;
	mask1.fill(net1[1][0], 9);
	if (mask1.getNumIgnored() == 0)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");

	printf("Case2 neuron with connections more than buswidth ... \n");
	ANN net2 = create_ann_big();
	net2[1][0].setWeight(0, -0.1f);
	net2[1][0].setWeight(1, 0.11f);
	net2[1][0].setWeight(2, 0.05f);
	net2[1][0].setWeight(3, 0.2f);
	net2[1][0].setWeight(4, 0.3f);
	net2[1][0].setWeight(5, 0.4f);
	net2[1][0].setWeight(6, 0.5f);
	net2[1][0].setWeight(7, 0.6f);
	net2[1][0].setWeight(8, 0.7f);
	net2[1][0].setWeight(9, 0.8f);
	net2[1][0].setWeight(10, 0.01f);
	ConnectionsIgnoreMask mask2;
	mask2.fill(net2[1][0], 9);
	if (mask2.getNumIgnored() == 2)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (mask2[0])
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (mask2[2])
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
}

std::vector<NeuronRawModel> create_neuron_raw_model() {
	nb_type model_data_1[74] = {	0,1,0, 0,1,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0,
									0,1,
									1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0,
									1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0 };

	nb_type model_data_2[74] = {	0,0,1, 0,1,0, 1,0,0, 1,0,0, 0,1,0, 0,0,1, 1,0,0, 1,0,0,
									1,0,
									1,0,0, 1,0,0, 1,0,0, 1,0,0, 0,1,0, 0,1,0, 1,0,0, 1,0,0,
									1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0 };

	nb_type model_data_3[74] = {	0,0,1, 0,1,0, 1,0,0, 1,0,0, 0,1,0, 0,0,1, 0,1,0, 0,1,0,
									1,0,
									1,0,0, 1,0,0, 1,0,0, 1,0,0, 0,1,0, 0,1,0, 0,1,0, 0,0,1,
									1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 0,1,0, 0,1,0 };
	std::vector<NeuronRawModel> ret;
	ret.push_back(NeuronRawModel(model_data_1, 74));
	ret[0].TopologyModel.iLayer = 1;
	ret[0].TopologyModel.InputsMap.push_back(0);
	ret[0].TopologyModel.InputsMap.push_back(1);

	ret.push_back(NeuronRawModel(model_data_2, 74));
	ret[1].TopologyModel.iLayer = 1;
	ret[1].TopologyModel.InputsMap.push_back(0);
	ret[1].TopologyModel.InputsMap.push_back(1);
	ret[1].TopologyModel.InputsMap.push_back(2);
	ret[1].TopologyModel.InputsMap.push_back(3);
	ret[1].TopologyModel.InputsMap.push_back(4);
	ret[1].TopologyModel.InputsMap.push_back(5);

	ret.push_back(NeuronRawModel(model_data_3, 74));
	ret[2].TopologyModel.iLayer = 1;
	ret[2].TopologyModel.InputsMap.push_back(0);
	ret[2].TopologyModel.InputsMap.push_back(1);
	ret[2].TopologyModel.InputsMap.push_back(2);
	ret[2].TopologyModel.InputsMap.push_back(3);
	ret[2].TopologyModel.InputsMap.push_back(4);
	ret[2].TopologyModel.InputsMap.push_back(5);
	ret[2].TopologyModel.InputsMap.push_back(6);
	ret[2].TopologyModel.InputsMap.push_back(7);

	ret.push_back(NeuronRawModel(model_data_3, 74));
	ret[3].TopologyModel.iLayer = 1;
	ret[3].TopologyModel.InputsMap.push_back(7);
	ret[3].TopologyModel.InputsMap.push_back(1);
	ret[3].TopologyModel.InputsMap.push_back(2);
	ret[3].TopologyModel.InputsMap.push_back(3);
	ret[3].TopologyModel.InputsMap.push_back(4);
	ret[3].TopologyModel.InputsMap.push_back(5);
	ret[3].TopologyModel.InputsMap.push_back(6);
	ret[3].TopologyModel.InputsMap.push_back(0);
	return ret;
}

NeuronInterpretedModel create_neuron_interpreted_model() {
	std::vector<NeuronRawModel> raws = create_neuron_raw_model();
	Interpreter interpreter(8);
	return interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws[0]);
}

void test_interpret_raw_neuron_model() {
	printf("\n\n");
	printf("Testing interpret neuron raw model ...\n");
	NeuronInterpretedModel interpreted = create_neuron_interpreted_model();
	if (GlobalTaxonomyScheme::STR_CLASS_TRANSFERED == interpreted.NeuronSubModels[0][0].getName())
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_TRANSFERED == interpreted.NeuronSubModels[0][1].getName())
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_INACTIVE == interpreted.NeuronSubModels[0][2].getName())
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_INACTIVE == interpreted.NeuronSubModels[0][3].getName())
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_INACTIVE == interpreted.NeuronSubModels[0][4].getName())
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_INACTIVE == interpreted.NeuronSubModels[0][5].getName())
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_INACTIVE == interpreted.NeuronSubModels[0][6].getName())
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_INACTIVE == interpreted.NeuronSubModels[0][7].getName())
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_R2 == interpreted.NeuronSubModels[1][0].getName())
		printf("Test 9 ................ [PASSED] \n");
	else
		printf("Test 9 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_SIMPLE == interpreted.NeuronSubModels[2][0].getName())
		printf("Test 10 ................ [PASSED] \n");
	else
		printf("Test 10 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_SIMPLE == interpreted.NeuronSubModels[2][1].getName())
		printf("Test 11 ................ [PASSED] \n");
	else
		printf("Test 11 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_PRIMARY == interpreted.NeuronSubModels[3][0].getName())
		printf("Test 13 ................ [PASSED] \n");
	else
		printf("Test 13 ................ [FAILED] \n");
	if (GlobalTaxonomyScheme::STR_CLASS_PRIMARY == interpreted.NeuronSubModels[3][1].getName())
		printf("Test 14 ................ [PASSED] \n");
	else
		printf("Test 14 ................ [FAILED] \n");
}

void test_reverse_interpret_neuron_model() {
	printf("\n\n");
	printf("Testing reverse interpret neuron raw model ...\n");
	std::vector<NeuronRawModel> raws_org = create_neuron_raw_model();
	Interpreter interpreter(8);
	NeuronInterpretedModel interpreted;
	NeuronRawModel raw;
	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[0]);
	raw = interpreter.reverseInterpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), interpreted);
	if (raw == raws_org[0])
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");

	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[1]);
	raw = interpreter.reverseInterpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), interpreted);
	if (raw == raws_org[1])
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");

	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[2]);
	raw = interpreter.reverseInterpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), interpreted);
	if (raw == raws_org[2])
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
}

void test_format_interpreted_model() {
	printf("\n\n");
	printf("Testing format interpreted neuron model ...\n");
	std::vector<NeuronRawModel> raws_org = create_neuron_raw_model();
	Interpreter interpreter(8);
	NeuronInterpretedModel interpreted;
	BooleanModelFormatter formatter(8, GlobalTaxonomyScheme::createBooleanTaxonomyModel());
	SymbolicRule rule;
	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[0]);
	rule = formatter.format(interpreted);
	if (rule.getOutputSymbols().size() == 1)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (rule.getIntermediateSymbols().size() == 0)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (rule.getInputSymbols().size() == 2)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (rule.getOutputSymbols()[0] == std::string("b0"))
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (rule.getInputSymbols()[0] == std::string("a0") && rule.getInputSymbols()[1] == std::string("a1"))
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (rule.format().find(std::string("b0 := a0 AND a1;")) != std::string::npos)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");

	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[1]);
	rule = formatter.format(interpreted);
	if (rule.getOutputSymbols().size() == 1)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (rule.getIntermediateSymbols().size() == 0)
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (rule.getInputSymbols().size() == 6)
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");
	if (rule.format().find(std::string("b0 := NOT(a0) OR a1 OR ( a4 AND NOT(a5) )")) != std::string::npos)
		printf("Test 9 ................ [PASSED] \n");
	else
		printf("Test 9 ................ [FAILED] \n");

	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[2]);
	rule = formatter.format(interpreted);
	if (rule.getOutputSymbols().size() == 1)
		printf("Test 10 ................ [PASSED] \n");
	else
		printf("Test 10 ................ [FAILED] \n");
	if (rule.getIntermediateSymbols().size() == 0)
		printf("Test 11 ................ [PASSED] \n");
	else
		printf("Test 11 ................ [FAILED] \n");
	if (rule.getInputSymbols().size() == 8)
		printf("Test 12 ................ [PASSED] \n");
	else
		printf("Test 12 ................ [FAILED] \n");
	if (rule.format().find(std::string("b0 := NOT(a0) OR a1 OR ( a4 AND NOT(a5) ) OR ( a7 AND ( a6 OR a7 ) )")) != std::string::npos)
		printf("Test 13 ................ [PASSED] \n");
	else
		printf("Test 13 ................ [FAILED] \n");

	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raws_org[3]);
	rule = formatter.format(interpreted);
	if (rule.getOutputSymbols().size() == 1)
		printf("Test 14 ................ [PASSED] \n");
	else
		printf("Test 14 ................ [FAILED] \n");
	if (rule.getIntermediateSymbols().size() == 0)
		printf("Test 15 ................ [PASSED] \n");
	else
		printf("Test 15 ................ [FAILED] \n");
	if (rule.getInputSymbols().size() == 8)
		printf("Test 16 ................ [PASSED] \n");
	else
		printf("Test 16 ................ [FAILED] \n");
	if (rule.format().find(std::string("b0 := NOT(a7) OR a1 OR ( a4 AND NOT(a5) ) OR ( a0 AND ( a6 OR a0 ) )")) != std::string::npos)
		printf("Test 17 ................ [PASSED] \n");
	else
		printf("Test 17 ................ [FAILED] \n");
}

ANN create_fully_connected_ANN_1() {
	ANN ann;
	unsigned int layers[] = { 5, 2, 1 };
	ann.createStandardArray(3, layers);
	return ann;
}

ANN create_fully_connected_ANN_2() {
	ANN ann;
	unsigned int layers[] = { 10, 2, 1 };
	ann.createStandardArray(3, layers);
	return ann;
}

ANNInterpretedModel create_ANN_interpreted_model_fully_connected_1() {
	ANNInterpretedModel ret;
	LayerInterpretedModel layer0, layer1, layer2;
	NeuronInterpretedModel Neuron_1_0, Neuron_1_1, Neuron_2_0;

	layer0.setNumInputs(5);
	ret.push_back(layer0);

	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.TopologyModel.iLayer = 1;
	Neuron_1_0.TopologyModel.InputsMap.push_back(0);
	Neuron_1_0.TopologyModel.InputsMap.push_back(1);
	Neuron_1_0.TopologyModel.InputsMap.push_back(2);
	Neuron_1_0.TopologyModel.InputsMap.push_back(3);
	Neuron_1_0.TopologyModel.InputsMap.push_back(4);
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR].push_back(GlobalTaxonomyScheme::STR_CLASS_R2);
	layer1.push_back(Neuron_1_0);

	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.TopologyModel.iLayer = 1;
	Neuron_1_1.TopologyModel.InputsMap.push_back(0);
	Neuron_1_1.TopologyModel.InputsMap.push_back(1);
	Neuron_1_1.TopologyModel.InputsMap.push_back(2);
	Neuron_1_1.TopologyModel.InputsMap.push_back(3);
	Neuron_1_1.TopologyModel.InputsMap.push_back(4);
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR].push_back(GlobalTaxonomyScheme::STR_CLASS_R2);
	layer1.push_back(Neuron_1_1);
	layer1.setNumInputs(5);
	ret.push_back(layer1);

	Neuron_2_0.IgnoreMask.push_back(false);
	Neuron_2_0.IgnoreMask.push_back(false);
	Neuron_2_0.TopologyModel.iLayer = 2;
	Neuron_2_0.TopologyModel.InputsMap.push_back(0);
	Neuron_2_0.TopologyModel.InputsMap.push_back(1);
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR].push_back(GlobalTaxonomyScheme::STR_CLASS_R1);
	layer2.push_back(Neuron_2_0);
	layer2.setNumInputs(2);
	ret.push_back(layer2);
	return ret;
}

ANNInterpretedModel create_ANN_interpreted_model_fully_connected_2() {
	ANNInterpretedModel ret;
	LayerInterpretedModel layer0, layer1, layer2;
	NeuronInterpretedModel Neuron_1_0, Neuron_1_1, Neuron_2_0;

	layer0.setNumInputs(10);
	ret.push_back(layer0);

	Neuron_1_0.IgnoreMask.push_back(true);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(true);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.IgnoreMask.push_back(false);
	Neuron_1_0.TopologyModel.iLayer = 1;
	Neuron_1_0.TopologyModel.InputsMap.push_back(0);
	Neuron_1_0.TopologyModel.InputsMap.push_back(1);
	Neuron_1_0.TopologyModel.InputsMap.push_back(2);
	Neuron_1_0.TopologyModel.InputsMap.push_back(3);
	Neuron_1_0.TopologyModel.InputsMap.push_back(4);
	Neuron_1_0.TopologyModel.InputsMap.push_back(5);
	Neuron_1_0.TopologyModel.InputsMap.push_back(6);
	Neuron_1_0.TopologyModel.InputsMap.push_back(7);
	Neuron_1_0.TopologyModel.InputsMap.push_back(8);
	Neuron_1_0.TopologyModel.InputsMap.push_back(9);
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR].push_back(GlobalTaxonomyScheme::STR_CLASS_R2);
	layer1.push_back(Neuron_1_0);

	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(false);
	Neuron_1_1.IgnoreMask.push_back(true);
	Neuron_1_1.IgnoreMask.push_back(true);
	Neuron_1_1.TopologyModel.iLayer = 1;
	Neuron_1_1.TopologyModel.InputsMap.push_back(0);
	Neuron_1_1.TopologyModel.InputsMap.push_back(1);
	Neuron_1_1.TopologyModel.InputsMap.push_back(2);
	Neuron_1_1.TopologyModel.InputsMap.push_back(3);
	Neuron_1_1.TopologyModel.InputsMap.push_back(4);
	Neuron_1_1.TopologyModel.InputsMap.push_back(5);
	Neuron_1_1.TopologyModel.InputsMap.push_back(6);
	Neuron_1_1.TopologyModel.InputsMap.push_back(7);
	Neuron_1_1.TopologyModel.InputsMap.push_back(8);
	Neuron_1_1.TopologyModel.InputsMap.push_back(9);
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_INVERTED);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_1_1.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR].push_back(GlobalTaxonomyScheme::STR_CLASS_R2);
	layer1.push_back(Neuron_1_1);
	layer1.setNumInputs(10);
	ret.push_back(layer1);

	Neuron_2_0.IgnoreMask.push_back(false);
	Neuron_2_0.IgnoreMask.push_back(false);
	Neuron_2_0.TopologyModel.iLayer = 2;
	Neuron_2_0.TopologyModel.InputsMap.push_back(0);
	Neuron_2_0.TopologyModel.InputsMap.push_back(1);
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels.push_back(NeuronInterpretedSubModel());
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].push_back(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].push_back(GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
	Neuron_2_0.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR].push_back(GlobalTaxonomyScheme::STR_CLASS_R1);
	layer2.push_back(Neuron_2_0);
	layer2.setNumInputs(2);
	ret.push_back(layer2);
	return ret;
}

ANN create_sparse_connected_ANN() {
	ANN ann;
	unsigned int layers[] = { 10, 2, 1 };
	float conn_rates[] = { 0.5f, 1.0f };
	ann.createSparseHeterogeneousArray(conn_rates, 3, layers);
	ann[1][0].setConnection(0, ann[0][0]);
	ann[1][0].setConnection(1, ann[0][2]);
	ann[1][0].setConnection(2, ann[0][4]);
	ann[1][0].setConnection(3, ann[0][6]);
	ann[1][0].setConnection(4, ann[0][8]);

	ann[1][1].setConnection(1, ann[0][1]);
	ann[1][1].setConnection(3, ann[0][3]);
	ann[1][1].setConnection(5, ann[0][5]);
	ann[1][1].setConnection(7, ann[0][7]);
	ann[1][1].setConnection(9, ann[0][9]);

	return ann;
}

void test_align_interpreted_to_ANN_structure() {
	printf("\n\n");
	printf("Testing align interpreted ANN model to ANN structure...\n");
	printf("Testing true fully connected with connections less than buswidth-1... \n");
	ANN ann1 = create_fully_connected_ANN_1();
	ANNInterpretedModel model1 = create_ANN_interpreted_model_fully_connected_1();
	BooleanModelFormatter formatter(8, GlobalTaxonomyScheme::createBooleanTaxonomyModel());
	formatter.alignInterpretedModelToANNStructure(model1, ann1);
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][0].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][1].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][2].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][3].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][4].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][5].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_INACTIVE))
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][6].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_INACTIVE))
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][7].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_INACTIVE))
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");

	printf("Testing physically fully connected but virtually partial connected with connections greater than buswidth-1... \n");
	ANN ann2 = create_fully_connected_ANN_2();
	ANNInterpretedModel model2 = create_ANN_interpreted_model_fully_connected_2();
	formatter.alignInterpretedModelToANNStructure(model2, ann2);
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][0].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_INACTIVE))
		printf("Test 9 ................ [PASSED] \n");
	else
		printf("Test 9 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][1].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 10 ................ [PASSED] \n");
	else
		printf("Test 10 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][2].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 11 ................ [PASSED] \n");
	else
		printf("Test 11 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][3].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 12 ................ [PASSED] \n");
	else
		printf("Test 12 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][4].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 13 ................ [PASSED] \n");
	else
		printf("Test 13 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][5].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_INACTIVE))
		printf("Test 14 ................ [PASSED] \n");
	else
		printf("Test 14 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][6].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 15 ................ [PASSED] \n");
	else
		printf("Test 15 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][7].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 16 ................ [PASSED] \n");
	else
		printf("Test 16 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][8].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 17 ................ [PASSED] \n");
	else
		printf("Test 17 ................ [FAILED] \n");
	if (!std::string(model2[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][9].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED))
		printf("Test 18 ................ [PASSED] \n");
	else
		printf("Test 18 ................ [FAILED] \n");

	printf("Testing physically fully connected but virtually partial connected with connections less than buswidth-1... \n");
	model1 = create_ANN_interpreted_model_fully_connected_1();
	model1[1][0].IgnoreMask[0] = true;
	formatter.alignInterpretedModelToANNStructure(model1, ann1);
	if (!std::string(model1[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][0].getName()).compare(GlobalTaxonomyScheme::STR_CLASS_INACTIVE))
		printf("Test 19 ................ [PASSED] \n");
	else
		printf("Test 19 ................ [FAILED] \n");

}

void test_format_interpret_ANN_model() {
	printf("\n\n");
	printf("-------------------------------------------------------------\n");
	printf("Testing formatting ANN model ... \n");
	BooleanModelFormatter formatter(8, GlobalTaxonomyScheme::createBooleanTaxonomyModel());
	ANN ann1 = create_fully_connected_ANN_1();
	ANNInterpretedModel model1 = create_ANN_interpreted_model_fully_connected_1();
	formatter.alignInterpretedModelToANNStructure(model1, ann1);
	SymbolicRule rule1 = formatter.format(model1);
	if (rule1.getInputSymbols().size() == 5)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");
	if (rule1.getIntermediateSymbols().size() == 2)
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (rule1.getOutputSymbols().size() == 1)
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (rule1.find(std::string("b0 := a0 AND a1 AND a2 AND a3 AND a4;")) != std::string::npos &&
		rule1.find(std::string("b1 := NOT(a0) AND NOT(a1) AND NOT(a2) AND NOT(a3) AND NOT(a4);")) != std::string::npos &&
		rule1.find(std::string("c0 := b0 OR b1;")) != std::string::npos)
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");

	ANN ann2 = create_fully_connected_ANN_2();
	ANNInterpretedModel model2 = create_ANN_interpreted_model_fully_connected_2();
	formatter.alignInterpretedModelToANNStructure(model2, ann2);
	SymbolicRule rule2 = formatter.format(model2);
	if (rule2.getInputSymbols().size() == 10)
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (rule2.getIntermediateSymbols().size() == 2)
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (rule2.getOutputSymbols().size() == 1)
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");
	if (rule2.find(std::string("b0 := a1 AND a2 AND a3 AND a4 AND a6 AND a7 AND a8 AND a9;")) != std::string::npos &&
		rule2.find(std::string("b1 := NOT(a0) AND NOT(a1) AND NOT(a2) AND NOT(a3) AND NOT(a4) AND NOT(a5) AND NOT(a6) AND NOT(a7);")) != std::string::npos &&
		rule2.find(std::string("c0 := b0 OR b1;")) != std::string::npos)
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");
}

TrainingData create_Alpha_Training_Data() {
	TrainingData ret(14, 3, 20);
	nb_type data[14][23] = {
		{ 4, 4, -7,		0,1,0, 0,1,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 4, 4, -2,		0,1,0, 0,1,0,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ -3, 4, -2,	0,0,1, 0,1,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 4, -3, -2,	0,1,0, 0,0,1,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ -8, -8, 7,	0,0,1, 0,0,1,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ -3, 6, 2,		0,0,1, 0,1,0,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 6, -3, 2,		0,1,0, 0,0,1,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ -4, -4, 7,	0,0,1, 0,0,1,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 2, 0, -1,		0,1,0, 1,0,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 0, 2, -1,		1,0,0, 0,1,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ -2, 0, 1,		0,0,1, 1,0,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 0, -2, 1,		1,0,0, 0,0,1,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 0, 0, 4,		1,0,0, 1,0,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
		{ 0, 0, -4,		1,0,0, 1,0,0,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0 },
	};
	ret.setSampleData(0, data[0]);
	ret.setSampleData(1, data[1]);
	ret.setSampleData(2, data[2]);
	ret.setSampleData(3, data[3]);
	ret.setSampleData(4, data[4]);
	ret.setSampleData(5, data[5]);
	ret.setSampleData(6, data[6]);
	ret.setSampleData(7, data[7]);
	ret.setSampleData(8, data[8]);
	ret.setSampleData(9, data[9]);
	ret.setSampleData(10, data[10]);
	ret.setSampleData(11, data[11]);
	ret.setSampleData(12, data[12]);
	ret.setSampleData(13, data[13]);
	return ret;
}

TrainingData create_Beta_Training_Data() {
	TrainingData ret(14, 20, 3);
	nb_type data[14][23] = {
		{ 0,1,0, 0,1,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		4, 4, -7 },
		{ 0,1,0, 0,1,0,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		4, 4, -2 },
		{ 0,0,1, 0,1,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		-3, 4, -2 },
		{ 0,1,0, 0,0,1,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		4, -3, -2 },
		{ 0,0,1, 0,0,1,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		-8, -8, 7 },
		{ 0,0,1, 0,1,0,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		-3, 6, 2 },
		{ 0,1,0, 0,0,1,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		6, -3, 2 },
		{ 0,0,1, 0,0,1,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		-4, -4, 7 },
		{ 0,1,0, 1,0,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		2, 0, -1 },
		{ 1,0,0, 0,1,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		0, 2, -1 },
		{ 0,0,1, 1,0,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		-2, 0, 1 },
		{ 1,0,0, 0,0,1,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		0, -2, 1 },
		{ 1,0,0, 1,0,0,		0,1,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		0, 0, 4 },
		{ 1,0,0, 1,0,0,		1,0,		1,0,0, 1,0,0,		1,0,0, 1,0,0,		0, 0, -4 },
	};
	ret.setSampleData(0, data[0]);
	ret.setSampleData(1, data[1]);
	ret.setSampleData(2, data[2]);
	ret.setSampleData(3, data[3]);
	ret.setSampleData(4, data[4]);
	ret.setSampleData(5, data[5]);
	ret.setSampleData(6, data[6]);
	ret.setSampleData(7, data[7]);
	ret.setSampleData(8, data[8]);
	ret.setSampleData(9, data[9]);
	ret.setSampleData(10, data[10]);
	ret.setSampleData(11, data[11]);
	ret.setSampleData(12, data[12]);
	ret.setSampleData(13, data[13]);
	return ret;
}

void test_train_LTM_Segment() {
	printf("\n\n");
	printf("-------------------------------------------------------------\n");
	printf("Testing LTM Segment Training ... \n");
	LTMSegment segment;
	std::vector<unsigned int> hidden_layers;
	TrainingData Alpha = create_Alpha_Training_Data();
	TrainingData Beta = create_Beta_Training_Data();
	hidden_layers.push_back(10);
	segment.create(3, 20, hidden_layers);
	segment.setMaxEpochs(10000);
	segment.setAlphaDesiredError(0.001f);
	segment.setBetaDesiredError(0.001f);
	segment.train(Alpha, Beta);
	if (segment.getAlpha()->getMSE() <= 0.001f && segment.getBeta()->getMSE() <= 0.001f)
		printf("Test 1 ................ [PASSED] \n");
	else
		printf("Test 1 ................ [FAILED] \n");

	TrainingData train_data(4, 2, 1);
	unsigned int layers[2] = { 2, 1 };
	ANN ann;
	ANNRawModel raw = segment.modelANN(ann);
	Interpreter interpreter(2);
	ANNInterpretedModel interpreted;


	nb_type d1[4][3] = {
		{0, 0, 0},
		{0, 1, 0},
		{1, 0, 0},
		{1, 1, 1}
	};
	train_data.setSamplesData(&d1[0][0]);
	ann.createStandardArray(2, layers);
	ann.setActivationFunctionOutput(FANN_SIGMOID);
	ann.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	ann.trainOnData(train_data, 10000, 100, 0.001f);
	raw = segment.modelANN(ann);
	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raw);
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][0].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED)))
		printf("Test 2 ................ [PASSED] \n");
	else
		printf("Test 2 ................ [FAILED] \n");
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][1].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED)))
		printf("Test 3 ................ [PASSED] \n");
	else
		printf("Test 3 ................ [FAILED] \n");
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR][0].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_R2)))
		printf("Test 4 ................ [PASSED] \n");
	else
		printf("Test 4 ................ [FAILED] \n");

	nb_type d2[4][3] = {
		{ 0, 0, 0 },
		{ 0, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 0 }
	};
	train_data.setSamplesData(&d2[0][0]);
	ann.createStandardArray(2, layers);
	ann.setActivationFunctionOutput(FANN_SIGMOID);
	ann.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	ann.trainOnData(train_data, 10000, 100, 0.001f);
	raw = segment.modelANN(ann);
	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raw);
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][0].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_INVERTED)))
		printf("Test 5 ................ [PASSED] \n");
	else
		printf("Test 5 ................ [FAILED] \n");
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][1].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED)))
		printf("Test 6 ................ [PASSED] \n");
	else
		printf("Test 6 ................ [FAILED] \n");
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR][0].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_R2)))
		printf("Test 7 ................ [PASSED] \n");
	else
		printf("Test 7 ................ [FAILED] \n");

	nb_type d3[4][3] = {
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 1, 0, 1 },
		{ 1, 1, 0 }
	};
	train_data.setSamplesData(&d3[0][0]);
	ann.createStandardArray(2, layers);
	ann.setActivationFunctionOutput(FANN_SIGMOID);
	ann.setTrainingAlgorithm(FANN_TRAIN_RPROP);
	ann.trainOnData(train_data, 10000, 100, 0.001f);
	raw = segment.modelANN(ann);
	interpreted = interpreter.interpret(GlobalTaxonomyScheme::createBooleanTaxonomyModel(), raw);
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][0].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_TRANSFERED)))
		printf("Test 8 ................ [PASSED] \n");
	else
		printf("Test 8 ................ [FAILED] \n");
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][1].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_INVERTED)))
		printf("Test 9 ................ [PASSED] \n");
	else
		printf("Test 9 ................ [FAILED] \n");
	if (!std::string(interpreted[1][0].NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR][0].getName()).compare(std::string(GlobalTaxonomyScheme::STR_CLASS_R2)))
		printf("Test 10 ................ [PASSED] \n");
	else
		printf("Test 10 ................ [FAILED] \n");

	return;
}

void test_L1() {
	printf("\n\n");
	printf("-------------------------------------------------------------\n");
	printf("Testing Abstraction Layer one of neural cuircuits ... \n");
	ANN net = create_ann();
	net.randomizeWeights(-10, 10);
	unsigned int layers[3] = { 2, 2, 1 };
	net.createStandardArray(3, layers);
	test_global_taxonomy_scheme();
	test_neuron_topology_model(net);
	test_connection_ignore_mask();
	test_interpret_raw_neuron_model();
	test_reverse_interpret_neuron_model();
	test_format_interpreted_model();
	test_align_interpreted_to_ANN_structure();
	test_format_interpret_ANN_model();
	test_train_LTM_Segment();
	return;
}

#endif