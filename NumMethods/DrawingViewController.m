//
//  DrawingViewController.m
//  NumMethods
//
//  Created by Andrii Kulian on 12/2/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "DrawingViewController.h"

@interface DrawingViewController ()

@end

@implementation DrawingViewController {

    CGPoint lastPoint;
    NSMutableArray* points;
    NSMutableArray* rip_point_numbers;
    BOOL mouseSwiped;

    CGFloat red;
    CGFloat green;
    CGFloat blue;
    CGFloat brush;
    CGFloat rip_width;
    CGFloat opacity;
    
    int numberOfTouches;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    red = 0.0/255.0;
    green = 0.0/255.0;
    blue = 0.0/255.0;
    brush = 10.0;
    rip_width = 25.0;
    opacity = 1.0;
    
    points = [NSMutableArray new];
    rip_point_numbers = [NSMutableArray new];
    
    numberOfTouches = 0;
    
    self.navigationController.navigationBar.translucent = NO;
    if ([self respondsToSelector:@selector(edgesForExtendedLayout)]) {
        self.edgesForExtendedLayout = UIRectEdgeNone;   // iOS 7 specific
    }
    [self.ripButton setEnabled:NO];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    mouseSwiped = NO;
    UITouch *touch = [touches anyObject];
    lastPoint = [touch locationInView:self.view];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
    mouseSwiped = YES;
    UITouch *touch = [touches anyObject];
    CGPoint currentPoint = [touch locationInView:self.view];
    
    /*UIGraphicsBeginImageContext(self.view.frame.size);
    [self.tempDrawImage.image drawInRect:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    CGContextMoveToPoint(UIGraphicsGetCurrentContext(), lastPoint.x, lastPoint.y);
    CGContextAddLineToPoint(UIGraphicsGetCurrentContext(), currentPoint.x, currentPoint.y);
    CGContextSetLineCap(UIGraphicsGetCurrentContext(), kCGLineCapRound);
    CGContextSetLineWidth(UIGraphicsGetCurrentContext(), brush );
    CGContextSetRGBStrokeColor(UIGraphicsGetCurrentContext(), red, green, blue, 1.0);
    CGContextSetBlendMode(UIGraphicsGetCurrentContext(),kCGBlendModeNormal);
    
    CGContextStrokePath(UIGraphicsGetCurrentContext());
    self.tempDrawImage.image = UIGraphicsGetImageFromCurrentImageContext();
    [self.tempDrawImage setAlpha:opacity];
    UIGraphicsEndImageContext();*/
    
    lastPoint = currentPoint;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    
    if(!mouseSwiped) {
        [self addPoint];
    }
    
    /*UIGraphicsBeginImageContext(self.view.frame.size);
    [self.drawImageView.image drawInRect:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) blendMode:kCGBlendModeNormal alpha:1.0];
    [self.tempDrawImage.image drawInRect:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) blendMode:kCGBlendModeNormal alpha:opacity];
    self.drawImageView.image = UIGraphicsGetImageFromCurrentImageContext();
    self.tempDrawImage.image = nil;
    UIGraphicsEndImageContext();*/
}

-(void)addPoint {
    UIGraphicsBeginImageContext(self.view.frame.size);
    [self.tempDrawImage.image drawInRect:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    CGContextSetLineCap(UIGraphicsGetCurrentContext(), kCGLineCapRound);
    CGContextSetLineWidth(UIGraphicsGetCurrentContext(), brush);
    CGContextSetRGBStrokeColor(UIGraphicsGetCurrentContext(), red, green, blue, opacity);
    CGPoint prevPoint;
    if (points && [points count]) {
        prevPoint = [[points lastObject] CGPointValue];
    } else {
        prevPoint = lastPoint;
    }
    NSLog(@"%f %f %f %f\n", prevPoint.x, prevPoint.y, lastPoint.x, lastPoint.y);
    CGContextMoveToPoint(UIGraphicsGetCurrentContext(), prevPoint.x, prevPoint.y);
    CGContextAddLineToPoint(UIGraphicsGetCurrentContext(), lastPoint.x, lastPoint.y);
    CGContextStrokePath(UIGraphicsGetCurrentContext());
    CGContextFlush(UIGraphicsGetCurrentContext());
    self.tempDrawImage.image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    [points addObject:[NSValue valueWithCGPoint:lastPoint]];
    [self.ripButton setEnabled:YES];
}

-(void)addRipPoint {
    UIGraphicsBeginImageContext(self.view.frame.size);
    [self.tempDrawImage.image drawInRect:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    CGContextSetLineCap(UIGraphicsGetCurrentContext(), kCGLineCapRound);
    CGContextSetLineWidth(UIGraphicsGetCurrentContext(), rip_width);
    CGContextSetRGBStrokeColor(UIGraphicsGetCurrentContext(), 0, 0, 1, opacity);
    CGPoint prevPoint = lastPoint;
    NSLog(@"%f %f %f %f\n", prevPoint.x, prevPoint.y, lastPoint.x, lastPoint.y);
    CGContextMoveToPoint(UIGraphicsGetCurrentContext(), prevPoint.x, prevPoint.y);
    CGContextAddLineToPoint(UIGraphicsGetCurrentContext(), lastPoint.x, lastPoint.y);
    CGContextStrokePath(UIGraphicsGetCurrentContext());
    CGContextFlush(UIGraphicsGetCurrentContext());
    self.tempDrawImage.image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
}

-(void)normalizeFigure {
    if (!points || !points.count) {
        return;
    }
    
    // find leftmost, rightmost, top and bottom
    double leftmost = [[points objectAtIndex:0] CGPointValue].x;
    double rightmost = [[points objectAtIndex:0] CGPointValue].x;
    double upper = [[points objectAtIndex:0] CGPointValue].y;
    double bottom = [[points objectAtIndex:0] CGPointValue].y;
    
    CGPoint temp;
    for (int i = 1; i < points.count; i++) {
        temp = [[points objectAtIndex:i] CGPointValue];
        if (temp.x < leftmost) {
            leftmost = temp.x;
        } else if (temp.x > rightmost) {
            rightmost = temp.x;
        }
        
        if (temp.y > upper) {
            upper = temp.y;
        } else if (temp.y < bottom) {
            bottom = temp.y;
        }
    }
    
    // find width, height and center
    double width = rightmost - leftmost;
    double height = upper - bottom;
    CGPoint center = CGPointMake((leftmost+rightmost)/2, (upper+bottom)/2);
    
    // move points to use in algorithm
    for (int i = 0; i < points.count; i++) {
        CGPoint temp = [[points objectAtIndex:i] CGPointValue];
        // center point
        temp.x -= center.x;
        temp.y -= center.y;
        
        // normalize point
        temp.x /= width;
        temp.y /= height;
        
        NSLog(@"%f %f", temp.x, temp.y);

        [points replaceObjectAtIndex:i withObject:[NSValue valueWithCGPoint:temp]];
    }
}

-(IBAction)clear:(id)sender {
    if (points && points.count) {
        [points removeAllObjects];
    }
    if (rip_point_numbers && rip_point_numbers.count) {
        [rip_point_numbers removeAllObjects];
    }
    
    UIGraphicsBeginImageContext(self.tempDrawImage.frame.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSetFillColorWithColor(context, [[UIColor whiteColor] CGColor]);
    
    CGContextFillRect(context, CGRectMake(0.0f, 0.0f, self.tempDrawImage.frame.size.width, self.tempDrawImage.frame.size.height));
    CGContextStrokePath(context);
    
    self.tempDrawImage.image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    [self.ripButton setEnabled:NO];
}

-(IBAction)rip_point:(id)sender {
    if (!points || !points.count) {
        UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Інфо" message:@"Спочатку введіть точку" delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
        [alert show];
        return;
    }

    [self addRipPoint];
    [rip_point_numbers addObject:[NSNumber numberWithInt:[points count] - 1]];
    [self.ripButton setEnabled:NO];
}

-(IBAction)proceed:(id)sender {
    if (!points || points.count < 2) {
        UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Інфо" message:@"Для продовження намалюйте фігуру" delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
        [alert show];
        return;
    }

    [self normalizeFigure];

    if (self.delegate) {
        [self.delegate didDrawPoints:points withRipPointNumbers:rip_point_numbers inViewController:self];
    }
}

@end
