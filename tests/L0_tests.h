#ifndef __L0_TESTS_H
#define __L0_TESTS_H

#include "ANN.h"

using namespace NEUROBASE;
using namespace NEUROBASE::L0;

ANN create_ann();
ANN create_ann_big();
void test_ann_navigation(ANN& net);
void test_layer_navigation(ANN& net);
void test_neuron_navigation(ANN& net);
void test_neuron_isolate(ANN& net);
void test_neuron_isolate_mask(ANN& net);
void test_training_data();
void test_L0();

#endif
