//=================================================================================================
/*!
//  \file blaze/math/expressions/DVecExpandExpr.h
//  \brief Header file for the dense vector expansion expression
//
//  Copyright (C) 2012-2020 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_EXPRESSIONS_DVECEXPANDEXPR_H_
#define _BLAZE_MATH_EXPRESSIONS_DVECEXPANDEXPR_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include "../../math/Aliases.h"
#include "../../math/constraints/DenseVector.h"
#include "../../math/constraints/TransposeFlag.h"
#include "../../math/Exception.h"
#include "../../math/expressions/DenseMatrix.h"
#include "../../math/expressions/DenseVector.h"
#include "../../math/expressions/ExpandExprData.h"
#include "../../math/expressions/Forward.h"
#include "../../math/expressions/Transformation.h"
#include "../../math/expressions/VecExpandExpr.h"
#include "../../math/shims/Serial.h"
#include "../../math/simd/SIMDTrait.h"
#include "../../math/traits/ExpandTrait.h"
#include "../../math/typetraits/IsAligned.h"
#include "../../math/typetraits/IsComputation.h"
#include "../../math/typetraits/IsExpression.h"
#include "../../math/typetraits/IsPadded.h"
#include "../../math/typetraits/RequiresEvaluation.h"
#include "../../system/Inline.h"
#include "../../util/Assert.h"
#include "../../util/EnableIf.h"
#include "../../util/FunctionTrace.h"
#include "../../util/InvalidType.h"
#include "../../util/MaybeUnused.h"
#include "../../util/mpl/If.h"
#include "../../util/Types.h"
#include "../../util/typetraits/GetMemberType.h"


namespace blaze {

//=================================================================================================
//
//  CLASS DVECEXPANDEXPR
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Expression object for dense vector expansion.
// \ingroup dense_vector_expression
//
// The DVecExpandExpr class represents the compile time expression for expansions of
// dense vectors.
*/
template< typename VT       // Type of the dense vector
        , bool TF           // Transpose flag
        , size_t... CEAs >  // Compile time expansion arguments
class DVecExpandExpr
   : public VecExpandExpr< DenseMatrix< DVecExpandExpr<VT,TF,CEAs...>, !TF >, CEAs... >
   , private Transformation
   , private ExpandExprData<CEAs...>
{
 private:
   //**Type definitions****************************************************************************
   using RT = ResultType_t<VT>;  //!< Result type of the dense vector expression.

   using DataType = ExpandExprData<CEAs...>;  //!< The type of the ExpandExprData base class.

   //! Definition of the GetConstIterator type trait.
   BLAZE_CREATE_GET_TYPE_MEMBER_TYPE_TRAIT( GetConstIterator, ConstIterator, INVALID_TYPE );
   //**********************************************************************************************

   //**Serial evaluation strategy******************************************************************
   //! Compilation switch for the serial evaluation strategy of the expansion expression.
   /*! The \a useAssign compile time constant expression represents a compilation switch for
       the serial evaluation strategy of the expansion expression. In case the dense vector
       operand is a computation or requires an intermediate evaluation, \a useAssign will
       be set to 1 and the expansion expression will be evaluated via the \a assign function
       family. Otherwise \a useAssign will be set to 0 and the expression will be evaluated
       via the function call operator. */
   static constexpr bool useAssign = IsComputation_v<VT> || RequiresEvaluation_v<VT>;

   /*! \cond BLAZE_INTERNAL */
   //! Helper variable template for the explicit application of the SFINAE principle.
   template< typename MT >
   static constexpr bool UseAssign_v = useAssign;
   /*! \endcond */
   //**********************************************************************************************

   //**Parallel evaluation strategy****************************************************************
   /*! \cond BLAZE_INTERNAL */
   //! Helper variable template for the explicit application of the SFINAE principle.
   /*! This variable template is a helper for the selection of the parallel evaluation strategy.
       In case the vector operand is not SMP assignable and requires an intermediate evaluation,
       the variable is set to 1 and the expression specific evaluation strategy is selected.
       Otherwise the variable is set to 0 and the default strategy is chosen. */
   template< typename MT >
   static constexpr bool UseSMPAssign_v = ( !VT::smpAssignable && useAssign );
   /*! \endcond */
   //**********************************************************************************************

 public:
   //**Type definitions****************************************************************************
   using This          = DVecExpandExpr<VT,TF,CEAs...>;  //!< Type of this DVecExpandExpr instance.
   using BaseType      = DenseMatrix<This,!TF>;          //!< Base type of this DVecExpandExpr instance.
   using ResultType    = ExpandTrait_t<VT,CEAs...>;      //!< Result type for expression template evaluations.
   using OppositeType  = OppositeType_t<ResultType>;     //!< Result type with opposite storage order for expression template evaluations.
   using TransposeType = TransposeType_t<ResultType>;    //!< Transpose type for expression template evaluations.
   using ElementType   = ElementType_t<VT>;              //!< Resulting element type.
   using ReturnType    = ReturnType_t<VT>;               //!< Return type for expression template evaluations.

   //! Data type for composite expression templates.
   using CompositeType = If_t< useAssign, const ResultType, const DVecExpandExpr& >;

   //! Iterator over the elements of the dense matrix.
   using ConstIterator = GetConstIterator_t<VT>;

   //! Composite data type of the dense matrix expression.
   using Operand = If_t< IsExpression_v<VT>, const VT, const VT& >;
   //**********************************************************************************************

   //**Compilation flags***************************************************************************
   //! Compilation switch for the expression template evaluation strategy.
   static constexpr bool simdEnabled = VT::simdEnabled;

   //! Compilation switch for the expression template assignment strategy.
   static constexpr bool smpAssignable = VT::smpAssignable;
   //**********************************************************************************************

   //**SIMD properties*****************************************************************************
   //! The number of elements packed within a single SIMD element.
   static constexpr size_t SIMDSIZE = SIMDTrait<ElementType>::size;
   //**********************************************************************************************

   //**Constructor*********************************************************************************
   /*!\brief Constructor for the DVecExpandExpr class.
   //
   // \param dv The dense vector operand of the expansion expression.
   // \param args The runtime expansion expression arguments.
   */
   template< typename... REAs >  // Runtime expansion arguments
   explicit inline DVecExpandExpr( const VT& dv, REAs... args ) noexcept
      : DataType( args... )  // Base class initialization
      , dv_     ( dv )       // Dense vector of the expansion expression
   {}
   //**********************************************************************************************

   //**Access operator*****************************************************************************
   /*!\brief 2D-access to the matrix elements.
   //
   // \param i Access index for the row. The index has to be in the range \f$[0..M-1]\f$.
   // \param j Access index for the column. The index has to be in the range \f$[0..N-1]\f$.
   // \return The resulting value.
   */
   inline ReturnType operator()( size_t i, size_t j ) const {
      if( TF ) {
         BLAZE_INTERNAL_ASSERT( i < expansion(), "Invalid row access index"    );
         BLAZE_INTERNAL_ASSERT( j < dv_.size() , "Invalid column access index" );
         return dv_[j];
      }
      else {
         BLAZE_INTERNAL_ASSERT( i < dv_.size(),  "Invalid row access index"    );
         BLAZE_INTERNAL_ASSERT( j < expansion(), "Invalid column access index" );
         return dv_[i];
      }
   }
   //**********************************************************************************************

   //**At function*********************************************************************************
   /*!\brief Checked access to the matrix elements.
   //
   // \param i Access index for the row. The index has to be in the range \f$[0..M-1]\f$.
   // \param j Access index for the column. The index has to be in the range \f$[0..N-1]\f$.
   // \return The resulting value.
   // \exception std::out_of_range Invalid matrix access index.
   */
   inline ReturnType at( size_t i, size_t j ) const {
      if( i >= ( TF ? expansion() : dv_.size() ) ) {
         BLAZE_THROW_OUT_OF_RANGE( "Invalid row access index" );
      }
      if( j >= ( TF ? dv_.size() : expansion() ) ) {
         BLAZE_THROW_OUT_OF_RANGE( "Invalid column access index" );
      }
      return (*this)(i,j);
   }
   //**********************************************************************************************

   //**Load function*******************************************************************************
   /*!\brief Access to the SIMD elements of the matrix.
   //
   // \param i Access index for the row. The index has to be in the range \f$[0..M-1]\f$.
   // \param j Access index for the column. The index has to be in the range \f$[0..N-1]\f$.
   // \return Reference to the accessed values.
   */
   BLAZE_ALWAYS_INLINE auto load( size_t i, size_t j ) const noexcept {
      if( TF ) {
         BLAZE_INTERNAL_ASSERT( i < expansion(), "Invalid row access index"    );
         BLAZE_INTERNAL_ASSERT( j < dv_.size() , "Invalid column access index" );
         BLAZE_INTERNAL_ASSERT( j % SIMDSIZE == 0UL, "Invalid row access index" );
         return dv_.load(j);
      }
      else {
         BLAZE_INTERNAL_ASSERT( i < dv_.size() , "Invalid row access index"    );
         BLAZE_INTERNAL_ASSERT( j < expansion(), "Invalid column access index" );
         BLAZE_INTERNAL_ASSERT( i % SIMDSIZE == 0UL, "Invalid row access index" );
         return dv_.load(i);
      }
   }
   //**********************************************************************************************

   //**Begin function******************************************************************************
   /*!\brief Returns an iterator to the first non-zero element of row/column \a i.
   //
   // \param i The row/column index.
   // \return Iterator to the first non-zero element of row/column \a i.
   */
   inline ConstIterator begin( size_t i ) const {
      MAYBE_UNUSED( i );
      return ConstIterator( dv_.begin() );
   }
   //**********************************************************************************************

   //**End function********************************************************************************
   /*!\brief Returns an iterator just past the last non-zero element of row/column \a i.
   //
   // \param i The row/column index.
   // \return Iterator just past the last non-zero element of row/column \a i.
   */
   inline ConstIterator end( size_t i ) const {
      MAYBE_UNUSED( i );
      return ConstIterator( dv_.end() );
   }
   //**********************************************************************************************

   //**Rows function*******************************************************************************
   /*!\brief Returns the current number of rows of the matrix.
   //
   // \return The number of rows of the matrix.
   */
   inline size_t rows() const noexcept {
      return ( TF ? expansion() : dv_.size() );
   }
   //**********************************************************************************************

   //**Columns function****************************************************************************
   /*!\brief Returns the current number of columns of the matrix.
   //
   // \return The number of columns of the matrix.
   */
   inline size_t columns() const noexcept {
      return ( TF ? dv_.size() : expansion() );
   }
   //**********************************************************************************************

   //**Operand access******************************************************************************
   /*!\brief Returns the dense vector operand.
   //
   // \return The dense vector operand.
   */
   inline Operand operand() const noexcept {
      return dv_;
   }
   //**********************************************************************************************

   //**********************************************************************************************
   using DataType::expansion;
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the expression can alias with the given address \a alias.
   //
   // \param alias The alias to be checked.
   // \return \a true in case the expression can alias, \a false otherwise.
   */
   template< typename T >
   inline bool canAlias( const T* alias ) const noexcept {
      return dv_.canAlias( alias );
   }
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the expression is aliased with the given address \a alias.
   //
   // \param alias The alias to be checked.
   // \return \a true in case an alias effect is detected, \a false otherwise.
   */
   template< typename T >
   inline bool isAliased( const T* alias ) const noexcept {
      return dv_.isAliased( alias );
   }
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the operands of the expression are properly aligned in memory.
   //
   // \return \a true in case the operands are aligned, \a false if not.
   */
   inline bool isAligned() const noexcept {
      return dv_.isAligned();
   }
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the expression can be used in SMP assignments.
   //
   // \return \a true in case the expression can be used in SMP assignments, \a false if not.
   */
   inline bool canSMPAssign() const noexcept {
      return dv_.canSMPAssign();
   }
   //**********************************************************************************************

 private:
   //**Member variables****************************************************************************
   Operand dv_;  //!< Dense vector of the expansion expression.
   //**********************************************************************************************

   //**Assignment to matrices**********************************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expression to be assigned.
   // \return void
   //
   // This function implements the performance optimized assignment of a dense vector expansion
   // expression to a matrix. Due to the explicit application of the SFINAE principle, this
   // function can only be selected by the compiler in case the operand requires an intermediate
   // evaluation.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto assign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( serial( ~rhs.dv_ ) );

      assign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Addition assignment to matrices*************************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Addition assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expression to be added.
   // \return void
   //
   // This function implements the performance optimized addition assignment of a dense vector
   // expansion expression to a matrix. Due to the explicit application of the SFINAE principle,
   // this function can only be selected by the compiler in case the operand requires an
   // intermediate evaluation.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto addAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( serial( ~rhs.dv_ ) );

      addAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Subtraction assignment to matrices**********************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Subtraction assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expression to be subtracted.
   // \return void
   //
   // This function implements the performance optimized subtraction assignment of a dense vector
   // expansion expression to a matrix. Due to the explicit application of the SFINAE principle,
   // this function can only be selected by the compiler in case the operand requires an
   // intermediate evaluation.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto subAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( serial( ~rhs.dv_ ) );

      subAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Schur product assignment to matrices********************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Schur product assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expression for the Schur product.
   // \return void
   //
   // This function implements the performance optimized Schur product assignment of a dense
   // matrix expansion expression to a matrix. Due to the explicit application of the SFINAE
   // principle, this function can only be selected by the compiler in case the operand requires
   // an intermediate evaluation.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto schurAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( serial( ~rhs.dv_ ) );

      schurAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Multiplication assignment to matrices*******************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Multiplication assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expression to be multiplied.
   // \return void
   //
   // This function implements the performance optimized multiplication assignment of a dense
   // matrix expansion expression to a matrix. Due to the explicit application of the SFINAE
   // principle, this function can only be selected by the compiler in case the operand requires
   // an intermediate evaluation.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto multAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( serial( ~rhs.dv_ ) );

      multAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP assignment to matrices******************************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expansion to be assigned.
   // \return void
   //
   // This function implements the performance optimized SMP assignment of a dense vector
   // expansion expansion to a matrix. Due to the explicit application of the SFINAE principle,
   // this function can only be selected by the compiler in case the expression specific parallel
   // evaluation strategy is selected.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto smpAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseSMPAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( ~rhs.dv_ );

      smpAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP addition assignment to matrices*********************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP addition assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expansion to be added.
   // \return void
   //
   // This function implements the performance optimized SMP addition assignment of a dense
   // vector expansion expansion to a matrix. Due to the explicit application of the SFINAE
   // principle, this function can only be selected by the compiler in case the expression
   // specific parallel evaluation strategy is selected.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto smpAddAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseSMPAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( ~rhs.dv_ );

      smpAddAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP subtraction assignment to matrices******************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP subtraction assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expansion to be subtracted.
   // \return void
   //
   // This function implements the performance optimized SMP subtraction assignment of a dense
   // vector expansion expansion to a matrix. Due to the explicit application of the SFINAE
   // principle, this function can only be selected by the compiler in case the expression
   // specific parallel evaluation strategy is selected.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto smpSubAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseSMPAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( ~rhs.dv_ );

      smpSubAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP Schur product assignment to matrices****************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP Schur product assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expansion for the Schur product.
   // \return void
   //
   // This function implements the performance optimized SMP Schur product assignment of a dense
   // vector expansion expansion to a matrix. Due to the explicit application of the SFINAE
   // principle, this function can only be selected by the compiler in case the expression
   // specific parallel evaluation strategy is selected.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto smpSchurAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseSMPAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( ~rhs.dv_ );

      smpSchurAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP multiplication assignment to matrices***************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP multiplication assignment of a dense vector expansion expression to a matrix.
   // \ingroup dense_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side expansion expression for the Schur product.
   // \return void
   //
   // This function implements the performance optimized SMP multiplication assignment of a dense
   // matrix expansion expression to a matrix. Due to the explicit application of the SFINAE
   // principle, this function can only be selected by the compiler in case the expression
   // specific parallel evaluation strategy is selected.
   */
   template< typename MT  // Type of the target matrix
           , bool SO >    // Storage order of the target matrix
   friend inline auto smpMultAssign( Matrix<MT,SO>& lhs, const DVecExpandExpr& rhs )
      -> EnableIf_t< UseSMPAssign_v<MT> >
   {
      using blaze::expand;

      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const RT tmp( ~rhs.dv_ );

      smpMultAssign( ~lhs, expand<CEAs...>( tmp, rhs.expansion() ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Compile time checks*************************************************************************
   /*! \cond BLAZE_INTERNAL */
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE( VT );
   BLAZE_CONSTRAINT_MUST_BE_VECTOR_WITH_TRANSPOSE_FLAG( VT, TF );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  GLOBAL OPERATORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Expansion of the given dense vector.
// \ingroup dense_vector
//
// \param dv The dense vector to be expanded.
// \param expansion The expansion.
// \return The expansion of the vector.
//
// This function returns an expression representing the expansion of the given dense vector:

   \code
   using blaze::rowMajor;
   using blaze::columnMajor;

   blaze::DynamicVector<int,columnVector> a{ 1, 5, -2, 4 };
   blaze::DynamicVector<int,rowVector> b{ 3, -1, 7, 0 };

   blaze::DynamicMatrix<double,columnMajor> A;
   blaze::DynamicMatrix<double,rowMajor> B;
   // ... Resizing and initialization

   // Expansion of the column vector 'a' to a 4x3 column-major matrix
   //
   //    (  1  1  1 )
   //    (  5  5  5 )
   //    ( -2 -2 -2 )
   //    (  4  4  4 )
   //
   A = expand( a, 3UL );

   // Expansion of the row vector 'b' to a 3x4 row-major matrix
   //
   //    ( 3, -1, 7, 0 )
   //    ( 3, -1, 7, 0 )
   //    ( 3, -1, 7, 0 )
   //
   B = expand( b, 3UL );
   \endcode
*/
template< typename VT  // Type of the dense vector
        , bool TF >    // Transpose flag
inline decltype(auto) expand( const DenseVector<VT,TF>& dv, size_t expansion )
{
   BLAZE_FUNCTION_TRACE;

   using ReturnType = const DVecExpandExpr<VT,TF>;
   return ReturnType( ~dv, expansion );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Expansion of the given dense vector.
// \ingroup dense_vector
//
// \param dv The dense vector to be expanded.
// \return The expansion of the vector.
//
// This function returns an expression representing the expansion of the given dense vector:

   \code
   using blaze::rowMajor;
   using blaze::columnMajor;

   blaze::DynamicVector<int,columnVector> a{ 1, 5, -2, 4 };
   blaze::DynamicVector<int,rowVector> b{ 3, -1, 7, 0 };

   blaze::DynamicMatrix<double,columnMajor> A;
   blaze::DynamicMatrix<double,rowMajor> B;
   // ... Resizing and initialization

   // Expansion of the column vector 'a' to a 4x3 column-major matrix
   //
   //    (  1  1  1 )
   //    (  5  5  5 )
   //    ( -2 -2 -2 )
   //    (  4  4  4 )
   //
   A = expand<3UL>( a );

   // Expansion of the row vector 'b' to a 3x4 row-major matrix
   //
   //    ( 3, -1, 7, 0 )
   //    ( 3, -1, 7, 0 )
   //    ( 3, -1, 7, 0 )
   //
   B = expand<3UL>( b );
   \endcode
*/
template< size_t E     // Compile time expansion argument
        , typename VT  // Type of the dense vector
        , bool TF >    // Transpose flag
inline decltype(auto) expand( const DenseVector<VT,TF>& dv )
{
   BLAZE_FUNCTION_TRACE;

   using ReturnType = const DVecExpandExpr<VT,TF,E>;
   return ReturnType( ~dv );
}
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Expansion of the given dense vector.
// \ingroup dense_vector
//
// \param dv The dense vector to be expanded.
// \param expansion The expansion.
// \return The expansion of the vector.
//
// This auxiliary overload of the \c expand() function accepts both a compile time and a runtime
// expansion. The runtime argument is discarded in favor of the compile time argument.
*/
template< size_t E     // Compile time expansion argument
        , typename VT  // Type of the dense vector
        , bool TF >    // Transpose flag
inline decltype(auto) expand( const DenseVector<VT,TF>& dv, size_t expansion )
{
   MAYBE_UNUSED( expansion );

   BLAZE_FUNCTION_TRACE;

   using ReturnType = const DVecExpandExpr<VT,TF,E>;
   return ReturnType( ~dv );
}
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISALIGNED SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename VT, bool TF, size_t... CEAs >
struct IsAligned< DVecExpandExpr<VT,TF,CEAs...> >
   : public IsAligned<VT>
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISPADDED SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename VT, bool TF, size_t... CEAs >
struct IsPadded< DVecExpandExpr<VT,TF,CEAs...> >
   : public IsPadded<VT>
{};
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
