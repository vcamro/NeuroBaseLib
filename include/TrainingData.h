#ifndef __TRAINING_DATA_H
#define __TRAINING_DATA_H

#include "nb_lib.h"

namespace NEUROBASE{
	namespace L0{
		/* Class: TrainingData

		Encapsulation training data, it is used also for recall (or testing/using neural network)
		*/
		class TrainingData : public FANN::training_data
		{
		public:
			/*Default constructor*/
			TrainingData() :training_data(){};
			/*Copy constructor*/
			TrainingData(const TrainingData &data) : training_data(data){};
			/*Constructor*/
			TrainingData(unsigned int num_data, unsigned int num_input, unsigned int num_output);
			/*Destructor*/
			~TrainingData();

		public:
			/*Load train data from previously saved file*/
			bool readTrainFromFile(const std::string &filename);
			/*Saves train data to a file*/
			bool save(const std::string &filename);
			/*Randomizes the order of training data, 
			This is recommended for incremental training, while it have no influence during batch training*/
			void shuffle();
			/*Merges the train data to this train data*/
			void merge(const training_data &data);
			/*Returns number of patterns*/
			unsigned int length();
			/*Returns number of inputs*/
			unsigned int numInput();
			/*Returns number of putputs*/
			unsigned int numOutput();
			/*Returns inputs array*/
			nb_type** getInputs();
			/*Returns outputs array*/
			nb_type** getOutputs();
			/*Returns inputs array of specific sample*/
			nb_type* getSampleInputs(unsigned int nSample);
			/*Copies inputs array of specififc sample*/
			void setSampleInputs(unsigned int nSample, const nb_type* sampleInputs);
			/*Returns outputs array of a specific sample*/
			nb_type* getSampleOutputs(unsigned int nSample);
			/*Copies outputs array of a specific sample*/
			void setSampleOutputs(unsigned int nSample, const nb_type* sampleOutputs);
			/*Copies specific sampl inputs and outputs*/
			void setSampleData(unsigned int nSample, const nb_type* sampleInputs, const nb_type* sampleOutputs);
			/*Copies specific sampl inputs and outputs, input array is assumed to include inputs then outputs*/
			void setSampleData(unsigned int nSample, const nb_type* sampleData);
			/*Copies inputs and outputs, input array is assumed to include inputs then outputs of every sample*/
			void setSamplesData(const nb_type* data);
			/*re-allocates and set train data*/
			void setTrainData(unsigned int num_data,
				unsigned int num_input, nb_type **input,
				unsigned int num_output, nb_type **output);
			/*Sets specific sample specific input value*/
			void setSampleInput(unsigned int nSample, unsigned int nInput, nb_type input);
			/*Sets specific sample specifc output value*/
			void setSampleOutput(unsigned int nSample, unsigned int nOutput, nb_type output);
			/*Re-acclocates train data*/
			void allocateTrainData(unsigned int num_data, unsigned int num_input, unsigned int num_output);
			//void destroyData();
			/*Assignment operator*/
			TrainingData& operator=(TrainingData& other);
			/*Equal operator*/
			bool operator==(TrainingData& other);
			nb_type getMSE(TrainingData& other);
			/*Prints train data values to standard output*/
			void print();
		};
	}
}

#endif