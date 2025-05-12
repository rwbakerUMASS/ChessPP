#include "test_base.h"
#include "bitboard.h"

class CheckSquareTC : public TestCase {
public:
    CheckSquareTC() {
        this->name = "CheckSquareTC";
    }
    bool run() override {
        return true;
    }
};

int main() {
    UnitTestSuite ts;
    for(int i = 0; i < 10000; i++){
    ts.addTestCase(new CheckSquareTC());
    }
    ts.runAll();
    return 0;
}