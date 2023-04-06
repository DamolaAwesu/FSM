/**
 *******************************************************************************
 * \addtogroup APP
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
*  This file is the FSM Test App Source file
*
*  end-description
*******************************************************************************
*/

/********************************************//**
 * Includes
 ***********************************************/
#include "CParser.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>



/** \brief Main Application
 *
 * \param None
 * \param
 * \return int
 *
 */

int main(void)
{
  /**< Local variables */
  Status_Type retVal = E_OK;
  CParserFSM CParser;
  Event evt;
  FILE * fp;

  const char * filename = "Sources\\main.c";

  /**< Get current directory */
  char currDir[512];
  memset(currDir,'\0', 512);
  if(getcwd(currDir, 512) == NULL)
  {
    exit(1);
  }

  /**< Get qualified file path */
  char testFile[strlen(currDir)+strlen(filename)+1];
  memset(testFile, '\0', strlen(currDir)+strlen(filename)+2);
  snprintf(testFile, strlen(currDir)+strlen(filename)+1, "%s\\%s",currDir,filename);
  printf("%s\n", testFile);

  /**< Exit if file open failed */
  if((fp = fopen(testFile,"r")) == NULL)
  {
    fclose(fp);
    return -1;
  }

  /**< Initialize FSM */
  retVal = Fsm_Init((FSM *)&CParser,(StateHandler)CParser_CodeState);

  if(E_OK == retVal)
  {
    /**< Read file line by line */
    char line[1024];
    memset(line, '\0', 1024);

    if(NULL != fp)
    {
      while(fgets(line,1024,fp) != NULL)
      {
        printf("%s", line);
        /**< Generate events based on file contents */
        for(int i = 0; i < strlen(line); i++)
        {
          switch(line[i])
          {
            case '/':
              evt.sig = SLASH_SIG;
              break;
            case '*':
              evt.sig = STAR_SIG;
              break;
            case '\n':
              continue;
            default:
              evt.sig = CHAR_SIG;
              break;
          }

          /**< Dispatch event to FSM */
          retVal = Fsm_Dispatch((FSM *)&CParser,(Event *)&evt);
        }
      }

      /**< Close file */
      fclose(fp);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}

/** \} doxygen end group definition */
