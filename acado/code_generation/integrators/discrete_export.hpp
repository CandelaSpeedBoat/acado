/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2014 by Boris Houska, Hans Joachim Ferreau,
 *    Milan Vukov, Rien Quirynen, KU Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC)
 *    under supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */



/**
 *    \file include/acado/code_generation/integrators/discrete_export.hpp
 *    \author Rien Quirynen
 *    \date 2013
 */


#ifndef ACADO_TOOLKIT_DT_EXPORT_HPP
#define ACADO_TOOLKIT_DT_EXPORT_HPP

#include <acado/code_generation/integrators/integrator_export.hpp>

#include <acado/code_generation/export_algorithm_factory.hpp>


BEGIN_NAMESPACE_ACADO


/** 
 *	\brief Allows to export a tailored discrete-time 'integrator' for fast model predictive control.
 *
 *	\ingroup NumericalAlgorithms
 *
 *	The class DiscreteTimeExport allows to export a tailored discrete-time 'integrator'
 *	for fast model predictive control.
 *
 *	\author Rien Quirynen
 */
class DiscreteTimeExport : public IntegratorExport
{
    //
    // PUBLIC MEMBER FUNCTIONS:
    //
    public:

		/** Default constructor. 
		 *
		 *	@param[in] _userInteraction		Pointer to corresponding user interface.
		 *	@param[in] _commonHeaderName	Name of common header file to be included.
		 */
        DiscreteTimeExport(	UserInteraction* _userInteraction = 0,
							const std::string& _commonHeaderName = ""
							);

		/** Copy constructor (deep copy).
		 *
		 *	@param[in] arg		Right-hand side object.
		 */
        DiscreteTimeExport(	const DiscreteTimeExport& arg
							);

        /** Destructor. 
		 */
        virtual ~DiscreteTimeExport( );

		/** Assignment operator (deep copy).
		 *
		 *	@param[in] arg		Right-hand side object.
		 */
		DiscreteTimeExport& operator=(	const DiscreteTimeExport& arg
										);


		/** Initializes export of a tailored integrator.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setup( );


		/** Assigns Differential Equation to be used by the integrator.
		 *
		 *	@param[in] rhs		Right-hand side expression.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		
		virtual returnValue setDifferentialEquation( const Expression& rhs );


		/** Sets a polynomial NARX model to be used by the integrator.
		 *
		 *	@param[in] delay		The delay for the states in the NARX model.
		 *	@param[in] parms		The parameters defining the polynomial NARX model.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setNARXmodel( const uint delay, const DMatrix& parms );


        /** Sets up the output with the grids for the different output functions.									\n
		*                                                                      										\n
		*  \param outputGrids_	  	The vector containing a grid for each output function.			  				\n
		*  \param rhs 	  	  		The expressions corresponding the output functions.								\n
		*                                                                      										\n
		*  \return SUCCESSFUL_RETURN
		*/
		virtual returnValue setupOutput(  const std::vector<Grid> outputGrids_,
									  	  const std::vector<Expression> rhs );


		/** Sets up the output with the grids for the different output functions.									\n
		 *                                                                      										\n
		 *  \param outputGrids_	  		The vector containing a grid for each output function.			  			\n
		 *  \param _outputNames 	  		The names of the output functions.									  		\n
		 *  \param _diffs_outputNames 	The names of the functions, evaluating the derivatives of the outputs.		\n
		 *  \param _dims_output 			The dimensions of the output functions.										\n
		 *                                                                      										\n
		 *  \return SUCCESSFUL_RETURN
		 */
		virtual returnValue setupOutput(  const std::vector<Grid> outputGrids_,
									  	  const std::vector<std::string> _outputNames,
									  	  const std::vector<std::string> _diffs_outputNames,
										  const std::vector<uint> _dims_output );


		/** Sets up the output with the grids for the different output functions.										\n
		 *                                                                      										\n
		 *  \param outputGrids_	  			The vector containing a grid for each output function.			  			\n
		 *  \param _outputNames 	  		The names of the output functions.									  		\n
		 *  \param _diffs_outputNames 		The names of the functions, evaluating the derivatives of the outputs.		\n
		 *  \param _dims_output 			The dimensions of the output functions.										\n
		 *  \param _outputDependencies		A separate dependency matrix for each output.								\n
		 *                                                                      										\n
		 *  \return SUCCESSFUL_RETURN
		 */
		virtual returnValue setupOutput(  const std::vector<Grid> outputGrids_,
									  	  const std::vector<std::string> _outputNames,
									  	  const std::vector<std::string> _diffs_outputNames,
										  const std::vector<uint> _dims_output,
										  const std::vector<DMatrix> _outputDependencies );


		/** Adds all data declarations of the auto-generated integrator to given list of declarations.
		 *
		 *	@param[in] declarations		List of declarations.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue getDataDeclarations(	ExportStatementBlock& declarations,
													ExportStruct dataStruct = ACADO_ANY
													) const;


		/** Adds all function (forward) declarations of the auto-generated integrator to given list of declarations.
		 *
		 *	@param[in] declarations		List of declarations.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue getFunctionDeclarations(	ExportStatementBlock& declarations
														) const;



		/** Exports source code of the auto-generated integrator into the given directory.
		 *
		 *	@param[in] code				Code block containing the auto-generated integrator.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue getCode(	ExportStatementBlock& code
										);



	protected:


		/** Returns the largest global export variable.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		ExportVariable getAuxVariable() const;


		/** Returns whether the right-hand side and its derivatives are evaluated in one function, which needs
		 *  CG_MERGE_RHS_AND_DIFFS and a model with only nonlinear states given as an expression.
		 *
		 *	\return true if rhs_diffs is used instead of rhs and diffs_rhs
		 */
		bool mergesRhsAndDiffs() const;


		/** Exports the code needed to propagate the sensitivities of the states defined by the nonlinear system.
		 *
		 *	With CG_EXPLOIT_SPARSITY, the terms with a structurally zero entry of the Jacobian of the right-hand side
		 *	are left out, and every sensitivity is summed in one statement, in the order of the dense propagation.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue propagateImplicitSystem( 	ExportStatementBlock* block,
														const ExportIndex& index1,
														const ExportIndex& index2,
														const ExportIndex& _index3,
														const ExportIndex& tmp_index  	);


		/** Copies all class members from given object.
		 *
		 *	@param[in] arg		Right-hand side object.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue copy(	const DiscreteTimeExport& arg
							);


    protected:

		ExportVariable  rk_diffsTemp3;

		/** For each entry of the Jacobian of the right-hand side (row-major, states then controls), whether it is
		 *  structurally zero. Empty if the model is given as external functions. */
		std::vector<bool> diffsIsZero;

		/** Evaluates the derivatives of the right-hand side, as diffs_rhs, followed by the right-hand side, for
		 *  CG_MERGE_RHS_AND_DIFFS. */
		ExportAcadoFunction rhs_diffs;

};

IntegratorExport* createDiscreteTimeExport(	UserInteraction* _userInteraction,
											const std::string &_commonHeaderName );


CLOSE_NAMESPACE_ACADO


#endif  // ACADO_TOOLKIT_DT_EXPORT_HPP

// end of file.
