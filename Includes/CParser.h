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
 * \brief     Code State StateHandler
 *
 * \return    FSM_STATUS_E
 *            INIT/HANDLED/TRANS/IGNORED/ERROR
 *
 * \param     [in] me
 *            FSM instance
 * \param     [in] evt
 *            Pointer to event to be handled by the statehandler
 *
 *******************************************************************************
 */
FSM_STATUS_E CParser_CodeState(CParserFSM * const me, Event const * const evt);

/**
 *******************************************************************************
 * \brief     Comment State StateHandler
 *
 * \return    FSM_STATUS_E
 *            INIT/HANDLED/TRANS/IGNORED/ERROR
 *
 * \param     [in] me
 *            FSM instance
 * \param     [in] evt
 *            Pointer to event to be handled by the statehandler
 *
 *******************************************************************************
 */
FSM_STATUS_E CParser_CommentState(CParserFSM * const me, Event const * const evt);

/**
 *******************************************************************************
 * \brief     Slash State StateHandler
 *
 * \return    FSM_STATUS_E
 *            INIT/HANDLED/TRANS/IGNORED/ERROR
 *
 * \param     [in] me
 *            FSM instance
 * \param     [in] evt
 *            Pointer to event to be handled by the statehandler
 *
 *******************************************************************************
 */
FSM_STATUS_E CParser_SlashState(CParserFSM * const me, Event const * const evt);

/**
 *******************************************************************************
 * \brief     Star State StateHandler
 *
 * \return    FSM_STATUS_E
 *            INIT/HANDLED/TRANS/IGNORED/ERROR
 *
 * \param     [in] me
 *            FSM instance
 * \param     [in] evt
 *            Pointer to event to be handled by the statehandler
 *
 *******************************************************************************
 */
FSM_STATUS_E CParser_StarState(CParserFSM * const me, Event const * const evt);

#endif // CPARSER_H_INCLUDED
