
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import "Country.h"

enum LogisticsFormTags {
    LGairports=0,
    LGairlines,
    LGtransportation,  
    LGhotels  
};


@interface TAController:NSObject
{
    id	tableView;
    id	celsius;
    id  commentsLabel;
    id	commentsField;
    id  converter;
    id	countryField;
    id  currencyDollarsField;
    id  currencyLocalField;
    id	currencyNameField;
    id	currencyRateField;
    id	englishSpokenSwitch;
    id	fahrenheit;
    id	languagesField;
    id	logisticsForm;

    NSMutableDictionary *countryDict;
    NSMutableArray *countryKeys;
    BOOL recordNeedsSaving;
}

/* target/action */
- (void)addRecord:(id)sender;
- (void)convertCelsius:(id)sender;
- (void)convertCurrency:(id)sender;
- (void)deleteRecord:(id)sender;
- (void)handleTVClick:(id)sender;
- (void)blankFields:(id)sender;
- (void)nextRecord:(id)sender;
- (void)priorRecord:(id)sender;
- (void)switchChecked:(id)sender;

/* Data read and write methods */
- (void)populateFields:(Country *)aRec;
- (void)extractFields:(Country *)aRec;

/* housekeeping methods */
- (id)init;
- (void)awakeFromNib;
- (void)dealloc;

/* delegate and notification methods */
- (void)textDidChange:(NSNotification *)notification;
- (BOOL)applicationShouldTerminate:(id)sender;

@end
