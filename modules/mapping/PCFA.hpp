/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

Copyright (c) 2019 Panda Team
*/

#ifndef _METRIC_MAPPING_PCFA_HPP
#define _METRIC_MAPPING_PCFA_HPP

#include <type_traits>
#include "../../3rdparty/blaze/Blaze.h"

namespace metric {



/**
 * @brief 
 * 
 * @param In 
 * @param n_components
 * @param averages - outputs average curve
 * @return 
 */
template <class BlazeMatrix>
blaze::DynamicMatrix<typename BlazeMatrix::ElementType> PCA_col(
        const BlazeMatrix & In,
        int n_components,
        blaze::DynamicVector<typename BlazeMatrix::ElementType> & averages
        );


/**
 * @brief
 *
 * @param In
 * @param n_components
 * @param averages - outputs average curve
 * @return
 */
template <class BlazeMatrix>
blaze::DynamicMatrix<typename BlazeMatrix::ElementType> PCA(
        const BlazeMatrix & In,
        int n_components,
        blaze::DynamicVector<typename BlazeMatrix::ElementType, blaze::rowVector> & averages
        );





/**
 * @class PCFA_col
 * 
 *@brief simple linear encoder based on PCA for data organized by columns
 * 
 */
template <typename V>
class PCFA_col {

public:
    using value_type = V;

    /**
   * @brief Construct a new PCFA_col object
   * 
   * @param TrainingData - training dataset with curves in columns
   * @param n_features - desired length of compressed code
   */
    PCFA_col(const blaze::DynamicMatrix<value_type>& TrainingData, size_t n_features = 1);

    /**
   * @brief 
   * 
   * @param Data
   * @return
   */
    blaze::DynamicMatrix<value_type> encode(const blaze::DynamicMatrix<value_type>& Data);

    /**
   * @brief 
   * 
   * @param Codes 
   * @param unshift - flag for adding average curve to each decoded one
   * @return blaze::DynamicMatrix<value_type>
   */
    blaze::DynamicMatrix<value_type> decode(const blaze::DynamicMatrix<value_type>& Codes, bool unshift=true);

    /**
   * @brief returns the average curve of training dataset, used for center shift
   *
   * @return blaze::DynamicMatrix<value_type>
   */
    blaze::DynamicMatrix<value_type> average();

    /**
   * @brief returns the encoder matrix concatenated with the average curve of training dataset, used for center shift
   *
   * @return blaze::DynamicMatrix<value_type>
   */
    blaze::DynamicMatrix<value_type> eigenmodes();


private:
    blaze::DynamicMatrix<value_type> W_decode;
    blaze::DynamicMatrix<value_type> W_encode;
    blaze::DynamicVector<value_type> averages;
    std::default_random_engine rgen;
};




/**
 * @class PCFA
 *
 *@brief simple linear encoder based on PCA
 *
 */
template <typename recType, typename Metric>
class PCFA {

private:


    template <typename>
    struct determine_container_type
    {
        constexpr static int code = 0;
    };

    template <template <typename, typename> class Container, typename ValueType, typename Allocator>
    struct determine_container_type<Container<ValueType, Allocator>>
    {
        constexpr static int code = 1;
    };

    template <template <typename, bool> class Container, typename ValueType, bool F>
    struct determine_container_type<Container<ValueType, F>>
    {
        constexpr static int code = 2;
    };





//    template<typename>
//    struct determine_element_type  // TODO replace with value_type/ElementType field detector!
//    {
//        using type = void;
//    };

//    template <typename ValueType, typename Allocator>
//    struct determine_element_type<std::vector<ValueType, Allocator>>
//    {
//        using type = typename std::vector<ValueType, Allocator>::value_type;
//    };

//    template <typename ValueType, bool F>
//    struct determine_element_type<blaze::DynamicVector<ValueType, F>>
//    {
//        using type = typename blaze::DynamicVector<ValueType, F>::ElementType;
//    };


//    template <typename ValueType, bool F>
//    struct determine_element_type<blaze::DynamicMatrix<ValueType, F>>
//    {
//        using type = typename blaze::DynamicMatrix<ValueType, F>::ElementType;
//    };



    template<typename C, int = determine_container_type<C>::code>
    struct determine_element_type
    {
        using type = void;
    };

    template<typename C>
    struct determine_element_type<C, 1>
    {
        using type = typename C::value_type;
    };

    template<typename C>
    struct determine_element_type<C, 2>
    {
        using type = typename C::ElementType;
    };



public:

    using value_type = typename determine_element_type<recType>::type;

    //constexpr static int ContainerCode = determine_container_type<recType>::code;

    /**
   * @brief Construct a new PCFA object from dataset in blaze DynamicMatrix
   *
   * @param TrainingData - training dataset with curves in rows
   * @param n_features - desired length of compressed code
   */
    PCFA(const blaze::DynamicMatrix<value_type> & TrainingData, size_t n_features = 1);

    /**
   * @brief Construct a new PCFA object vrom vector of records
   *
   * @param TrainingData - training dataset, vector of records
   * @param n_features - desired length of compressed code
   */
    PCFA(std::vector<recType> & TrainingData, size_t n_features = 1);


    /**
   * @brief
   *
   * @param Data
   * @return
   */
    blaze::DynamicMatrix<value_type> encode(const blaze::DynamicMatrix<value_type> & Data);

    /**
   * @brief
   *
   * @param Data
   * @return
   */
    std::vector<recType> encode(const std::vector<recType> & Data);


    /**
   * @brief
   *
   * @param Codes
   * @param unshift - flag for adding average curve to each decoded one
   * @return blaze::DynamicMatrix<value_type>
   */
    blaze::DynamicMatrix<value_type> decode(const blaze::DynamicMatrix<value_type>& Codes, bool unshift=true);

    /**
   * @brief
   *
   * @param Data
   * @return
   */
    std::vector<recType> decode(const std::vector<recType> & Data, bool unshift=true);


    /**
   * @brief returns the average curve of training dataset, used for center shift
   *
   * @return blaze::DynamicMatrix<value_type>
   */
    blaze::DynamicMatrix<value_type> average_mat();

    /**
   * @brief returns the average curve of training dataset, used for center shift
   *
   * @return blaze::DynamicMatrix<value_type>
   */
    std::vector<recType> average();

    /**
   * @brief returns the encoder matrix concatenated with the average curve of training dataset, used for center shift
   *
   * @return blaze::DynamicMatrix<value_type>
   */
    blaze::DynamicMatrix<value_type> eigenmodes_mat();

    /**
   * @brief returns the encoder matrix concatenated with the average curve of training dataset, used for center shift
   *
   * @return blaze::DynamicMatrix<value_type>
   */
    std::vector<recType> eigenmodes();


private:
    blaze::DynamicMatrix<value_type> W_decode;
    blaze::DynamicMatrix<value_type> W_encode;
    blaze::DynamicVector<value_type, blaze::rowVector> averages;
    std::default_random_engine rgen;

    blaze::DynamicMatrix<value_type> vector_to_blaze(const std::vector<recType> & In);


    template <typename R> // this template prevents from repeating the signature
    typename std::enable_if <
//     std::is_same<
//      R,
//      std::vector<typename PCFA<R, Metric>::value_type, typename std::allocator<typename PCFA<R, Metric>::value_type>>
//     >::value,
     determine_container_type<R>::code == 1,
     std::vector<R>
    >::type
    blaze_to_vector(const blaze::DynamicMatrix<typename PCFA<R, Metric>::value_type> & In);

    //std::enable_if <std::is_same<recType, blaze::DynamicVector<typename PCFA<recType, Metric>::value_type>, blaze::rowVector>::value, std::vector<recType>>
    template <typename R> // this template prevents from repeating the signature
    typename std::enable_if<
//     std::is_same<
//      R,
//      blaze::DynamicVector<typename PCFA<R, Metric>::value_type, blaze::rowVector>
//     >::value,
     determine_container_type<R>::code == 2,
     std::vector<R>
    >::type
    blaze_to_vector(const blaze::DynamicMatrix<typename PCFA<R, Metric>::value_type> & In);

//    template <typename R>  // for any other type
//    std::enable_if <
//     (
//      not std::is_same<
//       R,
//       std::vector<typename PCFA<R, Metric>::value_type>
//      >::value
//     ) and (
//      not std::is_same<
//       R,
//       blaze::DynamicVector<typename PCFA<R, Metric>::value_type, blaze::rowVector>
//      >::value
//     ),
//     std::vector<R>
//    >::type
//    blaze_to_vector(const blaze::DynamicMatrix<typename PCFA<R, Metric>::value_type> & In);
};




/**
* @brief Creates a new PCFA_col object
*
* @param TrainingData
* @param n_features
*/
template <typename BlazeMatrix>
PCFA_col<typename BlazeMatrix::ElementType> PCFA_col_factory(const BlazeMatrix & TrainingData, size_t n_features = 1);


/**
* @brief Creates a new PCFA object
*
* @param TrainingData
* @param n_features
*/
template <typename BlazeMatrix>
PCFA<typename BlazeMatrix::ElementType, void> PCFA_factory(const BlazeMatrix & TrainingData, size_t n_features = 1);




}  // namespace metric

#include "PCFA.cpp"

#endif  // _METRIC_MAPPING_PCFA_HPP