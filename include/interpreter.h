#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include "nb_lib.h"
#include "NeuronRawModel.h"
#include "Taxonomy.h"
#include "LTM.h"

namespace NEUROBASE{
	namespace L1{
		/*Type:- Represents a cluster of bits in the NeuronRawModel related to one taxonomy*/
		typedef TVector<ClassDef> NeuronInterpretedSubModel;

		/*Type:- Represents neuron interpreted model*/
		typedef TVector<NeuronInterpretedSubModel> NeuronInterpretedSubModels;

		/*Includes interpreted model of neuron and 
		considers also topology details of neuron*/
		class NeuronInterpretedModel {
		public:
			NeuronInterpretedModel():TopologyModel() {};
			NeuronInterpretedModel(const NeuronInterpretedModel& other) {
				NeuronSubModels = other.NeuronSubModels;
				TopologyModel = other.TopologyModel;
				IgnoreMask = other.IgnoreMask;
			}
			~NeuronInterpretedModel() {};
		public:
			NeuronInterpretedSubModels NeuronSubModels;
			NeuronTopologyModel TopologyModel;
			ConnectionsIgnoreMask IgnoreMask;
		public:
			virtual std::string format() {
				return NeuronSubModels.format();
			}
		};

		/*Type:- Represents layer interpreted model*/
		class LayerInterpretedModel : public TVector<NeuronInterpretedModel> {
		public:
			LayerInterpretedModel() { num_inputs = 0; };
			///LayerInterpretedModel(unsigned int nInputs) { num_inputs = nInputs; };
			LayerInterpretedModel(const LayerInterpretedModel& other)
				:TVector<NeuronInterpretedModel>(other) { num_inputs = other.num_inputs; };
			~LayerInterpretedModel() {};
		private:
			/*In layer zero it is the number of network inputs, 
			other layers it is the number of previous layer nodes excluding bias*/
			unsigned int num_inputs;
		public:
			unsigned int getNumInputs() { return num_inputs; };
			void setNumInputs(unsigned int nInputs) { num_inputs = nInputs; };
		};

		/*Type:- Represents ANN interpreted model*/
		typedef TVector<LayerInterpretedModel> ANNInterpretedModel;
	}
	namespace L2{
		typedef TVector<ANNInterpretedModel> MultiANNInterpretedModel;
	}

	using namespace L0;
	using namespace L1;
	using namespace L2;
	/* Class: Interpreter

	Encapsulates interpretation logic of raw model to classes using defined taxonomy scheme
	*/
	class Interpreter
	{
	public:
		/*Default constructor*/
		Interpreter(){ maxNeuronInputs = 0; };
		/*Constructor using maximum number of neuron inputs*/
		Interpreter(unsigned int param_inputs):maxNeuronInputs(param_inputs){};
		/*Destructor*/
		~Interpreter(){};
	private:
		/*Maximum number of neuron inputs (Buswidth -1)*/
		unsigned int maxNeuronInputs;
	public:
		/*Interprets Raw neuron model to interpreted model*/
		NeuronInterpretedModel interpret(TaxonomyScheme& taxonomy, NeuronRawModel& model);
		/*Interprets layer neurons' raw models to interpreted models of these neurons*/
		LayerInterpretedModel interpret(TaxonomyScheme& taxonomy, LayerRawModel& model);
		/*Interprets ANN neurons' raw models to interpreted models of these neurons*/
		ANNInterpretedModel interpret(TaxonomyScheme& taxonomy, ANNRawModel& model);
		MultiANNInterpretedModel interpret(TaxonomyScheme& taxonomy, MultiANNRawModel& model);
		NeuronRawModel reverseInterpret(TaxonomyScheme& taxonomy, NeuronInterpretedModel& model);
		LayerRawModel reverseInterpret(TaxonomyScheme& taxonomy, LayerInterpretedModel& model);
		ANNRawModel reverseInterpret(TaxonomyScheme& taxonomy, ANNInterpretedModel& model);
		/*Interpret submodel of the neuron model (cluster of classes related to one taxonomy)*/
		NeuronInterpretedSubModel interpretInputTypeClasses(Taxonomy& taxonomy, NeuronRawModel& subModel);
		/*Computes required number of classes of certain taxonomy scheme*/
		unsigned int computeRequiredNeuronModelSize(TaxonomyScheme& taxonomy);
		unsigned int getMaxNeuronInputs(){ return maxNeuronInputs; };
	};
}
#endif