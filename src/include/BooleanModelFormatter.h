#ifndef __BOOLEAN_MODEL_FROMATTER_H
#define __BOOLEAN_MODEL_FROMATTER_H

#include "nb_lib.h"
#include "ModelFormatter.h"
#include "GlobalTaxonomyScheme.h"

namespace NEUROBASE{
	using namespace L0;
	using namespace L1;
/* Class: BooleanModelFormatter

	Encapsulates the logic of formatting interpreted model to symbolic rule, this class is specific for boolean domain
	*/
	class BooleanModelFormatter : public ModelFormatter{
	public:
		/*Default constructor*/
		BooleanModelFormatter(){};
		/*Constructor with maximum number of neuron inputs and taxonomy scheme*/
		BooleanModelFormatter(unsigned int param_inputs, GlobalTaxonomyScheme param_taxonomy) :ModelFormatter(param_inputs, param_taxonomy){};
		/*Destructor*/
		~BooleanModelFormatter(){};
	public:
		void alignInterpretedModelToANNStructure(ANNInterpretedModel& interpretedModel, ANN& ann);
		void alignInterpretedModelToANNStructure(MultiANNInterpretedModel& interpretedModel, ANN& ann);
		/*Formats symbolic function of input state input*/
		std::string formatInputStateFunction(NeuronInterpretedModel& model, unsigned int nInput, char inputPrefix);
		/*Formats relation function*/
		std::string formatRelationFunction(NeuronInterpretedModel& model);
		/*Formats complementary relation fucntion*/
		std::string formatComplementingRelationFunction(NeuronInterpretedModel& model);
		/*Formats primary identity constant (i.e. in boolean domain for OR its is '0' for AND it is '1')*/
		std::string getPrimaryIdentityConstant(NeuronInterpretedModel& model);
		/*Formats the secondery identity function*/
		std::string getSeconderyIdentityConstant(NeuronInterpretedModel& model);
	};

//namespace L2{
//	class BooleanModelFormatter : public L2::ModelFormatter, L1::BooleanModelFormatter{
//	public:
//		BooleanModelFormatter() :L2::ModelFormatter(){};
//		BooleanModelFormatter(unsigned int param_inputs, GlobalTaxonomyScheme param_taxonomy) : L2::ModelFormatter(param_inputs, param_taxonomy){};
//		~BooleanModelFormatter(){};
//	public:
//		void alignInterpretedModelToANNStructure(MultiANNInterpretedModel& interpretedModel, ANN& ann){
//			for (unsigned int i = 0; i < interpretedModel.size(); i++)
//				L1::BooleanModelFormatter::alignInterpretedModelToANNStructure(interpretedModel[i], ann);
//		};
//	};
//}
}

#endif