#ifndef __NSA_H
#define __NSA_H

#include "nb_lib.h"
#include "LTMSegment.h"
#include "ModelFormatter.h"
#include "SymbolicMachine.h"

namespace NEUROBASE{
	using namespace L0;
	using namespace L1;
	using namespace L2;
	/* Class: NSA

	Encapsulates the Neural Symbolization Algorithm
	*/
	class NSA
	{
	public:
		/*Default constructor*/
		NSA();
		/*Destructor*/
		~NSA();
	public:
		typedef enum {
			enum_log_none = 0,
			enum_log_working_memory = 1,
			enum_log_raw_model = 2,
			enum_log_interpreted_model = 4,
			enum_log_symbolic_rule = 8,
			enum_log_all = 0xFFFFFFFF
		} enum_log_details;

	protected:
		/*Maximum epochs of backpropagation training of working memory*/
		unsigned int TrialMaxEpochs;
		/*Epochs between epochs during backpropagation training of working memory*/
		unsigned int TrialEpchsBetweenReports;
		/*Desired error when backpropagation training of working memory*/
		nb_type TrialDesiredError;
		/*maximum number of backpropagation training trials*/
		unsigned int MaxTrials;
		/*Maximum number of total epochs*/
		unsigned int MaxEpochs;
		/*Desired bit fail*/
		unsigned int DesiredBitFail;
		/*Last bit fail*/
		unsigned int LastBitFail;
		/*Last mean square error*/
		nb_type LastMSE;
		/*Last number of learning trials during symbolization*/
		unsigned int LastTrials;
		unsigned int LastTotalEpochs;
		ANNRawModel LastRawModel;
		ANNInterpretedModel LastInterpretedModel;
		SymbolicRule LastSymbolicRule;
		/*verbose during NSA loop*/
		bool bVerbose;
		static unsigned int temp;
		enum_log_details e_log_details;
		std::ofstream log_file;
	protected:
		void reset();
	public:
		/*Defaults*/
		static const unsigned int TRIAL_MAX_EPOCHS_DEFAULT;
		static const unsigned int TRIAL_EPOCHS_BETWEEN_REPORTS_DEFAULT;
		static const nb_type TRIAL_DESIRED_ERROR_DEFAULT;
		static const unsigned int MAX_TRIALS_DEFAULT;
		static const unsigned int MAX_EPOCHS_DEFAULT;
		static const unsigned int DESIRED_BIT_FAIL_DEFAULT;
	public:
		/*Apply NSA algorithm for symbolizing working memory*/
		virtual SymbolicRule symbolize(LTMSegment& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, TrainingData& trainData);
		virtual SymbolicRule symbolize(LTM& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, TrainingData& trainData);
		virtual void onTrialStart(unsigned int nTrial);
		virtual void onWorkingMemoryTrained(unsigned int totalEpochs, ANN& wm, TrainingData& traindata);
		virtual void onRawModel(LTMSegment& ltm, ANNRawModel& model);
		virtual void onInterpretedModel(TaxonomyScheme& taxonomy, Interpreter& interpreter, ANNInterpretedModel& interpretedModel);
		virtual void onSymbolicRule(ModelFormatter& formatter, SymbolicRule& rule);
		virtual void onSuccess(SymbolicMachine& sm, TrainingData& result);
		virtual void onGiveup(unsigned int nTrial, unsigned int totalEpochs);
		virtual void onTrialEnd(unsigned int nTrial, unsigned int totalEpochs);

		/*Setters and Getters*/
		void setTrialMaxEpochs(unsigned int max){ TrialMaxEpochs = max; };
		unsigned int getTrialMaxEpochs(){ return TrialMaxEpochs; };
		void setTrialEpochsBetweenReports(unsigned int epochs){ TrialEpchsBetweenReports = epochs; };
		unsigned int getTrialEpochsBetweenReports(){ return TrialEpchsBetweenReports; };
		void setTrialDesiredError(nb_type desired){ TrialDesiredError = desired; };
		nb_type setTrialDesiredError(){ return TrialDesiredError; };
		void setMaxTrials(unsigned int max){ MaxTrials = max; };
		unsigned int getMaxTrials(){ return MaxTrials; };
		void setMaxEpochs(unsigned int max){ MaxEpochs = max; };
		unsigned int getMaxEpochs(){ return MaxEpochs; };
		void setDesiredBitFail(unsigned int desired){ DesiredBitFail = desired; };
		unsigned int getDesiredBitFail(){ return DesiredBitFail; };
		void setVerbose(bool verbose){ bVerbose = verbose; };
		bool getVerbose(){ return bVerbose; };
		/*Returns last bit fail*/
		unsigned int getLastBitFail(){ return LastBitFail; };
		/*Returns last MSE*/
		nb_type getLastMSE(){ return LastMSE; };
		unsigned int getLastTrials(){ return LastTrials; };
		ANNRawModel& getLastRawModel(){ return LastRawModel; };
		ANNInterpretedModel& getLastInterpretedModel(){ return LastInterpretedModel; };
		SymbolicRule& getLastSymbolicRule(){ return LastSymbolicRule; };
		void setLogDetails(enum_log_details eLogDetails) { e_log_details = eLogDetails; };
		enum_log_details getLogDetails() { return e_log_details; };
	};
}

#endif