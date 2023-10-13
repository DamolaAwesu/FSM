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
*  This file is the FSM Header file
*
*  end-description
*******************************************************************************
*/

#ifndef INCLUDES_FSM_H_
#define INCLUDES_FSM_H_

/******************************************************************************
* Include Files
******************************************************************************/
#include "stdint.h"
#include "assert.h"

/******************************************************************************
* Type definitions
******************************************************************************/
typedef struct FSM FSM;            /**< Forward declaration of FSM struct    */
typedef struct Event Event;        /**< Forward declaration of Event struct  */

/********************************************//**
 * \enum  Status_Type
 *
 * \brief Indicate pass/fail of an operation
 *
 ***********************************************/
typedef enum
{
    E_OK,
    E_NOT_OK
}Status_Type;

/********************************************//**
 * \enum  FSM_STATUS_E
 *
 * \brief Indicate status of FSM event processing
 *
 ***********************************************/
typedef enum {
  INIT_STATUS,
  HANDLED_STATUS,
  TRANS_STATUS,
  IGNORED_STATUS,
  ERROR_STATUS
}FSM_STATUS_E;

/********************************************//**
 * \enum  RESERVED_SIGNALS_E
 *
 * \brief Signals reserved solely for FSM use
 *
 ***********************************************/
typedef enum {
  INIT_SIG = 1,
  ENTRY_SIG,
  EXIT_SIG,
  USER_SIG
}RESERVED_SIGNALS_E;

/**< State Handler function prototype */
typedef FSM_STATUS_E (*StateHandler)(FSM *me, Event const * const evt);

/********************************************//**
 * \struct  FSM
 *
 * \brief   Representation of FSM class
 *
 ***********************************************/
struct FSM {
  StateHandler stateHandler;
};

/********************************************//**
 * \struct  Event
 *
 * \brief   Representation of Event class
 *
 ***********************************************/
struct Event {
  uint32_t sig;
};

/**
 *******************************************************************************
 * \brief     This function initializes the FSM to a known initial state
 *
 * \return    Std_ReturnType
 *            E_OK/E_NOT_OK
 *
 * \param     [in] me
 *            instance of FSM to be initialized
 * \param     [in] initialState
 *            pointer to StateHandler function for desired FSM initial state
 *
 *******************************************************************************
 */
Status_Type Fsm_Init(FSM * const me, StateHandler initialState);

/**
 *******************************************************************************
 * \brief     This function is called regularly to dispatch events
 *            to the state handlers
 *
 * \return    Std_ReturnType
 *            E_OK/E_NOT_OK
 *
 * \param     [in] me
 *            instance of FSM to be initialized
 * \param     [in] evt
 *            pointer to event to be passed to the active StateHandler
 *
 *******************************************************************************
 */
Status_Type Fsm_Dispatch(FSM * const me, Event const * const evt);

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
FSM_STATUS_E Fsm_Transition(FSM * const me, StateHandler nextStateHandler);

#endif  /* INCLUDES_FSM_H_ */
/** \} doxygen end group definition */
