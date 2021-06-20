#include <iostream>
#include <cstdlib> // for exit()

#include "main.h"

extern int program_state;
extern int action;

int main()
{
    while(true)
    {
        switch(program_state)
        {
            case(CREATE_ARRAY):
            {
                creation_type();
            }
            break;
            case(AUTO):
            {
                SafeArray dynArr(set_size());
                dynArr.autoFill();

//                SafeArray dynArr2(set_array_size());
//                dynArr2.autoFill();

//                dynArr = dynArr2;
//                print_array(dynArr);
//                std::cout << "Dyn Arr is - " << dynArr2.isEmpty() << std::endl;

                action_type(dynArr);
            }
            break;
            case(MANUALLY):
            {
                SafeArray dynArr(set_size());
                dynArr.manuallyFill();
                action_type(dynArr);
            }
            break;
        }
    }

    return 0;
}
    // CHRONO OF AUTO FILL ARRAY IN BEGIN //
//    auto begin = std::chrono::high_resolution_clock::now();

//    auto end = std::chrono::high_resolution_clock::now();
//    auto time_took = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
//    std::cout << "Executed in " << time_took.count();
    // CHRONO OF AUTO FILL ARRAY IN END //
