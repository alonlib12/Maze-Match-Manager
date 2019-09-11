/*
 * AlgorithmRegistration.cpp
 *
 *  Created on: Apr 29, 2019
 *      Author: Alon Liberman
 */

#include "AlgorithmRegistration.h"
#include "AlgorithmRegistrar.h"

using namespace std;


AlgorithmRegistration::AlgorithmRegistration(std::function<unique_ptr<AbstractAlgorithm>()> algorithmFactory) {
    AlgorithmRegistrar::getInstance().registerAlgorithm(algorithmFactory);
}
