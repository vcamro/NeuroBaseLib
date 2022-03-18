#ifndef __STM_H
#define __STM_H

#include "nb_lib.h"
#include "neuron.h"
#include "SymbolicRuleInspector.h"

namespace NEUROBASE{
	namespace L1{
		using namespace L0;

		typedef TMemoryItem<TrainingData, CachableNeuron> STMItem;
		typedef TMemoryCases<STMItem> STMCases;
	}
}
#endif