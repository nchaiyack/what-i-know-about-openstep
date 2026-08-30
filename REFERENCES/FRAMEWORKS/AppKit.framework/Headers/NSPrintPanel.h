#ifndef STRICT_OPENSTEP


/*
	NSPrintPanel.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>
#import <AppKit/AppKitDefines.h>



@class NSPopUpButton;
@class NSButtonCell;
@class NSMatrix;

#ifndef WIN32
enum {
    NSPPSaveButton			= 3,
    NSPPPreviewButton			= 4,
    NSFaxButton				= 5,
    NSPPTitleField			= 40,
    NSPPImageButton			= 41,
    NSPPNameTitle			= 42,
    NSPPNameField			= 43,
    NSPPNoteTitle			= 44,
    NSPPNoteField			= 45,
    NSPPStatusTitle			= 46,
    NSPPStatusField			= 47,
    NSPPCopiesField			= 49,
    NSPPPageChoiceMatrix		= 50,
    NSPPPageRangeFrom			= 51,
    NSPPPageRangeTo			= 52,
    NSPPScaleField			= 53,
    NSPPOptionsButton			= 54,
    NSPPPaperFeedButton			= 55,
    NSPPLayoutButton			= 56,
};

@interface NSPrintPanel : NSPanel
{
    id			_buttons;
    id                  _cancel;
    id                  _copies;
    id                  _feed;
    id			_feedBox;
    id                  _firstPage;
    id                  _lastPage;
    NSPopUpButton 	*_layoutList;
    id                  _name;
    id                  _note;
    NSButtonCell	*_ok;
    id			_optionsButton;
    id                  _pageMode;
    id                  _preview;
    id			_printerListBox;
    id                  _save;
    id			_scaleFactor;
    id                  _status;
    id			_deviceButtonsBox;
    id			_ppdMessage;
    id                  _accessoryView;
    NSMatrix		*_printers;
    int                 _exitTag;
    BOOL		_isPPDFileOK;
    BOOL		_recyclable;
    id			_controlBox;
    id			_printerFeatures;
    NSPopUpButton	*_printServicesPopUp;
    BOOL		_checkedForPrintServicesPopUp;
    unsigned int _reservedPrintPanel1;
}

+ (NSPrintPanel *)printPanel;

- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)pickedButton:(id)sender;
- (void)pickedLayoutList:(id)sender;
- (void)pickedAllPages:(id)sender;
- (void)updateFromPrintInfo;
- (void)finalWritePrintInfo;
- (int)runModal;

@end

#else  WIN32

#import <AppKit/NSPrintInfo.h>

@interface NSPrintPanel : NSObject
{
    void *_printdlg;
    NSPrintInfo *_printInfo;
    id _accessoryView;
    NSPopUpButton	*_printServicesPopUp;
    BOOL		_checkedForPrintServicesPopUp;
    unsigned int _reservedPrintPanel1;
}

+ (NSPrintPanel *)printPanel;

- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)updateFromPrintInfo;
- (void)finalWritePrintInfo;
- (int) runModal;

@end


#endif WIN32

#endif STRICT_OPENSTEP

