#ifndef __LTM_SEGMENT_H
#define __LTM_SEGMENT_H

#include "nb_lib.h"
#include "ANN.h"
#include "NeuronRawModel.h"

namespace NEUROBASE{
	namespace L1{
		typedef TMemoryItem<NeuronRawModel, CachableNeuron> LTMPair;
		class LTMCases : public TMemoryCases<LTMPair>{
		public:
			LTMCases(){};
			LTMCases(const LTMCases& other) :TMemoryCases<LTMPair>(other){};
			LTMCases(const TMemoryCases<LTMPair>& other) :TMemoryCases<LTMPair>(other){};
			~LTMCases(){};
		public:
			bool exists(NeuronRawModel& model){
				bool ret = false;
				for (unsigned int i = 0; i < size(); i++){
					bool eq = true;
					for (unsigned int j = 0; j < model.size(); j++){
						if (at(i).first.at(j) != model[j]){
							eq = false;
							break;
						}
					}
					if (eq){
						ret = true;
						break;
					}
				}
				return ret;
			};
			bool exists(Neuron& neuron){
				bool ret = false;
				for (unsigned int i = 0; i < size(); i++){
					bool eq = true;
					for (unsigned int j = 0; j < neuron.getNumConnections(); j++){
						if (at(i).second.getWeight(j) != neuron.getWeight(j)){
							eq = false;
							break;
						}
					}
					if (eq){
						ret = true;
						break;
					}
				}
				return ret;
			}
		};

		/* Class: LTMSegment

		Encapsulates Long Term Memory, it is composed of two memories Alpha and Beta. 
		Alpha neural network models neurons and returns Neuron Models (Raw models)
		and Beta neural network synthesis neurons from raw models
		*/
		class LTMSegment
		{
		public:
			/*Default constructor*/
			LTMSegment();
			LTMSegment(const LTMSegment& other);
			/*Constructor*/
			LTMSegment(L0::ANN alpha, L0::ANN beta);
			/*Destructor*/
			~LTMSegment();

		public:
			/*Used in boxing neuron weights. It is important for neuron synthesis by Beta ANN*/
			static const nb_type MAX_WEIGHT;
			/*Used in boxing neuron weights. It is important for neuron synthesis by Beta ANN*/
			static const nb_type MIN_WEIGHT;
			static const unsigned int MAX_EPOCHS_DEFAULT;
			static const unsigned int EPOCHS_BETWEEN_REPORTS_DEFAULT;
			static const nb_type DESIRED_ALPHA_ERROR_DEFAULT;
			static const nb_type DESIRED_BETA_ERROR_DEFAULT;

		private:
			/*maximum number of neuron's connections could be used in neuron modeling*/
			unsigned int busWidth;
			/*Number of neuron model classes*/
			unsigned int num_classes;
			/*Alpha and beta neural networks*/
			L0::ANN alpha, beta;
			unsigned int max_epochs; 
			unsigned int epochs_between_reports; 
			nb_type desired_alpha_error;
			nb_type desired_beta_error;

		public:
			/*Return LTM bus width: maximum number of neuron's connections couls be used in modeling*/
			unsigned int getBusWidth();
			/*Returns number of neuron model classes*/
			unsigned int getNumClasses();
			/*Creates LTM from files already saved*/
			bool createFromFiles(const std::string &alpha_file, const std::string &beta_file);
			void save(const std::string &alpha_file, const std::string &beta_file);
			void create(unsigned int busWidth, unsigned int NumClasses, std::vector<unsigned int>& hiddenLayers);
			/*Models neuron weights using alpha network*/
			NeuronRawModel const modelNeuron(L0::Neuron& neuron);
			/*synthesisize weights using beta network*/
			nb_vector const synthesisNeuronWeights(NeuronRawModel& model);
			/*Model neuron, then use resulted model in synthesising the same neuron again based on the model*/
			NeuronRawModel modelSynthesisNeuron(Neuron& neuron);
			/*Model every neuron in the layer*/
			LayerRawModel modelLayer(L0::Layer& layer);
			/*Model-Synthesis every neuron in the layer*/
			LayerRawModel modelSynthesisLayer(L0::Layer& layer);
			/*Model every neuron in the neural network*/
			ANNRawModel modelANN(L0::ANN& wm);
			/*Mode-Synthesis every neuron in the neural network*/
			ANNRawModel modelSynthesisANN(L0::ANN& wm);
			TrainingData convertAlphaCases(LTMCases& cases);
			TrainingData convertBetaCases(LTMCases& cases);
			void train(TrainingData &AlphaData, TrainingData &BetaData);
			void train(LTMCases& cases);
			void setMaxEpochs(unsigned int param_maxEpcohs){ max_epochs = param_maxEpcohs; };
			unsigned int getMaxEpochs(){ return max_epochs; };
			void setEpochsBetweenReports(unsigned int param_epochs){ epochs_between_reports = param_epochs; };
			unsigned int getEpochsBetweenReports(){ return epochs_between_reports; };
			void setAlphaDesiredError(nb_type err) { desired_alpha_error = err; };
			nb_type getAlphaDesiredError(){ return desired_alpha_error; };
			void setBetaDesiredError(nb_type err) { desired_beta_error = err; };
			nb_type getBetaDesiredError(){ return desired_beta_error; };
			ANN* getAlpha(){ return &alpha; };
			ANN* getBeta(){ return &beta; };

		private:
			/*Initializes LTM*/
			void init();
			/*adds neuron as a testing data for alpha neural network*/
			L0::TrainingData sampleNeuronWeights(L0::Neuron& neuron);
			L0::TrainingData sampleNeuronWeights(L0::Neuron& neuron, ConnectionsIgnoreMask& IgnoreMask);
				/*used to box the weights values between two constant values.*/
			nb_type getBoxedWeight(L0::Neuron& neuron, unsigned int nConnection);
			/*Apply boxing boundaries to a vector of weights*/
			void boxWeights(nb_vector weights);
			/*Adds neuron model to a testing data to be used in recalling beta neural network*/
			L0::TrainingData sampleModel(NeuronRawModel& model);
			/*Used to update the neuron weights from beta recall result*/
			void updateNeuronWeights(Neuron& neuron, const nb_vector weights);
			void updateNeuronWeights(Neuron& neuron, const nb_vector weights, ConnectionsIgnoreMask& IgnoreMask);
		};
	}
}
#endif