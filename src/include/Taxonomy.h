#ifndef __TAXONOMY_H
#define __TAXONOMY_H

#include "nb_lib.h"
#include <string>

namespace NEUROBASE{
	using namespace L0;
	namespace L1{
		/* Class: ClassDef

		Represents single taxonomy class of Neuron Model
		*/
		class ClassDef{
		public:
			/*Default constructor*/
			ClassDef(){};
			/*Constructor takes name*/
			ClassDef(std::string param_name):name(param_name){};
			/*Copy constructor*/
			ClassDef(const ClassDef& other){ name = other.getName(); };
			/*Destructor*/
			~ClassDef(){};
		private:
			/*Class definition name*/
			std :: string name;
		public:
			/*Returns class definition name*/
			const char* getName() const { return name.data(); };
			std::string format(){return name + ", ";};
			/*Prints class definition*/
			void print(){ printf(format().data()); };
		};



		/* Class: Taxonomy

		Every cluster of class definitions model are related to single taxonomy
		Ther are two types of taxonomy, relation taxonomy describes the relation combining the inputs together
		and input taxonomy describes the effect single input
		*/
		class Taxonomy : public TVector<ClassDef>{
		public:
			/*Taxonomy type*/
			typedef enum{ InputTaxonomy = 0, RelationTaxonomy = 1 } TaxonomyType;
			/*Default constructor*/
			Taxonomy(){};
			/*Copy constructor*/
			Taxonomy(const Taxonomy& other) :TVector<ClassDef>(other){
				name = other.getName();//name
				type = other.getType();//type
			}
			/*Constructor*/
			Taxonomy(std::string param_name, TaxonomyType param_type) :name(param_name),type(param_type) {};
			/*Destructor*/
			~Taxonomy(){};
		private:
			/*Taxonomy name*/
			std::string name;
			/*Taxonomy type*/
			TaxonomyType type;
		public:
			/*Returns taxonomy type*/
			TaxonomyType getType() const { return type; };
			/*Returns taxonomy name*/
			const char* getName() const { return name.data(); };
			/*Returns number of defined classes for that taxonomy*/
			unsigned int getNumClasses() const { return size(); };
		};



		/* Class: TaxonomyScheme

		Taxonomy scheme is a complete set of taxonomies that are completely capable to describe the neuron behaviour
		It is assumed that there is a universal taxonomy schem that can describe any neuron in any domain (needs to be proved)
		It is composed of single relation taxonomy composed of tw classes, and three taxonomies 
		one for describing how input is transfered (inactive, transfered, inverted), one for (Simple/compund parts) 
		and one for (Primary / Secondery) parts
		*/
		class TaxonomyScheme : public TVector<Taxonomy>{
		public:
			/*Default constructor*/
			TaxonomyScheme(){};
			/*Copy constructor*/
			TaxonomyScheme(const TaxonomyScheme& other) :TVector<Taxonomy>(other){};
			/*Destructor*/
			~TaxonomyScheme(){};
		};
	}
}

#endif