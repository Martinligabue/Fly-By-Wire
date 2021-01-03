#include "pfc.h"
#include "../fman/fman.h"
#include "../utility/string.h"
#include "../constants.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

int BIAS = DEFAULT_BIAS;

void signalUserHandler(int signum)
{
    if (signum == SIGUSR1) {
        BIAS = 1;
    }
}

void pfc(char *filePath, char *sentence, unsigned int connectionType) {
    PFC pfc, *ppfc = &pfc;
    PTP ptp, *pptp = &ptp;
    ppfc->filePath = filePath;

    signal(SIGUSR1, signalUserHandler);

    ppfc->fileLog = extractPFCLogName(connectionType);

    parseNMEA(ppfc, pptp, sentence, connectionType); 
}

void parseNMEA(PFC *pPFC, PTP *pPointToPoint, char *sElement, unsigned int connectionType) {
    char sLine[255];
    char sRecordHead[255];
    FILE *pFile, *pLog;
    PTP *pPTP = pPointToPoint;
    pFile = fopen(pPFC->filePath, "r");
    pLog = fopen(pPFC->fileLog, "w+");

    fprintf(pLog, "PFC %d\n", getpid());

    conMeta *pCM = malloc(sizeof(conMeta));
    pCM->connectionType = connectionType;
    fprintf(pLog, "Open server connection\n");
    generateConnectionWithTrans(pCM);

    while (fgets(sLine, sizeof(sLine), pFile) != NULL) {
        strExtrSeparator(sRecordHead, sLine, ",");
        fprintf(pLog, "Compare %s with  %s\n", sElement, sRecordHead);
        if (strcmp(sRecordHead, sElement) == 0) {
            fprintf(pLog, "\tCatch: %s", sLine);

            RawElement *pRawElement = (RawElement *)malloc(sizeof(RawElement));
            extractRawElements(pRawElement, sLine);

            GLL *pGLL = (GLL *)malloc(sizeof(GLL));
            extractGLL(pGLL, pRawElement);
            addPoint(pPTP, pGLL);

            if (BIAS) {
                pPTP->instantSpeed = (float)((int)round(pPTP->instantSpeed) << 2);
                fprintf(pLog, "\t\tBias %f\n", pPTP->instantSpeed);
                BIAS = DEFAULT_BIAS;
            }

            char *sInstantSpeed = malloc(sizeof(char[255]));
            sprintf(sInstantSpeed, "%f" , pPTP->instantSpeed);
            fprintf(pLog, "\tSend to Transducer %s\n", sInstantSpeed);
            sendDataToTrans(pCM, sInstantSpeed);

            if (NULL != pPTP->next) {
                pPTP = pPTP->next;
            }

        }
        sleep(CLOCK);
    };

    fprintf(pLog, "No more data on file\n");
    fprintf(pLog, "\tStop connection with Transducer\n");
    stopConnection(pCM);

    fclose(pFile);
    fclose(pLog);
}

void generateConnectionWithTrans(conMeta *pCM) {
    switch (pCM->connectionType) {
        case PFC_TRANS_SOCKET:
            createSocketServer(pCM, SOCK_TRANS_NAME);
            pCM->fdClient = accept(pCM->fdServer, pCM->pCliAdd, &(pCM->cliLen));
            break;
        case PFC_TRANS_PIPE:
            createPipeServer(pCM, PIPE_TRANS_NAME);
            break;
        case PFC_TRANS_FILE:
            break;
    }
}

void sendDataToTrans(conMeta *pCM, char *data) {
    switch (pCM->connectionType) {
        case PFC_TRANS_SOCKET:
            write(pCM->fdClient, data, strlen(data) + 1);
            wait(NULL);
            break;
        case PFC_TRANS_PIPE:
            write(pCM->fdServer, data, strlen(data) + 1);
            wait(NULL);
            break;
        case PFC_TRANS_FILE:
            do {
                pCM->pFile = fopen(FILE_TRANS_NAME, "w+");
                if (pCM->pFile != NULL) {
                    break;
                }
            } while (1);
            fputs(data, pCM->pFile);
            fclose(pCM->pFile);
            break;
    }
}

void stopConnection(conMeta *pCM) {
    sendDataToTrans(pCM, STOP_SIGNAL);
    switch (pCM->connectionType) {
        case PFC_TRANS_SOCKET:
            break;
        case PFC_TRANS_PIPE:
            close(pCM->fdServer);
            break;
        case PFC_TRANS_FILE:
            break;
    }
}

char *extractPFCLogName(unsigned int connectionType) {
    char *logName;
    switch (connectionType) {
        case PFC_TRANS_SOCKET:
            logName = PFC_SOCK_LOG;
            break;
        case PFC_TRANS_PIPE:
            logName = PFC_PIPE_LOG;
            break;
        case PFC_TRANS_FILE:
            logName = PFC_FILE_LOG;
            break;
        default:
            logName = "";
            break;
    }

    char *logPathName = malloc(1 + strlen(PFC_LOGS_PATH) + strlen(logName));
    strcpy(logPathName, PFC_LOGS_PATH);
    strcat(logPathName, logName);

    return logPathName;
}
