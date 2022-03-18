#ifndef __SYMBOLIC_MACHINE
#define __SYMBOLIC_MACHINE

#include "nb_lib.h"
#include "ModelFormatter.h"
#include "TrainingData.h"

namespace NEUROBASE{
		/* Class: SymbolicMachine

		Encapsulates the logic of testing symbolic rule
		*/
		class SymbolicMachine
		{
		public:
			/*Default constructor*/
			SymbolicMachine();
			/*Destructor*/
			~SymbolicMachine();
		private:
			/*Test results*/
			TrainingData testResult;
			/*Number of bit fails of test*/
			unsigned int nBitFail;
			/*Threshold of bit fail decision*/
			nb_type threshold;
			/*Mean square error of last test*/
			nb_type MSE;
			/*Initializes a vraiables vector of suitable size. It is required for symbol table*/
			nb_vector createVariablesVector(SymbolicRule& rule);
			/*Fills symbol table*/
			void fillSymbolTable(SymbolicRule& rule, nb_vector& variables, exprtk::symbol_table<fann_type>& SymbolTable);
			/*Computes MSE*/
			nb_type computeMSE(TrainingData& testData);

		public:
			/*The dafault threshold of bit fail*/
			static const nb_type BIT_FAIL_DEFAULT_THRESHOLD;
			/*Tests symbolic rule*/
			TrainingData testSymbolicRule(SymbolicRule& rule, TrainingData& testData);
			/*Returns bit fail*/
			unsigned int getBitFail(){ return nBitFail; };
			/*Returns latest computed MSE*/
			nb_type getMSE(){ return MSE; };
			/*Sets bit fail threshold*/
			void setBitFailThreshold(nb_type param_threshold){ threshold = param_threshold; };
			/*Returns latest computed bit fail*/
			nb_type getBitFailThreshold(){ return threshold; };
			static TrainingData generateBooleanCases(unsigned int nNumInputs);
			static void quantizetBooleanOutputs(TrainingData& data);
		};
}
#endif