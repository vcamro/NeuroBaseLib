#include "Interpreter.h"

namespace NEUROBASE{
	NeuronInterpretedModel Interpreter::interpret(TaxonomyScheme& taxonomy, NeuronRawModel& model){
		if (model.getNumClasses() != computeRequiredNeuronModelSize(taxonomy))
			throw nb_exception("Neuron model data size must be of the same size of its taxonomy model");
		NeuronInterpretedModel ret;
		ret.TopologyModel = model.TopologyModel;
		ret.IgnoreMask = model.IgnoreMask;
		unsigned int neuronModelOffset = 0;
		for (TaxonomyScheme::iterator it = taxonomy.begin(); it != taxonomy.end(); it++){
			nb_type* start_it = model.begin()._Ptr + neuronModelOffset;
			nb_type* end_it = NULL;
			unsigned int nClasses = 0;
			switch (it->getType()){
			case Taxonomy::RelationTaxonomy:{
												nClasses = it->getNumClasses();
												end_it = start_it + nClasses;
												NeuronRawModel vec(start_it, end_it);
												NeuronInterpretedSubModel part;
												part.push_back(it->at(vec.getMax()));
												ret.NeuronSubModels.push_back(part);
												break;
			}
			case Taxonomy::InputTaxonomy:{
												nClasses = maxNeuronInputs * it->getNumClasses();
												end_it = start_it + nClasses;
												NeuronRawModel vec(start_it, end_it);
												NeuronInterpretedSubModel temp = interpretInputTypeClasses(*it, vec);
												ret.NeuronSubModels.push_back(temp);
												break;
			}
			}
			neuronModelOffset += nClasses;
		}
		return ret;
	}

	LayerInterpretedModel Interpreter::interpret(TaxonomyScheme& taxonomy, LayerRawModel& model){
		LayerInterpretedModel ret;
		ret.setNumInputs(model.getNumInputs());
		for (LayerRawModel::iterator it = model.begin(); it != model.end(); it++)
			ret.push_back(interpret(taxonomy, *it));
		return ret;
	}

	ANNInterpretedModel Interpreter::interpret(TaxonomyScheme& taxonomy, ANNRawModel& model){
		ANNInterpretedModel ret;
		for (ANNRawModel::iterator it = model.begin(); it != model.end(); it++)
			ret.push_back(interpret(taxonomy, *it));
		return ret;
	}

	MultiANNInterpretedModel Interpreter::interpret(TaxonomyScheme& taxonomy, MultiANNRawModel& model){
		MultiANNInterpretedModel ret;
		for (unsigned int i = 0; i < model.size(); i++)
			ret.push_back(interpret(taxonomy, model[i]));
		return ret;
	};

	NeuronRawModel Interpreter::reverseInterpret(TaxonomyScheme& taxonomy, NeuronInterpretedModel& model){
		if (model.NeuronSubModels.size() != taxonomy.size())
			throw nb_exception("Interpreted model size should equal to taxonomy scheme size");
		NeuronRawModel ret;
		ret.TopologyModel = model.TopologyModel;
		ret.IgnoreMask = model.IgnoreMask;
		for (unsigned int i = 0; i < taxonomy.size(); i++){
			if (taxonomy[i].getType() == Taxonomy::TaxonomyType::InputTaxonomy){
				for (unsigned int j = 0; j < getMaxNeuronInputs(); j++){
					for (unsigned int k = 0; k < taxonomy[i].size(); k++) {
						if (std::string(taxonomy[i][k].getName()) == std::string(model.NeuronSubModels[i][j].getName()))
								ret.push_back(1.0f);
							else
								ret.push_back(0.0f);
					}
				}
			}
			else {
				for (unsigned int k = 0; k < taxonomy[i].size(); k++){
					if (std::string(taxonomy[i][k].getName()) == std::string(model.NeuronSubModels[i][0].getName()))
						ret.push_back(1.0f);
					else
						ret.push_back(0.0f);
				}
			}
		}
		return ret;
	}

	LayerRawModel Interpreter::reverseInterpret(TaxonomyScheme& taxonomy, LayerInterpretedModel& model){
		LayerRawModel ret;
		for (LayerInterpretedModel::iterator it = model.begin(); it != model.end(); it++)
			ret.push_back(reverseInterpret(taxonomy, *it));
		return ret;
	}

	ANNRawModel Interpreter::reverseInterpret(TaxonomyScheme& taxonomy, ANNInterpretedModel& model){
		ANNRawModel ret;
		for (ANNInterpretedModel::iterator it = model.begin(); it != model.end(); it++)
			ret.push_back(reverseInterpret(taxonomy, *it));
		return ret;
	}

	unsigned int Interpreter::computeRequiredNeuronModelSize(TaxonomyScheme& taxonomy){
		unsigned int ret = 0;
		for (TaxonomyScheme::iterator it = taxonomy.begin(); it != taxonomy.end(); it++){
			switch (it->getType()){
			case Taxonomy::RelationTaxonomy:
				ret += it->getNumClasses();
				break;
			case Taxonomy::InputTaxonomy:
				ret += it->getNumClasses() * maxNeuronInputs;
				break;
			}
		}
		return ret;
	}

	NeuronInterpretedSubModel Interpreter::interpretInputTypeClasses(Taxonomy& taxonomy, NeuronRawModel& subModel){
		if (taxonomy.getType() != Taxonomy::InputTaxonomy)
			throw nb_exception("To use this operation taxonomy of input taxonomy type should be used");
		if (taxonomy.getNumClasses() * maxNeuronInputs != subModel.size())
			throw nb_exception("Size of taxonomy inputs and classes should match with neuron model size");
		NeuronInterpretedSubModel ret;
		unsigned int nClasses = taxonomy.getNumClasses();
		for (unsigned int i = 0; i < maxNeuronInputs; i++){
			nb_type* start_it = subModel.begin()._Ptr + (nClasses * i);
			nb_type* end_it = start_it + nClasses;
			nb_vector vec(start_it, end_it);
			NeuronInterpretedSubModel part;
			ret.push_back(taxonomy.at(vec.getMax()));
		}
		return ret;
	}
}