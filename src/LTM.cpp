#include "LTM.h"

namespace NEUROBASE{
	namespace L2{
		const std::string LTM::ALPHA_NAME_STRING = "alpha";
		const std::string LTM::BETA_NAME_STRING = "beta";

		MultiANNRawModel LTM::modelANN(L0::ANN& wm){
			MultiANNRawModel ret;
			for (unsigned int i = 0; i < size(); i++)
				ret.push_back(at(i).modelANN(wm));
			return ret;
		}

		unsigned int LTM::getBusWidth(){
			if (size() == 0)
				throw nb_exception("LTM segments count must be greater than zero");
			return at(0).getBusWidth();
		}

		unsigned int LTM::getNumClasses(){
			if (size() == 0)
				throw nb_exception("LTM segments count must be greater than zero");
			return at(0).getNumClasses();
		}

		void LTM::createFromFiles(const std::string& fileNameTemplate){
			unsigned int i = 0;
			bool bCreated = false;
			unsigned int busWidth = 0;
			unsigned int numClasses = 0;
			do{
				char bufAlpha[100];
				char bufBeta[100];
				snprintf(bufAlpha, sizeof(bufAlpha), fileNameTemplate.c_str(), ALPHA_NAME_STRING.c_str(), i);
				snprintf(bufBeta, sizeof(bufBeta), fileNameTemplate.c_str(), BETA_NAME_STRING.c_str(), i);
				LTMSegment* pLTMSegment = new LTMSegment();
				bCreated = pLTMSegment->createFromFiles(bufAlpha, bufBeta);
				if (bCreated){
					push_back(*pLTMSegment);
					if (i == 0){
						busWidth = pLTMSegment->getBusWidth();
						numClasses = pLTMSegment->getNumClasses();
					}
					else if (busWidth != pLTMSegment->getBusWidth() || numClasses != pLTMSegment->getNumClasses())
						throw nb_exception("All ltm segments should have the same bus width and number of classes");
				}
				i++;
				delete pLTMSegment;
			} while (bCreated);
		}

		void LTM::save(const std::string& fileNameTemplate){
			for (unsigned int i = 0; i < size(); i++){
				char bufAlpha[100];
				char bufBeta[100];
				snprintf(bufAlpha, sizeof(bufAlpha), fileNameTemplate.c_str(), ALPHA_NAME_STRING.c_str(), i);
				snprintf(bufBeta, sizeof(bufBeta), fileNameTemplate.c_str(), BETA_NAME_STRING.c_str(), i);
				at(i).save(bufAlpha, bufBeta);
			}
		}
	}
}