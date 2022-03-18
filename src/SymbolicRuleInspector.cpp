#include "SymbolicRuleInspector.h"
#include "SymbolicMachine.h"

namespace NEUROBASE{
	TrainingData SymbolicRuleInspector::computeNeuronResponses(Neuron& neuron){
		TrainingData ret = SymbolicMachine::generateBooleanCases(neuron.getNumConnections() - 1);
		ANN ann = neuron.isolate();
		ann.run(ret);
		SymbolicMachine::quantizetBooleanOutputs(ret);
		return ret;
	}

	TrainingData SymbolicRuleInspector::computeSymbolicRuleResponses(SymbolicRule& neuronRule, unsigned int numInputs){
		SymbolicMachine sm;
		TrainingData cases = SymbolicMachine::generateBooleanCases(numInputs);
		TrainingData ret = sm.testSymbolicRule(neuronRule, cases);
		return ret;
	}

	NeuronInspectedSymbolicRule SymbolicRuleInspector::inspect(SymbolicRule& neuronRule, Neuron& neuron){
		TrainingData neuronResponses = computeNeuronResponses(neuron);
		TrainingData modelResponses = computeSymbolicRuleResponses(neuronRule, neuron.getNumConnections() - 1);
		return NeuronInspectedSymbolicRule(neuronRule, neuronResponses.getMSE(modelResponses));
	}

	LayerInspectedSymbolicRule SymbolicRuleInspector::inspect(LayerSymbolicRules& layerRules, Layer& layer){
		if (layerRules.size() != layer.getNumNodes())
			throw nb_exception("Layer Symbolic rule size should equal to number of neurons");
		LayerInspectedSymbolicRule ret;
		for (unsigned int i = 0; i < layerRules.size(); i++)
			ret.push_back(inspect(layerRules[i], layer[i]));
		return ret;
	}

	ANNInspectedSymbolicRule SymbolicRuleInspector::inspect(ANNSymbolicRules& annRules, ANN& ann){
		if (annRules.size() != ann.getNumLayers())
			throw nb_exception("ANN Symbolic rule size should equal to number of layers");
		ANNInspectedSymbolicRule ret;
		for (unsigned int i = 0; i < annRules.size(); i++)
			ret.push_back(inspect(annRules[i], ann[i]));
		return ret;
	}

	MultiANNInspectedSymbolicRule SymbolicRuleInspector::inspect(MultiANNSymbolicRules& MultiANNRules, ANN& ann){
		// This needs enhancement because the same ann response is computed every iteration below
		MultiANNInspectedSymbolicRule ret;
		for (unsigned int i = 0; i < MultiANNRules.size(); i++)
			ret.push_back(inspect(MultiANNRules[i], ann));
		return ret;
	}
}