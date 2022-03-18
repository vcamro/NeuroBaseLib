#include "BooleanModelFormatter.h"

namespace NEUROBASE{
	void BooleanModelFormatter::alignInterpretedModelToANNStructure(ANNInterpretedModel& interpretedModel, ANN& ann){
		for (unsigned int i = 0; i < ann.getNumLayers(); i++){
			unsigned int k = 0;
			for (unsigned int j = 0; j < ann[i].getNumNeurons(); j++){
				if (ann[i][j].isNode()){
					for (unsigned int l = ann[i][j].getNumConnections() - 1; l < getMaxNeuronInputs(); l++)
						interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][l] = GlobalTaxonomyScheme::STR_CLASS_INACTIVE;

					for (unsigned int m = 0; m < interpretedModel[i][j].IgnoreMask.size(); m++) {
						if (interpretedModel[i][k].IgnoreMask[m]) {
							// Hypothetical case if neuron inputs less than buswidth however there are true ignore mask for any reason
							if (interpretedModel[i][k].IgnoreMask.size() <= getMaxNeuronInputs()) {
								//throw nb_exception("It is not expected that there is ture ignore mask while no need to ignore");
								interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][m] = GlobalTaxonomyScheme::STR_CLASS_INACTIVE;
								interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE][m] = GlobalTaxonomyScheme::STR_CLASS_SIMPLE;
								interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE][m] = GlobalTaxonomyScheme::STR_CLASS_PRIMARY;
							}
							else{ // Normal case ignore mask because of neuron inputs greater than bus width
								interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].insert(interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES].begin() + m, GlobalTaxonomyScheme::STR_CLASS_INACTIVE);
								interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].insert(interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE].begin() + m, GlobalTaxonomyScheme::STR_CLASS_SIMPLE);
								interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].insert(interpretedModel[i][k].NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE].begin() + m, GlobalTaxonomyScheme::STR_CLASS_PRIMARY);
							}
						}
					}

					k++;
				}
			}
		}
	}

	void BooleanModelFormatter::alignInterpretedModelToANNStructure(MultiANNInterpretedModel& interpretedModel, ANN& ann){
		for (unsigned int i = 0; i < interpretedModel.size(); i++)
			alignInterpretedModelToANNStructure(interpretedModel[i], ann);
	}

	std::string BooleanModelFormatter::formatInputStateFunction(NeuronInterpretedModel& model, unsigned int nInput, char inputPrefix){
		if (!isActiveInput(model, nInput))
			throw nb_exception("Input must be active to be able to format it");
		std::string strPrefix;
		strPrefix = inputPrefix;
		std::string var = strPrefix + std::to_string(model.TopologyModel.InputsMap[nInput]);
		std::string ret;
		if (isInvertedInput(model, nInput))
			ret = "NOT(" + var + ")";
		else
			ret = var;
		return ret;
	}

	std::string BooleanModelFormatter::formatRelationFunction(NeuronInterpretedModel& model){
		return (model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR][0].getName() == GlobalTaxonomyScheme::STR_CLASS_R1) ? "OR" : "AND";
	}

	std::string BooleanModelFormatter::formatComplementingRelationFunction(NeuronInterpretedModel& model){
		return (model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR][0].getName() == GlobalTaxonomyScheme::STR_CLASS_R1) ? "AND" : "OR";
	}

	std::string BooleanModelFormatter::getPrimaryIdentityConstant(NeuronInterpretedModel& model){
		return (formatRelationFunction(model) == "OR") ? "0" : "1";
	}

	std::string BooleanModelFormatter::getSeconderyIdentityConstant(NeuronInterpretedModel& model){
		return (formatComplementingRelationFunction(model) == "OR") ? "0" : "1";
	}
}