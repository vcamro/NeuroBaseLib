#ifndef __NEURON_RAW_MODEL_H
#define __NEURON_RAW_MODEL_H

#include "nb_lib.h"
#include "neuron.h"
#include "layer.h"

namespace NEUROBASE{
	using namespace L0;
	namespace L1{
		/*Carries topology summary inside the raw model too be used in interpreteation and rules formation steps*/
		class NeuronTopologyModel {
		public:
			/*Default constructor*/
			NeuronTopologyModel() { iLayer = 0; };

			/*Constructor using neuron object for extracting topology details*/
			NeuronTopologyModel(Neuron& neuron) { fromNeuron(neuron); };

			/*Copy constructor*/
			NeuronTopologyModel(const NeuronTopologyModel& other) {
				iLayer = other.iLayer;
				InputsMap = other.InputsMap;
			}
		public:
			unsigned int iLayer;
			std::vector<unsigned int> InputsMap;
		public:
			/*extracts topology information from neuron object*/
			void fromNeuron(Neuron& neuron) {
				if (neuron.getNumConnections()) {
					// Get bias of prev layer
					Layer layer = neuron.getLayer().getPrev();
					Neuron bias = layer.getBias();

					//Fill inputs map
					iLayer = neuron.getLayerIndex();
					InputsMap.clear();
					for (unsigned int i = 0; i < neuron.getNumConnections(); i++) {
						Neuron connNeuron = neuron.getConnection(i);
						//Exclude bias from inputs map
						if (connNeuron != bias)
							InputsMap.push_back(connNeuron.getIndexInLayer());
					}
				}
			}
			/*Format*/
			virtual std::string format() {
				std::string ret;
				ret += "Layer = " + std::to_string(iLayer) + ", ";
				ret += "Map = ";
				for (unsigned int i = 0; i< InputsMap.size(); i++)
					ret += std::to_string(InputsMap[i]) + ", ";
				return ret;
			}
		};



		class ConnectionsIgnoreMask : public std::vector<bool> {
		public:
			typedef std::vector<bool> IGNORE_MASK_TYPE;
		public:
			ConnectionsIgnoreMask() {};
			ConnectionsIgnoreMask(const ConnectionsIgnoreMask& other) :IGNORE_MASK_TYPE(other){};
			ConnectionsIgnoreMask(bool* start, bool* end) :IGNORE_MASK_TYPE(start, end) {};
		private:
			nb_vector getConnectionsStrengthes(Neuron& neuron) {
				nb_vector ret;
				for (unsigned int i = 0; i < neuron.getNumConnections() - 1; i++)
					ret.push_back(sqrt(neuron.getWeight(i) * neuron.getWeight(i)));
				return ret;
			}
			std::vector<unsigned int> sortConnectionsStrengthesindices(nb_vector& strengthes) {
				std::vector<unsigned int> ret;
				nb_type max_val = strengthes[strengthes.getMax()]+100.0f;
				for (unsigned int i = 0; i < strengthes.size(); i++) {
					unsigned int min = 0;
					for (unsigned int j = 1; j < strengthes.size(); j++)
						if (strengthes[j] < strengthes[min]) min = j;
					strengthes[min] = max_val;
					ret.push_back(min);
				}
				return ret;
			}
		public:
			void fill(Neuron& neuron, unsigned int busWidth) {
				int nConn = neuron.getNumConnections() - 1;
				clear();
				for (int i = 0; i < nConn; i++)
					push_back(false);
				std::vector<unsigned int> sorted;
				if (nConn > (int)busWidth - 1) {
					nb_vector strengthes = getConnectionsStrengthes(neuron);
					sorted = sortConnectionsStrengthesindices(strengthes);
				}
				for (int j = 0; j < ((nConn - (int)busWidth + 1)); j++)
					at(sorted[j]) = true;
			};
			unsigned int getNumIgnored() {
				unsigned int ret = 0;
				for (unsigned int i = 0; i < size(); i++)
					if (at(i)) ret++;
				return ret;
			}
			unsigned int getNumNotIgnored() {
				unsigned int ret = 0;
				for (unsigned int i = 0; i < size(); i++)
					if (!at(i)) ret++;
				return ret;
			}
		};



		/* Class: NeuronRawModel

		Represents classes array resulted from Alpha Neural Network
		*/
		class NeuronRawModel : public nb_vector
		{
		public:
			/*Default constructor*/
			NeuronRawModel(){};

			/*Copy constructor*/
			NeuronRawModel(const NeuronRawModel& copy) :nb_vector(copy){
				TopologyModel = copy.TopologyModel;
				IgnoreMask = copy.IgnoreMask;
			};

			NeuronRawModel(const nb_type* start, const nb_type* end)
				:nb_vector(start, end){};

			/*Constructor takes start and end of an array*/
			NeuronRawModel(const nb_type* start, const nb_type* end, Neuron& neuron) 
				:nb_vector(start, end),
				TopologyModel(neuron){};

			/*Constructor takes size of the array*/
			NeuronRawModel(unsigned int nClasses) :nb_vector(nClasses){};

			NeuronRawModel(const nb_type* param_classes, unsigned int nClasses)
				:nb_vector(param_classes, param_classes + nClasses){};

			/*Constructor takes start of an array and size*/
			NeuronRawModel(const nb_type* param_classes, unsigned int nClasses, Neuron& neuron) 
				:nb_vector(param_classes, param_classes + nClasses), 
				TopologyModel(neuron){};

			/*Constructor takes nb_vector*/
			NeuronRawModel(nb_vector& param_classes, Neuron& neuron) 
				:nb_vector(param_classes),
				TopologyModel(neuron) {};

			/*Destructor*/
			~NeuronRawModel(){};
		public:
			NeuronTopologyModel TopologyModel;
			ConnectionsIgnoreMask IgnoreMask;
		public:
			void quantizeClasses(){
				for (unsigned int i = 0; i < size(); i++)
					at(i) = (at(i) >= 0.5f) ? 1.0f : 0.0f;
			};
			/*Retrieves number of classes bit*/
			unsigned int getNumClasses();
			std::string format();
		};



		/*Layer neurons' models*/
		//typedef TVector<NeuronRawModel> LayerRawModel;
		class LayerRawModel : public TVector<NeuronRawModel>{
		public:
			/*Default constructor*/
			LayerRawModel() { num_inputs = 0; };

			/*Copy constructor*/
			LayerRawModel(const LayerRawModel& other)
				:TVector<NeuronRawModel>(other) { num_inputs = other.num_inputs; };

			/*Destructor*/
			~LayerRawModel() {};
		private:
			/*Number of layer inputs excluding the bias*/
			/*This is important for constructing symbol tables in formatter*/
			unsigned int num_inputs;
		public:
			unsigned int getNumInputs() { return num_inputs; };
			void setNumInputs(unsigned int nInputs) { num_inputs = nInputs; };
		};

		/*ANN neurons' models*/
		typedef TVector<LayerRawModel> ANNRawModel;
	}
}

#endif