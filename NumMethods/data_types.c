//
//  data_types.c
//  NumMethods
//
//  Created by Andrii Kulian on 11/27/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data_types.h"

double dist(point* p1, point* p2) {
    if (!p1 || !p2) {
        printf("null point pointer");
        return 0;
    }
    
    return sqrt((p1->x-p2->x)*(p1->x-p2->x) + (p1->y-p2->y)*(p1->y-p2->y));
}

point* add_points(point* p1, point* p2) {
    if (!p1 && !p2) {
        return NULL;
    }
    
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    result->x = p1->x + p2->x;
    result->y = p1->y + p2->y;
    
    return result;
}

point* sub_points(point* p1, point* p2) {
    if (!p1 && !p2) {
        return NULL;
    }
    
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    result->x = p1->x - p2->x;
    result->y = p1->y - p2->y;
    
    return result;
}

point* mul_point(point* p1, double k) {
    if (!p1) {
        return NULL;
    }
    
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    result->x = p1->x * k;
    result->y = p1->y * k;
    
    return result;
}

void minus(point* p) {
    if (!p) {
        return;
    }
    
    p->x = -p->x;
    p->y = -p->y;
}

point* zero_point() {
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    result->x = 0;
    result->y = 0;
    
    return result;
}

double dot_product(point* p1, point* p2) {
    if (!p1 || !p2) {
        return 0;
    }

    return (p1->x)*(p2->x) + (p1->y)*(p2->y);
}

double length(point* p) {
    if (!p) {
        return 0;
    }
    return sqrt(p->x*p->x + p->y*p->y);
}

// figure
double part_length(figure* fig, int part_start) {
    if (!fig || !fig->points || part_start < 0) {
        return 0;
    }
    
    return dist(fig->points+part_start, fig->points + (part_start+1));
}

double figure_length(figure* fig) {
    if (!fig || !fig->points || fig->point_number <= 0) {
        return 0;
    }
    
    double length = 0.;
    for (int i = 0; i < fig->point_number - 1; i++) {
        length += part_length(fig, i);
    }
    
    return length;
}