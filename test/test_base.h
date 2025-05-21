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
        bool pass = true;
        virtual void run() = 0;
        void testFailed(string reason)
        {
            cout << this->name << ": fails because " << reason << endl;
            this->pass = false;
        }

};

class UnitTestSuite {
public:
    UnitTestSuite(string name)
    {
        this->name = name;
    }
    void runAll()
    {
        int passedTests = 0;
        int failedTests = 0;
        cout << "Starting " << this->name << " tests" << endl;
        setSuiteStartTime();
        for(size_t i = 0; i < this->allTests.size(); i++)
        {
            TestCase* tc = this->allTests[i];
            cout << endl << "Running test: " << tc->name << "... " << endl;
            setTestStartTime();
            tc->run();
            if (tc->pass)
            {
                cout << tc->name << ": Passed";
                passedTests++;
            }
            else
            {
                cout << tc->name << ": Failed";
                failedTests++;
            }
            milliseconds dur = duration_cast<milliseconds>(getTime() - testStart);
            cout << "(" << dur.count() << "ms)" << endl;
        }

        milliseconds dur = duration_cast<milliseconds>(getTime() - suiteStart);

        // Summary of tests
        cout << endl << "Tests Passed: " << passedTests << endl;
        cout << "Tests Failed: " << failedTests << endl;
        cout << "Runtime: " << dur.count() << "ms" << endl;
    }
    void addTestCase(TestCase* tc) {
        this->allTests.push_back(tc);
    }
private:
    string name;
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
