#include "ModelFormatter.h"

namespace NEUROBASE{
	namespace L1{
		const unsigned int SymbolicRule::SYMBOL_TYPE_INPUT_INDEX = 0;
		const unsigned int SymbolicRule::SYMBOL_TYPE_INTERMEDIATE_INDEX = 1;
		const unsigned int SymbolicRule::SYMBOL_TYPE_OUTPUT_INDEX = 2;
	}

	char ModelFormatter::INPUT_PREFIX_START = 'a';
	const unsigned int ModelFormatter::MAX_LAYERS = 20;

	SymbolicRule ModelFormatter::format(ANNInterpretedModel& model){
		SymbolicRule ret = initSymbolicRule(model);
		char inputPrefix = INPUT_PREFIX_START;
		for (ANNInterpretedModel::iterator it = model.begin()+1; it != model.end(); it++, inputPrefix++)
			ret += format(*it, inputPrefix, inputPrefix+1);
		return ret;
	}

	SymbolicRule ModelFormatter::format(LayerInterpretedModel & model, char inputPrefix, char outputPrefix){
		SymbolicRule ret;
		unsigned int i = 0;
		std::string strPrefix;
		strPrefix = outputPrefix;
		for (LayerInterpretedModel::iterator it = model.begin(); it != model.end(); it++, i++)
			ret += format(*it, inputPrefix, strPrefix + std::to_string(i));
		return ret;
	}

	SymbolicRule ModelFormatter::format(NeuronInterpretedModel& model, char inputPrefix, std::string outputVariable){
		SymbolicRule ret;
		SymbolicRule PrimarySimple, PrimaryCompund, SeconderySimple, SeconderyCompound;
		PrimarySimple = formatPrimarySimplePart(model, inputPrefix);
		PrimaryCompund = formatPrimaryCompundPart(model, inputPrefix);
		SeconderySimple = formatSeconderySimplePart(model, inputPrefix);
		SeconderyCompound = formatSeconderyCompundPart(model, inputPrefix);
		SymbolicRule PrimaryOperator(formatRelationFunction(model));
		SymbolicRule SeconderyOperator(formatComplementingRelationFunction(model));
		ret = outputVariable + std::string(" :=") + PrimarySimple;
		if (!PrimaryCompund.empty()){
			ret += " ";
			ret += PrimaryOperator;
			ret += SymbolicRule(" ( ") + PrimaryCompund + SymbolicRule(" )");
		}
		if (!SeconderySimple.empty()){
			ret += " ";
			ret += PrimaryOperator;
			ret += SymbolicRule(" ( ") + SeconderySimple;
			if (!SeconderyCompound.empty()){
				ret += " ";
				ret += SeconderyOperator;
				ret += SymbolicRule(" ( ") + SeconderyCompound + SymbolicRule(" )");
			}
			ret += SymbolicRule(" )");
		}
		ret += ";\n";
		return ret;
	}

	SymbolicRule ModelFormatter::format(NeuronInterpretedModel& model){
		SymbolicRule ret = initSymbolicRule(model);
		char outPrefix = ModelFormatter::INPUT_PREFIX_START + 1;
		std::string out;
		out = outPrefix + std::to_string(0);
		ret += format(model, INPUT_PREFIX_START, out);
		return ret;
	}

	LayerSymbolicRules ModelFormatter::formatLayerRules(LayerInterpretedModel& model){
		LayerSymbolicRules ret;
		for (unsigned int i = 0; i < model.size(); i++)
			ret.push_back(format(model[i]));
		return ret;
	}

	ANNSymbolicRules ModelFormatter::formatANNRules(ANNInterpretedModel& model){
		ANNSymbolicRules ret;
		for (unsigned int i = 0; i < model.size(); i++)
			ret.push_back(formatLayerRules(model[i]));
		return ret;
	}

	MultiANNSymbolicRules ModelFormatter::formatANNRules(MultiANNInterpretedModel& model){
		MultiANNSymbolicRules ret;
		for (unsigned int i = 0; i < model.size(); i++)
			ret.push_back(formatANNRules(model[i]));
		return ret;
	}

	SymbolicRule ModelFormatter::formatPrimarySimplePart(NeuronInterpretedModel& model, char inputPrefix){
		SymbolicRule ret;
		unsigned int neuronInputs = getNeuronInputs(model);
		for (unsigned int i = 0; i < neuronInputs; i++){
			if (isSimpleInput(model, i) && isPrimaryInput(model, i)){
				if (!ret.empty())
					ret += " " + formatRelationFunction(model);
				ret += " " + formatInputStateFunction(model, i, inputPrefix);
			}
		}
		if (ret.empty())
			ret = getPrimaryIdentityConstant(model);
		return ret;
	}

	SymbolicRule ModelFormatter::formatPrimaryCompundPart(NeuronInterpretedModel& model, char inputPrefix){
		SymbolicRule ret;
		unsigned int neuronInputs = getNeuronInputs(model);
		for (unsigned int i = 0; i < neuronInputs; i++){
			if (isCompoundInput(model, i) && isPrimaryInput(model, i)){
				if (!ret.empty())
					ret += " " + formatComplementingRelationFunction(model) + " ";
				ret += formatInputStateFunction(model, i, inputPrefix);
			}
		}
		return ret;
	}

	SymbolicRule ModelFormatter::formatSeconderySimplePart(NeuronInterpretedModel& model, char inputPrefix){
		SymbolicRule ret;
		unsigned int neuronInputs = getNeuronInputs(model);
		for (unsigned int i = 0; i < neuronInputs; i++){
			if (isSimpleInput(model, i) && isSeconderyInput(model, i)){
				if (!ret.empty())
					ret += " " + formatComplementingRelationFunction(model) + " ";
				ret += formatInputStateFunction(model, i, inputPrefix);
			}
		}
		if (ret.empty() && hasSeconderyCompound(model))
			ret = getPrimaryIdentityConstant(model);
		return ret;
	}

	SymbolicRule ModelFormatter::formatSeconderyCompundPart(NeuronInterpretedModel& model, char inputPrefix){
		SymbolicRule ret;
		unsigned int neuronInputs = getNeuronInputs(model);
		for (unsigned int i = 0; i < neuronInputs; i++){
			if (isCompoundInput(model, i) && isSeconderyInput(model, i)){
				if (!ret.empty())
					ret += " " + formatRelationFunction(model) + " ";
				ret += formatInputStateFunction(model, i, inputPrefix);
			}
		}
		return ret;
	}

	bool ModelFormatter::hasSeconderyCompound(NeuronInterpretedModel& model){
		unsigned int neuronInputs = getNeuronInputs(model);
		for (unsigned int i = 0; i < neuronInputs; i++){
			if (isCompoundInput(model, i) && isSeconderyInput(model, i))
				return true;
		}
		return false;
	}

	unsigned int ModelFormatter::getNeuronInputs(NeuronInterpretedModel & model)
	{
		for (unsigned int i = 0; i < taxonomyScheme.size(); i++) {
			if (taxonomyScheme[i].getType() == Taxonomy::InputTaxonomy)
				return model.NeuronSubModels[i].size();
		}
		return 0;
	}

	SymbolicRule ModelFormatter::initSymbolicRule (ANNInterpretedModel& model){
		if (model.size() > MAX_LAYERS)
			throw nb_exception(std::string("Formatter can't format network with layers more than ") + std::to_string(MAX_LAYERS) + std::string(" layers"));
		char inputPrefix = INPUT_PREFIX_START;
		std::string strPrefix;
		strPrefix = inputPrefix;
		SymbolicRule rule;
		for (unsigned int i = 0; i < model[0].getNumInputs(); i++){
			strPrefix = inputPrefix;
			rule.addInputSymbol(strPrefix + std::to_string(i));
		}
		inputPrefix++;
		for (ANNInterpretedModel::iterator it = model.begin()+1; it != model.end(); it++, inputPrefix++){
			strPrefix = inputPrefix;
			if (it < model.end() - 1)
				for (unsigned int i = 0; i < it->size(); i++)
					rule.addIntermediateSymbol(strPrefix + std::to_string(i));
			else
				for (unsigned int i = 0; i < it->size(); i++)
					rule.addOutputSymbol(strPrefix + std::to_string(i));
		}
		return rule;
	}

	SymbolicRule ModelFormatter::initSymbolicRule(NeuronInterpretedModel& model){
		char inputPrefix = INPUT_PREFIX_START;
		std::string strPrefix;
		strPrefix = inputPrefix;
		SymbolicRule rule;
		for (unsigned int i = 0; i < model.TopologyModel.InputsMap.size(); i++){
			strPrefix = inputPrefix;
			rule.addInputSymbol(strPrefix + std::to_string(model.TopologyModel.InputsMap[i]));
		}
		strPrefix = inputPrefix+1;
		rule.addOutputSymbol(strPrefix + std::to_string(0));
		return rule;
	}

	bool ModelFormatter::isActiveInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_INACTIVE) ? false : true;
	}

	bool ModelFormatter::isTransferedInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_TRANSFERED) ? true : false;
	}

	bool ModelFormatter::isInvertedInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_INPUT_STATES][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_INVERTED) ? true : false;
	}

	bool ModelFormatter::isSimpleInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (isActiveInput(model, nInput) &&
			(model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_SIMPLE ||
				model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_BOTH)) ? true : false;
	}

	bool ModelFormatter::isCompoundInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (isActiveInput(model, nInput) &&
			(model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_COMPOUND ||
				model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_TERM_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_BOTH)) ? true : false;
	}

	bool ModelFormatter::isPrimaryInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (isActiveInput(model, nInput) &&
			(model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_PRIMARY ||
				model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_BOTH)) ? true : false;
	}

	bool ModelFormatter::isSeconderyInput(NeuronInterpretedModel& model, unsigned int nInput){
		if (nInput >= getNeuronInputs(model))
			throw nb_exception("input should be less than neuron inputs");
		return (isActiveInput(model, nInput) &&
			(model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_SECONDERY ||
				model.NeuronSubModels[GlobalTaxonomyScheme::INDEX_PART_TYPE][nInput].getName() == GlobalTaxonomyScheme::STR_CLASS_BOTH)) ? true : false;
	}
}