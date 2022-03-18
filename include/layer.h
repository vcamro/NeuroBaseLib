#ifndef __LAYER_H
#define __LAYER_H

#include "nb_lib.h"
#include "Neuron.h"

namespace NEUROBASE{
	namespace L0{
		/* Class: Layer

		Encapsulation of a neural network layer
		*/
		class Layer : public TANNObject<fann_layer>
		{
		public:
			typedef TANNObject<fann_layer> LAYER_TYPE;
		public:
			/*Constructor*/
			Layer(HANDLE_TYPE* param_hLayer) :LAYER_TYPE(param_hLayer) {};
			/*Copy Constructor*/
			Layer(const Layer& other):LAYER_TYPE(other){};
			/*Destructor*/
			~Layer(){ /*if (handle) delete handle;*/ };
		protected:
			/*Protected default constructor, to prohibit explicit use of it creating objects*/
			Layer():LAYER_TYPE(){};

		public:
			/*Returns number of neurons in layer*/
			unsigned int getNumNeurons();
			unsigned int getNumNodes();
			unsigned int getNumInputs();
			Neuron getNode(unsigned int nNode);
			/*Returns certain neuron of the layer*/
			Neuron getNeuron(unsigned int nNeuron);
			/*Returns certain neuron of the layer*/
			Neuron operator [] (unsigned int nNeuron);
			/*Bias neuron of layer*/
			Neuron getBias();
			/*First neuron of layer*/
			Neuron getFirst();
			/*Last neuron of layer*/
			Neuron getLast();
			/*Sets activation function of the layer*/
			void setActivationFunction(nb_activationfunc_enum activationFunc);
			/*Returns the index of this layer within the neural network*/
			unsigned int getLayerIndex();
			virtual std::string format();
		};
	}
}

#endif