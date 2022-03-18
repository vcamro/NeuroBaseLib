#include "NeuronRawModel.h"

namespace NEUROBASE{
	namespace L1{
		unsigned int NeuronRawModel::getNumClasses(){
			return size();
		}

		std::string NeuronRawModel::format(){
			std::string ret = "classes=";
			unsigned int size = getNumClasses();
			for (unsigned int i = 0; i < size; i++)
				ret += std::to_string(at(i)) + ", ";
			ret += "\n";
			return ret;
		}
	}
}
