#ifndef CHESSPP_BASETEST_H
#define CHESSPP_BASETEST_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class TestCase {
    public:
        string name;
        virtual bool run() = 0;

};

class UnitTestSuite {
public:
    void runAll()
    {
        int passedTests = 0;
        int failedTests = 0;
        cout << "Starting SUITE" << endl;
        setSuiteStartTime();
        for(size_t i = 0; i < this->allTests.size(); i++)
        {
            TestCase* tc = this->allTests[i];
            cout << "Running test: " << tc->name << " ... ";
            setTestStartTime();
            
            if (tc->run())
            {
                cout << "Passed";
                passedTests++;
            }
            else
            {
                cout << "Failed";
                failedTests++;
            }
            milliseconds dur = duration_cast<milliseconds>(getTime() - testStart);
            cout << "(" << dur.count() << "ms)" << endl;
        }

        milliseconds dur = duration_cast<milliseconds>(getTime() - suiteStart);

        // Summary of tests
        cout << "Tests Passed: " << passedTests << endl;
        cout << "Tests Failed: " << failedTests << endl;
        cout << "Runtime: " << dur.count() << "ms" << endl;
    }
    void addTestCase(TestCase* tc) {
        this->allTests.push_back(tc);
    }
private:
    vector<TestCase*> allTests;
    high_resolution_clock::time_point suiteStart;
    high_resolution_clock::time_point testStart;
    void setSuiteStartTime()
    {
        this->suiteStart = getTime();
    }
    void setTestStartTime()
    {
        this->testStart = getTime();
    }
    high_resolution_clock::time_point getTime()
    {
        return chrono::high_resolution_clock::now();
    }
};

#endif
