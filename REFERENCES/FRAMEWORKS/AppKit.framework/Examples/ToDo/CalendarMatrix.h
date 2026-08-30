/* CalendarMatrix.h created by tjdono on Mon 30-Oct-1995 */

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface CalendarMatrix : NSMatrix
{
    id	monthName;
    id  leftButton;
    id  rightButton;
    
    NSCalendarDate *selectedDay;
    short startOffset;
}

- (void)choseDay:sender;
- (void)monthChanged:sender;
- (void)refreshCalendar;

- (id)initWithFrame:(NSRect)frameRect;
- (void)dealloc;

- (void)setSelectedDay:(NSCalendarDate *)newDay;
- (NSCalendarDate *)selectedDay;
@end

@interface NSObject(CalendarMatrixDelegate)
 - (void)calendarMatrix:(CalendarMatrix *)obj didChangeToDate:(NSDate *)date;
 - (void)calendarMatrix:(CalendarMatrix *)obj didChangeToMonth:(int)mo year:(int)yr;
@end
