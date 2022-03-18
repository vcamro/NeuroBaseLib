#ifndef MODEL_FORMATTER_H
#define MODEL_FORMATTER_H

#include "nb_lib.h"
#include "interpreter.h"
#include "GlobalTaxonomyScheme.h"
#include "ann.h"

namespace NEUROBASE {
	namespace L1{
		/* Class: SymbolicRule

		Encapsulates formatted symbolic rule
		*/
		class SymbolicRule : public std::string{
		public:
			/*Default constructor*/
			SymbolicRule() :symbols(3){};
			/*Copy constructor*/
			SymbolicRule(const SymbolicRule& other) :std::string(other){ symbols = other.symbols; };
			/*Constructor with standard string*/
			SymbolicRule(const std::string& str) :std::string(str), symbols(3){};
			/*Destructor*/
			~SymbolicRule(){};
		public:
			/*Type:- Vector of variables symbols of the same type*/
			typedef std::vector<std::string> TSymbols;
			/*Type:- Lists of variables symbols classified by their type (Types include Input, intermediate and output variables)*/
			typedef std::vector<TSymbols> TClassifiedSymbols;
		private:
			/*Classified variables symbols vectors*/
			TClassifiedSymbols symbols;
		public:
			/*Index of input variables symbols*/
			static const unsigned int SYMBOL_TYPE_INPUT_INDEX;
			/*Index of intermediate variables symbols*/
			static const unsigned int SYMBOL_TYPE_INTERMEDIATE_INDEX;
			/*Index of output variables symbols*/
			static const unsigned int SYMBOL_TYPE_OUTPUT_INDEX;
			/*returns symbols veactors*/
			TClassifiedSymbols getSymbols(){
				return symbols;
			}
			/*returns input symbols vector*/
			TSymbols getInputSymbols(){
				return symbols[SYMBOL_TYPE_INPUT_INDEX];
			};
			/*Returns intermediate symbols vector*/
			TSymbols getIntermediateSymbols(){
				return symbols[SYMBOL_TYPE_INTERMEDIATE_INDEX];
			};
			/*Returns output symbols vector*/
			TSymbols getOutputSymbols(){
				return symbols[SYMBOL_TYPE_OUTPUT_INDEX];
			};
			/*Inserts input symbol in inputs symbol vector*/
			void addInputSymbol(std::string symbol){
				symbols[SYMBOL_TYPE_INPUT_INDEX].push_back(symbol);
			}
			/*Inserts intermediate symbol in intermediate symbols vector*/
			void addIntermediateSymbol(std::string symbol){
				symbols[SYMBOL_TYPE_INTERMEDIATE_INDEX].push_back(symbol);
			}
			/*Inserts output symbol in output symbols vector*/
			void addOutputSymbol(std::string symbol){
				symbols[SYMBOL_TYPE_OUTPUT_INDEX].push_back(symbol);
			}
			std::string format(){
				std::string ret = "Rule is\n";
				ret += data();
				ret += "Input Symbols are\n";
				for (TSymbols::iterator it = symbols[SYMBOL_TYPE_INPUT_INDEX].begin(); it != symbols[SYMBOL_TYPE_INPUT_INDEX].end(); it++)
					ret += *it + ", ";
				ret += "\n";
				ret += "Intermediate Symbols are\n";
				for (TSymbols::iterator it = symbols[SYMBOL_TYPE_INTERMEDIATE_INDEX].begin(); it != symbols[SYMBOL_TYPE_INTERMEDIATE_INDEX].end(); it++)
					ret += *it + ", ";
				ret += "\n";
				ret += "Output Symbols are\n";
				for (TSymbols::iterator it = symbols[SYMBOL_TYPE_OUTPUT_INDEX].begin(); it != symbols[SYMBOL_TYPE_OUTPUT_INDEX].end(); it++)
					ret += *it + ", ";
				ret += "\n";
				return ret;
			};
			/*Prints symbolic rule contents*/
			void print(){ printf(format().data()); };
			void save(std::ofstream& out) { out << format(); };
		};
		typedef TVector<SymbolicRule> LayerSymbolicRules;
		typedef TVector<LayerSymbolicRules> ANNSymbolicRules;
	}
	namespace L2{
		typedef TVector<ANNSymbolicRules> MultiANNSymbolicRules;
	}


	using namespace L0;
	using namespace L1;
	/* Class: ModelFormatter

	Encapsulates the logic of formatting interpreted model to symbolic rule
	*/
	class ModelFormatter{
	public:
		/*Default constructor*/
		ModelFormatter(){ maxNeuronInputs = 0; };
		/*Constructor with maimum neuron inputs and taxonomy scheme*/
		ModelFormatter(unsigned int param_inputs, GlobalTaxonomyScheme param_taxonomy) :maxNeuronInputs(param_inputs), taxonomyScheme(param_taxonomy){};
		/*Destructor*/
		~ModelFormatter(){};
	private:
		/*Maximum neuron inputs (Bus width -1)*/
		unsigned int maxNeuronInputs;
		/*Taxonomy scheme*/
		GlobalTaxonomyScheme taxonomyScheme;
		/*Initializes symbolic rule*/
		SymbolicRule initSymbolicRule(ANNInterpretedModel& model);
		SymbolicRule initSymbolicRule(NeuronInterpretedModel& model);
		/*Formats primary simple part*/
		SymbolicRule formatPrimarySimplePart(NeuronInterpretedModel& model, char inputPrefix);
		/*Formats primary compound part*/
		SymbolicRule formatPrimaryCompundPart(NeuronInterpretedModel& model, char inputPrefix);
		/*Formats secondery simple part*/
		SymbolicRule formatSeconderySimplePart(NeuronInterpretedModel& model, char inputPrefix);
		/*Formats secondery compound part*/
		SymbolicRule formatSeconderyCompundPart(NeuronInterpretedModel& model, char inputPrefix);
		/*Checks the model to know if it has secondery compound part*/
		bool hasSeconderyCompound(NeuronInterpretedModel& model);
		unsigned int getNeuronInputs(NeuronInterpretedModel& model);
	public:
		/*First neural network layer starts with veriables of this prefix, prefix is one single character
		every consecutive layer has incremented prefix value*/
		static char INPUT_PREFIX_START;
		/*Maximum number of layers is limited by number of letters (less than or equal 26)*/
		static const unsigned int MAX_LAYERS;
		unsigned int getMaxNeuronInputs(){ return maxNeuronInputs; };
		/*Checks of from neuron interpreted model if input is active*/
		virtual bool isActiveInput(NeuronInterpretedModel& model, unsigned int nInput);
		/*Checks from neuron interpreted model if input is transfered*/
		bool isTransferedInput(NeuronInterpretedModel& model, unsigned int nInput);
		/*Checks from neuron interpreted model if input is inverted*/
		bool isInvertedInput(NeuronInterpretedModel& model, unsigned int nInput);
		/*Checks from neuron interpreted model if input is simple*/
		virtual bool isSimpleInput(NeuronInterpretedModel& model, unsigned int nInput);
		/*Checks from neuron interpreted model if input is compound*/
		virtual bool isCompoundInput(NeuronInterpretedModel& model, unsigned int nInput);
		/*Checks from neuron interpreted model if input is primary input*/
		virtual bool isPrimaryInput(NeuronInterpretedModel& model, unsigned int nInput);
		/*Checks from neuron interpreted model if input is secondery input*/
		virtual bool isSeconderyInput(NeuronInterpretedModel& model, unsigned int nInput);
	/*Format methods*/
	protected:
		/*Symbol arrays are not prepared when formatting using these methods*/
		/*Formats layer interpreted model*/
		SymbolicRule format(LayerInterpretedModel& model, char inputPrefix, char outputPrefix);
		/*Formats neuron model*/
		SymbolicRule format(NeuronInterpretedModel& model, char inputPrefix, std::string outputVariable);
	public:
		/*Returns symbolic rule list with symbol tables are prepared on the single neuron level only*/
		MultiANNSymbolicRules formatANNRules(MultiANNInterpretedModel& model);
		ANNSymbolicRules formatANNRules(ANNInterpretedModel& model);
		LayerSymbolicRules formatLayerRules(LayerInterpretedModel& model);
		/*Formats and returns single symbolic rule with prepared symbols lists*/
		SymbolicRule format(ANNInterpretedModel& model);
		SymbolicRule format(NeuronInterpretedModel& model);
	/*Pure methods*/
	public:
		virtual void alignInterpretedModelToANNStructure(ANNInterpretedModel& interpretedModel, ANN& ann) = 0;
		virtual void alignInterpretedModelToANNStructure(MultiANNInterpretedModel& interpretedModel, ANN& ann) = 0;
		/*Formats symbolic function of input state input*/
		virtual std::string formatInputStateFunction(NeuronInterpretedModel& model, unsigned int nInput, char inputPrefix)=0;
		/*Formats relation function*/
		virtual std::string formatRelationFunction(NeuronInterpretedModel& model) = 0;
		/*Formats complementary relation fucntion*/
		virtual std::string formatComplementingRelationFunction(NeuronInterpretedModel& model) = 0;
		/*Formats primary identity constant (i.e. in boolean domain for OR its is '0' for AND it is '1')*/
		virtual std::string getPrimaryIdentityConstant(NeuronInterpretedModel& model) = 0;
		/*Formats the secondery identity function*/
		virtual std::string getSeconderyIdentityConstant(NeuronInterpretedModel& model) = 0;
	};
}
#endif