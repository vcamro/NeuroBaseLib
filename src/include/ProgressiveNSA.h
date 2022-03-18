#ifndef __PROGRESSIVE_NSA
#define __PROGRESSIVE_NSA
#include "nb_lib.h"
#include "NSA.h"
#include "LTM.h"

namespace NEUROBASE{
	using namespace L0;
	using namespace L1;
	using namespace L2;
	class ProgressiveNSA : public NSA
	{
	public:
		ProgressiveNSA();
		~ProgressiveNSA();
	public:
		typedef enum {
			enum_log_none=0,
			enum_log_working_memory=1,
			enum_log_raw_model=2,
			enum_log_interpreted_model=4,
			enum_log_symbolic_rule=8,
			enum_log_consolidated_model=16,
			enum_log_consolidated_symbolic_rule=32,
			enum_log_all=0xFFFFFFFF
		} enum_progressiveNSA_log_details;
	private:
		LTMCases stm;
		unsigned int STMAbsoluteCounter;
		unsigned int STMCounter;
		bool bBreadown;
		unsigned int maxBreakdownTrials;
		MultiANNRawModel LastMultiRawModel;
		MultiANNInterpretedModel LastMultiInterpretedModel;
		MultiANNSymbolicRules LastMultiSymbolicRules;
		unsigned int nLTMSegmentHiddenNodes;
		unsigned int nChunkSize;
		enum_progressiveNSA_log_details e_progressiveNSA_log_details;
		std::ofstream progressiveNSA_log_file;
	private:
		void init();
		void reset();
		ANNInterpretedModel consolidate(LTM& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, MultiANNInterpretedModel& interpreted, MultiANNSymbolicRules& rules);
	public:
		static unsigned int MAX_BREAKDOWN_TRIALS_DEFAULT;
		static unsigned int CHUNK_SIZE_DEFAULT;
		static unsigned int NUM_LTM_SEGMENT_HIDDEN_NODES;
	public:
		SymbolicRule symbolize(LTM& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, TrainingData& trainData);
		//NSA overrides
		virtual void onTrialStart(unsigned int nTrial);
		virtual void onWorkingMemoryTrained(unsigned int totalEpochs, ANN& wm, TrainingData& traindata);
		virtual void onInterpretedModel(TaxonomyScheme& taxonomy, Interpreter& interpreter, ANNInterpretedModel& interpretedModel);
		virtual void onSymbolicRule(ModelFormatter& formatter, SymbolicRule& rule);
		//ProgressiveNSA overrides
		virtual void onRawModel(LTM& ltm, MultiANNRawModel& model);
		virtual void onInterpretedModel(TaxonomyScheme& taxonomy, Interpreter& interpreter, MultiANNInterpretedModel& interpretedModel);
		virtual void onSymbolicRule(ModelFormatter& formatter, MultiANNSymbolicRules& rule);
		virtual void onSuccess(SymbolicMachine& sm, TrainingData& result);
		virtual void onGiveup(unsigned int nTrial, unsigned int totalEpochs);
		virtual void onTrialEnd(unsigned int nTrial, unsigned int totalEpochs);
	public:
		LTMCases getSTM(){ return stm; };
		void setMaxBreakdownTrials(unsigned int maxTrials){ maxBreakdownTrials = maxTrials; };
		unsigned int getMaxBreakdownTrials(){ return maxBreakdownTrials; };
		void setNumLTMSegmentHiddenNodes(unsigned int num){ nLTMSegmentHiddenNodes = num; };
		unsigned int getNumLTMSegmentHiddenNodes(){ return nLTMSegmentHiddenNodes; };
		void setBreakdownFlag(bool bFlag){ bBreadown = bFlag; };
		bool getBreakdownFlag(){ return bBreadown; };
		void setChunkSize(unsigned int size){ nChunkSize = size; };
		unsigned int getChunkSize(){ return nChunkSize; };
		void setProgressiveNSALogDetails(enum_progressiveNSA_log_details eLogDetails) { e_progressiveNSA_log_details = eLogDetails; };
		enum_progressiveNSA_log_details getProgressiveNSALogDetails() { return e_progressiveNSA_log_details; };
	};
}

#endif