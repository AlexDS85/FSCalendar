//
//  MultipleSelectionViewController.m
//  FSCalendar
//
//  Created by dingwenchao on 9/9/15.
//  Copyright (c) 2015 wenchaoios. All rights reserved.
//

#import "MultipleSelectionViewController.h"

@implementation MultipleSelectionViewController

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.title = @"FSCalendar";
    }
    return self;
}

- (void)loadView
{
    UIView *view = [[UIView alloc] initWithFrame:[UIScreen mainScreen].bounds];
    view.backgroundColor = [UIColor groupTableViewBackgroundColor];
    self.view = view;
    
    CGFloat height = [[UIDevice currentDevice].model hasPrefix:@"iPad"] ? 450 : 300;
    FSCalendar *calendar = [[FSCalendar alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(self.navigationController.navigationBar.frame), view.bounds.size.width, height)];
    calendar.dataSource = self;
    calendar.delegate = self;
    calendar.backgroundColor = [UIColor whiteColor];
    calendar.allowsMultipleSelection = YES;
    calendar.appearance.cellShape = FSCalendarCellShapeRoundedRect;
    calendar.appearance.headerBackgroundColor = [UIColor greenColor];
    calendar.appearance.caseOptions = FSCalendarCaseOptionsWeekdayUsesSingleUpperCase;
    calendar.weekdayHeight = 50;
    calendar.firstWeekday = 2;
    calendar.weekdayBackgroundColor = [UIColor redColor];;
    calendar.weekDaysView.layer.borderColor = [UIColor brownColor].CGColor;
    calendar.weekDaysView.layer.borderWidth =1;
    calendar.appearance.allowInterruptSelections = YES;
    calendar.appearance.selectionPart = 0.7;
 //   [calendar selectDate:[NSDate date]];
//    [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:3600*24]];
//    [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:3600*24*2]];
   // [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:3600*24*3]];
//    [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:3600*24*4]];
//    [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:2*3600*24]];
    [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:11*3600*24]];
//    [calendar selectDate:[NSDate dateWithTimeIntervalSinceNow:7*3600*24]];
    
    [self.view addSubview:calendar];
    self.calendar = calendar;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
   // [_calendar selectDate:[_calendar dateByAddingDays:1 toDate:[NSDate date]]];
    
#if 0
    FSCalendarTestSelectDate
#endif
}

- (BOOL)calendar:(FSCalendar *)calendar shouldSelectDate:(NSDate *)date
{
 //   return NO;
//    BOOL shouldDedeselect = [_calendar dayOfDate:date] != 5;
//    if (!shouldDedeselect) {
//        [[[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"Forbidden date %@ to be selected",[calendar stringFromDate:date]] message:@"" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil] show];
//        return NO;
//    }
    return YES;
}

- (BOOL)calendar:(FSCalendar *)calendar shouldDeselectDate:(NSDate *)date
{
//    BOOL shouldDedeselect = [_calendar dayOfDate:date] != 7;
//    if (!shouldDedeselect) {
//        [[[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"Forbidden date %@ to be deselected",[calendar stringFromDate:date]] message:@"" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil] show];
//        return NO;
//    }
    return YES;
}

- (void)calendar:(FSCalendar *)calendar didSelectDate:(NSDate *)date
{
    NSMutableArray *selectedDates = [NSMutableArray arrayWithCapacity:calendar.selectedDates.count];
    [calendar.selectedDates enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [selectedDates addObject:[calendar stringFromDate:obj format:@"yyyy/MM/dd"]];
    }];
   // NSLog(@"selected dates is %@",selectedDates);
}

- (void)calendar:(FSCalendar *)calendar didDeselectDate:(NSDate *)date
{
    NSMutableArray *selectedDates = [NSMutableArray arrayWithCapacity:calendar.selectedDates.count];
    [calendar.selectedDates enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [selectedDates addObject:[calendar stringFromDate:obj format:@"yyyy/MM/dd"]];
    }];
  //  NSLog(@"selected dates is %@",selectedDates);
}

- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance selectionColorForDate:(NSDate *)date
{
    if ([_calendar dayOfDate:date] % 2 == 0) {
        return appearance.selectionColor;
    }
    
    if ([date compare:[NSDate date]]==NSOrderedSame) {
        return [UIColor yellowColor];

    }else
        return [UIColor purpleColor];
}

- (UIColor *)calendar:(FSCalendar *)calendar appearance:(FSCalendarAppearance *)appearance borderDefaultColorForDate:(NSDate *)date
{
//    if ([@[@17,@18,@19] containsObject:@([calendar dayOfDate:date])]) {
//        return [UIColor magentaColor];
//    }
    return appearance.borderDefaultColor;
}

@end
