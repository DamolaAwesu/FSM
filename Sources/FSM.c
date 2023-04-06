/**
 *******************************************************************************
 * \addtogroup FSM
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
*  This file is the FSM Source file
*
*  end-description
*******************************************************************************
*/

/*********************************************
* Includes
*********************************************/
#include "FSM.h"

/*********************************************
* Static global variables
*********************************************/
static Event const entryEvt = { ENTRY_SIG };
static Event const exitEvt  = { EXIT_SIG };
static Event const initEvt  = { INIT_SIG };

/**
 *******************************************************************************
 * \brief     This function initializes the FSM to a known initial state
 *
 * \return    Status_Type
 *            E_OK/E_NOT_OK
 *
 * \param     [in] me
 *            instance of FSM to be initialized
 * \param     [in] initialState
 *            pointer to StateHandler function for desired FSM initial state
 *
 *******************************************************************************
 */
Status_Type Fsm_Init(FSM * const me, StateHandler initialState)
{
  /**< Local Variables */
  Status_Type retVal = E_OK;
  FSM_STATUS_E status;

  /**< Check arguments are not NULL */
  assert(me && initialState);

  /**< Initialize FSM */
  me->stateHandler = initialState;
  status = (me->stateHandler)(me, &initEvt);

  /**< Perform entry action of intial state */
  if(status != ERROR_STATUS)
  {
    status = (me->stateHandler)(me, &entryEvt);
  }
  if(status == ERROR_STATUS)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /** end of Fsm_Init */

/**
 *******************************************************************************
 * \brief     This function is called regularly to dispatch events
 *            to the state handlers
 *
 * \return    Status_Type
 *            E_OK/E_NOT_OK
 *
 * \param     [in] me
 *            instance of FSM to be initialized
 * \param     [in] e
 *            pointer to event to be passed to the active StateHandler
 *
 *******************************************************************************
 */
Status_Type Fsm_Dispatch(FSM * const me, Event const * const evt)
{
  /**< Local variables */
  FSM_STATUS_E status;
  Status_Type retVal = E_OK;

  /**< Check arguments are not NULL */
  assert(me && evt);

  /**< Pass event to the statehandler */
  status = (me->stateHandler)(me, evt);
  if(status == ERROR_STATUS)
  {
    retVal = E_NOT_OK;
  }
  return retVal;
} /** end of Fsm_Dispatch */

/**
 *******************************************************************************
 * \brief     This function is called by state handlers to handle transition
 *            from one state to another
 *
 * \return    FSM_STATUS_E
 *            INIT/HANDLED/TRANS/IGNORED/ERROR
 *
 * \param     [in] me
 *            FSM instance
 * \param     [in] nextStateHandler
 *            Pointer to function for target state
 *
 *******************************************************************************
 */
FSM_STATUS_E Fsm_Transition(FSM * const me, StateHandler nextStateHandler)
{
  /**< Local Variables */
  FSM_STATUS_E status = ERROR_STATUS;

  /**< Check arguments are not NULL */
  assert(me && nextStateHandler);

  /**< Perform exit actions of previous state and entry actions of new state */
  status = (me->stateHandler)(me, &exitEvt);
  if(status != ERROR_STATUS)
  {
    me->stateHandler = nextStateHandler;
    status = (me->stateHandler)(me, &entryEvt);
  }

  return status;
} /** end of Fsm_Transition */

/** \} doxygen end group definition */
