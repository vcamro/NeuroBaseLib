#include "Neuron.h"
#include "ann.h"

namespace NEUROBASE{
	namespace L0{
		unsigned int Neuron::getNumConnections(){
			return handle->getObject()->last_con - handle->getObject()->first_con;
		}

		Neuron Neuron::getConnection(unsigned int nConnection){
			unsigned int nConn = handle->getObject()->first_con + nConnection;
			return new HANDLE_TYPE(this->handle->getParentObject(), handle->getParentObject()->connections[nConn]);
		}


		void Neuron::setConnection(unsigned int nConnection, Neuron& neuron) {
			unsigned int nConn = handle->getObject()->first_con + nConnection;
			handle->getParentObject()->connections[nConn] = neuron.getHandle()->getObject();
		}


		unsigned int Neuron::getLayerIndex()
		{
			fann* ann = handle->getParentObject();
			fann_neuron* neuron = handle->getObject();
			unsigned int nLayers = fann_get_num_layers(ann);
			for (fann_layer* layer = ann->first_layer; layer < ann->last_layer; layer++) {
				if (neuron >= layer->first_neuron && neuron < layer->last_neuron)
					return layer - ann->first_layer;
			}
			return (unsigned int) -1;
		}

		Layer Neuron::getLayer()
		{
			unsigned int iLayer = getLayerIndex();
			fann* ann = handle->getParentObject();
			return Layer(new Layer::HANDLE_TYPE(ann, ann->first_layer+iLayer));
		}

		unsigned int Neuron::getIndexInLayer()
		{
			unsigned int iLayer = getLayerIndex();
			fann* ann = handle->getParentObject();
			fann_neuron* neuron = handle->getObject();
			fann_layer* layer = ann->first_layer + iLayer;
			return neuron - layer->first_neuron; 
		}

		Neuron Neuron::operator[](unsigned int nConnection){
			return getConnection(nConnection);
		}

		nb_type Neuron::getWeight(unsigned int nConnection){
			unsigned int nConn = handle->getObject()->first_con + nConnection;
			return handle->getParentObject()->weights[nConn];
		}

		void Neuron::setWeight(unsigned int nConnection, nb_type weight){
			unsigned int nConn = handle->getObject()->first_con + nConnection;
			handle->getParentObject()->weights[nConn] = weight;
			return;
		}

		nb_type Neuron::getSum(){
			return handle->getObject()->sum;
		}

		nb_type Neuron::getValue(){
			return handle->getObject()->value;
		}

		nb_type Neuron::getActivationSteepness(){
			return handle->getObject()->activation_steepness;
		}

		nb_activationfunc_enum Neuron::getActivationFunction(){
			return handle->getObject()->activation_function;
		}

		std::string Neuron::format(){
			std::string ret;
			ret = "num connections = " + std::to_string(getNumConnections()) +"\n";
			ret += "weights = ";
			for (unsigned int i = 0; i < getNumConnections(); i++)
				ret += std::to_string(getWeight(i)) + ", ";
			ret += "\n";
			return ret;
		}

		bool Neuron::isNode(){
			return (getNumConnections()>0);
		}

		/*A neuron is bias when it is last neuron in layer*/
		bool Neuron::isBias()
		{
			return (*this == getLayer().getBias());
		}

		ANN Neuron::isolate(){
			if (!isNode())
				throw nb_exception("isolate should be used on node neurons only");
			ANN ann;
			unsigned int num_inputs = getNumConnections() - 1;
			unsigned int layers[2] = { num_inputs, 1 };
			ann.createStandardArray(2, layers);
			ann.setActivationFunctionOutput((handle->getParentObject()->last_layer-1)->first_neuron->activation_function);
			ann.setTrainingAlgorithm(handle->getParentObject()->training_algorithm);
			for (unsigned int i = 0; i < getNumConnections(); i++)
				ann[1][0].setWeight(i, getWeight(i));
			return ann;
		}

		ANN Neuron::isolate(std::vector<bool>& ignoreMask) {
			if (!isNode())
				throw nb_exception("isolate should be used on node neurons only");
			if (ignoreMask.size() != getNumConnections()-1)
				throw nb_exception("ignore mask size should be the same number of neuron inputs");

			unsigned int nIgnore = 0;
			for (unsigned int i = 0; i < ignoreMask.size(); i++)
				nIgnore = (ignoreMask[i]) ? nIgnore + 1 : nIgnore;
			if (nIgnore >= getNumConnections()-1)
				throw nb_exception("At least one input should not be ignored");

			ANN ann;
			unsigned int num_inputs = getNumConnections() - 1 - nIgnore;
			unsigned int layers[2] = { num_inputs, 1 };
			ann.createStandardArray(2, layers);
			ann.setActivationFunctionOutput((handle->getParentObject()->last_layer - 1)->first_neuron->activation_function);
			ann.setTrainingAlgorithm(handle->getParentObject()->training_algorithm);
			unsigned int n = 0;
			for (unsigned int i = 0; i < getNumConnections()-1; i++)
				if (!ignoreMask[i]) {
					ann[1][0].setWeight(n, getWeight(i));
					n++;
				}
			ann[1][0].setWeight(n, getWeight(getNumConnections() - 1));
			return ann;
		}
	}
}
