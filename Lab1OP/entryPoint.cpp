#include "entryPoint.h"
#include "logic/logic.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case INITIALIZATION:
        initialize(context);
        break;
    case SWAP:
        swapNumberSystem(context, params);
        break;
    case VALIDATION:
        validateNumber(context, params);
        break;
    case CONVERTION:
        convertNumber(context, params);
        break;
    }
}







