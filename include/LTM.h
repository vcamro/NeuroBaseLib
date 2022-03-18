#ifndef __LTM_H
#define __LTM_H

#include "nb_lib.h"
#include "LTMSegment.h"

namespace NEUROBASE{
	using namespace NEUROBASE::L1;
	namespace L2{
		typedef TVector<ANNRawModel> MultiANNRawModel;
		class LTM : public std::vector<LTMSegment>
		{
		public:
			LTM(){};
			~LTM(){};
		public:
			static const std::string ALPHA_NAME_STRING;
			static const std::string BETA_NAME_STRING;
		public:
			MultiANNRawModel modelANN(L0::ANN& wm);
			void createFromFiles(const std::string& fileNameTemplate);
			void save(const std::string& fileNameTemplate);
			unsigned int getBusWidth();
			unsigned int getNumClasses();
		};
	}
}
#endif