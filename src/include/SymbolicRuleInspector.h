#ifndef __SYMBOLIC_RULE_INSPECTOR_H
#define __SYMBOLIC_RULE_INSPECTOR_H

#include "nb_lib.h"
#include "TrainingData.h"
#include "neuron.h"
#include "ModelFormatter.h"

namespace NEUROBASE{
	namespace L1{
		class NeuronInspectedSymbolicRule : public SymbolicRule{
		public:
			NeuronInspectedSymbolicRule(){ inspectedMSE = 0.0f; };
			NeuronInspectedSymbolicRule(const SymbolicRule& other) :SymbolicRule(other){ inspectedMSE = 0.0f; };
			NeuronInspectedSymbolicRule(const NeuronInspectedSymbolicRule& other, nb_type MSE) :NeuronInspectedSymbolicRule(other){ inspectedMSE = MSE; };
			NeuronInspectedSymbolicRule(const NeuronInspectedSymbolicRule& other) :SymbolicRule(other){ inspectedMSE = other.inspectedMSE; };
			~NeuronInspectedSymbolicRule(){};
		private:
			nb_type inspectedMSE;
		public:
			std::string format(){
				return SymbolicRule::format() + std::string("inspectedMSE = ") + std::to_string(inspectedMSE) + "\n";
			}
			virtual void print(){ printf(format().data()); };
			nb_type getInspectedMSE(){ return inspectedMSE; };
		};
		typedef TVector<NeuronInspectedSymbolicRule> LayerInspectedSymbolicRule;
		typedef TVector<LayerInspectedSymbolicRule> ANNInspectedSymbolicRule;
	}
	namespace L2{
		class MultiANNInspectedSymbolicRule : public TVector<ANNInspectedSymbolicRule>{
		public:
			MultiANNInspectedSymbolicRule(){};
			MultiANNInspectedSymbolicRule(const MultiANNInspectedSymbolicRule& other) :TVector<ANNInspectedSymbolicRule>(other){};
			MultiANNInspectedSymbolicRule(const TVector<ANNInspectedSymbolicRule>& other) :TVector<ANNInspectedSymbolicRule>(other){};
			~MultiANNInspectedSymbolicRule(){};
		public:
			unsigned int getANNWithMinNodeMSE(unsigned int layer, unsigned int node){
				if (size() == 0) throw nb_exception("At least one Inspected Symbolic Rules for one Memory result should exist");
				unsigned int minIndex = 0;
				nb_type minMSE = at(minIndex)[layer][node].getInspectedMSE();
				for (unsigned int i = 0; i < size(); i++){
					if ((at(i))[layer][node].getInspectedMSE() <= minMSE){
						minMSE = at(i)[layer][node].getInspectedMSE();
						minIndex = i;
					}
					if (minMSE == 0) break;
				}
				return minIndex;
			}
		};
	}

	using namespace L0;
	using namespace L1;
	using namespace L2;
	class SymbolicRuleInspector
	{
	public:
		SymbolicRuleInspector(){};
		~SymbolicRuleInspector(){};
	private:
		TrainingData computeNeuronResponses(Neuron& neuron);
		TrainingData computeSymbolicRuleResponses(SymbolicRule& rule, unsigned int numInputs);
	public:
		NeuronInspectedSymbolicRule inspect(SymbolicRule& neuronRule, Neuron& neuron);
		LayerInspectedSymbolicRule inspect(LayerSymbolicRules& layerRules, Layer& layer);
		ANNInspectedSymbolicRule inspect(ANNSymbolicRules& annRules, ANN& ann);
		MultiANNInspectedSymbolicRule inspect(MultiANNSymbolicRules& annRules, ANN& ann);
	};
}

#endif