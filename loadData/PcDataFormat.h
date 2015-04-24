#ifndef PC_DATA_FORMAT_H
#define PC_DATA_FORMAT_H
#include "Model.h"
#include <stdio.h>
#include <stdlib.h>

//��ƽ̨��ؽӿ�
HMM * getHmm(NETWORK * network, int hmmInd);

//��ƽ̨��ؽӿ�
SPHMM * getSPHMM(NETWORK * network);

SILHMM * getSILHMM(NETWORK * network);
//ƽ̨��ؽӿ�
int getTranslations(NETWORK * network,State *state, Translation **translations,  int *count);

//ƽ̨��ؽӿ�
int getState(NETWORK * network, int stateID, State *state);

#endif