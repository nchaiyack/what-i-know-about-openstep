
#import "TAController.h"
#import "Converter.h"
@implementation TAController

- (void)addRecord:(id)sender
{
    Country *aCountry;
    NSString *countryName = [countryField stringValue];
    
    /* look up country name in dictionary */
    /* if exists, remove record in dictionary, else create new one*/

    if (countryName && (![countryName isEqualToString:@""])) {
        aCountry = [countryDict objectForKey:countryName];
 
        if (aCountry && recordNeedsSaving) {
           /* remove old Country object from dictionary */
           [countryDict removeObjectForKey:[aCountry name]];
         }
        else if (!aCountry)  /* record is new */
            aCountry = [[Country alloc] init];
        else return;   /* record already exists and hasn't changed */

        /* extract field values and put in dictionary and keys array */
        [self extractFields:aCountry];
        [countryDict setObject:aCountry forKey:[aCountry name]];
        [countryKeys addObject:[aCountry name]];
        
        /* sort array */
        [countryKeys sortUsingSelector:@selector(compare:)];
        
        recordNeedsSaving=NO;
        [commentsLabel setStringValue:[NSString stringWithFormat:@"Notes and Itinerary for %@", [countryField stringValue]]];
        [countryField selectText:self];
        [tableView tile];
        [tableView selectRow:[countryKeys indexOfObject:[aCountry name]] byExtendingSelection:NO];

    }
    return;

}

- (void)blankFields:(id)sender
{
    [countryField setStringValue:@""];

    [[logisticsForm cellAtIndex:LGairports] setStringValue:@""];
    [[logisticsForm cellAtIndex:LGairlines] setStringValue:@""];
    [[logisticsForm cellAtIndex:LGtransportation] setStringValue:@""];
    [[logisticsForm cellAtIndex:LGhotels] setStringValue:@""];

    [currencyNameField setStringValue:@""];
    [currencyRateField setFloatValue:0.000];
    [languagesField setStringValue:@""];
    [englishSpokenSwitch setState:NO];

    [currencyDollarsField setFloatValue:0.00];
    [currencyLocalField setFloatValue:0.00];
    [celsius setIntValue:0];
    [fahrenheit setIntValue:0];

    [commentsField setString:@""];

    [countryField selectText:self];

    return;
}

- (void)populateFields:(Country *)aRec
{
    [countryField setStringValue:[aRec name]];

    [[logisticsForm cellAtIndex:LGairports] setStringValue:[aRec airports]];
    [[logisticsForm cellAtIndex:LGairlines] setStringValue:[aRec airlines]];
    [[logisticsForm cellAtIndex:LGtransportation] setStringValue:[aRec transportation]];
    [[logisticsForm cellAtIndex:LGhotels] setStringValue:[aRec hotels]];

    [currencyNameField setStringValue:[aRec currencyName]];
    [currencyRateField setFloatValue:[aRec currencyRate]];
    [languagesField setStringValue:[aRec languages]];
    [englishSpokenSwitch setState:[aRec englishSpoken]];

    [commentsField setString:[aRec comments]];

    [countryField selectText:self];

    return;

}

- (void)extractFields:(Country *)aRec
{
    [aRec setName:[countryField stringValue]];

    [aRec setAirports:[[logisticsForm cellAtIndex:LGairports] stringValue]];
    [aRec setAirlines:[[logisticsForm cellAtIndex:LGairlines] stringValue]];
    [aRec setTransportation:[[logisticsForm cellAtIndex:LGtransportation] stringValue]];
    [aRec setHotels:[[logisticsForm cellAtIndex:LGhotels] stringValue]];

    [aRec setCurrencyName:[currencyNameField stringValue]];
    [aRec setCurrencyRate:[currencyRateField floatValue]];
    [aRec setLanguages:[languagesField stringValue]];
    [aRec setEnglishSpoken:[englishSpokenSwitch state]];

    [aRec setComments:[commentsField string]];
     
    return;
}


- (void)convertCelsius:(id)sender
{
    
    return;
}

- (void)convertCurrency:(id)sender
{

    [currencyLocalField setFloatValue:[converter convertAmount:[currencyDollarsField floatValue] byRate:[currencyRateField floatValue]]];

    return;
}

- (void)deleteRecord:(id)sender
{
    Country *aCountry;
    NSString *countryName = [countryField stringValue];
    
    if (countryName && (![countryName isEqualToString:@""])) {
        aCountry = [countryDict objectForKey:countryName];

        if (aCountry) {
            [countryDict removeObjectForKey:countryName];
            [countryKeys removeObject:countryName];
            [self blankFields:self];
            [tableView tile];
        }
    }    
    return;
}

- (void)switchChecked:(id)sender { recordNeedsSaving = YES; }

- (void)handleTVClick:(id)sender
{
    Country *aRec, *newRec, *newerRec;
    int index = [sender selectedRow];

    /* does current obj need to be saved? */
    if (recordNeedsSaving) {
        /* is current object already in dictionary? */
        if ( aRec = [countryDict objectForKey:[countryField stringValue]] ) {
            /* remove if it's been changed */
            if (aRec) {
                [countryDict removeObjectForKey:[aRec name]];
                [countryKeys removeObject:[aRec name]];
            }
        }

        /* Create Country obj, add it to dict and add name to keys array */
        newRec = [[Country alloc] init];
        [self extractFields:newRec];
        [countryDict setObject:newRec forKey:[countryField stringValue]];
        [countryKeys addObject:[countryField stringValue]];

        /* sort array here */
        [countryKeys sortUsingSelector:@selector(compare:)];
    }
    if (index >= 0 && index < [countryKeys count]) {
        newerRec = [countryDict objectForKey:[countryKeys objectAtIndex:index]];
        [self populateFields:newerRec];
        [commentsLabel setStringValue:[NSString stringWithFormat:
               @"Notes and Itinerary for %@", [countryField stringValue]]];
        recordNeedsSaving=NO;
        [tableView tile];
    }
    return;
}

- (void)nextRecord:(id)sender
{
    int r;

    r = [tableView selectedRow];
    if (r == [countryKeys indexOfObject:[countryKeys lastObject]])
        r = 0; /* wrap to beginning */
    else
        r++;
    [tableView selectRow:r byExtendingSelection:NO];
    [self handleTVClick:tableView];
    
    return;
}

- (void)priorRecord:(id)sender
{
    int r;

    r = [tableView selectedRow];
    if (r == 0)
        /* wrap to end */
        r = [countryKeys indexOfObject:[countryKeys lastObject]]; 
    else
        r--;
    [tableView selectRow:r byExtendingSelection:NO];
    [self handleTVClick:tableView];
    
    return;
}

/* ** enabling/disabling menu items, an alternative to "wrapping"
   ** the selection in nextRecord: and priorRecord:
   ** uncomment to see what happens
- (BOOL)validateMenuItem:(NSMenuItem *)anItem
{
    int row = [tableView selectedRow];
    if ([[anItem title] isEqualToString:@"Next Record"] &&
        (row == [countryKeys indexOfObject:[countryKeys lastObject]])) {
        NSBeep();
        return NO;
    }
    if ([[anItem title] isEqualToString:@"Prior Record"] && row == 0 ) {
        NSBeep();
        return NO;
    }
    return YES;
}
**************************************************** */

- (id)init
{
    NSString *storePath = [[NSBundle mainBundle] pathForResource:@"TravelData" ofType:nil];
    [super init];

    countryDict = [NSUnarchiver unarchiveObjectWithFile:storePath];

    if (!countryDict) {
        countryDict = [[NSMutableDictionary alloc] initWithCapacity:10];
        countryKeys = [[NSMutableArray alloc] initWithCapacity:10];
    } else
        countryDict = [countryDict retain];
    
    recordNeedsSaving=NO;
    
    return self;
}

- (void)dealloc
{
    [countryDict release];
    [countryKeys release];
    [super dealloc];
}

- (void)awakeFromNib
{
    NSArray *tmpArray = [[countryDict allKeys] /* 1 */
                         sortedArrayUsingSelector:@selector(compare:)];
    countryKeys = [[NSMutableArray alloc] initWithArray:tmpArray];

    /* select first field */
    [countryField selectText:self];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                          selector:@selector(textDidChange:)
                          name:@"NSControlTextDidChangeNotification" object:nil];
    
    [tableView setDataSource:self];
    [tableView setDelegate:self];
    [tableView sizeLastColumnToFit];

    [commentsField setDelegate:self];
    [currencyRateField setDelegate:self];

    [[currencyRateField cell] setEntryType:NSFloatType];
    [[currencyRateField cell] setFloatingPointFormat:YES left:2 right:1];       
    [[currencyDollarsField cell] setEntryType:NSFloatType];
    [[currencyDollarsField cell] setFloatingPointFormat:YES left:5 right:2];       
    [[currencyLocalField cell] setEntryType:NSFloatType];
    [[currencyLocalField cell] setFloatingPointFormat:YES left:5 right:2];
    [[celsius cell] setEntryType:NSFloatType];
    [[celsius cell] setFloatingPointFormat:YES left:2 right:1];
}

/* NSTableView data source methods */

- (int)numberOfRowsInTableView:(NSTableView *)theTableView
{
    return [countryKeys count];
}

- (id)tableView:(NSTableView *)theTableView
      objectValueForTableColumn:(NSTableColumn *)theColumn
            row:(int)rowIndex
{
    if ([[theColumn identifier] intValue]==0)
        return [countryKeys objectAtIndex:rowIndex];
    else
        return nil;
}
      
    

/* Delegation and notification methods */

- (void)textDidChange:(NSNotification *)notification
{
    recordNeedsSaving=YES;
}

- (void)controlTextDidChange:(NSNotification *)notification
{
    recordNeedsSaving=YES;
}

- (BOOL)textShouldBeginEditing:(NSText *)textObj
{
    recordNeedsSaving=YES;
    return YES;
}

- (BOOL)applicationShouldTerminate:(id)sender
{
    NSString *storePath = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"TravelData"];
    /* save current record if it is new or changed */
   [self addRecord:self];

   /* save dictionary (if it has contents) to archive file */
   if (countryDict && [countryDict count])
        [NSArchiver archiveRootObject:countryDict toFile:storePath];

    return YES;
}

- (BOOL)control:(NSControl *)control isValidObject:(id)obj
{
    if (control == currencyRateField) {
        if ([obj floatValue] < 0.0) {
            NSRunAlertPanel(@"Travel Advisor", @"Rate cannot be negative.", nil, nil, nil);
            return NO;
        }
    }
    return YES;
}

@end
