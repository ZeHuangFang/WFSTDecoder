#ifndef MODEL_H
#define MODEL_H

#define FRAM_VAR_SIZE  39 //����ά��
#define HMM_STATE_NUM 5 //����Ʒ�ģ��״̬����
#define EMIT_STATE_NUM 3 //
#define HMM_FIN_STATE (HMM_STATE_NUM - 1)
#define GMM_COMP_NUM  1 //��ϸ�˹����
#define TRANS_MATRIX_NUM  (2*HMM_STATE_NUM -1)
#define HMM_TOTAL_NUM 35190 //����ģ������
#define LOG_2_PI   1.83787706640934548355
#define FLT_MAX 3.402823466e+38F
#define INF FLT_MAX
#define LOG_ZERO (-1.0E10)   /* ~log(0) */
#define INFINIT  1.0e-5
#define REAL_ZERO  0.0
#define LSMALL (-0.5E10)   /* log values < LSMALL are set to LZERO */
#define MINEARG (-708.3)   /* lowest exp() arg  = log(MINLARG) */
#define MINLARG 2.45E-308  /* lowest log() arg  = exp(MINEARG) */
#define LINFINIT -11.5129254649702     /* log(INFINIT) */


#define	SP 590 
#define SIL 15786

#define IS_SPHMM(X)   (X == SP)
#define IS_SILHMM(X)  (X == SIL)

typedef float real;  

typedef struct {
	real  logCompWeights ;//��ϸ�˹������Ȩ��
	real  sumLogVarPlusNObsLog2Pi ;//var
	real  means[FRAM_VAR_SIZE];//��ֵ
	real  minusHalfOverVars[FRAM_VAR_SIZE];//-(1/2* var)
}GMM;

typedef struct{
  GMM mGmm[GMM_COMP_NUM];
}MGMM;


typedef struct{
	real transMatrix[TRANS_MATRIX_NUM];
	MGMM mixtureGmm[EMIT_STATE_NUM];
}HMM;

typedef struct {
	real transMatrix[HMM_STATE_NUM][HMM_STATE_NUM];
	MGMM mixtureGmm[1];
}SPHMM;

typedef struct {
	real transMatrix[HMM_STATE_NUM][HMM_STATE_NUM];
	MGMM mixtureGmm[EMIT_STATE_NUM];
}SILHMM;

typedef struct{
	int		toStateID;				//Ŀ��״̬ID
	int     hmmID;					//����ģ��ID
	int		wordID;					//�������
	real    weight;                 //·��Ȩ��
}Translation;

typedef struct{
	int  transIDBegin;
	int  transIDNum;
}State;


typedef struct {
	HMM *amHmms;
	int n_amHmm;
	SPHMM spHmm;
	SILHMM silHmm;
	State *states;
	int n_state;
	Translation *translations;
	int n_translation;
	int *wordIds;
	int n_wordId;
	char *words;

}NETWORK;

int init(NETWORK * network, const char * hmmfile, const char *transfile, const char *wordIDmapfile);
int getTextsByWordIds(NETWORK * network, int *wordID, int size, char *words, int *resultLen);
int getHmmTransScore(NETWORK * network,int hmmInd, int currState, int nextState, real * frameScore);
int getTranslationIDs(NETWORK * network, int stateID,  Translation **translations,  int *count);

real getFrameScore(NETWORK *network, real *frame, int hmmInd, int currState, int nextState);
real calHmmEmitScore(NETWORK * network,real *frame,int hmmInd, int currState);
real calSpHmmEmitScore(NETWORK * network,real *frame,int hmmInd, int currState);
real calSilHmmEmitScore(NETWORK * network,real *frame,int hmmInd, int currState);

real getHmmTransScore(NETWORK * network,int hmmInd, int currState, int nextState);
real getSilHmmTransScore(NETWORK * network,int hmmInd, int currState, int nextState);
real getSpHmmTransScore(NETWORK * network,int hmmInd, int currState, int nextState);


int getTranslationIDs(NETWORK * network, int stateID,  Translation **translations);

#endif
