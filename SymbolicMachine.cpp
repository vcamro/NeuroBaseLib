#include "SymbolicMachine.h"

namespace NEUROBASE{
	const nb_type SymbolicMachine::BIT_FAIL_DEFAULT_THRESHOLD = 0.35f;
	SymbolicMachine::SymbolicMachine() :threshold(SymbolicMachine::BIT_FAIL_DEFAULT_THRESHOLD){
	}


	SymbolicMachine::~SymbolicMachine(){
	}

	TrainingData SymbolicMachine::testSymbolicRule(SymbolicRule& rule, TrainingData& testData){
		if (testData.numInput() > rule.getInputSymbols().size())
			throw nb_exception("Number of inputs of test data should be less than number of inputs of Symbolic rule");
		if (testData.numOutput() != rule.getOutputSymbols().size())
			throw nb_exception("Number of outputs of test data should equal number of outputs of Symbolic rule");

		exprtk::symbol_table<fann_type> symbol_table;
		exprtk::expression<fann_type> expression;
		exprtk::parser<fann_type> parser;
		nb_vector variables = createVariablesVector(rule);
		fillSymbolTable(rule, variables, symbol_table);
		expression.register_symbol_table(symbol_table);
		if (!parser.compile(rule, expression))
			throw nb_exception("Can't compile this symbolic rule");
		//SymbolicMachine::TTest_Result ret;
		testResult = testData;
		nBitFail = 0;
		MSE = 0.0f;
		SymbolicRule::TSymbols inputSymbols = rule.getInputSymbols();
		SymbolicRule::TSymbols outputSymbols = rule.getOutputSymbols();
		for (unsigned int i = 0; i < testData.length(); i++){
			nb_vector res;
			SymbolicRule::TSymbols::iterator in = inputSymbols.begin();
			for (unsigned int j = 0; j < testData.numInput(); j++, in++)
				symbol_table.get_variable(*in)->ref() = testData.get_input()[i][j];
			expression.value();//Evaluate Expression
			SymbolicRule::TSymbols::iterator out = outputSymbols.begin();
			for (unsigned int j = 0; j < testData.numOutput(); j++, out++) {
				nb_type temp = symbol_table.get_variable(*out)->value();
				testResult.setSampleOutput(i, j, temp);
			}
		}
		computeMSE(testData);
		return testResult;
	}

	nb_vector SymbolicMachine::createVariablesVector(SymbolicRule& rule){
		return nb_vector(rule.getInputSymbols().size() + rule.getIntermediateSymbols().size() + rule.getOutputSymbols().size());
	}

	void SymbolicMachine::fillSymbolTable(SymbolicRule& rule, nb_vector& variables, exprtk::symbol_table<fann_type>& SymbolTable){
		if (rule.getInputSymbols().size() + rule.getIntermediateSymbols().size() + rule.getOutputSymbols().size() != variables.size())
			throw nb_exception("count of Symbols of symbolic rule should equal count of variables");
		SymbolicRule::TClassifiedSymbols symbols = rule.getSymbols();
		unsigned int i = 0;
		for (SymbolicRule::TClassifiedSymbols::iterator it = symbols.begin(); it != symbols.end(); it++){
			SymbolicRule::TSymbols ClassifiedSymbols = *it;
			for (SymbolicRule::TSymbols::iterator s_it = ClassifiedSymbols.begin(); s_it != ClassifiedSymbols.end(); s_it++, i++)
				SymbolTable.create_variable(*s_it, variables[i]);
		}
		return;
	}

	nb_type SymbolicMachine::computeMSE(TrainingData& testData){
		if (testData.length() != testResult.length())
			throw nb_exception("TestData and test result should be of the same numer of samples");
		if (testData.numOutput() != testResult.numOutput())
			throw nb_exception("Test data and results should have the same number of outputs");
		nb_type SE = 0;
		nb_type error = 0;
		for (unsigned int i = 0; i < testData.length(); i++){
			for (unsigned int j = 0; j < testData.numOutput(); j++){
				error = (testData.getSampleOutputs(i)[j] - testResult.getSampleOutputs(i)[j]) * (testData.getSampleOutputs(i)[j] - testResult.getSampleOutputs(i)[j]);
				if (sqrt(error) >= threshold)
					nBitFail++;
				SE += error;
			}
		}
		MSE = SE / (testData.length() * testData.numOutput());
		return MSE;
	}
	TrainingData SymbolicMachine::generateBooleanCases(unsigned int nNumInputs){
		unsigned int nCases = (unsigned int)pow(2.0f, (double)nNumInputs);
		TrainingData cases(nCases, nNumInputs, 1);
		for (unsigned int i = 0; i < nCases; i++){
			unsigned int num = i;
			for (unsigned int j = 0; num>0; j++){
				div_t d = div(num, 2);
				cases.getSampleInputs(i)[j] = (nb_type)d.rem;
				num = d.quot;
			}
		}
		return cases;
	}
	void SymbolicMachine::quantizetBooleanOutputs(TrainingData& data){
		for (unsigned int i = 0; i < data.length(); i++){
			for (unsigned int j = 0; j < data.numOutput(); j++)
				data.getSampleOutputs(i)[j] = (data.getSampleOutputs(i)[j] >= 0.5f) ? 1.0f : 0.0f;
		}
		return;
	}
}