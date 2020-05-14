/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_GRAPH                      2       /* control type: graph, callback function: (none) */
#define  PANEL_COMMANDBUTTON              3       /* control type: command, callback function: RefreshWaveProc */
#define  PANEL_COMMANDBUTTON_2            4       /* control type: command, callback function: ClearWaveProc */
#define  PANEL_TEXT_PERIOD                5       /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXT_VPP                   6       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ClearWaveProc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RefreshWaveProc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
