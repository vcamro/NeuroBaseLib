#include "GlobalTaxonomyScheme.h"

namespace NEUROBASE{
	namespace L1{
		const std::string GlobalTaxonomyScheme::STR_TAXONOMY_INPUT_STATES = "InputStates";
		const std::string GlobalTaxonomyScheme::STR_TAXONOMY_PAIRED_OPERATOR = "PairedOperator";
		const std::string GlobalTaxonomyScheme::STR_TAXONOMY_TERM_TYPE = "InputTermType";
		const std::string GlobalTaxonomyScheme::STR_TAXONOMY_PART_TYPE = "ExpressionPartType";
		const std::string GlobalTaxonomyScheme::STR_CLASS_INACTIVE = "Inactive";
		const std::string GlobalTaxonomyScheme::STR_CLASS_TRANSFERED = "Transfered";
		const std::string GlobalTaxonomyScheme::STR_CLASS_INVERTED = "Inverted";
		const std::string GlobalTaxonomyScheme::STR_CLASS_R1 = "R1";
		const std::string GlobalTaxonomyScheme::STR_CLASS_R2 = "R2";
		const std::string GlobalTaxonomyScheme::STR_CLASS_SIMPLE = "Simple";
		const std::string GlobalTaxonomyScheme::STR_CLASS_COMPOUND = "Compound";
		const std::string GlobalTaxonomyScheme::STR_CLASS_BOTH = "Both";
		const std::string GlobalTaxonomyScheme::STR_CLASS_PRIMARY = "Primary";
		const std::string GlobalTaxonomyScheme::STR_CLASS_SECONDERY = "Secondery";
		const unsigned int GlobalTaxonomyScheme::INDEX_INPUT_STATES = 0;
		const unsigned int GlobalTaxonomyScheme::INDEX_PAIRED_OPERATOR = 1;
		const unsigned int GlobalTaxonomyScheme::INDEX_TERM_TYPE = 2;
		const unsigned int GlobalTaxonomyScheme::INDEX_PART_TYPE = 3;

		GlobalTaxonomyScheme GlobalTaxonomyScheme::createBooleanTaxonomyModel(){
			GlobalTaxonomyScheme ret;
			Taxonomy InputStates(STR_TAXONOMY_INPUT_STATES, Taxonomy::InputTaxonomy);
			InputStates.push_back(ClassDef(STR_CLASS_INACTIVE));
			InputStates.push_back(ClassDef(STR_CLASS_TRANSFERED));
			InputStates.push_back(ClassDef(STR_CLASS_INVERTED));
			ret.push_back(InputStates);

			Taxonomy PairedOperator(STR_TAXONOMY_PAIRED_OPERATOR, Taxonomy::RelationTaxonomy);
			PairedOperator.push_back(ClassDef(STR_CLASS_R1));
			PairedOperator.push_back(ClassDef(STR_CLASS_R2));
			ret.push_back(PairedOperator);

			Taxonomy InputTermType(STR_TAXONOMY_TERM_TYPE, Taxonomy::InputTaxonomy);
			InputTermType.push_back(ClassDef(STR_CLASS_SIMPLE));
			InputTermType.push_back(ClassDef(STR_CLASS_COMPOUND));
			InputTermType.push_back(ClassDef(STR_CLASS_BOTH));
			ret.push_back(InputTermType);

			Taxonomy ExpressionPartType(STR_TAXONOMY_PART_TYPE, Taxonomy::InputTaxonomy);
			ExpressionPartType.push_back(ClassDef(STR_CLASS_PRIMARY));
			ExpressionPartType.push_back(ClassDef(STR_CLASS_SECONDERY));
			ExpressionPartType.push_back(ClassDef(STR_CLASS_BOTH));
			ret.push_back(ExpressionPartType);

			return ret;
		};
	}
}