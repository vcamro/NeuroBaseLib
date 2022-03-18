#ifndef __TESTS_H
#define __TESTS_H

#include "ANN.h"
#include "LTMSegment.h"
#include "interpreter.h"
#include "GlobalTaxonomyScheme.h"
#include "BooleanModelFormatter.h"
#include "SymbolicMachine.h"
#include "NSA.h"
#include "SymbolicRuleInspector.h"
#include "ProgressiveNSA.h"
#include <time.h>

using namespace NEUROBASE;
using namespace NEUROBASE::L0;
using namespace NEUROBASE::L1;
using namespace NEUROBASE::L2;

// Tests
void train_LTM_Series();
void self_test();
void test2();

//Decoder Problem
void DEC11_NoBreakDown();
void DEC20_NoBreakDown();
void DEC37_NoBreakDown();
void DEC20_BreakDown();
void DEC37_BreakDown();
void DEC70_BreakDown();
void DEC135_BreakDown();
void DEC264_BreakDown();

// DEMUX Problems
void DEMUX6();
void DEMUX11();
void DEMUX20();
void DEMUX37();
void DEMUX70();
void DEMUX135();

//MUX Problems
void MUX3();
void MUX6();
void MUX11();

void and_10();
void and_or_10();
void and_or_pairs_10();


//Math tests
void test_addition();
void test_multiplication_non_digitized();
void test_multiplication_digitized();

#endif
