/* CalendarMatrix.m created by tjdono on Mon 30-Oct-1995 */

#import "ToDoDoc.h"
#import "ToDoController.h"
#import "ToDoItem.h"
#import "CalendarMatrix.h"

static short MonthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#define isLeap(year) (((((year) % 4) == 0 && (((year) % 100) != 0)) || ((year) % 400) == 0))

@implementation CalendarMatrix

- (void)refreshCalendar
{
    NSCalendarDate *firstOfMonth, *selDate = [self selectedDay], *now = [NSCalendarDate date];
    int i, j, currentMonth = [selDate monthOfYear];
    unsigned int currentYear = [selDate yearOfCommonEra];
    short daysInMonth;
    id cell;
 
    firstOfMonth = [NSCalendarDate dateWithYear:currentYear
                                          month:currentMonth
                                            day:1 hour:0 minute:0 second:0
                                       timeZone:[NSTimeZone localTimeZone]];
    [monthName setStringValue:[firstOfMonth descriptionWithCalendarFormat:@"%B %Y"]];
    daysInMonth = MonthDays[currentMonth-1]+1;
    /* correct Feb for leap year */
    if ((currentMonth == 2) && (isLeap(currentYear))) daysInMonth++;
    startOffset = [firstOfMonth dayOfWeek];

    /* "remove" leading cells */
    for (i=0; i<startOffset; i++) {
        cell = [self cellWithTag:i];
        [cell setBordered:NO];
        [cell setEnabled:NO];
        [cell setTitle:@""];
        [cell setCellAttribute:NSCellHighlighted to:NO];
    }
    for (j=1; j < daysInMonth; i++, j++) {
        cell = [self cellWithTag:i];
        [cell setBordered:YES];
        [cell setEnabled:YES];
        [cell setFont:[NSFont systemFontOfSize:12]];
        [cell setTitle:[NSString stringWithFormat:@"%d", j]];
        [cell setCellAttribute:NSCellHighlighted to:NO];
    }
    for (;i<42;i++) {
        cell = [self cellWithTag:i];
        [cell setBordered:NO];
        [cell setEnabled:NO];
        [cell setTitle:@""];
        [cell setCellAttribute:NSCellHighlighted to:NO];
    }
       if ((currentYear == [now yearOfCommonEra])
           && (currentMonth == [now monthOfYear])) {
        [[self cellWithTag:([now dayOfMonth]+startOffset)-1]
		setCellAttribute:NSCellHighlighted to:YES];
        [[self cellWithTag:([now dayOfMonth]+startOffset)-1]
		setHighlightsBy:NSMomentaryChangeButton];
       }
}
   
- (void)monthChanged:sender
{
    NSCalendarDate *thisDate = [self selectedDay];
    int currentYear = [thisDate yearOfCommonEra];
    unsigned int currentMonth = [thisDate monthOfYear];
    
    if (sender == rightButton) {
        if (currentMonth == 12) {
            currentMonth = 1;
            currentYear++;
        } else {
            currentMonth++;
        }
    } else {
        if (currentMonth == 1) {
            currentMonth = 12;
            currentYear--;
        } else {
            currentMonth--;
        }
    }
    [self setSelectedDay: [NSCalendarDate dateWithYear:currentYear
                                                  month:currentMonth
                           day:1 hour:0 minute:0 second:0
                                               timeZone:[NSTimeZone localTimeZone]]];
    [self refreshCalendar];
    [[self delegate] calendarMatrix:self didChangeToMonth:currentMonth year:currentYear];
}

- (void)awakeFromNib
{
    [monthName setAlignment:NSCenterTextAlignment];
    [self setTarget:self];
    [self setAction:@selector(choseDay:)];
    [self setAutosizesCells:YES];
    [self refreshCalendar];
}

- (id)initWithFrame:(NSRect)frameRect
{
    int i, j, cnt=0;
    id cell = [[NSButtonCell alloc] initTextCell:@""];
    NSCalendarDate *now = [NSCalendarDate date];

    [super initWithFrame:frameRect
                    mode:NSRadioModeMatrix
               prototype:cell
            numberOfRows:6
         numberOfColumns:7];
    // set cell tags
    for (i=0; i<6; i++) {
        for (j=0; j<7; j++) {
            [[self cellAtRow:i column:j] setTag:cnt++];
        }
    }
    [cell release];
    selectedDay = [[NSCalendarDate dateWithYear:[now yearOfCommonEra]
                                          month:[now monthOfYear]
                                            day:[now dayOfMonth]
                                           hour:0 minute:0 second:0
                                       timeZone:[NSTimeZone localTimeZone]] copy];

    return self;
}


- (void)dealloc
{
    [selectedDay release];
    [super dealloc];
}


- (void)choseDay:sender
{
    NSCalendarDate *selDate, *thisDate = [self selectedDay];
    unsigned int selDay = [[self selectedCell] tag]-startOffset+1;

    // compose date 
    selDate = [NSCalendarDate dateWithYear:[thisDate yearOfCommonEra]
                                     month:[thisDate monthOfYear]
         day:selDay hour:0 minute:0 second:0
                                  timeZone:[NSTimeZone localTimeZone]];
    [[self cellWithTag:[thisDate dayOfMonth]+startOffset-1] setFont:[NSFont systemFontOfSize:12]];
    [[self cellWithTag:selDay+startOffset-1] setFont:[NSFont boldSystemFontOfSize:12]];

    [self setSelectedDay:selDate];
    [[self delegate] calendarMatrix:self didChangeToDate:selDate];
}

- (void)setSelectedDay:(NSCalendarDate *)newDay
{
    if (selectedDay)
        [selectedDay autorelease];
    if (newDay) {
        selectedDay = [newDay copy];
    } else {
        selectedDay = nil;
    }      
}

- (NSCalendarDate *)selectedDay { return selectedDay; }

@end
