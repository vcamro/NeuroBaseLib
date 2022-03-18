#ifndef __NEURON_H
#define __NEURON_H

#include "nb_lib.h"

namespace NEUROBASE{
	namespace L0{
		/* Class: Neuron

		Encapsulation of a neuron
		*/
		class ANN;
		class Layer;
		class Neuron : public TANNObject<fann_neuron>
		{
		public:
			typedef TANNObject<fann_neuron> NEURON_TYPE;
		public:
			/*Constructor*/
			Neuron(HANDLE_TYPE* param_hLayer) :NEURON_TYPE(param_hLayer) {};

			/*Copy Constructor*/
			Neuron(const Neuron& other) :NEURON_TYPE(other) {};

			/*Destructor*/
			~Neuron(){ /*if (hNeuron) delete hNeuron;*/ };
		protected:
			/*Protected default constructor, to prohibit explicit use of it creating objects*/
			Neuron() :NEURON_TYPE() {};

		public:
			/*Returns number of Neuron connections*/
			unsigned int getNumConnections();

			/*Returns connection's connected neuron*/
			Neuron getConnection(unsigned int nConnection);
			void setConnection(unsigned int nConnection, Neuron& neuron);

			// Returns the layer index containing this neuron
			unsigned int getLayerIndex();

			// Returns Layer object containing the neuron
			Layer getLayer();

			// Returns the index of the neuron in the layer containing this neuron
			unsigned int getIndexInLayer();

			/*Returns connection's connected neuron*/
			Neuron operator[](unsigned int nConnection);

			/*Returns connection's weight*/
			nb_type getWeight(unsigned int nConnection);

			/*Sets connection's weight*/
			void setWeight(unsigned int nConnection, nb_type weight);

			/* The sum of the inputs multiplied with the weights */
			nb_type getSum();

			/* The value of the activation function applied to the sum */
			nb_type getValue();

			/* The steepness of the activation function */
			nb_type getActivationSteepness();

			/* Used to choose which activation function to use */
			nb_activationfunc_enum getActivationFunction();

			virtual std::string format();

			/*A neuron is a node if it has connections, neurons doesn't have conenctions like input neurons and bias neurons*/
			bool isNode();

			/*Returns true is this neuron is bias neuron*/
			bool isBias();

			/*Creates new ann using the weights of this single neuron*/
			ANN isolate();
			ANN isolate(std::vector<bool>& ignoreMask);
		};

		class CachableNeuron : public Neuron{
		public:
			CachableNeuron(){};
			CachableNeuron(const CachableNeuron& other) :Neuron(other){};
			CachableNeuron(const Neuron& other) :Neuron(other){};
			~CachableNeuron(){};
		};
	}
}

#endif