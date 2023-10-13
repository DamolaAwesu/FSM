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
*  This file is the CParserFSM Source file
*
*  end-description
*******************************************************************************
*/

/********************************************//**
 * Includes
 ***********************************************/
#include "CParser.h"
#include "stdio.h"

/********************************************//**
 * Reserved Reminder Signal definition
 ***********************************************/
typedef enum {
    EMPTY_SIG
}HiddenSignals;

static Event const emptySig = {EMPTY_SIG};

/********************************************//**
 * \brief StateHandler function prototypes
 *
 * \param   [in] me
 *          Pointer to FSM instance
 * \param   [in] evt
 *          Pointer to active event
 * \return  FSM_STATUS_E
 *          INIT/HANDLED/TRANS/IGNORED/ERROR
 *
 ***********************************************/
static FSM_STATUS_E CParser_SlashState(CParserFSM * const me, Event const * const evt);
static FSM_STATUS_E CParser_StarState(CParserFSM * const me, Event const * const evt);
static FSM_STATUS_E CParser_CodeState(CParserFSM * const me, Event const * const evt);
static FSM_STATUS_E CParser_CommentState(CParserFSM * const me, Event const * const evt);

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
Status_Type CParser_Init(CParserFSM * fsm)
{
  Status_Type retVal = E_OK;

  if((NULL != fsm))
  {
    /**< Initialize FSM */
    retVal = Fsm_Init(&fsm->super,(StateHandler)CParser_CodeState);
    if(retVal == E_OK)
    {
      fsm->state = CODE_STATE;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

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
static FSM_STATUS_E CParser_CodeState(CParserFSM * const me, Event const * const evt)
{
    FSM_STATUS_E retStatus;

    switch(evt->sig)
    {
        case INIT_SIG:
            me->state = CODE_STATE;
            retStatus = INIT_STATUS;
            break;
        case ENTRY_SIG:
            printf("Entering Code state\n");
            me->state = CODE_STATE;
            retStatus = HANDLED_STATUS;
            break;
        case EXIT_SIG:
            retStatus = HANDLED_STATUS;
            break;
        case SLASH_SIG:
            retStatus = Fsm_Transition((FSM *)me, (StateHandler)CParser_SlashState);
            break;
        case EMPTY_SIG:
            printf("Reminder Event\n");
            retStatus = HANDLED_STATUS;
            break;
        default:
            retStatus = IGNORED_STATUS;
            break;
    }

    return retStatus;
}

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
static FSM_STATUS_E CParser_CommentState(CParserFSM * const me, Event const * const evt)
{
    FSM_STATUS_E retStatus;

    switch(evt->sig)
    {
        case ENTRY_SIG:
            printf("Entering Comment state\n");
            me->state = COMMENT_STATE;
            retStatus = HANDLED_STATUS;
            break;
        case EXIT_SIG:
            retStatus = HANDLED_STATUS;
            break;
        case STAR_SIG:
            retStatus = Fsm_Transition((FSM *)me, (StateHandler)CParser_StarState);
            break;
        default:
            retStatus = IGNORED_STATUS;
            break;
    }

    return retStatus;
}

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
static FSM_STATUS_E CParser_SlashState(CParserFSM * const me, Event const * const evt)
{
    FSM_STATUS_E retStatus;

    switch(evt->sig)
    {
        case ENTRY_SIG:
            printf("Entering Slash state\n");
            me->state = SLASH_STATE;
            retStatus = HANDLED_STATUS;
            break;
        case EXIT_SIG:
            retStatus = HANDLED_STATUS;
            break;
        case CHAR_SIG:
        case SLASH_SIG:
            retStatus = Fsm_Transition((FSM *)me, (StateHandler)CParser_CodeState);
            break;
        case STAR_SIG:
            retStatus = Fsm_Transition((FSM *)me, (StateHandler)CParser_CommentState);
            break;
        default:
            retStatus = IGNORED_STATUS;
            break;
    }

    return retStatus;
}

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
static FSM_STATUS_E CParser_StarState(CParserFSM * const me, Event const * const evt)
{
    FSM_STATUS_E retStatus;

    switch(evt->sig)
    {
        case ENTRY_SIG:
            printf("Entering Star state\n");
            me->state = STAR_STATE;
            retStatus = HANDLED_STATUS;
            break;
        case EXIT_SIG:
            retStatus = HANDLED_STATUS;
            break;
        case CHAR_SIG:
            retStatus = Fsm_Transition((FSM *)me, (StateHandler)CParser_CommentState);
            break;
        case SLASH_SIG:
            retStatus = Fsm_Transition((FSM *)me, (StateHandler)CParser_CodeState);
            break;
        default:
            retStatus = IGNORED_STATUS;
            break;
    }

    return retStatus;
}
/** \} doxygen end group definition */
