/**
 *	@file	Sinus.hpp
 * 	@brief 	Sinus class (standalone version) header file
 * 	@author	
 * 	@date	2023-01
 * 
 */
#ifndef __SINUS_H__
#define	__SINUS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <filesystem>
#include "ComputeParameters.h"

constexpr	unsigned int	defaultNbPoints = 100;	/**< Default number of points : 100	*/
constexpr	float 			defaulttStart = 0;		/**< Default start time : 0 (sec)	*/
constexpr	float 			defaulttStop = 1;		/**< Default stop time : 1 (sec)	*/

constexpr float defaultA0 = 1;
constexpr float defaultAmplitude = 1;
constexpr float defaultOmega = 2*std::numbers::pi;
constexpr float defaultPhi0 = 0;

/**
 *	Type SinusParam : Signal caractéristics
 * 
 *    	sin_tn(tn) = A0 + amplitude * sin(omega*tn + phi0)
 */
struct	SinusParam{
		// 
		float 	A0;							/**<  Offset			*/
		float 	Amplitude;					/**<  Amplitude		*/
		float 	Omega;						/**<  Angular frequency  (rad.s-1) */
		float 	Phi0;						/**<  Phase at t=0		*/
	};

/**
 *	Type SignalPoint 
 */
struct	SignalPoint{
		float	tn;				/**< t (X) coordinates of the point		*/
		float 	sig_tn;			/**< s(t) (Y) coordinates of the point 	*/
	};

/**
 *	helper Class for computing the signal
 * 
 * 	Could be unnecessary... really ?
 * 	What about :
 * 		- Single Responsability Service (SRP) ? Is the Sinus class is a "container" or an "algorithm" ? Should not be both... With this helper, the Sinus is clearly a container, the helper an algorithm.
 * 		- Open Close Principle (OCP) : is the Sinus more or less extensible with or without this class (parallel calculus...)
 * 		- Dont Repeat Yourself (DRY) : The computing class (function) could be easily reused
 *  	- Testability : How the compute function (private) could have been tested without this helper class ?  
 * 
 */
class SinusComputeHelper{
	public:
		SinusComputeHelper() = default;
		std::vector<SignalPoint> Compute(const SinusParam &SinusParameters, const ComputeParameters &SimulParameters) const noexcept;
		~SinusComputeHelper() = default;
};


// approx equality between 2 floats

bool approxEqual(float a, float b, float epsilon = 0.001f) noexcept;


/**
 *	Sinus class (standalone version)
 */ 	
class Sinus{
	private:


    SinusParam Parameters{defaultA0, defaultAmplitude, defaultOmega, defaultPhi0};	/**< Sinus parameters */
	
	mutable	bool	needToRecompute{true};											/**< Flag set if the signal needs to be "recomputed" (change of params)	*/ 
		
	SinusComputeHelper	helper{};													/**< Composition of the helper class		*/
	
	/**
	 * Compute (private) method
	 * 		links to the Compute public method of the helper
	 * 
	 * const : callable with a const object  
	 * noexcept : this method throws no exception
	 * 
	 */
    std::vector<SignalPoint> tabSignal;
    const ComputeParameters &SimulParams;
	void compute() const noexcept {this->tabSignal = this->helper.Compute(this->Parameters, this->SimulParams);};
	
	// private accessors
	[[nodiscard]] bool	getNeedToRecompute() const noexcept {return this->needToRecompute;};
	void	setNeedToRecompute(bool value) const noexcept {this->needToRecompute = value;};
	
	public:
	// create constructor

	// SMF
	Sinus() = default;						/**< Default Ctor	*/
	
	virtual ~Sinus() = default;				/**< Default Dtor	*/
	
	Sinus(const Sinus&) = default;			/**< Default Copy Ctor	*/
	Sinus& operator=(const Sinus&) = default;	/**< Default copy assignment operator	*/
	
	Sinus(Sinus&&) noexcept = default;			/**< Default move Ctor	*/
	Sinus& operator=(Sinus&&) = default;		/**< Default move assignment operator	*/
	
	
	
	// Public Accessors
	/**
	 * getter (public) for the A0 parameter 
	 * 
	 * const : callable with a const object  
	 * noexcept : this method throws no exception
	 * 
	 * @return value of A0 parameter (inside the Parameters structure)
	 * [[nodiscard]] : the return value should not be discarded (compiler warning)
	 */
	[[nodiscard]] float 	getA0()const  noexcept {
        return this->Parameters.A0;
    };
	
	/**
	 * setter (public) for the A0 parameter (inside the Parameters structure)
	 * 
	 * @param[in]	A0	Value of A0
	 * noexcept : this method throws no exception
	 */
	void	setA0(float A0) noexcept {/*this->Parameters.A0 = A0;setNeedToRecompute(true);*/};
	
	/**
	 * getter (public) for the Omega parameter 
	 * 
	 * const : callable with a const object  
	 * noexcept : this method throws no exception
	 * 
	 * @return value of Omega parameter (rad/s) (inside the Parameters structure)
	 * [[nodiscard]] : the return value should not be discarded (compiler warning)
	 */	
	[[nodiscard]] float 	getOmega()const noexcept{
        return(this->Parameters.Omega);
    };
	
	/**
	 * setter (public) for the Omega parameter (inside the Parameters structure)
	 * 		This value must be >= 0
	 * @param[in]	_Omega	Value of Omega
	 * @throw 	std::domain_error("Omega can’t be negative.") if the given parameter is negative
	 */
	void	setOmega(float _Omega){
        if (_Omega < 0) throw std::domain_error("Omega can’t be negative.") ;
        this->Parameters.Omega = _Omega;setNeedToRecompute(true);
    };
		
	
	/**
	 * 	generate method
	 * 		
	 * 	@param[in] 	FileName(=defaultFileName)	The complete path of the data file to write.	
	 * 
	 * 	@return : Size of the generated file (bytes)
	 * 
	 * @throw  std::ios::exceptions 
	 */
	unsigned int	generate(const std::filesystem::path FileName /*=defaultFileName*/)const;	// return value can be discarded
};



#endif

