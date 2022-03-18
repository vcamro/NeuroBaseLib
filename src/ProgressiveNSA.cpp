#include "ProgressiveNSA.h"
#include "SymbolicRuleInspector.h"

namespace NEUROBASE{
	unsigned int ProgressiveNSA::MAX_BREAKDOWN_TRIALS_DEFAULT = 7;
	unsigned int ProgressiveNSA::CHUNK_SIZE_DEFAULT = 64;
	unsigned int ProgressiveNSA::NUM_LTM_SEGMENT_HIDDEN_NODES = 49;

	ProgressiveNSA::ProgressiveNSA() {
		init();
	}
	ProgressiveNSA::~ProgressiveNSA() {
		LastMultiInterpretedModel.clear();
		LastMultiSymbolicRules.clear();
	}

	void ProgressiveNSA::init(){
		maxBreakdownTrials = MAX_BREAKDOWN_TRIALS_DEFAULT;
		nLTMSegmentHiddenNodes = NUM_LTM_SEGMENT_HIDDEN_NODES;
		STMAbsoluteCounter = 0;
		STMCounter = 0;
		nChunkSize = CHUNK_SIZE_DEFAULT;
		bBreadown = false;
		progressiveNSA_log_file.open("ProgressiveNSA.log", std::ofstream::out | std::ofstream::app);
	}

	void ProgressiveNSA::reset(){
		NSA::reset();
		stm.clear();
		STMCounter = 0;
		LastMultiRawModel.clear();
	}

	ANNInterpretedModel ProgressiveNSA::consolidate(LTM& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, MultiANNInterpretedModel& interpreted, MultiANNSymbolicRules& rules){
		ANNInterpretedModel ret;
		SymbolicRuleInspector inspector;
		MultiANNInspectedSymbolicRule inspected = inspector.inspect(rules, wm);
		NSA nsa;
		nsa.setLogDetails(getLogDetails());
		nsa.setTrialMaxEpochs(getTrialMaxEpochs());
		Interpreter interpreter(ltm.getBusWidth() - 1);
		nsa.setMaxTrials(maxBreakdownTrials);
		for (unsigned int i = 0; i < wm.getNumLayers(); i++){//For every layer
			Layer layer = wm[i];
			ret.push_back(LayerInterpretedModel());
			// Default is segment zero for num inputs of layer zero 
			//which equals number of ANN inputs and this will not change from segment to segment
			ret[i].setNumInputs(interpreted[0][i].getNumInputs());
			for (unsigned int j = 0; j < layer.getNumNodes(); j++){// For every node
				unsigned int k = inspected.getANNWithMinNodeMSE(i, j);
				if (inspected[k][i][j].getInspectedMSE() == 0 || bBreadown == false){
					ltm[k].modelSynthesisNeuron(wm[i].getNode(j));
					ret[i].push_back(interpreted[k][i][j]);
				}
				else{
					ANN isolatedANN = layer.getNode(j).isolate(interpreted[0][i][j].IgnoreMask);
					TrainingData trainData = SymbolicMachine::generateBooleanCases(isolatedANN.getNumInputs());
					isolatedANN.run(trainData);
					SymbolicMachine::quantizetBooleanOutputs(trainData);
					SymbolicRule rule = nsa.symbolize(ltm, isolatedANN, taxonomy, formatter, trainData);
					if (nsa.getLastBitFail() == 0){
						ANNInterpretedModel interpretedModel = nsa.getLastInterpretedModel();
						interpretedModel[1][0].IgnoreMask = interpreted[0][i][j].IgnoreMask;
						//NeuronInterpretedModel neuronInterpretedModel = interpretedModel[1][0];
						//neuronInterpretedModel.IgnoreMask = interpreted[0][i][j].IgnoreMask;
						NeuronRawModel neuronRawModel = interpreter.reverseInterpret(taxonomy, interpretedModel[1][0]);
						neuronRawModel.TopologyModel = interpreted[0][i][j].TopologyModel;
						if (!stm.exists(wm[i].getNode(j)) && !stm.exists(neuronRawModel))
							stm.push_back(LTMPair(neuronRawModel, wm[i].getNode(j)));
						else
							STMCounter++;
						// Flush STM cases to LTM
						if (stm.size() >= nChunkSize || (stm.size()>0 && STMCounter >= nChunkSize)){
							LTMSegment newMemSegment;
							unsigned int hiddenLayers[1] = { nLTMSegmentHiddenNodes };
							newMemSegment.create(ltm.getBusWidth(), ltm.getNumClasses(), std::vector<unsigned int>(hiddenLayers, hiddenLayers + 1));
							printf("\n\nTraining new LTM Segment ...\n");
							newMemSegment.train(stm);
							// If LTM Segment trained successfully
							//if (newMemSegment.getAlpha()->getMSE() <= LTMSegment::DESIRED_ALPHA_ERROR_DEFAULT && newMemSegment.getBeta()->getMSE() <= LTMSegment::DESIRED_BETA_ERROR_DEFAULT){
								ltm.push_back(newMemSegment);
								printf("New segment is added to LTM\n");
							//}
							// Save log of STM cases
							std::string strAlphaFileName = ".\\log\\STM_TRAIN_ALPHA_" + std::to_string(STMAbsoluteCounter) + ".train";
							std::string strBetaFileName = ".\\log\\STM_TRAIN_BETA_" + std::to_string(STMAbsoluteCounter) + ".train";
							TrainingData AlphaData = newMemSegment.convertAlphaCases(stm);
							TrainingData BetaData = newMemSegment.convertBetaCases(stm);
//							AlphaData.save(strAlphaFileName);
//							BetaData.save(strBetaFileName);
							STMAbsoluteCounter++;
							// Clear STM Cases
							stm.clear();
							STMCounter = 0;
						}
						formatter.alignInterpretedModelToANNStructure(interpretedModel, isolatedANN);
						ret[i].push_back(interpretedModel[1][0]);
					}
					else
						ret[i].push_back(interpreted[k][i][j]);
				}
				ret[i].setNumInputs(interpreted[k][i].getNumInputs());
				ret[i][j].TopologyModel = interpreted[0][i][j].TopologyModel;
			}
		}
		return ret;
	}

	SymbolicRule ProgressiveNSA::symbolize(LTM& ltm, ANN& wm, TaxonomyScheme& taxonomy, ModelFormatter& formatter, TrainingData& trainData){
		bool bTrained = false;
		bool bGiveUp = false;
		SymbolicRule ret;
		wm.enableCallback();
		reset();
		Interpreter interpreter(ltm.getBusWidth() - 1);
		unsigned int lastLTMSize = 0;
		unsigned int lastSTMSize = 0;
		while (!bTrained && !bGiveUp){
			onTrialStart(LastTrials);
			lastLTMSize = ltm.size();
			lastSTMSize = stm.size();
			wm.trainOnData(trainData, TrialMaxEpochs, TrialEpchsBetweenReports, TrialDesiredError);
			//do {
			//	wm.trainOnData(trainData, TrialMaxEpochs, TrialEpchsBetweenReports, TrialDesiredError);
			//	if (wm.getBitFail() > 0)
			//		wm.randomizeWeights(/*LTMSegment::MIN_WEIGHT, LTMSegment::MAX_WEIGHT*/-1.0f, 1.0f);
			//} while (wm.getBitFail() > 0);
			onWorkingMemoryTrained(LastTotalEpochs, wm, trainData);
			LastTotalEpochs += wm.getLastEpochs();
			LastMultiRawModel = ltm.modelANN(wm);
			onRawModel(ltm, LastMultiRawModel);
			LastMultiInterpretedModel = interpreter.interpret(taxonomy, LastMultiRawModel);
			onInterpretedModel(taxonomy, interpreter, LastMultiInterpretedModel);
			formatter.alignInterpretedModelToANNStructure(LastMultiInterpretedModel, wm);
			MultiANNSymbolicRules LastMultiSymbolicRules = formatter.formatANNRules(LastMultiInterpretedModel);
			onSymbolicRule(formatter, LastMultiSymbolicRules);
			ANNInterpretedModel LastInterpretedModel = consolidate(ltm, wm, taxonomy, formatter, LastMultiInterpretedModel, LastMultiSymbolicRules);
			onInterpretedModel(taxonomy, interpreter, LastInterpretedModel);
			//formatter.alignInterpretedModelToANNStructure(LastInterpretedModel, wm);
			SymbolicRule LastSymbolicRule = formatter.format(LastInterpretedModel);
			onSymbolicRule(formatter, LastSymbolicRule);
			SymbolicMachine sm;
			TrainingData result = sm.testSymbolicRule(LastSymbolicRule, trainData);
			//if ((lastLTMSize == ltm.size() && lastSTMSize == stm.size() && LastBitFail == sm.getBitFail()))
				//wm.initWeights(trainData);
				//wm.randomizeWeights(LTMSegment::MIN_WEIGHT, LTMSegment::MAX_WEIGHT);
				//wm.randomizeWeights(/*LTMSegment::MIN_WEIGHT, LTMSegment::MAX_WEIGHT*/-1.0f, 1.0f);
			LastBitFail = sm.getBitFail();
			LastMSE = sm.getMSE();
			result.save("result.data");
			trainData.save("train.data");
			if (sm.getBitFail() <= DesiredBitFail){
				bTrained = true;
				onSuccess(sm, result);
			}
			if (LastTrials > MaxTrials /*|| LastTotalEpochs > MaxEpochs*/){
				bGiveUp = true;
				onGiveup(LastTrials, LastTotalEpochs);
			}
			ret = LastSymbolicRule;
			LastTrials++;
			onTrialEnd(LastTrials, LastTotalEpochs);
			if (bVerbose || bTrained || bGiveUp){
				printf("-----------------------------------------------------\n");
				LastSymbolicRule.print();
				printf(".....................................................\n");
				printf("Trained = %d, Giveup = %d\n", bTrained, bGiveUp);
				printf("Bit Fail = %d\n", LastBitFail);
				printf("MSE = %f \n", LastMSE);
				printf("Trials = %d\n", LastTrials);
				printf("Total Epochs = %d\n", LastTotalEpochs);
				printf("LTM Segments = %d\n", ltm.size());
				printf("STM buffer size = %d\n", stm.size());
				printf("-----------------------------------------------------\n");
			}
		}
		return ret;
	}

	void ProgressiveNSA::onTrialStart(unsigned int nTrial)
	{
		if (e_progressiveNSA_log_details)
			progressiveNSA_log_file << "********************** New Trial *****************************\n";
	}

	void ProgressiveNSA::onWorkingMemoryTrained(unsigned int totalEpochs, ANN & wm, TrainingData & traindata)
	{
		//NSA::onWorkingMemoryTrained(totalEpochs, wm, traindata);
		if (e_progressiveNSA_log_details & enum_log_working_memory) {
			progressiveNSA_log_file << "------------------- Working Memory ---------------------------\n";
			wm.save(progressiveNSA_log_file);
		}
	}

	void ProgressiveNSA::onInterpretedModel(TaxonomyScheme & taxonomy, Interpreter & interpreter, ANNInterpretedModel & interpretedModel)
	{
		//NSA::onInterpretedModel(taxonomy, interpreter, interpretedModel);
		if (e_progressiveNSA_log_details & enum_log_consolidated_model) {
			progressiveNSA_log_file << "----------------- Consolidated Model ---------------------------\n";
			interpretedModel.save(progressiveNSA_log_file);
		}
	}

	void ProgressiveNSA::onSymbolicRule(ModelFormatter & formatter, SymbolicRule & rule)
	{
		//NSA::onSymbolicRule(formatter, rule);
		if (e_progressiveNSA_log_details & enum_log_consolidated_symbolic_rule) {
			progressiveNSA_log_file << "----------------- Consolidated Rule ---------------------------\n";
			rule.save(progressiveNSA_log_file);
		}
	}

	void ProgressiveNSA::onRawModel(LTM& ltm, MultiANNRawModel& model){
		if (e_progressiveNSA_log_details & enum_log_raw_model) {
			progressiveNSA_log_file << "---------------------- Raw Model ------------------------------\n";
			model.save(progressiveNSA_log_file);
		}
	}
	void ProgressiveNSA::onInterpretedModel(TaxonomyScheme& taxonomy, Interpreter& interpreter, MultiANNInterpretedModel& interpretedModel){
		if (e_progressiveNSA_log_details & enum_log_interpreted_model) {
			progressiveNSA_log_file << "------------------ Interpreted Model ---------------------------\n";
			interpretedModel.save(progressiveNSA_log_file);
		}
	}
	void ProgressiveNSA::onSymbolicRule(ModelFormatter& formatter, MultiANNSymbolicRules& rule){
		if (e_progressiveNSA_log_details & enum_log_symbolic_rule) {
			progressiveNSA_log_file << "------------------- Symbolic Rule -----------------------------\n";
			rule.save(progressiveNSA_log_file);
		}
	}

	void ProgressiveNSA::onSuccess(SymbolicMachine & sm, TrainingData & result)
	{
	}

	void ProgressiveNSA::onGiveup(unsigned int nTrial, unsigned int totalEpochs)
	{
	}

	void ProgressiveNSA::onTrialEnd(unsigned int nTrial, unsigned int totalEpochs)
	{
		if (e_progressiveNSA_log_details) {
			progressiveNSA_log_file << "********************** End Trial *****************************\n";
			progressiveNSA_log_file << "Last Trials:- " + std::to_string(LastTrials) + "\n";
			progressiveNSA_log_file << "Last Bit Fail:- " + std::to_string(LastBitFail) + "\n";
			progressiveNSA_log_file.flush();
		}
	}

}
