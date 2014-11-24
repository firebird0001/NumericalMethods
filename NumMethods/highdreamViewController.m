//
//  highdreamViewController.m
//  NumMethods
//
//  Created by Andrii Kulian on 9/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "highdreamViewController.h"

#import "tools.h"
#import "data_types.h"

@interface highdreamViewController ()

@end

@implementation highdreamViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [self test];
}

-(void)test {
    /*figure* fig = malloc(sizeof(figure));
    fig->point_number = 4;
    fig->points = malloc(sizeof(point)*fig->point_number);
    for (int i=0; i<fig->point_number; i++) {
        point* p = malloc(sizeof(point));
        p->x = 0.0 + i*10;
        p->y = 0.0 + i*10;
        fig->points[i] = *p;
    }
    
    NSLog(@"%f", dist(fig->points+1, fig->points+2));
    
    point** points_of_interest = malloc(sizeof(point*));
    point** collocation_points = malloc(sizeof(point*));
    
    int point_number = 10;
    get_points_from_simple_figure(fig, point_number, points_of_interest, collocation_points);
    
    for (int i = 0; i < point_number; i++) {
        point *poi = *points_of_interest+i;
        if (i < point_number - 1) {
            point *cp = *collocation_points+i;
            NSLog(@"");
        }
    }*/
    
    int n = 2;
    double** A = (double**)malloc(sizeof(double**)*n);
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(sizeof(double*)*n);
    }
    double* B = (double*)malloc(sizeof(double*)*n);
    A[0][0] = 5;
    A[0][1] = 4;
    B[0] = 9;
    
    A[1][0] = 13;
    A[1][1] = -58;
    B[1] = -45;
    
    double* result = Gauss(A, B, n);
    for (int i = 0; i < n; i++) {
        NSLog(@"%f", result[i]);
    }
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
