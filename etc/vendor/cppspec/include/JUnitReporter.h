/*
 * Copyright 2007 Timo Puronen
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef JUNITREPORTER_H_
#define JUNITREPORTER_H_

#include "Reporter.h"
#include "Timer.h"
#include <vector>
#include <string>

namespace CppSpec {

class JUnitReporter : public Reporter {
public:
	JUnitReporter(Timer& timer);
	JUnitReporter(Timer& timer, const std::string& reportDirectory);

	~JUnitReporter();

public: // from Reporter
	void specificationStarted(const Runnable& specification);
	void behaviorStarted(const std::string& behavior);
	void behaviorSucceeded();
	void behaviorFailed(const std::string& file, int line, const std::string& description);
	void specificationEnded(const std::string& specName);

public:
	struct Result {
		Result(const std::string& behaviorName, const std::string& reason, bool pass, const std::string& duration, const std::string& file, int line)
			: behaviorName(behaviorName), reason(reason), pass(pass), duration(duration), file(file), line(line) {
		}

		std::string behaviorName;
		std::string reason;
		bool pass;
		std::string duration;
		std::string file;
		int line;
	};

private:
	std::ostream* createOutputStream();
	void calculateResults(int& pass, int& fails);
	void printSpecResults(std::ostream& result);
	std::string currentTime();

private:
	JUnitReporter(const JUnitReporter& rhs);
	JUnitReporter& operator= (const JUnitReporter& rhs);

private:
	std::string specificationName;
	std::string behaviorName;
	std::vector<Result> behaviorResults;
	bool createLogFiles;
	std::string reportDirectory;
	Timer& timer;
};

}

#endif /*JUNITREPORTER_H_*/