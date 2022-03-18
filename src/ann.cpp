#include "ANN.h"
#include "Layer.h"

namespace NEUROBASE{
	namespace L0{
		unsigned int ANN::getNumLayers(){
			return get_num_layers();
		}

		unsigned int ANN::getNumInputs(){
			return get_num_input();
		}
		
		unsigned int ANN::getNumOutputs(){
			return get_num_output();
		}

		unsigned int ANN::getTotalNeurons(){
			return get_total_neurons();
		}

		unsigned int ANN::getNumNodes(){
			unsigned int ret = 0;
			for (unsigned int i = 0; i < getNumLayers(); i++)
				ret += getLayer(i).getNumNodes();
			return ret;
		}

		unsigned int ANN::getTotalConnections(){
			return get_total_connections();
		}

		float ANN::getMSE(){
			return get_MSE();
		}

		unsigned int ANN::getBitFail() {
			return get_bit_fail();
		}

		void ANN::enableCallback(){
			fann_set_user_data(ann, this);
			fann_set_callback(ann, ANN::internal_callback);
		}

		void ANN::setTrainingAlgorithm(nb_train_enum training_algorithm){
			set_training_algorithm((FANN::training_algorithm_enum)training_algorithm);
			return;
		}

		nb_train_enum ANN::getTrainingAlgorithm(){
			return (nb_train_enum)get_training_algorithm();
		}

		Layer ANN::getLayer(unsigned int nLayer){
			return new Layer::HANDLE_TYPE(ann, ann->first_layer + nLayer);
		}

		Layer ANN::getInputLayer(){
			return getLayer(0);
		}

		Layer ANN::getOutputLayer(){
			return getLayer(getNumLayers()-1);
		}

		Layer ANN::operator [](unsigned int nLayer){
			return getLayer(nLayer);
		}

		bool ANN::createStandardArray(unsigned int num_layers, const unsigned int * layers){
			bool bRet = create_standard_array(num_layers, layers);
			set_train_error_function(FANN::ERRORFUNC_LINEAR);
			return bRet;
		}

		bool ANN::create(std::vector<unsigned int>& layers){
			return createStandardArray(layers.size(), layers.data());
		}

		bool ANN::createSparseArray(float connection_rate, unsigned int num_layers, const unsigned int *layers) {
			bool bRet = create_sparse_array(connection_rate, num_layers, layers);
			set_train_error_function(FANN::ERRORFUNC_LINEAR);
			return bRet;
		}

		bool ANN::createSparseHeterogeneousArray(float* connection_rates, unsigned int num_layers, const unsigned int *layers) {
			destroy();
			ann = fann_create_sparse_heterogeneous_array(connection_rates, num_layers, layers);
			set_train_error_function(FANN::ERRORFUNC_LINEAR);
			return (ann != NULL);
		}

		void ANN::destroy(){
			FANN::neural_net::destroy();
		}

		nb_type* ANN::run(nb_type *input){
			return neural_net::run(input);
		}
		void ANN::run(TrainingData& testData){
			if (testData.numInput() != getNumInputs())
				throw nb_exception("testing patterns and neural network should have the same number of inputs");
			for (unsigned int i = 0; i < testData.length(); i++)
				memcpy(testData.getSampleOutputs(i), run(testData.getSampleInputs(i)), sizeof(nb_type)*testData.numOutput());
		}

		void ANN::initWeights(const TrainingData &data){
			return init_weights(data);
		}

		void ANN::randomizeWeights(nb_type min_weight, nb_type max_weight){
			return randomize_weights(min_weight, max_weight);
		}

		void ANN::printConnections(){
			return print_connections();
		}

		bool ANN::createFromFile(const std::string &configuration_file){
			return create_from_file(configuration_file);
		}

		bool ANN::save(const std::string &configuration_file){
			return neural_net::save(configuration_file);
		}

		bool ANN::save(std::ofstream& out) {
			out << format();
			return true;
		}

		void ANN::train(nb_type *input, nb_type *desired_output){
			return neural_net::train(input, desired_output);
		}

		float ANN::trainEpoch(const TrainingData &data){
			return train_epoch(data);
		}

		void ANN::trainOnData(const TrainingData &data, unsigned int max_epochs,
			unsigned int epochs_between_reports, float desired_error){
			return train_on_data(data, max_epochs, epochs_between_reports, desired_error);
		}

		void ANN::setActivationFunctionOutput(nb_activationfunc_enum activationFunc){
			Layer(getOutputLayer()).setActivationFunction(activationFunc);
		}

		std::string ANN::format(){
			std::string ret;
			unsigned int nLayers = getNumLayers();
			for (unsigned int i = 0; i < nLayers; i++)
				ret += getLayer(i).format();
			return ret;
		}

		void ANN::print(){ printf(format().data()); };

		void ANN::saveLog(std::string FileName){
			std::ofstream out(FileName);
			out << format();
			out.close();
		}

		int __stdcall ANN::internal_callback(struct fann *ann, struct fann_train_data *train,
			unsigned int max_epochs, unsigned int epochs_between_reports,
			float desired_error, unsigned int epochs){
			printf("Epochs, %8d, Current error, %.10f, Bit fail, %d.\n", epochs, ann->MSE_value, ann->num_bit_fail);
			ANN* pANN = (ANN*)fann_get_user_data(ann);
			if (pANN != NULL)
				return pANN->onReportBetweenEpochs(*pANN, max_epochs, epochs_between_reports, desired_error, epochs);
			return 0;
		}
		int ANN::onReportBetweenEpochs(ANN& pANN, unsigned int max_epochs, unsigned int epochs_between_reports,
			nb_type desired_error, unsigned int epochs){
			LastEpochs = epochs;
			return 0;
		}
	}
}