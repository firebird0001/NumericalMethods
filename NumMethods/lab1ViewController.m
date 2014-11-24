//
//  lab1ViewController.m
//  NumMethods
//
//  Created by Andrii Kulian on 9/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "lab1ViewController.h"
#import "lab1.h"
#import "DrawingTools.h"
#import "MBProgressHUD.h"
#import "OptionsViewController.h"

@implementation lab1ViewController {
    figure* inputFigure;
    point** points_of_interest;
    point** collocation_points;
    point** normal_vectors;
    double** gamma;
    
    int* separation_points_numbers;
    int* initial_separation_points_numbers;
    int num_p;
    double*** j_arr;
    double** delta_t;
    point*** trace;

    double min;
    double max;
    double step;
    
    int finishedNumber;
    int finishedImagesNumber;
    int numberOfThreads;
    
    NSMutableArray* colors;
    NSMutableArray* images;
    double* tresholds;
    
    BOOL processingNow;
}
@synthesize statusLabel, pointNumberTextField;

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
    
    UIBarButtonItem* newDrawing = [[UIBarButtonItem alloc] initWithTitle:@"Нова фігура" style:UIBarButtonItemStyleBordered target:self action:@selector(newDrawing)];
    UIBarButtonItem* optionsEdit = [[UIBarButtonItem alloc] initWithTitle:@"Параметри" style:UIBarButtonItemStyleBordered target:self action:@selector(showOptions)];
    
    self.navigationItem.leftBarButtonItem = newDrawing;
    self.navigationItem.rightBarButtonItem = optionsEdit;
    
    if (!self.options) {
        self.options = [[Options alloc] initDefault];
    }
    
    if (!self.points) {
        [self newDrawing];
    }
    
    switch (self.options.drawing_mode) {
        case MODE_PHI:
            [self.modeControl setSelectedSegmentIndex:0];
            break;
        case MODE_PSI:
            [self.modeControl setSelectedSegmentIndex:1];
            break;
        case MODE_CP:
            [self.modeControl setSelectedSegmentIndex:2];
            break;
    }
    [self.modeControl addTarget:self action:@selector(modeChange:) forControlEvents:UIControlEventValueChanged];
    
    self.navigationController.navigationBar.translucent = NO;
    if ([self respondsToSelector:@selector(edgesForExtendedLayout)])
        self.edgesForExtendedLayout = UIRectEdgeNone;   // iOS 7 specific
    
    //Try setting this to UIPopoverController to use the iPad popover. The API is exactly the same!
	popoverClass = [WEPopoverController class];
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
	
	currentPopoverCellIndex = -1;

    processingNow = NO;
}

-(void)newDrawing {
    if (processingNow) {
        return;
    }
    DrawingViewController* drawingViewController = [[DrawingViewController alloc] initWithNibName:@"DrawingViewController" bundle:nil];
    drawingViewController.delegate = self;
    [self presentViewController:drawingViewController animated:YES completion:nil];
}

-(void)showOptions {
    if (processingNow) {
        return;
    }
    OptionsViewController* optionsViewController = [[OptionsViewController alloc] initWithNibName:@"OptionsViewController" bundle:nil];
    optionsViewController.delegate = self;
    optionsViewController.options = self.options;
    [self presentViewController:[[UINavigationController alloc] initWithRootViewController:optionsViewController] animated:YES completion:nil];
}

-(void)modeChange:(id)sender {
    if (processingNow) {
        return;
    }
    
    UISegmentedControl *segmentedControl = (UISegmentedControl *) sender;
    switch (segmentedControl.selectedSegmentIndex) {
        case 0: // Phi
            self.options.drawing_mode = MODE_PHI;
            break;
        case 1: // Psi
            self.options.drawing_mode = MODE_PSI;
            break;
        case 2: // Cp
            self.options.drawing_mode = MODE_CP;
            break;
    }
    [self redraw];
}

#pragma mark process drawing
-(void)savePoints:(NSArray*)points {
    if (inputFigure) {
        if (inputFigure->points) {
            free(inputFigure->points);
            inputFigure->points = NULL;
        }
        free(inputFigure);
    }
    inputFigure = malloc(sizeof(figure));
    if (!inputFigure) {
        printf("Low memory\n");
        return;
    }
    inputFigure->points = malloc(sizeof(point)*points.count);
    if (!inputFigure->points) {
        printf("Low memory\n");
        return;
    }
    
    for (int i = 0; i < points.count; i++) {
        inputFigure->points[i].x = [[points objectAtIndex:i] CGPointValue].x;
        inputFigure->points[i].y = [[points objectAtIndex:i] CGPointValue].y;
    }
    inputFigure->point_number = points.count;
}

-(void)saveRipPointNumbers:(NSArray*)ripPointNumbers {
    if (initial_separation_points_numbers) {
        free(initial_separation_points_numbers);
        initial_separation_points_numbers = NULL;
    }
    
    num_p = ripPointNumbers.count;
    initial_separation_points_numbers = (int*)(malloc(sizeof(int) * num_p));
    for (int i = 0; i < num_p; i++) {
        initial_separation_points_numbers[i] = [[ripPointNumbers objectAtIndex:i] integerValue];
    }
}

double f(double x, double radius) {
    return (double)sqrt(radius * radius - x * x);
}

-(void)processPoints {
    if (!inputFigure) {
        [self complain:@"Фігура не введена"];
        return;
    }
    
    processingNow = YES;
    [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    
    // TODO free all array
    if (points_of_interest && *points_of_interest) {
        free(*points_of_interest);
        *points_of_interest = NULL;
        free(points_of_interest);
        points_of_interest = NULL;
    }
    // TODO free all array
    if (collocation_points && *collocation_points) {
        free(*collocation_points);
        *collocation_points = NULL;
        free(collocation_points);
        collocation_points = NULL;
    }
    // TODO free all array
    if (normal_vectors && *normal_vectors) {
        free(*normal_vectors);
        *normal_vectors = NULL;
        free(normal_vectors);
        normal_vectors = NULL;
    }

    points_of_interest = malloc(sizeof(point*));
    collocation_points = malloc(sizeof(point*));
    normal_vectors = malloc(sizeof(point*));

    if (self.options.isTest) {
        self.options.number_of_points = 19;
    }
    
    get_points_from_simple_figure(inputFigure, self.options.number_of_points, points_of_interest, collocation_points, normal_vectors, self.options.isTest);
    
    // now separation points are only two points
    // TODO free all array
    if (separation_points_numbers) {
        free(separation_points_numbers);
        separation_points_numbers = NULL;
    }
    
    if (!self.options.isTest) {
        separation_points_numbers = (int*)malloc(sizeof(int)*num_p);
        
        for (int i = 0; i < num_p; i++) {
            for (int j = 0; j < self.options.number_of_points; j++) {
                if (dist(&(inputFigure->points[initial_separation_points_numbers[i]]), *points_of_interest + j) < 0.0000001) {
                    separation_points_numbers[i] = j;
                    printf("separation point numer : %d\n", j);
                    break;
                }
            }
        }
    } else {
        num_p = 2;
        separation_points_numbers = (int*)malloc(sizeof(int)*num_p);

        separation_points_numbers[0] = 0;
        separation_points_numbers[1] = self.options.number_of_points - 1;
    }
    
    if (self.options.delta < 0) {
        self.options.delta = 0.02;
    }
    
    if (!points_of_interest || !collocation_points || !normal_vectors) {
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        [self complain:@"Помилка розбиття фігури"];
        processingNow = NO;
        return;
    }

    [self redraw];
}

-(void)redraw {
    processingNow = YES;
    [MBProgressHUD hideHUDForView:self.view animated:NO];
    [MBProgressHUD showHUDAddedTo:self.view animated:NO];
    
    // TODO set time correctly
    // TODO cleanup all array
    if (j_arr) {
        free(j_arr);
        j_arr = NULL;
    }
    j_arr = (double***)malloc(sizeof(double**));
    
    // TODO cleanup all array
    if (trace) {
        free(trace);
        trace = NULL;
    }
    trace = (point***)malloc(sizeof(point**));

    // TODO free all array
    if (gamma) {
        free(gamma);
        gamma = NULL;
    }
    
    // TODO free all array
    if (delta_t) {
        free(delta_t);
        delta_t = NULL;
    }
    delta_t = (double**)malloc(sizeof(double*));

    gamma = find_Gamma_2(*collocation_points, *points_of_interest, *normal_vectors, separation_points_numbers, self.options.time, num_p, j_arr, trace, self.options.number_of_points, degreeToRad(self.options.alpha), self.options.gamma_0, self.options.delta, delta_t);
    /*for (int i = 0; i <= self.options.time - 1; i++) {
        printf("delta2 %d: %f\n", i, (*delta_t)[i]);
    }*/

    if (!gamma) {
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        [self complain:@"Помилка обчислення гамма"];
        processingNow = NO;
        return;
    }

    float width = self.imageView.frame.size.width*2;
    float height = self.imageView.frame.size.height*2;
    self.options.real_height = self.options.real_width * height / width;

    step = self.options.real_width/width;
    
    /*UIImage* phiImage = [DrawingTools createImageWithSize:CGSizeMake(width, height) andBackgroundColor:[UIColor blackColor]];
    
    point* screenPoints = malloc(sizeof(point)*inputFigure->point_number);
    point* startPoint1 = malloc(sizeof(point));
    startPoint1->x = -self.options.real_width/2;
    startPoint1->y = -self.options.real_height/2;
    for (int i = 0; i < inputFigure->point_number; i++) {
        screenPoints[i].x = (inputFigure->points[i].x - startPoint1->x)/step;
        screenPoints[i].y = (inputFigure->points[i].y - startPoint1->y)/step;
        //printf("screenpoint %f %f\n", inputFigure->points[i].x, inputFigure->points[i].y);
    }
    
    UIImage* resultImage = [DrawingTools drawConnectedPoints:screenPoints number:inputFigure->point_number withWidth:3. andColor:[UIColor yellowColor] onImage:phiImage];
    phiImage = nil;
    free(screenPoints);
    
    point* screenPoints2 = malloc(sizeof(point)*current_time);
    UIImage* fullImage = resultImage;
    for (int j = 0; j < num_p; j++) {
        for (int i = 0; i < current_time; i++) {
            screenPoints2[i].x = ((*trace)[j][i].x - startPoint1->x)/step;
            screenPoints2[i].y = ((*trace)[j][i].y - startPoint1->y)/step;
            NSLog(@"Point x = %f, y = %f", (*trace)[j][i].x, (*trace)[j][i].y);
            //printf("screenpoint %f %f\n", inputFigure->points[i].x, inputFigure->points[i].y);
        }
        fullImage = [DrawingTools drawConnectedPoints:screenPoints2 number:current_time withWidth:3. andColor:[UIColor redColor] onImage:fullImage];
    }
    free(startPoint1);
    free(screenPoints2);
    
    if (self.imageScrollView) {
        [self.imageScrollView removeFromSuperview];
        self.imageScrollView = nil;
    }
    self.imageScrollView = [[KFImageZoomView alloc] initWithImage:fullImage atLocation:CGPointMake(0, 0)];
    self.imageScrollView.frame = self.imageView.frame;
    [self.view addSubview:self.imageScrollView];
    
    if (self.axisView) {
        [self.axisView removeFromSuperview];
        self.axisView = nil;
    }
    self.axisView = [[PlotView alloc] initWithFrame:self.imageScrollView.frame];
    [self.axisView setBackgroundColor:[UIColor clearColor]];
    [self.axisView setUserInteractionEnabled:NO];
    [self.view addSubview:self.axisView];
    
    [MBProgressHUD hideHUDForView:self.view animated:YES];
    
    self.imageScrollView.delegate = self;
    [self.imageScrollView zoomToRect:CGRectMake(0, 0, fullImage.size.width, fullImage.size.height) animated:YES];
*/
    // schedule multithreaded calculation
    numberOfThreads = 2;
    finishedNumber = 0;
    finishedImagesNumber = 0;

    colors = [[NSMutableArray alloc] initWithCapacity:self.options.number_of_colors];
    
    if (tresholds) {
        free(tresholds);
        tresholds = NULL;
    }
    
    tresholds = malloc(sizeof(double)*(self.options.number_of_colors));
    if (!tresholds) {
        // failure
        processingNow = NO;
        return;
    }

    min = MAXFLOAT;
    max = -MAXFLOAT;

    if (images) {
        [images removeAllObjects];
    } else {
        images = [[NSMutableArray alloc] init];
    }
    [images addObject:[NSNull null]];
    [images addObject:[NSNull null]];

    point* startPoint1 = malloc(sizeof(point));
    startPoint1->x = -self.options.real_width/2;
    startPoint1->y = -self.options.real_height/2;
    [self startCalculationThreadWithStartPoint:startPoint1 andSize:CGSizeMake(width, height/2) andNumber:0];

    point* startPoint2 = malloc(sizeof(point));
    startPoint2->x = -self.options.real_width/2;
    startPoint2->y = 0;
    [self startCalculationThreadWithStartPoint:startPoint2 andSize:CGSizeMake(width, height/2) andNumber:1];
}

-(void)startCalculationThreadWithStartPoint:(point*)startPoint andSize:(CGSize)size andNumber:(int)currentNumber{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^(void) {
        double** values;
        double* tempMin = malloc(sizeof(double));
        double* tempMax = malloc(sizeof(double));
        *tempMin = MAXFLOAT;
        *tempMax = -MAXFLOAT;

        switch (self.options.drawing_mode) {
            case MODE_PHI:
                if (self.options.dipol_presentation) {
                    values = phi_dipol_for_rect_2(startPoint, step, size.width, size.height, points_of_interest, *j_arr, collocation_points, gamma[self.options.time-1], self.options.number_of_points, degreeToRad(self.options.alpha), tempMin, tempMax, *trace, self.options.time, num_p);
                } else {
                    values = phi_for_rect_2(startPoint, step, size.width, size.height, points_of_interest, gamma[self.options.time-1], self.options.number_of_points, degreeToRad(self.options.alpha), tempMin, tempMax, trace, j_arr, self.options.time, num_p);
                }
                break;
            case MODE_PSI:
                values = ksi_for_rect_2(startPoint, step, size.width, size.height, points_of_interest, *trace, gamma[self.options.time-1], self.options.number_of_points, degreeToRad(self.options.alpha), self.options.delta, tempMin, tempMax, j_arr, self.options.time, num_p);
                break;
            case MODE_CP:
                values = Cp_for_rect_2(startPoint, step, size.width, size.height, points_of_interest, gamma[self.options.time-1], self.options.number_of_points, degreeToRad(self.options.alpha), tempMin, tempMax, self.options.delta, j_arr, gamma, self.options.time, *trace, num_p, *delta_t, collocation_points, separation_points_numbers, self.options.value_window_size);
                break;
        }

        if (!values || !*values) {
            [MBProgressHUD hideHUDForView:self.view animated:YES];
            [self complain:@"Помилка обчислення"];
            processingNow = NO;
            return;
        }

        if (*tempMin < min) {
            min = *tempMin;
        }
        if (*tempMax > max) {
            max = *tempMax;
        }

        NSLog(@"Calculating colors");
        
        if (finishedNumber == numberOfThreads - 1) {
            // last thread to finish will calculate colors
            [colors removeAllObjects];
            
            //printf("min: %f\n", min);
            //printf("max: %f\n", max);
            //min = -2;
            //max = 2;
            
            double colorStep = (max - min) / self.options.number_of_colors;
            for (int i = 0; i < self.options.number_of_colors; i++) {
                tresholds[i] = min+colorStep*(i+1);
                //printf("thresholds %f\n", tresholds[i]);
            }
            
            for (int i = 0; i < self.options.number_of_colors; i++) {
                [colors addObject:[DrawingTools colorForValue:tresholds[i] withBottomThreshold:min andTopThreshold:max]];
            }
            finishedNumber++;
        } else {
            finishedNumber++;
            printf("waiting\n");
            while (finishedNumber < numberOfThreads) {
                // wait
                //printf("waiting\n");
            }
        }
        
        free(tempMin);
        free(tempMax);
        
        printf("calculating colors\n");
        int** colorNumbers = [self calculateColorsForValues:values size:size];
        if (!colorNumbers || !*colorNumbers) {
            [MBProgressHUD hideHUDForView:self.view animated:YES];
            [self complain:@"Помилка обчислення кольорів"];
            processingNow = NO;
            return;
        }
        
        for (int i = 0; i < size.height; i++) {
            free(values[i]);
        }
        free(values);
        
        NSLog(@"Loading image");
        
        UIImage* phiImage = [DrawingTools createImageWithSize:size andColorNumbers:colorNumbers andColors:colors];
        if (!phiImage) {
            [MBProgressHUD hideHUDForView:self.view animated:YES];
            [self complain:@"Помилка створення графіку"];
            processingNow = NO;
            return;
        }
        for (int i = 0; i < size.height; i++) {
            free(colorNumbers[i]);
        }
        free(colorNumbers);

        point* screenPoints = malloc(sizeof(point)*inputFigure->point_number);
        for (int i = 0; i < inputFigure->point_number; i++) {
            screenPoints[i].x = (inputFigure->points[i].x - startPoint->x)/step;
            screenPoints[i].y = (inputFigure->points[i].y - startPoint->y)/step;
            //printf("screenpoint %f %f\n", inputFigure->points[i].x, inputFigure->points[i].y);
        }

        UIImage* resultImage = [DrawingTools drawConnectedPoints:screenPoints number:inputFigure->point_number withWidth:3. andColor:[UIColor yellowColor] onImage:phiImage];
        phiImage = nil;
        free(screenPoints);
        
        point* screenPoints2 = malloc(sizeof(point) * (self.options.time + 1));
        UIImage* traceImage = resultImage;
        for (int j = 0; j < num_p; j++) {
            for (int i = 0; i < self.options.time; i++) {
                screenPoints2[i].x = ((*trace)[j][i].x - startPoint->x)/step;
                screenPoints2[i].y = ((*trace)[j][i].y - startPoint->y)/step;
                //NSLog(@"Point x = %f, y = %f", (*trace)[j][i].x, (*trace)[j][i].y);
                //printf("screenpoint %f %f\n", inputFigure->points[i].x, inputFigure->points[i].y);
            }
            screenPoints2[self.options.time].x = ((*points_of_interest + separation_points_numbers[j])->x - startPoint->x)/step;
            screenPoints2[self.options.time].y = ((*points_of_interest + separation_points_numbers[j])->y - startPoint->y)/step;
            traceImage = [DrawingTools drawConnectedPoints:screenPoints2 number:self.options.time+1 withWidth:3. andColor:[UIColor redColor] onImage:traceImage];
        }
        resultImage = nil;
        free(startPoint);
        free(screenPoints2);

        
        [images replaceObjectAtIndex:currentNumber withObject:traceImage];
        
        if (++finishedImagesNumber == numberOfThreads) {
            dispatch_async(dispatch_get_main_queue(), ^(void) {
                UIImage* fullImage = [DrawingTools combineImages:images];
                
                if (self.options.show_V) {
                    int resultNum = 0;
                    point* startPoint1 = malloc(sizeof(point));
                    startPoint1->x = -self.options.real_width/2;
                    startPoint1->y = -self.options.real_height/2;
                    vect* v_vectors = V_for_rect_2(startPoint1, step, fullImage.size.width, fullImage.size.height, self.options.v_window_size, points_of_interest, gamma[self.options.time-1], self.options.number_of_points, degreeToRad(self.options.alpha), &resultNum, self.options.delta, trace, j_arr, self.options.time, num_p);
                    
                    fullImage = [DrawingTools drawVectors:v_vectors number:resultNum withWidth:1. andColor:[UIColor yellowColor] onImage:fullImage];
                    free(startPoint1);
                    free(v_vectors);
                }
                
                if (self.imageScrollView) {
                    [self.imageScrollView removeFromSuperview];
                    self.imageScrollView = nil;
                }
                self.imageScrollView = [[KFImageZoomView alloc] initWithImage:fullImage atLocation:CGPointMake(0, 0)];
                self.imageScrollView.frame = self.imageView.frame;
                [self.view addSubview:self.imageScrollView];
                
                if (self.axisView) {
                    [self.axisView removeFromSuperview];
                    self.axisView = nil;
                }
                self.axisView = [[PlotView alloc] initWithFrame:self.imageScrollView.frame];
                [self.axisView setBackgroundColor:[UIColor clearColor]];
                [self.axisView setUserInteractionEnabled:NO];
                [self.view addSubview:self.axisView];

                [MBProgressHUD hideHUDForView:self.view animated:YES];
                
                self.imageScrollView.delegate = self;
                [self.imageScrollView zoomToRect:CGRectMake(0, 0, fullImage.size.width, fullImage.size.height) animated:YES];
                processingNow = NO;
            });
        }
    });
}

#pragma mark drawing delegate
-(void)didDrawPoints:(NSArray *)points withRipPointNumbers:(NSArray*)ripPointNumbers inViewController:(DrawingViewController *)viewController {
    [self savePoints:points];
    [self saveRipPointNumbers:ripPointNumbers];
    
    [self dismissViewControllerAnimated:YES completion:nil];
    
    [self processPoints];
}

-(void)didCancelDrawingViewController:(DrawingViewController *)viewController {
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark options delegate
-(void)didEndEditing:(Options *)options inViewController:(OptionsViewController *)viewController {
    self.options = options;
    [self dismissViewControllerAnimated:YES completion:nil];
    [self processPoints];
}

#pragma mark tools
-(void)complain:(NSString*)message {
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Помилка" message:message delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [alert show];
}

-(int**)calculateColorsForValues:(double**)values size:(CGSize)size {
    int** colorNumbers = malloc(sizeof(int*)*size.height);
    if (!colorNumbers) {
        printf("Low memory\n");
        return nil;
    }
    int* colorsNum = malloc(sizeof(int)*self.options.number_of_colors);
    for (int i = 0; i < self.options.number_of_colors; i++) {
        colorsNum[i] = 0;
    }
    for (int i = 0; i < size.height; i++) {
        colorNumbers[i] = malloc(sizeof(int)*size.width);
        if (!colorNumbers[i]) {
            printf("Low memory\n");
            return nil;
        }
    }

    for (int i = 0; i < size.height; i++) {
        for (int j = 0; j < size.width; j++) {
            //printf("looking for value %f...\n", values[i][j]);
            BOOL found = NO;
            for (int k = 0; k < self.options.number_of_colors; k++) {
                if (values[i][j] <= tresholds[k] + 0.1) {
                    colorNumbers[i][j] = k;
                    colorsNum[k]++;
                    found = YES;
                    break;
                }
            }
            if (!found) {
                //printf("not found for value %f...\n", values[i][j]);
                values[i][j] = 0;
                colorNumbers[i][j] = 0;
            }
        }
    }
    /*for (int i = 0; i < self.options.number_of_colors; i++) {
        printf("%d\n", colorsNum[i]);
    }*/
    free(colorsNum);

    return colorNumbers;
}

-(void)handleScrollViewUpdates:(UIScrollView*)scrollView {
    CGRect visibleRect;
    visibleRect.origin = scrollView.contentOffset;
    visibleRect.size = scrollView.bounds.size;
    
    float theScale = 1.0 / scrollView.zoomScale;
    visibleRect.origin.x *= theScale;
    visibleRect.origin.y *= theScale;
    visibleRect.size.width *= theScale;
    visibleRect.size.height *= theScale;
    
    CGPoint topLeftPoint;
    topLeftPoint.x = visibleRect.origin.x*step - self.options.real_width/2;
    topLeftPoint.y = visibleRect.origin.y*step - self.options.real_height/2;
    //NSLog(@"top left: %f %f", topLeftPoint.x, topLeftPoint.y);
    
    CGPoint bottomLeftPoint;
    bottomLeftPoint.x = visibleRect.origin.x*step - self.options.real_width/2;
    bottomLeftPoint.y = (visibleRect.origin.y + visibleRect.size.height)*step - self.options.real_height/2;
    //NSLog(@"bottom left: %f %f", bottomLeftPoint.x, bottomLeftPoint.y);
    
    CGPoint bottomRightPoint;
    bottomRightPoint.x = (visibleRect.origin.x + visibleRect.size.width)*step - self.options.real_width/2;
    bottomRightPoint.y = (visibleRect.origin.y + visibleRect.size.height)*step - self.options.real_height/2;
    //NSLog(@"bottom right: %f %f", bottomLeftPoint.x, bottomLeftPoint.y);
    
    [self.axisView.topLabel setText:[NSString stringWithFormat:@"%.1f", topLeftPoint.y]];
    [self.axisView.centerLabel setText:[NSString stringWithFormat:@"%.1f, %.1f", bottomLeftPoint.x, bottomLeftPoint.y]];
    [self.axisView.rightLabel setText:[NSString stringWithFormat:@"%.1f", bottomRightPoint.x]];
}

#pragma mark scroll view delegate
-(void)scrollViewDidScroll:(UIScrollView *)scrollView {
    if (scrollView == self.imageScrollView && self.axisView) {
        [self handleScrollViewUpdates:scrollView];
    }
}

-(void)scrollViewDidZoom:(UIScrollView *)scrollView {
    if (scrollView == self.imageScrollView && self.axisView) {
        [self handleScrollViewUpdates:scrollView];
    }
}

// called on start of dragging (may require some time and or distance to move)
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView{
    NSLog(@"scrollViewWillBeginDragging");
}

- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset{
    NSLog(@"scrollViewWillEndDragging");
}

- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView{
    NSLog(@"scrollViewWillBeginDecelerating");
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView{
    NSLog(@"scrollViewDidEndDecelerating");
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView {
    return self.imageScrollView.imageView;
}

#pragma mark popoverDelegate
/**
 Thanks to Paul Solt for supplying these background images and container view properties
 */
- (WEPopoverContainerViewProperties *)improvedContainerViewProperties {
	
	WEPopoverContainerViewProperties *props = [WEPopoverContainerViewProperties alloc];
	NSString *bgImageName = nil;
	CGFloat bgMargin = 0.0;
	CGFloat bgCapSize = 0.0;
	CGFloat contentMargin = 4.0;
	
	bgImageName = @"popoverBg.png";
	
	// These constants are determined by the popoverBg.png image file and are image dependent
	bgMargin = 13; // margin width of 13 pixels on all sides popoverBg.png (62 pixels wide - 36 pixel background) / 2 == 26 / 2 == 13
	bgCapSize = 31; // ImageSize/2  == 62 / 2 == 31 pixels
	
	props.leftBgMargin = bgMargin;
	props.rightBgMargin = bgMargin;
	props.topBgMargin = bgMargin;
	props.bottomBgMargin = bgMargin;
	props.leftBgCapSize = bgCapSize;
	props.topBgCapSize = bgCapSize;
	props.bgImageName = bgImageName;
	props.leftContentMargin = contentMargin;
	props.rightContentMargin = contentMargin - 1; // Need to shift one pixel for border to look correct
	props.topContentMargin = contentMargin;
	props.bottomContentMargin = contentMargin;
	
	props.arrowMargin = 4.0;
	
	props.upArrowImageName = @"popoverArrowUp.png";
	props.downArrowImageName = @"popoverArrowDown.png";
	props.leftArrowImageName = @"popoverArrowLeft.png";
	props.rightArrowImageName = @"popoverArrowRight.png";
	return props;
}

#pragma mark -
#pragma mark Actions

- (IBAction)showPopover:(UIButton*)sender {
	if (!self.w_popoverController) {
        if (!colors || !colors.count) {
            return;
        }
        
		WEPopoverContentViewController *contentViewController = [[WEPopoverContentViewController alloc] initWithStyle:UITableViewStylePlain];
        contentViewController.colors = colors;
        NSMutableArray* values = [[NSMutableArray alloc] init];
        for (int i = 0; i < colors.count; i++) {
            [values addObject:[NSNumber numberWithDouble:tresholds[i]]];
        }
        contentViewController.values = values;
		self.w_popoverController = [[popoverClass alloc] initWithContentViewController:contentViewController];
		self.w_popoverController.delegate = self;
		
		[self.w_popoverController presentPopoverFromRect:sender.frame
                                                  inView:self.view
                                permittedArrowDirections:(UIPopoverArrowDirectionUp|UIPopoverArrowDirectionDown)
													   animated:YES];
	} else {
		[self.w_popoverController dismissPopoverAnimated:YES];
		self.w_popoverController = nil;
	}
}

#pragma mark -
#pragma mark WEPopoverControllerDelegate implementation

- (void)popoverControllerDidDismissPopover:(WEPopoverController *)thePopoverController {
	//Safe to release the popover here
	self.w_popoverController = nil;
}

- (BOOL)popoverControllerShouldDismissPopover:(WEPopoverController *)thePopoverController {
	//The popover is automatically dismissed if you click outside it, unless you return NO here
	return YES;
}
@end
