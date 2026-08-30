#import "ToDoItem.h"

@implementation ToDoItem

- (id)initWithName:(NSString *)name andDate:(NSCalendarDate *)date
{
    NSCalendarDate *tDate;

    if (!name && ![name isKindOfClass:[NSString class]]) return nil;
    [super init];

    if (!date)
        tDate = [NSCalendarDate date];
    else
        tDate = date;
            
    [self setDay: tDate];
    [self setItemName:name];
    [self setItemStatus:incomplete];
    [self setNotes:@""];
     
    return self;
}

- (void)dealloc
{
    [day release];
    [itemName release];
    [notes release];
    if (itemTimer) {
        [itemTimer invalidate];
        [itemTimer release];
    }
    [super dealloc];
}

- (id)copyWithZone:(NSZone *)zone
{    
    ToDoItem *newobj = [[ToDoItem alloc] initWithName:itemName andDate:day];
    [newobj setNotes:notes];
    [newobj setItemStatus:itemStatus];
    [newobj setSecsUntilDue:secsUntilDue];
    [newobj setSecsUntilNotif:secsUntilNotif];

    return newobj;
}

- (BOOL)isEqual:(id)anObj
{
    if ([anObj isKindOfClass:[ToDoItem class]] &&
        [itemName isEqualToString:[anObj itemName]] &&
        [day isEqualToDate:[anObj day]])
        return YES;
    else
        return NO;
}

- (NSString *)description
{
    NSString *desc = [NSString stringWithFormat:@"%@\n\tName: %@\n\tDate: %@\n\tNotes: %@\n\tCompleted: %@\n\tSecs Until Due: %d\n\tSecs Until Notif: %d",
        [super description],
        [self itemName],
        [self day],
        [self notes],
        (([self itemStatus]==complete)?@"Yes":@"No"),
        [self secsUntilDue],
        [self secsUntilNotif]];

    return (desc);
}

- (id)initWithCoder:(NSCoder *)coder
{
    day = [coder decodeObject];
    itemName = [coder decodeObject];
    [coder decodeValueOfObjCType:@encode(typeof(secsUntilDue)) at:&secsUntilDue];
    [coder decodeValueOfObjCType:@encode(typeof(secsUntilNotif)) at:&secsUntilNotif];
    [coder decodeValueOfObjCType:@encode(typeof(itemStatus)) at:&itemStatus];
    notes = [coder decodeObject];

    day = [day copy];
    itemName = [itemName copy];
    notes = [notes copy];

    return self;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeObject:day];
    [coder encodeObject:itemName];
    [coder encodeValueOfObjCType:@encode(typeof(secsUntilDue)) at:&secsUntilDue];
    [coder encodeValueOfObjCType:@encode(typeof(secsUntilNotif)) at:&secsUntilNotif];
    [coder encodeValueOfObjCType:@encode(typeof(itemStatus)) at:&itemStatus];
    [coder encodeObject:notes];
}

-(void) setDay:(NSCalendarDate *)newDay
{
    [day autorelease];
    day = [newDay copy];
}

- (NSCalendarDate *)day { return day; }

- (void)setItemName:(NSString *)newName
{
    [itemName autorelease];
    itemName = [newName copy];
}

- (NSString *)itemName { return itemName; }

- (void)setNotes:(NSString *)newNotes
{
    [notes autorelease];
    notes = [newNotes copy];
}

- (NSString *)notes { return notes; }

- (void)setSecsUntilNotif:(long)secs
{
    secsUntilNotif = secs;
}

- (long)secsUntilNotif { return secsUntilNotif; }

- (void)setSecsUntilDue:(long)secs
{
    secsUntilDue = secs;
}

- (long)secsUntilDue { return secsUntilDue; }

- (void)setItemStatus:(ToDoItemStatus)newStatus
{
    itemStatus = newStatus;
}

- (ToDoItemStatus)itemStatus { return itemStatus; }

- (void)setItemTimer:(NSTimer *)aTimer
{
    if (itemTimer) {
        [itemTimer invalidate];
        [itemTimer autorelease];
    }
    if (aTimer) itemTimer = [aTimer retain];
}

- (NSTimer *)itemTimer { return itemTimer; }



long ConvertTimeToSeconds(int hr, int min, BOOL flag)
{
    if (flag) { /* PM */
        if (hr >= 1 && hr < 12)
            hr += 12;
    } else {
        if (hr == 12)
            hr = 0;
    }
    return ((hr * hrInSecs) + (min * minInSecs));
}


BOOL ConvertSecondsToTime(long secs, int *hour, int *minute)
{
    int hr=0;
    BOOL pm=NO;

    if (secs) {
        hr = secs / hrInSecs;
        if (hr > 12) {
            *hour = (hr -= 12);
            pm = YES;
        } else {
            pm = NO;
            if (hr == 0)
                hr = 12;
            *hour = hr;
        }
        *minute = ((secs%hrInSecs) / minInSecs);
    }
    return pm;
}

@end
