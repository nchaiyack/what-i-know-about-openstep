/*
** IODisplayInspector - Inspects display mode for display cards.
**
** Copyright 1993 by NeXT Computer, Inc.  All Rights Reserved.
*/
#import "IODeviceInspector.h"

typedef struct _IODisplayMode
{
    int	  width, height;
    int	  refreshRate;
    char  colorSpace[256];
} IODisplayMode;

@interface IODisplayInspector:IODeviceInspector
{
    id displayAccessoryHolder;
    id displayMode;
    id panel;
    id modes;
    id okButton;
    id selectButton;
    id modeText;
    
@private
    void  *_private;
    int   _reserved;
}

- init;
- setAccessoryView:aView;
- runPanel:sender;
- panelDone:sender;
- cancel:sender;
- doubleClicked:sender;
- setTable:(NXStringTable *)instance;
@end
