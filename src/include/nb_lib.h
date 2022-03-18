#ifndef __NB_LIB_H
#define __NB_LIB_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string>
#include <vector>
#include <fstream>
#include <floatfann.h>
#include <fann_cpp.h>

#ifdef _MSC_VER
#define snprintf _snprintf_s
#endif

#undef min
#undef max
#include <exprtk.hpp>

namespace NEUROBASE{
	/*Type:- used to contain neural network inputs, outputs and weights*/
	typedef fann_type nb_type;


	/*Class: nb_exception

	Encapsulates NEUROBASE exceptions
	*/
	class nb_exception{
	public:
		/*Default constructor*/
		nb_exception(){};
		/*Constructor*/
		nb_exception(const char* param_message){ message = param_message; };
		/*Constructor*/
		nb_exception(std::string param_message){ message = param_message; };
		/*Destructor*/
		~nb_exception(){};

	protected:
		/*String Message*/
		std::string message;
	};



	/* Template Class: TVector

	Inherits the standard vector template, and additionally includes some customized behaviour like the print function
	*/
	template <typename T> class TVector : public std::vector<T>{
	public:
		/*Default constructor*/
		TVector(){};
		/*Constructor with vector size*/
		TVector(unsigned int nCount) :std::vector<T>(nCount){};
		/*Copy constructor*/
		TVector(const TVector& other) : std::vector<T>(other){};
		/*Destructor*/
		~TVector(){};

	public:
		/*Type def*/
		typedef vector<T> TMODEL_TYPE;

	public:
		virtual std::string format(){
			std::string ret;
			for (TMODEL_TYPE::iterator it = begin(); it != end(); it++)
				ret += it->format();
			ret += "\n";
			return ret;
		}
		/*Prints the vector contents*/
		virtual void print(){printf(format().data());};
		virtual void save(std::ofstream& out) { out << format(); };
		virtual void save(std::string& fileName){
			std::ofstream out(fileName);
			save(out);
			out.close();
		}
	};



	/* Class: nb_vector

	standard vector of nb_type. A special typed vector used in carrying vectors of neural network inputs, outputs, weights ... etc
	*/
	class nb_vector : public std::vector<nb_type>{
	public:
		/*Default constructor*/
		nb_vector(){};
		/*Constructor by vector size*/
		nb_vector(unsigned int count) :std::vector<nb_type>(count){};
		/*Constructor by start and end pointers*/
		nb_vector(const nb_type* start, const nb_type* end) : std::vector<nb_type>(start, end){};
		/*Copy constructor*/
		nb_vector(const nb_vector& copy) : std::vector<nb_type>(copy){
		};
		/*Searches for maximum value*/
		unsigned int getMax(){
			iterator max = begin();
			unsigned int max_index = 0;
			unsigned int i = 0;
			for (iterator it = begin(); it != end(); it++, i++){
				if (*it > *max) {
					max = it;
					max_index = i;
				}
			}
			return max_index;
		}
		std::string format(){
			std::string ret;
			for (iterator it = begin(); it != end(); it++)
				ret += std::to_string(*it) + ", ";
			ret += "\n";
			return ret;
		}
		/*Print vector contents to standard output*/
		void print(){ printf(format().data()); };
	};



	template <typename T1, typename T2> class TMemoryItem : public std::pair<T1, T2>{
	public:
		typedef std::pair<T1, T2> TPair;
	public:
		TMemoryItem(){};
		TMemoryItem(const TMemoryItem& other) :TPair(other){};
		TMemoryItem(const TPair& other) : TPair(other){};
		TMemoryItem(const T1& first, const T2& second) : TPair(std::pair<T1, T2>(first, second)){};
		~TMemoryItem(){};
	public:
		std::string format(){
			std::string ret;
			ret = "First:-\n";
			ret += first.format();
			ret += "Second:-\n";
			ret += second.format();
			return ret;
		}
		void print(){ printf(format().data()); };
	};



	template <typename T> class TMemoryCases : public TVector<T>{
	public:
		TMemoryCases(){};
		TMemoryCases(const TMemoryCases& other) :TVector<T>(other){};
		TMemoryCases(const TVector<T>& other) :TVector<T>(other){};
		~TMemoryCases(){};
	};



	namespace L0{
		/* Template Class: THandle

		Represents a handle object, used to encapsulate FANN objects.
		It has mainly a pointer for FANN network and a pointer for the encapsulated object contained by the FANN
		*/
		template <typename T> class THandle{
		public:
			/*Default constructor*/
			THandle(){ pANN = NULL; pObject = NULL; };
			/*constructor*/
			THandle(fann* param_ann, T* param_T){
				pANN = param_ann;
				pObject = param_T;
			};
			/*Copy Constructor*/
			THandle(const THandle& from){
				pANN = from.pANN;
				pObject = from.pObject;
			}
			/*Assignment Operator*/
			THandle& operator=(THandle& other){
				if (this != &other){
					pANN = other.pANN;
					pObject = other.pObject;
				}
				return *this;
			}
			/*Destructor*/
			~THandle(){};
		private:
			/*Neural network struct object*/
			fann* pANN;	
			/*Pointer to object whose this handle*/
			T* pObject;
		public:
			/*Get the handle Parent Neural Network Object*/
			fann* getParentObject(){ return pANN; };
			/*Get the handle opbject*/
			T* getObject(){ return pObject; };
			/*Returns next object handle*/
			THandle* getNext() { return new THandle<T>(pANN, pObject + 1); };
			/*Returns previous object handle*/
			THandle* getPrev() { return new THandle<T>(pANN, pObject - 1); };
			bool operator==(const THandle& other) {
				return (pANN == other.pANN && pObject == other.pObject);
			};
			bool operator!=(const THandle& other) {
				return !(pANN == other.pANN && pObject == other.pObject);
			};
		};


		template <typename T> class TANNObject {
		public:
			typedef typename THandle<T> HANDLE_TYPE;
			typedef typename TANNObject<T> ANNOBJECT_TYPE;
		public:
			/*Constructor*/
			TANNObject(HANDLE_TYPE* param_handle) { handle = param_handle; };
			/*Copy Constructor*/
			TANNObject(const ANNOBJECT_TYPE& other) { handle = new HANDLE_TYPE(*other.handle); };
			/*Assignment Operator*/
			ANNOBJECT_TYPE& operator=(ANNOBJECT_TYPE& other) {
				if (this != &other)
					handle = new HANDLE_TYPE(*other.handle);
				return *this;
			};
			/*Destructor*/
			~TANNObject() { if (handle) delete handle; };
		protected:
			/*Protected default constructor, to prohibit explicit use of it creating objects*/
			TANNObject() { handle = NULL; };
		public:
			/*Pure function to be implemented by ANN classes*/
			virtual std::string format() = 0;
			/*Prints formatted object*/
			void print() { printf(format().data()); };
			/*Saves formatted object to text file*/
			void save(std::string fileName) {
				std::ofstream out(fileName);
				out << format();
				out.close();
			};
			/*Returns object handle*/
			HANDLE_TYPE* getHandle() { return handle; };
			/*Returns previous object*/
			HANDLE_TYPE* getPrev() {
				return getHandle()->getPrev();
			};
			/*Returns next object*/
			HANDLE_TYPE* getNext() {
				return getHandle()->getNext();
			};
			THandle<fann>* getANN() {
				return new THandle<fann>(handle->getParentObject(), handle->getParentObject());
			};
			bool operator==(const ANNOBJECT_TYPE& other) {
				return *handle == *other.handle;
			};
			bool operator!=(const ANNOBJECT_TYPE& other) {
				return *handle != *other.handle;
			};
		protected:
			/*Handle*/
			HANDLE_TYPE* handle;
		};


		/*Activation Functions*/
		typedef fann_activationfunc_enum nb_activationfunc_enum;
		/*Training Algorithms*/
		typedef fann_train_enum nb_train_enum;
	}
}
#endif