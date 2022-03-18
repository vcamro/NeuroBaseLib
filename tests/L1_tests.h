#ifndef __L1_TESTS_H
#define __L1_TESTS_H

#include "ann.h"
#include "LTMSegment.h"
#include "interpreter.h"
#include "GlobalTaxonomyScheme.h"
#include "interpreter.h"
#include "BooleanModelFormatter.h"

using namespace NEUROBASE;
using namespace NEUROBASE::L0;
using namespace NEUROBASE::L1;

void test_global_taxonomy_scheme();
void test_neuron_topology_model(ANN net);
void test_connection_ignore_mask();
std::vector<NeuronRawModel> create_neuron_raw_model();
NeuronInterpretedModel create_neuron_interpreted_model();
void test_interpret_raw_neuron_model();
void test_reverse_interpret_neuron_model();
void test_format_interpreted_model();
void test_align_interpreted_to_ANN_structure();
void test_format_interpret_ANN_model();
void test_train_LTM_Segment();

void test_L1();

#endif
