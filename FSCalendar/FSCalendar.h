//
//  FSCalendar.h
//  FSCalendar
//
//  Created by Wenchao Ding on 29/1/15.
//  Copyright © 2016 Wenchao Ding. All rights reserved.
// 
//  https://github.com/WenchaoD
//

#import <UIKit/UIKit.h>
#import "FSCalendarAppearance.h"
#import "FSCalendarConstance.h"

//! Project version number for FSCalendar.
FOUNDATION_EXPORT double FSCalendarVersionNumber;

//! Project version string for FSCalendar.
FOUNDATION_EXPORT const unsigned char FSCalendarVersionString[];

typedef NS_ENUM(NSUInteger, FSCalendarScope) {
    FSCalendarScopeMonth,
    FSCalendarScopeWeek
};

typedef NS_ENUM(NSUInteger, FSCalendarScrollDirection) {
    FSCalendarScrollDirectionVertical,
    FSCalendarScrollDirectionHorizontal
};

typedef NS_ENUM(NSUInteger, FSCalendarUnit) {
    FSCalendarUnitMonth = NSCalendarUnitMonth,
    FSCalendarUnitWeekOfYear = NSCalendarUnitWeekOfYear,
    FSCalendarUnitDay = NSCalendarUnitDay
};

@class FSCalendar;

@protocol FSCalendarDataSource <NSObject>

@optional
- (NSString *)calendar:(FSCalendar *)calendar subtitleForDate:(NSDate *)date;
- (UIImage *)calendar:(FSCalendar *)calendar imageForDate:(NSDate *)date;
- (NSDate *)minimumDateForCalendar:(FSCalendar *)calendar;
- (NSDate *)maximumDateForCalendar:(FSCalendar *)calendar;
- (NSInteger)calendar:(FSCalendar *)calendar numberOfEventsForDate:(NSDate *)date;

- (BOOL)calendar:(FSCalendar *)calendar hasEventForDate:(NSDate *)date FSCalendarDeprecated(-calendar:numberOfEventsForDate:);

@end

@protocol FSCalendarDelegate <NSObject>

@optional
- (BOOL)calendar:(FSCalendar *)calendar shouldSelectDate:(NSDate *)date;
- (void)calendar:(FSCalendar *)calendar didSelectDate:(NSDate *)date;
- (BOOL)calendar:(FSCalendar *)calendar shouldDeselectDate:(NSDate *)date;
- (void)calendar:(FSCalendar *)calendar didDeselectDate:(NSDate *)date;
- (void)calendar:(FSCalendar *)calendar boundingRectWillChange:(CGRect)bounds animated:(BOOL)animated;
- (void)calendarCurrentPageDidChange:(FSCalendar *)calendar;

- (void)calendarCurrentScopeWillChange:(FSCalendar *)calendar animated:(BOOL)animated FSCalendarDeprecated(-calendar:boundingRectWillChange:animated:);
- (void)calendarCurrentMonthDidChange:(FSCalendar *)calendar FSCalendarDeprecated(-calendarCurrentPageDidChange:);

@end

@protocol FSCalendarDelegateAppearance <NSObject>

@optional
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance selectionColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance titleDefaultColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance titleSelectionColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance subtitleDefaultColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance subtitleSelectionColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance eventColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance borderDefaultColorForDate:(NSDate *)date;
- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance borderSelectionColorForDate:(NSDate *)date;
- (FSCalendarCellShape)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance cellShapeForDate:(NSDate *)date;


- (FSCalendarCellStyle)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance cellStyleForDate:(NSDate *)date FSCalendarDeprecated(-calendar:appearance:cellShapeForDate:);

@end

#pragma mark - Primary

IB_DESIGNABLE
@interface FSCalendar : UIView

@property (weak, nonatomic) IBOutlet id<FSCalendarDelegate> delegate;
@property (weak, nonatomic) IBOutlet id<FSCalendarDataSource> dataSource;

@property (strong, nonatomic) NSDate *today;
@property (strong, nonatomic) NSDate *currentPage;
@property (strong, nonatomic) NSLocale *locale;
@property (strong, nonatomic) NSString *identifier;
@property (assign, nonatomic) FSCalendarScrollDirection scrollDirection;
@property (assign, nonatomic) FSCalendarScope scope;
@property (assign, nonatomic) IBInspectable NSUInteger firstWeekday;
@property (assign, nonatomic) IBInspectable CGFloat headerHeight;
@property (assign, nonatomic) IBInspectable CGFloat weekdayHeight;
@property (assign, nonatomic) IBInspectable BOOL allowsSelection;
@property (assign, nonatomic) IBInspectable BOOL allowsMultipleSelection;
@property (assign, nonatomic) IBInspectable BOOL pagingEnabled;
@property (assign, nonatomic) IBInspectable BOOL scrollEnabled;
@property (assign, nonatomic) IBInspectable BOOL focusOnSingleSelectedDate;
@property (assign, nonatomic) IBInspectable BOOL showsPlaceholders;

@property (strong, nonatomic) UIColor *weekdayBackgroundColor;
@property (strong, nonatomic) UIView *weekDaysView;

@property (readonly, nonatomic) FSCalendarAppearance *appearance;
@property (readonly, nonatomic) NSDate *minimumDate;
@property (readonly, nonatomic) NSDate *maximumDate;

@property (readonly, nonatomic) NSDate *selectedDate;
@property (readonly, nonatomic) NSArray *selectedDates;
@property (strong, nonatomic) NSMutableIndexSet        *selectedRanges;

- (NSInteger)lastWeekDay;
- (void)reloadData;
- (CGSize)sizeThatFits:(CGSize)size;
- (void)setMinimumDaysInFirstWeek:(NSUInteger)minimumDays;
- (NSUInteger)minimumDaysInFirstWeek;
- (void)setScope:(FSCalendarScope)scope animated:(BOOL)animated;

- (void)selectDate:(NSDate *)date;
- (void)selectDate:(NSDate *)date scrollToDate:(BOOL)scrollToDate;
- (void)deselectDate:(NSDate *)date;

- (void)setCurrentPage:(NSDate *)currentPage animated:(BOOL)animated;

@end


#pragma mark - DateTools

@interface FSCalendar (DateTools)

- (NSInteger)yearOfDate:(NSDate *)date;
- (NSInteger)monthOfDate:(NSDate *)date;
- (NSInteger)dayOfDate:(NSDate *)date;
- (NSInteger)weekdayOfDate:(NSDate *)date;
- (NSInteger)weekdayOfDateWithFirstWeekDayCorrection:(NSDate *)date;
- (NSInteger)weekOfDate:(NSDate *)date;
- (NSInteger)hourOfDate:(NSDate *)date;
- (NSInteger)miniuteOfDate:(NSDate *)date;
- (NSInteger)secondOfDate:(NSDate *)date;
- (NSInteger)numberOfRowsInMonth:(NSDate *)month;

- (NSDate *)dateByIgnoringTimeComponentsOfDate:(NSDate *)date;
- (NSDate *)beginingOfMonthOfDate:(NSDate *)date;
- (NSDate *)endOfMonthOfDate:(NSDate *)date;
- (NSDate *)beginingOfWeekOfDate:(NSDate *)date;
- (NSDate *)middleOfWeekFromDate:(NSDate *)date;
- (NSDate *)tomorrowOfDate:(NSDate *)date;
- (NSDate *)yesterdayOfDate:(NSDate *)date;
- (NSInteger)numberOfDatesInMonthOfDate:(NSDate *)date;

- (NSDate *)dateFromString:(NSString *)string format:(NSString *)format;
- (NSDate *)dateWithYear:(NSInteger)year month:(NSInteger)month day:(NSInteger)day;

- (NSDate *)dateByAddingYears:(NSInteger)years toDate:(NSDate *)date;
- (NSDate *)dateBySubstractingYears:(NSInteger)years fromDate:(NSDate *)date;
- (NSDate *)dateByAddingMonths:(NSInteger)months toDate:(NSDate *)date;
- (NSDate *)dateBySubstractingMonths:(NSInteger)months fromDate:(NSDate *)date;
- (NSDate *)dateByAddingWeeks:(NSInteger)weeks toDate:(NSDate *)date;
- (NSDate *)dateBySubstractingWeeks:(NSInteger)weeks fromDate:(NSDate *)date;
- (NSDate *)dateByAddingDays:(NSInteger)days toDate:(NSDate *)date;
- (NSDate *)dateBySubstractingDays:(NSInteger)days fromDate:(NSDate *)date;

- (NSInteger)yearsFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;
- (NSInteger)monthsFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;
- (NSInteger)daysFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;
- (NSInteger)weeksFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;

- (BOOL)isDate:(NSDate *)date1 equalToDate:(NSDate *)date2 toCalendarUnit:(FSCalendarUnit)unit;
- (BOOL)isDateInToday:(NSDate *)date;

- (NSString *)stringFromDate:(NSDate *)date format:(NSString *)format;
- (NSString *)stringFromDate:(NSDate *)date;

@end


#pragma mark - Deprecate

@interface FSCalendar (Deprecated)
@property (strong, nonatomic) NSDate *currentMonth FSCalendarDeprecated('currentPage');
@property (assign, nonatomic) FSCalendarFlow flow FSCalendarDeprecated('scrollDirection');
- (void)setSelectedDate:(NSDate *)selectedDate FSCalendarDeprecated(-selectDate:);
- (void)setSelectedDate:(NSDate *)selectedDate animate:(BOOL)animate FSCalendarDeprecated(-selectDate:scrollToDate:);
- (BOOL)date:(NSDate *)date sharesSameMonthWithDate:(NSDate *)anotherDate FSCalendarDeprecated(-isDate:equalToDate:toCalendarUnit);
- (BOOL)date:(NSDate *)date sharesSameWeekWithDate:(NSDate *)anotherDate FSCalendarDeprecated(-isDate:equalToDate:toCalendarUnit);
- (BOOL)date:(NSDate *)date sharesSameDayWithDate:(NSDate *)anotherDate FSCalendarDeprecated(-isDate:equalToDate:toCalendarUnit);
@end

