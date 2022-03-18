#include "NSA.h"

namespace NEUROBASE{
	const unsigned int NSA::TRIAL_MAX_EPOCHS_DEFAULT = 10000;
	const unsigned int NSA::TRIAL_EPOCHS_BETWEEN_REPORTS_DEFAULT = 1000;
	const nb_type NSA::TRIAL_DESIRED_ERROR_DEFAULT = 0.00001f;
	const unsigned int NSA::MAX_TRIALS_DEFAULT = 1000;
	const unsigned int NSA::MAX_EPOCHS_DEFAULT = 10000000;
	const unsigned int NSA::DESIRED_BIT_FAIL_DEFAULT = 0;
	unsigned int NSA::temp = 0;

	NSA::NSA(){
		TrialMaxEpochs = TRIAL_MAX_EPOCHS_DEFAULT;
		TrialEpchsBetweenReports = TRIAL_EPOCHS_BETWEEN_REPORTS_DEFAULT;
		TrialDesiredError = TRIAL_DESIRED_ERROR_DEFAULT;
		MaxTrials = MAX_TRIALS_DEFAULT;
		MaxEpochs = MAX_EPOCHS_DEFAULT;
		DesiredBitFail = DESIRED_BIT_FAIL_DEFAULT;
		bVerbose = false;
		log_file.open("NSA.log", std::ofstream::out | std::ofstream::app);
	};

	NSA::~NSA(){
		log_file.flush();
		log_file.close();
	};

	SymbolicRule NSA::symbolize(LTMSegment& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, TrainingData& trainData){
		bool bTrained = false;
		bool bGiveUp = false;
		SymbolicRule ret;
		wm.enableCallback();
		reset();
		while (!bTrained && !bGiveUp){
			onTrialStart(LastTrials);
			wm.trainOnData(trainData, TrialMaxEpochs, TrialEpchsBetweenReports, TrialDesiredError);
			//do {
			//	wm.trainOnData(trainData, TrialMaxEpochs, TrialEpchsBetweenReports, TrialDesiredError);
			//	if (wm.getBitFail() > 0)
			//		wm.randomizeWeights(-1.0f, 1.0f);
			//} while (wm.getBitFail() > 0);
			onWorkingMemoryTrained(LastTotalEpochs, wm, trainData);
			LastTotalEpochs += wm.getLastEpochs();
			LastRawModel = ltm.modelSynthesisANN(wm);
			onRawModel(ltm, LastRawModel);
			Interpreter interpreter(ltm.getBusWidth() - 1);
			LastInterpretedModel = interpreter.interpret(taxonomy, LastRawModel);
			onInterpretedModel(taxonomy, interpreter, LastInterpretedModel);
			formatter.alignInterpretedModelToANNStructure(LastInterpretedModel, wm);
			LastSymbolicRule = formatter.format(LastInterpretedModel);
			onSymbolicRule(formatter, LastSymbolicRule);
			SymbolicMachine sm;
			TrainingData result = sm.testSymbolicRule(LastSymbolicRule, trainData);
			LastBitFail = sm.getBitFail();
			LastMSE = sm.getMSE();
			if (sm.getBitFail() <= DesiredBitFail){
				bTrained = true;
				onSuccess(sm, result);
			}
			if (LastTrials > MaxTrials || LastTotalEpochs > MaxEpochs){
				bGiveUp = true;
				onGiveup(LastTrials, LastTotalEpochs);
			}
			ret = LastSymbolicRule;
			LastTrials++;
			onTrialEnd(LastTrials, LastTotalEpochs);
			if (bVerbose || bTrained || bGiveUp){
				printf("-----------------------------------------------------\n");
				//wm.print();
				//printf(".....................................................\n");
				//model.print();
				//printf(".....................................................\n");
				//interpretedModel.print();
				//printf(".....................................................\n");
				//result.print();
				//printf(".....................................................\n");
				trainData.print();
				printf(".....................................................\n");
				LastSymbolicRule.print();
				printf(".....................................................\n");
				printf("Trained = %d, Giveup = %d\n", bTrained, bGiveUp);
				printf("Bit Fail = %d\n", LastBitFail);
				printf("MSE = %f \n", LastMSE);
				printf("Trials = %d\n", LastTrials);
				printf("Total Epochs = %d\n", LastTotalEpochs);
				printf("-----------------------------------------------------\n");
			}
		}
		return ret;
	}
	SymbolicRule NSA::symbolize(LTM& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, TrainingData& trainData){
		SymbolicRule ret;
		for (unsigned int i = 0; i < ltm.size(); i++){
			ANN* pANN = new ANN((const ANN&)wm);
			//std::vector<unsigned int> layers;
			//for (unsigned int j = 0; j < wm.getNumLayers(); j++)
			//	layers.push_back(wm[j].getNumNeurons()-1);
			///pANN->create(layers);
			//pANN->setActivationFunctionOutput(wm[wm.getNumLayers() - 1][0].getActivationFunction());
			//pANN->setTrainingAlgorithm(wm.getTrainingAlgorithm());
			//pANN->randomizeWeights(LTMSegment::MIN_WEIGHT, LTMSegment::MAX_WEIGHT);
			ret = symbolize(ltm[i], *pANN, taxonomy, formatter, trainData);
			if (LastBitFail == 0){
				delete pANN;
				pANN = NULL;
				break;
			}
			else{
				LastRawModel.save(std::string(".\\log\\FAILED_SYMBOLIZE_RAW_") + std::to_string(temp)+".txt");
				wm.saveLog(std::string(".\\log\\FAILED_SYMBOLIZE_ANN_") + std::to_string(temp) + ".txt");
//				trainData.save(std::string(".\\log\\train_") + std::to_string(temp) + ".train");
				temp++;
			}
			if (pANN)
				delete pANN;
		}
		return ret;
	}

	void NSA::reset(){
		LastBitFail = 0;
		LastMSE = 0.0f;
		LastTrials = 0;
		LastTotalEpochs = 0;
		LastRawModel.clear();
		LastInterpretedModel.clear();
		LastSymbolicRule.clear();
	}

	void NSA::onTrialStart(unsigned int nTrial){
		if (e_log_details)
			log_file << "********************** New Trial *****************************\n";
	}
	void NSA::onWorkingMemoryTrained(unsigned int totalEpochs, ANN& wm, TrainingData& traindata){
		if (e_log_details & enum_log_working_memory) {
			log_file << "------------------- Working Memory ---------------------------\n";
			wm.save(log_file);
		}
	}
	void NSA::onRawModel(LTMSegment& ltm, ANNRawModel& model){
		if (e_log_details & enum_log_raw_model) {
			log_file << "---------------------- Raw Model ------------------------------\n";
			model.save(log_file);
		}
	}
	void NSA::onInterpretedModel(TaxonomyScheme& taxonomy, Interpreter& interpreter, ANNInterpretedModel& interpretedModel){
		if (e_log_details & enum_log_interpreted_model) {
			log_file << "------------------ Interpreted Model ---------------------------\n";
			interpretedModel.save(log_file);
		}
	}
	void NSA::onSymbolicRule(ModelFormatter& formatter, SymbolicRule& rule){
		if (e_log_details & enum_log_symbolic_rule) {
			log_file << "------------------- Symbolic Rule -----------------------------\n";
			rule.save(log_file);
		}
	}
	void NSA::onSuccess(SymbolicMachine& sm, TrainingData& result){
	}
	void NSA::onGiveup(unsigned int nTrial, unsigned int totalEpochs){
	}
	void NSA::onTrialEnd(unsigned int nTrial, unsigned int totalEpochs){
		if (e_log_details) {
			log_file << "********************** End Trial *****************************\n";
			log_file << "Last Trials:- " + std::to_string(LastTrials) + "\n";
			log_file << "Last Bit Fail:- " + std::to_string(LastBitFail) + "\n";
			log_file.flush();
		}
	}
}