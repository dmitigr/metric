/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Copyright (c) 2019 Panda Team
*/
#include <algorithm>
#include <deque>
#include "../details/mgc.hpp"
//#include "details/metrics.hpp"
#include "../../distance/metric_distance.hpp"
#include "../../../utils/graph/connected-components.hpp"

#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <random>
#include <limits>


template <typename T>
std::vector<T> generateVector(size_t size)
{
	std::default_random_engine g;
	std::normal_distribution<T> nd(0, 1);

	std::vector<T> vector(size);

	for (auto i = 0; i < size; ++i) {
		vector[i] = nd(g);
	}

	return vector;
}

template <typename T>
std::vector<std::vector<T>> generateMatrix(size_t rows, size_t cols)
{
	std::vector<std::vector<T>> matrix;
	matrix.reserve(rows);

	for (auto i = 0; i < rows; ++i) {
		matrix.emplace_back(generateVector<T>(cols));
	}

	return matrix;
}

template <typename T>
blaze::DynamicMatrix<T> generateRandomMatrix(size_t rows, size_t cols)
{
	std::default_random_engine g;
	std::normal_distribution<T> nd(0, 1);

	blaze::DynamicMatrix<T> matrix(rows, cols);

	for (auto i = 0; i < rows; ++i) {
		for (auto j = 0; j < cols; ++j) {
			matrix(i, j) = nd(g);
		}
	}

	return matrix;
}

BOOST_AUTO_TEST_CASE(Metrics)
{
	auto vectorNull = generateVector<double>(0);

	metric::distance::Euclidian<double> euclidian;
	metric::distance::Manhatten<double> manhatten;

	BOOST_CHECK_EQUAL(euclidian(vectorNull, vectorNull), 0);
	BOOST_CHECK_EQUAL(manhatten(vectorNull, vectorNull), 0);

	std::vector<double> vector0(1000, 0);
	BOOST_CHECK_EQUAL(euclidian(vector0, vector0), 0);
	BOOST_CHECK_EQUAL(manhatten(vector0, vector0), 0);

	auto vector = generateVector<double>(2000);
	BOOST_CHECK_EQUAL(euclidian(vector, vector), 0);
	BOOST_CHECK_EQUAL(manhatten(vector, vector), 0);

	//auto vector1 = generateVector<double>(std::numeric_limits<size_t>::max());
	//auto vector2 = generateVector<double>(std::numeric_limits<size_t>::max());

	//euclidian(vector1, vector2);
	//manhatten(vector1, vector2);
}

BOOST_AUTO_TEST_CASE(CRACKER)
{
	blaze::DynamicMatrix<bool> M(10, 10, true);
	blaze::row(M, 2) = false;

	auto result = metric::graph::largest_connected_component(M)[0];
}

BOOST_AUTO_TEST_CASE(MGC)
{

	double t = 1e-13;
	//BOOST_CHECK_CLOSE(metric(vNull, vNull), 0, t);
	//BOOST_CHECK_CLOSE(metric(v0, v0), 0, t);
	//BOOST_CHECK_CLOSE(metric(v7, v), 15.070832757349542, t);

    std::vector<std::vector<double>> A1 = {{-1.08661677587398},
                                           {-1.00699896410939},
                                           {-0.814135753976830},
                                           {-0.875364720432552},
                                           {-0.659607023272462},
                                           {-0.798949992922930},
                                           {-0.431585448024267},
                                           {-0.619123703544758},
                                           {-0.351492263653510},
                                           {-0.394814371972061},
                                           {-0.309693618374598},
                                           {-0.352009525808777},
                                           {-0.0803413535982411},
                                           {0.0103940699342647},
                                           {-0.130735385695596},
                                           {-0.138214899507693},
                                           {0.0279270082022143},
                                           {0.141670765995995},
                                           {0.112221224566625},
                                           {0.376767573021755},
                                           {0.186729429735154},
                                           {0.597349318463320},
                                           {0.451380104139401},
                                           {0.639237742050564},
                                           {0.797420868050314},
                                           {0.690091614630087},
                                           {0.921722674141222},
                                           {0.852593762434809},
                                           {0.954771723842945},
                                           {1.03297970279357}};

    std::deque<std::array<float, 1>> B1 = {{2.70625143351230},
                                           {1.41259513494005},
                                           {0.666086793692617},
                                           {0.647856446084279},
                                           {0.887764969338737},
                                           {0.286220905202707},
                                           {0.543682026943014},
                                           {0.0402339224257120},
                                           {0.105812168910424},
                                           {0.0230915137205610},
                                           {0.00298976085950325},
                                           {0.00366997150982423},
                                           {0.000384825484363474},
                                           {7.27293780465119e-05},
                                           {2.50809340229209e-07},
                                           {0.00306636655437742},
                                           {0.000456283181338950},
                                           {0.00801756105329616},
                                           {1.17238339150888e-09},
                                           {0.0803830108071682},
                                           {0.0774478107095828},
                                           {0.0474847202878941},
                                           {0.0818772460512609},
                                           {0.486406609209630},
                                           {0.197547677770060},
                                           {0.628321368933714},
                                           {1.02400551043736},
                                           {0.552591658802459},
                                           {1.52144482984914},
                                           {3.43908991254968}};

    typedef std::vector<double> Rec1;
    typedef std::array<float, 1> Rec2;

    typedef metric::distance::Euclidian<double> Met1;
    typedef metric::distance::Manhatten<float> Met2;


    auto mgc_corr = metric::correlation::MGC<Rec1, Met1, Rec2, Met2>();

    auto result = mgc_corr(A1, B1);
	BOOST_CHECK_CLOSE(result, 0.28845660296530595, t);

    auto mgc_corr2 = metric::correlation::MGC<Rec2, Met2, Rec1, Met1>();
    result = mgc_corr2(B1, A1);
	BOOST_CHECK_CLOSE(result, 0.28845660296530595, t);

	typedef std::vector<double> Rec;
	auto mgc = metric::correlation::MGC<Rec, Met1, Rec, Met1>();
	auto m1 = generateMatrix<double>(4, 4);
	auto m2 = generateMatrix<double>(4, 4);
	mgc(m1, m2);
}

BOOST_AUTO_TEST_CASE(MGC_Estimate)
{
	const int dataSize = 1e6;
	std::default_random_engine generator;
	std::normal_distribution<double> normal(0, 0.5);

	std::vector<std::vector<double>> dataX;
	std::vector<std::vector<double>> dataY;

	std::uniform_real_distribution<double> uniform(0, 1);
	for (auto i = 0; i < dataSize; ++i) {
		double x1 = uniform(generator);
		double x2 = uniform(generator);
		double x3 = uniform(generator);
		double y1 = x1 * x1 + normal(generator);
		double y2 = x2 * x2 * x2 + normal(generator);
		double y3 = std::pow(x3, 0.5) + normal(generator);

		dataX.emplace_back(std::initializer_list<double>{x1, x2, x3});
		dataY.emplace_back(std::initializer_list<double>{y1, y2, y3});
	}

	typedef std::vector<double> Rec;
	typedef metric::distance::Euclidian<double> Met;


	auto mgc = metric::correlation::MGC<Rec, Met, Rec, Met>();

	auto result = mgc.estimate(dataX, dataY);
	std::cout << result << std::endl;
}
