//
//  data_types.h
//  NumMethods
//
//  Created by Andrii Kulian on 9/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#ifndef NumMethods_data_types_h
#define NumMethods_data_types_h

#include <stdbool.h>

typedef struct {
    double x;
    double y;
} point;

double dist(point* p1, point* p2);
point* add_points(point* p1, point* p2);
point* sub_points(point* p1, point* p2);
point* mul_point(point* p1, double k);
void minus(point* p);
point* zero_point();
double dot_product(point* p1, point* p2);
double length(point* p);

typedef struct {
    point* points;
    int point_number;
} figure;

double part_length(figure* fig, int part_start);
double figure_length(figure* fig);

typedef struct {
    point start;
    point finish;
} vect;

#endif
