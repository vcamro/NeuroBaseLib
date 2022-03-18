#include "Layer.h"

namespace NEUROBASE{
	namespace L0{
		unsigned int Layer::getNumNeurons(){
			return handle->getObject()->last_neuron - handle->getObject()->first_neuron;
		}

		unsigned int Layer::getNumNodes(){
			unsigned int ret = 0;
			for (unsigned int i = 0; i < getNumNeurons(); i++){
				if (getNeuron(i).isNode())
					ret++;
			}
			return ret;
		}

		unsigned int Layer::getNumInputs()
		{
			unsigned int ret = 0;
			if (getLayerIndex() == 0)
				ret = getHandle()->getParentObject()->num_input;
			else
				ret = Layer(getPrev()).getNumNeurons() - 1;
			return ret;
		}

		Neuron Layer::getNode(unsigned int nNode){
			if (nNode >= getNumNeurons())
				throw nb_exception("node index should be in neurons range");
			unsigned int j = 0;
			for (unsigned int i = 0; i < getNumNeurons() && j<= nNode; i++){
				if (getNeuron(i).isNode()){
					if (j == nNode)
						return getNeuron(i);
					j++;
				}
			}
			throw nb_exception("node index should be in nodes range");
		}

		Neuron Layer::getNeuron(unsigned int nNeuron){
			return new Neuron::HANDLE_TYPE(handle->getParentObject(), handle->getObject()->first_neuron + nNeuron);
		}

		Neuron Layer::operator [] (unsigned int nNeuron){
			return getNeuron(nNeuron);
		}

		Neuron Layer::getBias()
		{
			return Neuron(new Neuron::HANDLE_TYPE(handle->getParentObject(), handle->getObject()->last_neuron-1));
		}

		Neuron Layer::getFirst()
		{
			return Neuron(new Neuron::HANDLE_TYPE(handle->getParentObject(), handle->getObject()->first_neuron));
		}

		Neuron Layer::getLast()
		{
			return Neuron(new Neuron::HANDLE_TYPE(handle->getParentObject(), handle->getObject()->last_neuron));
		}

		unsigned int Layer::getLayerIndex(){
			return (handle->getObject()) - (handle->getParentObject()->first_layer);
		}

		void Layer::setActivationFunction(nb_activationfunc_enum activationFunc){
			fann_set_activation_function_layer(this->handle->getParentObject(), (fann_activationfunc_enum)activationFunc, getLayerIndex());
		}
		
		std::string Layer::format(){
			std::string ret;
			unsigned int nNeurons = getNumNeurons();
			for (unsigned int i = 0; i < nNeurons; i++)
				ret += getNeuron(i).format();
			return ret;
		}
	}
}