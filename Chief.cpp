#include "Chief.h"

ostream& operator<<(ostream& os, const Chief* chief) {
    chief->Print();
    return os;
}