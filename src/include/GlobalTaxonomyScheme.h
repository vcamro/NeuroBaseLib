#ifndef __MY_TAXONOMY_SCHEME_H
#define __MY_TAXONOMY_SCHEME_H

#include "nb_lib.h"
#include "Taxonomy.h"

namespace NEUROBASE{
	namespace L1{
		/* Class: GlobalTaxonomyScheme

		Encapsulates generic taxonomy scheme
		*/
		class GlobalTaxonomyScheme : public TaxonomyScheme{
		public:
			/*Default constructor*/
			GlobalTaxonomyScheme(){};
			/*Copy constructor*/
			GlobalTaxonomyScheme(const GlobalTaxonomyScheme& other) :TaxonomyScheme(other){};
			
		public:
			/*Input States Taxonomy name*/
			static const std::string STR_TAXONOMY_INPUT_STATES;
			/*Paird Operator / Relation Taxonomy name*/
			static const std::string STR_TAXONOMY_PAIRED_OPERATOR;
			/*Input Term Type taxonomy name*/
			static const std::string STR_TAXONOMY_TERM_TYPE;
			/*Input prt type taxonomy name*/
			static const std::string STR_TAXONOMY_PART_TYPE;
			/*Inactive input state class name*/
			static const std::string STR_CLASS_INACTIVE;
			/*Transfered input state class name*/
			static const std::string STR_CLASS_TRANSFERED;
			/*Inverted input state class name*/
			static const std::string STR_CLASS_INVERTED ;
			/*Paired operator / first Relation class name*/
			static const std::string STR_CLASS_R1; //OR
			/*Paired operator / Second relation class name*/
			static const std::string STR_CLASS_R2; // AND
			/*Simple term type class name*/
			static const std::string STR_CLASS_SIMPLE;
			/*Compound term type class name*/
			static const std::string STR_CLASS_COMPOUND;
			/*Used to describe both simple and compound class name. 
			Describes also both primary and secondary part type*/
			static const std::string STR_CLASS_BOTH;
			/*Primary input part type*/
			static const std::string STR_CLASS_PRIMARY;
			/*Secondery input part type*/
			static const std::string STR_CLASS_SECONDERY;
			/*Index of input states taxonomy in scheme*/
			static const unsigned int INDEX_INPUT_STATES;
			/*Index of paired operator taxonomy in scheme*/
			static const unsigned int INDEX_PAIRED_OPERATOR;
			/*Index of term type taxonomy in scheme*/
			static const unsigned int INDEX_TERM_TYPE;
			/*Index of part type taxonom in scheme*/
			static const unsigned int INDEX_PART_TYPE;
			/*Creates taxonomy scheme using the above constants*/
			static GlobalTaxonomyScheme createBooleanTaxonomyModel();
		};
	}
}

#endif