#include "protocol.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

PDU *mkPDU(uint uiMsgLen)
{
    uint uiPDULen = sizeof(PDU)+uiMsgLen;
    PDU *pdu = (PDU*)malloc(uiPDULen);
    if (NULL == pdu) {
        exit(EXIT_FAILURE);
    }
    memset(pdu, 0, uiPDULen);
    pdu->uiPDULen = uiPDULen;
    pdu->uiMsgLen = uiMsgLen;
    return pdu;
}
