#include "Date.h"


int main() {
    Date dt(Date::DATE_NUM_FMAT);

    dt.now();

    std::cout << "Date [" << dt.toString() << "]" << std::endl;
}