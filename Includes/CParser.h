/**
 *******************************************************************************
 * \addtogroup CParser
 * \{
 *******************************************************************************
*/

/**
*******************************************************************************
*  \file
*  $Rev: $
*  $Date: $
*  $HeadURL: $
*
*  \brief
*  This file is the CParserFSM header file
*
*  end-description
*******************************************************************************
*/
#ifndef CPARSER_H_INCLUDED
#define CPARSER_H_INCLUDED

#include "FSM.h"

/********************************************//**
 * \enum    CParser_State
 *
 * \brief   All possible states of the CParser FSM
 *
 ***********************************************/
typedef enum{
    CODE_STATE,
    COMMENT_STATE,
    SLASH_STATE,
    STAR_STATE,
    MAX_STATES
}CParser_State;

/********************************************//**
 * \enum    CParser_Signals
 *
 * \brief   CParserFSM-specific events
 *
 ***********************************************/
typedef enum {
    CHAR_SIG = USER_SIG,
    SLASH_SIG,
    STAR_SIG
}CParser_Signals;

/********************************************//**
 * \struct  CParserFSM
 *
 * \brief   Concrete FSM class for CParser
 *
 ***********************************************/
typedef struct {
    FSM super;
    CParser_State state;
}CParserFSM;

/**
 *******************************************************************************
 * \brief     CParser Init function
 *
 * \return    Status_Type
 *            E_OK/E_NOT_OK
 *
 * \param     [in] fsm
 *            FSM instance
 *
 *******************************************************************************
 */
Status_Type CParser_Init(CParserFSM * fsm);

#endif // CPARSER_H_INCLUDED
