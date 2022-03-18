#ifndef __ANN_H
#define __ANN_H

#include "nb_lib.h"
#include "Layer.h"
#include "TrainingData.h"

namespace NEUROBASE{
	namespace L0{
		/* Class: ANN

		Encapsulation of a neural network
		*/
		class ANN : FANN::neural_net{
		public:
			typedef THandle<fann> ANN_HANDLE_TYPE;
		public:
			/*Default constructor*/
			ANN() :neural_net(){};

			/*Copy constructor, creates a network clone*/
			ANN(const ANN& other){
				ann = NULL;
				copy_from_struct_fann(other.ann);
			};

			/*Constructor attaches an ANN for a fann structure, 
			it has to be dettached after usage using deattach or fann will be destroyed in destructor*/
			ANN(ANN_HANDLE_TYPE* handle) {
				ann = handle->getParentObject();
				delete handle;
			}

			~ANN(){ if (ann) fann_set_user_data(ann, NULL); };
		private:
			unsigned int LastEpochs;
		public:
			/*Enables callback on this network*/
			void enableCallback();

			/*Returns number of layers*/
			unsigned int getNumLayers();

			/*Returns number of inputs*/
			unsigned int getNumInputs();

			/*Returns number of outputs*/
			unsigned int getNumOutputs();

			/*Returns total number of neurons*/
			unsigned int getTotalNeurons();

			/*Counts the node neurons (neurons with non-zero number of connections)*/
			unsigned int getNumNodes();

			/*Returns total number of connections*/
			unsigned int getTotalConnections();

			/*Sets activation function of output layer*/
			void setActivationFunctionOutput(nb_activationfunc_enum activationFunc);

			/*Sets training algorithm*/
			void setTrainingAlgorithm(nb_train_enum training_algorithm);

			/*Gets training algorithm*/
			nb_train_enum getTrainingAlgorithm();

			/*Get MSE*/
			float getMSE();

			/*Get Bit fail*/
			unsigned int getBitFail();

			/*Creates fully connected MLP ANN - uses array of layer sizes*/
			bool createStandardArray(unsigned int num_layers, const unsigned int * layers);

			/*Creates fully connected MLP ANN - uses vector of layer sizes*/
			bool create(std::vector<unsigned int>& Layers);

			/*Creates partially connected ANN with ANN global connection ratio*/
			bool createSparseArray(float connection_rate, unsigned int num_layers, const unsigned int *layers);

			/*Creates partially connected ANN with hetergeneous layer specific connection ratios*/
			bool createSparseHeterogeneousArray(float* connection_rates, unsigned int num_layers, const unsigned int *layers);

			void destroy();

			/*Recalls ANN*/
			nb_type* run(nb_type *input);
			void run(TrainingData& testData);

			/*Randomize weights values*/
			void randomizeWeights(nb_type min_weight, nb_type max_weight);

			/*Reinitialize weights based on training values*/
			void initWeights(const TrainingData &data);

			/*Print connections*/
			void printConnections();

			/*Create the ANN from a previously saved file*/
			bool createFromFile(const std::string &configuration_file);

			/*Save file ANN to fann format config file*/
			bool save(const std::string &configuration_file);

			/*Saves ANN to format created in format method*/
			bool save(std::ofstream& out);

			/*Train network using one sample input and output arrays for one epoch, using back propagation algorithm*/
			void train(nb_type *input, nb_type *desired_output);

			/*Train one epoch*/
			float trainEpoch(const TrainingData &data);

			/*Trains neural network until desired error or max epochs*/
			void trainOnData(const TrainingData &data, unsigned int max_epochs,
					unsigned int epochs_between_reports, float desired_error);

			unsigned int getLastEpochs(){ return LastEpochs; };

			/*Formats internal ANN data in string*/
			virtual std::string format();

			/*Prints neural network neurons connections*/
			void print();

			void saveLog(std::string FileName);

			/*Default callback function*/
			static int __stdcall internal_callback(struct fann *ann, struct fann_train_data *train,
				unsigned int max_epochs, unsigned int epochs_between_reports,
				float desired_error, unsigned int epochs);
			virtual int onReportBetweenEpochs(ANN& pANN, unsigned int max_epochs, unsigned int epochs_between_reports, 
				nb_type desired_error, unsigned int epochs);

			/*De-attach fann struct from the object*/
			void deattach() { ann = NULL; };

		public:
			/*Returns specific layer*/
			Layer getLayer(unsigned int nLayer);
			/*Returns specific layer*/
			Layer operator [](unsigned int nLayer);
			/*Returns input layer*/
			Layer getInputLayer();
			/*Returns output layer*/
			Layer getOutputLayer();
		};
	}
}

#endif