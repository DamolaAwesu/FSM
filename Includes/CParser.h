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

/** \brief Enum of possible states of CParser FSM
 *
 * \param
 * \param
 * \return
 *
 */
typedef enum{
    CODE_STATE,
    COMMENT_STATE,
    SLASH_STATE,
    STAR_STATE,
    MAX_STATES
}CParser_State;

/** \brief Signals handled by CParser FSM
 *
 * \param
 * \param
 * \return
 *
 */
typedef enum {
    CHAR_SIG = USER_SIG,
    SLASH_SIG,
    STAR_SIG
}CParser_Signals;

/** \brief CParser FSM class
 *
 * \param
 * \param
 * \return
 *
 */
typedef struct {
    FSM super;
    CParser_State state;
}CParserFSM;

/********************************************************
* StateHandler Prototypes
********************************************************/
FSM_STATUS_E CParser_CodeState(CParserFSM * const me, Event const * const evt);
FSM_STATUS_E CParser_CommentState(CParserFSM * const me, Event const * const evt);
FSM_STATUS_E CParser_SlashState(CParserFSM * const me, Event const * const evt);
FSM_STATUS_E CParser_StarState(CParserFSM * const me, Event const * const evt);


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
