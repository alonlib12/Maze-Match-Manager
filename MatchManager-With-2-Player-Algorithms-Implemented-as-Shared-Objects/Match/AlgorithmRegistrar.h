/*
 * AlgorithmRegistrar.h
 *
 *  Created on: Apr 29, 2019
 *      Author: alon
 */

#ifndef MATCHMANAGER_ALGORITHMREGISTRAR_H_
#define MATCHMANAGER_ALGORITHMREGISTRAR_H_

#include <string>
#include <list>
#include <memory>
#include <assert.h>
#include <unordered_map>
#include "AbstractAlgorithm.h"
#include "DLClass.h"
/* A class for loading and retrieving algorithms */
class AlgorithmRegistrar {
	std::list<std::string> algorithmNames;
    std::list<std::function<std::unique_ptr<AbstractAlgorithm>()>> algorithmFactories;
    std::list<DLClass> dllHandlers;

    void registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithmFactory) {
        instance.algorithmFactories.push_back(algorithmFactory);
    }
    void setNameForLastAlgorithm(const std::string& algorithmName) {
		assert(algorithmFactories.size()-1 == algorithmNames.size());
		algorithmNames.push_back(algorithmName);
	}
public:
    friend class AlgorithmRegistration;
    virtual ~AlgorithmRegistrar() {algorithmFactories.clear();}; //Clear shared files functions before calling dlclose function.
    void loadAlgorithms(const std::string& path, const std::list<std::string>& soFiles);
    std::list<std::function<std::unique_ptr<AbstractAlgorithm>()>> getAlgorithmFactories()const {
    	return algorithmFactories;
    };
    const std::list<std::string>& getAlgorithmNames()const {
        return algorithmNames;
    }
    static AlgorithmRegistrar& getInstance() {
        return instance;
    }
private:
    static AlgorithmRegistrar instance;
};


#endif /* MATCHMANAGER_ALGORITHMREGISTRAR_H_ */
