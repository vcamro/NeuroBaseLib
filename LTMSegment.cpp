#include "LTMSegment.h"
#include "Layer.h"

namespace NEUROBASE{
	namespace L1{
		LTMSegment::LTMSegment() :
			alpha(), 
			beta(),
			busWidth(0),
			num_classes(0),
			max_epochs(MAX_EPOCHS_DEFAULT),
			epochs_between_reports(EPOCHS_BETWEEN_REPORTS_DEFAULT),
			desired_alpha_error(DESIRED_ALPHA_ERROR_DEFAULT),
			desired_beta_error(DESIRED_BETA_ERROR_DEFAULT){
			}
		LTMSegment::LTMSegment(const LTMSegment& other) :
			alpha(other.alpha),
			beta(other.beta),
			busWidth(other.busWidth),
			num_classes(other.num_classes),
			max_epochs(other.max_epochs),
			epochs_between_reports(other.epochs_between_reports),
			desired_alpha_error(other.desired_alpha_error),
			desired_beta_error(other.desired_beta_error)
		{
		};
		LTMSegment::LTMSegment(L0::ANN param_alpha, L0::ANN param_beta) : alpha(param_alpha), beta(param_beta){
			init();
		}
		LTMSegment::~LTMSegment(){}

		const nb_type LTMSegment::MAX_WEIGHT = 50.0f;
		const nb_type LTMSegment::MIN_WEIGHT = -50.0f;
		const unsigned int LTMSegment::MAX_EPOCHS_DEFAULT = /*1000*/5000;
		const unsigned int LTMSegment::EPOCHS_BETWEEN_REPORTS_DEFAULT = 100;
		const nb_type LTMSegment::DESIRED_ALPHA_ERROR_DEFAULT = 0.002f;
		const nb_type LTMSegment::DESIRED_BETA_ERROR_DEFAULT = 2.0f;
		//const std::string LTMSegment::ALPHA_NAME_STRING = "alpha";
		//const std::string LTMSegment::BETA_NAME_STRING = "beta";

		void LTMSegment::init(){
			if (alpha.getNumInputs() != beta.getNumOutputs())
				throw nb_exception("alpha ANN number of inputs should equal to beta ANN number of outputs");
			else
				busWidth = alpha.getNumInputs();

			if (alpha.getNumOutputs() != beta.getNumInputs())
				throw nb_exception("alpha ANN number of outputs should equal to beta ANN number of inputs");
			else
				num_classes = beta.getNumInputs();

			max_epochs = MAX_EPOCHS_DEFAULT;
			epochs_between_reports = EPOCHS_BETWEEN_REPORTS_DEFAULT;
			desired_alpha_error = DESIRED_ALPHA_ERROR_DEFAULT;
			desired_beta_error = DESIRED_BETA_ERROR_DEFAULT;
		}

		bool LTMSegment::createFromFiles(const std::string &alpha_file, const std::string &beta_file){
			bool bAlpha = alpha.createFromFile(alpha_file);
			bool bBeta = beta.createFromFile(beta_file);
			if (bAlpha && bBeta)
				init();
			return bAlpha && bBeta;
		}

		void LTMSegment::create(unsigned int busWidth_param, unsigned int NumClasses_param, std::vector<unsigned int>& hiddenLayers){
			std::vector<unsigned int> alphaLayers;
			std::vector<unsigned int> betaLayers;
			alphaLayers.push_back(busWidth_param);
			betaLayers.push_back(NumClasses_param);
			busWidth = busWidth_param;
			num_classes = NumClasses_param;
			for (unsigned int i = 0; i < hiddenLayers.size(); i++){
				alphaLayers.push_back(hiddenLayers[i]);
				betaLayers.push_back(hiddenLayers[i]);
			}
			alphaLayers.push_back(NumClasses_param);
			betaLayers.push_back(busWidth_param);
			alpha.destroy();
			beta.destroy();
			if (!alpha.create(alphaLayers))
				throw nb_exception("alpha network is not created successfully");
			if (!beta.create(betaLayers))
				throw nb_exception("beta network is not created successfully");
			alpha.setActivationFunctionOutput(nb_activationfunc_enum::FANN_SIGMOID);
			beta.setActivationFunctionOutput(nb_activationfunc_enum::FANN_LINEAR);
			alpha.setTrainingAlgorithm(nb_train_enum::FANN_TRAIN_RPROP);
			beta.setTrainingAlgorithm(nb_train_enum::FANN_TRAIN_RPROP);
		}

		unsigned int LTMSegment::getBusWidth(){
			return busWidth;
		}

		unsigned int LTMSegment::getNumClasses(){
			return num_classes;
		}

		NeuronRawModel const LTMSegment::modelNeuron(L0::Neuron& neuron){
			ConnectionsIgnoreMask IgnoreMask;
			IgnoreMask.fill(neuron, getBusWidth());
			L0::TrainingData sample = sampleNeuronWeights(neuron, IgnoreMask);
			NeuronRawModel ret(alpha.run(sample.getInputs()[0]), getNumClasses(), neuron);
			ret.IgnoreMask = IgnoreMask;
			return ret;
		}

		L0::TrainingData LTMSegment::sampleNeuronWeights(L0::Neuron& neuron){
			if (neuron.getNumConnections() > busWidth)
				throw nb_exception("Number of neuron connections should be less than LTM bus width");
			unsigned int neuronConnections = neuron.getNumConnections();
			L0::TrainingData sample(L0::TrainingData(1, busWidth, num_classes));
			for (unsigned int i = 0; i < neuronConnections-1; i++)
				sample.setSampleInput(0, i, getBoxedWeight(neuron, i));
			for (unsigned int i = neuronConnections-1; i < busWidth-1; i++)
				sample.setSampleInput(0, i, 0.0f);
			sample.setSampleInput(0, busWidth - 1, getBoxedWeight(neuron, neuronConnections - 1));
			return sample;
		}

		L0::TrainingData LTMSegment::sampleNeuronWeights(L0::Neuron& neuron, ConnectionsIgnoreMask& IgnoreMask) {
			if (IgnoreMask.size() != neuron.getNumConnections() - 1)
				throw nb_exception("Number of neuron inputs should be the same length of ignore mask");
			unsigned int neuronConnections = neuron.getNumConnections();
			L0::TrainingData sample(L0::TrainingData(1, busWidth, num_classes));
			unsigned int nInput = 0;
			for (unsigned int i = 0; i < neuronConnections - 1; i++) {
				if (!IgnoreMask[i]) {
					sample.setSampleInput(0, nInput, getBoxedWeight(neuron, i));
					nInput++;
				}
			}
			for (unsigned int i = nInput; i < busWidth - 1; i++)
				sample.setSampleInput(0, i, 0.0f);
			sample.setSampleInput(0, busWidth - 1, getBoxedWeight(neuron, neuronConnections - 1));
			return sample;
		}

		nb_type LTMSegment::getBoxedWeight(L0::Neuron& neuron, unsigned int nConnection){
			nb_type boxedWeight = neuron.getWeight(nConnection);
			if (boxedWeight > MAX_WEIGHT)
				boxedWeight = MAX_WEIGHT;
			else if (boxedWeight < MIN_WEIGHT)
				boxedWeight = MIN_WEIGHT;
			return boxedWeight;
		}

		void LTMSegment::boxWeights(nb_vector weights){
			for (unsigned int i = 0; i < weights.size(); i++){
				if (weights[i] > MAX_WEIGHT)
					weights[i] = MAX_WEIGHT;
				else if (weights[i] < MIN_WEIGHT)
					weights[i] = MIN_WEIGHT;
			}
			return;
		}

		nb_vector const LTMSegment::synthesisNeuronWeights(NeuronRawModel& model){
			L0::TrainingData sample = sampleModel(model);
			nb_type* pWeights = beta.run(sample.getInputs()[0]);
			nb_vector ret(pWeights, pWeights + getBusWidth());
			boxWeights(ret);
			return ret;
		};

		L0::TrainingData LTMSegment::sampleModel(NeuronRawModel& model){
			if (model.getNumClasses() != num_classes)
				throw nb_exception("Number of model classes should equal to LTM supported number of classes");
			L0::TrainingData sample(1, num_classes, busWidth);
			for (unsigned int i = 0; i < num_classes; i++)
				sample.setSampleInput(0, i, model[i]);
			return sample;
		}

		void LTMSegment::updateNeuronWeights(Neuron& neuron, const nb_vector weights){
			if (weights.size() != getBusWidth())
				throw nb_exception("Synthesized weights count should be equal to bus width");
			if (neuron.getNumConnections() > weights.size())
				throw nb_exception("Number of neuron connections should be less than or equal synthesised weights");
			unsigned int nConn = neuron.getNumConnections();
			for (unsigned int i = 0; i < nConn - 1; i++)
				neuron.setWeight(i, weights[i]);
			neuron.setWeight(nConn-1, weights[busWidth-1]);
			return;
		}

		void LTMSegment::updateNeuronWeights(Neuron& neuron, const nb_vector weights, ConnectionsIgnoreMask& IgnoreMask) {
			if (weights.size() != getBusWidth())
				throw nb_exception("Synthesized weights count should be equal to bus width");
			if (IgnoreMask.size() != neuron.getNumConnections()-1)
				throw nb_exception("Size of ignoring mask should be the same as number of neuron input connections");
			if (neuron.getNumConnections()-IgnoreMask.getNumIgnored() > weights.size())
				throw nb_exception("Number of non ignored neuron connections should be less than or equal synthesised weights");
			unsigned int nConn = neuron.getNumConnections();
			unsigned int w = 0;
			for (unsigned int i = 0; i < nConn - 1; i++) {
				if (!IgnoreMask[i]) {
					neuron.setWeight(i, weights[w]);
					w++;
				}
				else
					neuron.setWeight(i, 0.0f);
			}
			neuron.setWeight(nConn - 1, weights[busWidth - 1]);
		}

		NeuronRawModel LTMSegment::modelSynthesisNeuron(Neuron& neuron){
			NeuronRawModel model = modelNeuron(neuron);
			updateNeuronWeights(neuron, synthesisNeuronWeights(model), model.IgnoreMask);
			return model;
		}

		LayerRawModel LTMSegment::modelLayer(L0::Layer& layer){
			LayerRawModel ret;
			ret.setNumInputs(layer.getNumInputs());
			//if (layer.getLayerIndex() == 0)
			//	ret.setNumInputs(layer.getHandle()->getParentObject()->num_input);
			//else
			//	ret.setNumInputs(Layer(layer.getPrev()).getNumNeurons()-1);
			unsigned int nNeurons = layer.getNumNeurons();
			for (unsigned int i = 0; i < nNeurons; i++){
				Neuron neuron = layer[i];
				if (neuron.isNode())
					ret.push_back(modelNeuron(neuron));
			}
			return ret;
		}

		LayerRawModel LTMSegment::modelSynthesisLayer(L0::Layer& layer){
			LayerRawModel ret;
			ret.setNumInputs(layer.getNumInputs());
			//if (layer.getLayerIndex() == 0)
			//	ret.setNumInputs(layer.getHandle()->getParentObject()->num_input);
			//else
			//	ret.setNumInputs(Layer(layer.getPrev()).getNumNeurons());
			unsigned int nNeurons = layer.getNumNeurons();
			for (unsigned int i = 0; i < nNeurons; i++){
				Neuron neuron = layer[i];
				if (neuron.isNode())
					ret.push_back(modelSynthesisNeuron(neuron));
			}
			return ret;
		}

		ANNRawModel LTMSegment::modelANN(L0::ANN& wm){
			ANNRawModel ret;
			unsigned int nLayers = wm.getNumLayers();
			for (unsigned int i = 0; i < nLayers; i++){
				LayerRawModel LayerModel = modelLayer(wm[i]);
				ret.push_back(LayerModel);
			}
			return ret;
		}

		ANNRawModel LTMSegment::modelSynthesisANN(L0::ANN& wm){
			ANNRawModel ret;
			unsigned int nLayers = wm.getNumLayers();
			for (unsigned int i = 0; i < nLayers; i++){
				LayerRawModel LayerModel = modelSynthesisLayer(wm[i]);
				ret.push_back(LayerModel);
			}
			return ret;
		}

		TrainingData LTMSegment::convertAlphaCases(LTMCases& cases){
			TrainingData ret(cases.size(), getBusWidth(), getNumClasses());
			for (unsigned int i = 0; i < cases.size(); i++){
				if (cases[i].first.IgnoreMask.size() - cases[i].first.IgnoreMask.getNumIgnored() > getBusWidth() - 1)
					throw nb_exception("Total non ignored inputs must be less than bus width");
				unsigned int nTotalInputs = cases[i].first.IgnoreMask.size();
				unsigned int nConn = 0;

				//Weights
				// Busy weights
				for (unsigned int j = 0; j < nTotalInputs; j++)
					if (!cases[i].first.IgnoreMask[j]) { // If not ignored
						ret.getSampleInputs(i)[nConn] = getBoxedWeight(cases[i].second, j);
						nConn++;
					}
				// Empty weights
				for (unsigned int j=nConn; j < getBusWidth()-1; j++)
					ret.getSampleInputs(i)[j] = 0;
				// Bias weight
				ret.getSampleInputs(i)[getBusWidth() - 1] = getBoxedWeight(cases[i].second, cases[i].second.getNumConnections() - 1);


				//Classes
				for (unsigned int k = 0; k < getNumClasses(); k++)
					ret.getSampleOutputs(i)[k] = cases[i].first[k];
			}
			return ret;
		}

		TrainingData LTMSegment::convertBetaCases(LTMCases& cases){
			TrainingData ret(cases.size(), getNumClasses(), getBusWidth());
			for (unsigned int i = 0; i < cases.size(); i++){
				if (cases[i].first.IgnoreMask.size() - cases[i].first.IgnoreMask.getNumIgnored() > getBusWidth() - 1)
					throw nb_exception("Total non ignored inputs must be less than bus width");
				unsigned int nTotalInputs = cases[i].first.IgnoreMask.size();
				unsigned int nConn = 0;
				//Classes
				for (unsigned int j = 0; j < getNumClasses(); j++)
					ret.getSampleInputs(i)[j] = cases[i].first[j];

				//Weights
				// Busy weights
				for (unsigned int k = 0; k < nTotalInputs; k++)
					if (!cases[i].first.IgnoreMask[k]) { // If not ignored
						ret.getSampleOutputs(i)[nConn] = getBoxedWeight(cases[i].second, k);
						nConn++;
					}
				// Empty weights
				for (unsigned int k = nConn; k < getBusWidth() - 1; k++)
					ret.getSampleInputs(i)[k] = 0;
				// Bias weight
				ret.getSampleInputs(i)[getBusWidth() - 1] = getBoxedWeight(cases[i].second, cases[i].second.getNumConnections() - 1);
			}
			return ret;
		}

		void LTMSegment::train(TrainingData &AlphaData, TrainingData &BetaData){
			alpha.trainOnData(AlphaData, max_epochs, epochs_between_reports, desired_alpha_error);
			beta.trainOnData(BetaData, max_epochs, epochs_between_reports, desired_beta_error);
		}

		void LTMSegment::train(LTMCases& cases){
			TrainingData AlphaData = convertAlphaCases(cases);
			TrainingData BetaData = convertBetaCases(cases);
			train(AlphaData, BetaData);
		}

		void LTMSegment::save(const std::string &alpha_file, const std::string &beta_file){
			alpha.save(alpha_file);
			beta.save(beta_file);
		}
	}
}