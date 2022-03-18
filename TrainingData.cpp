#include "TrainingData.h"


namespace NEUROBASE{
	namespace L0{
		TrainingData::TrainingData(unsigned int num_data, unsigned int num_input, unsigned int num_output){
			allocateTrainData(num_data, num_input, num_output);
		}
		TrainingData::~TrainingData(){
			//destroyData();
		};
		bool TrainingData::readTrainFromFile(const std::string &filename){
			return read_train_from_file(filename);
		}

		bool TrainingData::save(const std::string &filename){
			return save_train(filename);
		}

		void TrainingData::shuffle(){
			return shuffle_train_data();
		}

		void TrainingData::merge(const training_data &data){
			return merge_train_data(data);
		}

		unsigned int TrainingData::length(){
			return length_train_data();
		}

		unsigned int TrainingData::numInput(){
			return num_input_train_data();
		}

		unsigned int TrainingData::numOutput(){
			return num_output_train_data();
		}

		nb_type** TrainingData::getInputs(){
			return train_data->input;
		}

		nb_type** TrainingData::getOutputs(){
			return train_data->output;
		}

		nb_type* TrainingData::getSampleInputs(unsigned int nSample){
			if (nSample >= train_data->num_data)
				throw nb_exception("sample index should be within allocated samples range");
			return train_data->input[nSample];
		}

		void TrainingData::setSampleInputs(unsigned int nSample, const nb_type* sampleInputs){
			if (nSample >= train_data->num_data)
				throw nb_exception("sample index should be within allocated samples range");
			memcpy(train_data->input[nSample], sampleInputs, train_data->num_input*sizeof(nb_type));
			return;
		}

		nb_type* TrainingData::getSampleOutputs(unsigned int nSample){
			if (nSample >= train_data->num_data)
				throw nb_exception("sample index should be within allocated samples range");
			return train_data->output[nSample];
		}

		void TrainingData::setSampleOutputs(unsigned int nSample, const nb_type* sampleOutputs){
			if (nSample >= train_data->num_data)
				throw nb_exception("sample index should be within allocated samples range");
			memcpy(train_data->output[nSample], sampleOutputs, train_data->num_output*sizeof(nb_type));
			return;
		}

		void TrainingData::setSampleData(unsigned int nSample, const nb_type* sampleInputs, const nb_type* sampleOutputs){
			setSampleInputs(nSample, sampleInputs);
			setSampleOutputs(nSample, sampleOutputs);
			return;
		}

		void TrainingData::setSampleData(unsigned int nSample, const nb_type* sampleData){
			setSampleData(nSample, sampleData, &sampleData[train_data->num_input]);
		}

		void TrainingData::setSamplesData(const nb_type* data){
			for (unsigned int i = 0; i < train_data->num_data; i++)
				setSampleData(i, &data[i * (train_data->num_input + train_data->num_output)]);
		}

		void TrainingData::setTrainData(unsigned int num_data,
			unsigned int num_input, nb_type **input,
			unsigned int num_output, nb_type **output){
			return set_train_data(num_data, num_input, input, num_output, output);
		}

		void TrainingData::setSampleInput(unsigned int nSample, unsigned int nInput, nb_type input){
			train_data->input[nSample][nInput] = input;
		}

		void TrainingData::setSampleOutput(unsigned int nSample, unsigned int nOutput, nb_type output){
			train_data->output[nSample][nOutput] = output;
		}

		void TrainingData::allocateTrainData(unsigned int num_data, unsigned int num_input, unsigned int num_output){
			nb_type** input = (nb_type**)calloc(num_data, sizeof(nb_type*));
			input[0] = (nb_type*)calloc(num_data * num_input, sizeof(nb_type));
			for (unsigned int i = 0; i < num_data; i++)
				input[i] = input[0] + (i*num_input);
			nb_type** output = (nb_type**)calloc(num_data, sizeof(nb_type*));
			output[0] = (nb_type*)calloc(num_data * num_output, sizeof(nb_type));
			for (unsigned int i = 0; i < num_data; i++)
				output[i] = output[0] + (i*num_output);

			destroy_train();
			train_data = (fann_train_data*)calloc(1, sizeof(fann_train_data));
			train_data->num_data = num_data;
			train_data->num_input = num_input;
			train_data->num_output = num_output;
			train_data->input = input;
			train_data->output = output;
			return;
		}

		//void TrainingData::destroyData()
		//{
		//	if (train_data != NULL)
		//	{
		//		if (train_data->input){
		//			if (train_data->input[0])
		//				free(train_data->input[0]);
		//			free(train_data->input);
		//		}
		//		if (train_data->output){
		//			if (train_data->output[0])
		//				free(train_data->output[0]);
		//			free(train_data->output);
		//		}
		//		free(train_data);
		//		train_data = NULL;
		//	}
		//}

		void TrainingData::print(){
			for (unsigned int i = 0; i < train_data->num_data; i++){
				for (unsigned int j = 0; j < train_data->num_input; j++)
					printf("%f, ", train_data->input[i][j]);
				printf(" || ");
				for (unsigned int j = 0; j < train_data->num_output; j++)
					printf("%f, ", train_data->output[i][j]);
				printf("\n");
			}
		}
		TrainingData& TrainingData::operator=(TrainingData& other){
			if (this != &other){
				destroy_train();
				if (other.train_data != NULL)
					train_data = fann_duplicate_train_data(other.train_data);
			}
			return *this;
		}
		bool TrainingData::operator == (TrainingData& other){
			if (numInput() == other.numInput()){
				if (numOutput() == other.numOutput()){
					if (length() == other.length()){
						for (unsigned int i = 0; i < length(); i++){
							for (unsigned int j = 0; j < numInput(); j++){
								if (getSampleInputs(i)[j] != other.getSampleInputs(i)[j])
									return false;
							}
							for (unsigned int k = 0; k < numOutput(); k++){
								if (getSampleOutputs(i)[k] != other.getSampleOutputs(i)[k])
									return false;
							}
						}
					}
					else return false;
				}
				else return false;
			}
			else return false;
			return true;
		}
		nb_type TrainingData::getMSE(TrainingData& other){
			if (numInput() != other.numInput())
				throw nb_exception("Number of inputs should be equal of both training data");
			if (numOutput() != other.numOutput())
				throw nb_exception("Number of outputs should be equal of both training data");
			if (length() != other.length())
				throw nb_exception("Number of samples should be equal of both training data");
			nb_type MSE = 0.0f;
			for (unsigned int i = 0; i < length(); i++){
				for (unsigned int j = 0; j < numInput(); j++){
					if (getSampleInputs(i)[j] != other.getSampleInputs(i)[j])
						throw nb_exception("values of inputs of both training data obejects should be the same values in the same order");
				}
				for (unsigned int k = 0; k < numOutput(); k++)
					MSE += (getSampleOutputs(i)[k] - other.getSampleOutputs(i)[k]) * (getSampleOutputs(i)[k] - other.getSampleOutputs(i)[k]);
			}
			return MSE;
		}
	}
}