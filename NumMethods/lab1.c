//
//  lab1.c
//  NumMethods
//
//  Created by Andrii Kulian on 11/30/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lab1.h"
#include "TraceCallback.h"

void get_points_from_simple_figure(figure* fig, int point_number, point** points_of_interest, point** collocation_points, point** normal_vectors, int isTest) {
    if (!fig || !points_of_interest || !collocation_points) {
        return;
    }
    
    *points_of_interest = (point*)malloc(sizeof(point)*point_number);
    *collocation_points = (point*)malloc(sizeof(point)*point_number-1);
    *normal_vectors = (point*)malloc(sizeof(point)*point_number-1);
    
    if (!points_of_interest || !collocation_points || !normal_vectors) {
        printf("Low memory\n");
        return;
    }

    // points of interest
    double figure_total_length = figure_length(fig);
    double current_part_length = 0;
    int points_to_place = point_number - fig->point_number;
    int current_point = 0;
    int cur_points_to_place = 0;
    
    for (int i = 0; i < fig->point_number - 1; i++) {
        (*points_of_interest+current_point)->x = fig->points[i].x;
        (*points_of_interest+current_point)->y = fig->points[i].y;
        current_point++;
        
        if (i < fig->point_number-2) {
            current_part_length = part_length(fig, i);
            cur_points_to_place = (current_part_length / figure_total_length) * points_to_place;
        } else {
            cur_points_to_place = points_to_place;
        }
        for (int j = 0; j < cur_points_to_place; j++) {
            place_for_point(fig->points + i, fig->points + (i+1), (1.+j)/(1.+cur_points_to_place), *points_of_interest + current_point);
            current_point++;
            points_to_place--;
        }
    }
    (*points_of_interest+current_point)->x = fig->points[fig->point_number-1].x;
    (*points_of_interest+current_point)->y = fig->points[fig->point_number-1].y;
    
    if (isTest) {
        // poi
        (*points_of_interest + 0) -> x =0.35;
        (*points_of_interest + 0) -> y =0.35707143;
        (*points_of_interest + 1) -> x =0.25;
        (*points_of_interest + 1) -> y =0.4330127;
        (*points_of_interest + 2) -> x =0.15;
        (*points_of_interest + 2) -> y =0.4769696;
        (*points_of_interest + 3) -> x =0.050000004;
        (*points_of_interest + 3) -> y =0.4974937;
        (*points_of_interest + 4) -> x =-0.049999997;
        (*points_of_interest + 4) -> y =0.4974937;
        (*points_of_interest + 5) -> x =-0.15;
        (*points_of_interest + 5) -> y =0.4769696;
        (*points_of_interest + 6) -> x =-0.25;
        (*points_of_interest + 6) -> y =0.4330127;
        (*points_of_interest + 7) -> x =-0.35;
        (*points_of_interest + 7) -> y =0.35707143;
        (*points_of_interest + 8) -> x =-0.45;
        (*points_of_interest + 8) -> y =0.21794498;
        (*points_of_interest + 9) -> x =-0.5;
        (*points_of_interest + 9) -> y =0.0;
        (*points_of_interest + 10) -> x =-0.45;
        (*points_of_interest + 10) -> y =-0.21794498;
        (*points_of_interest + 11) -> x =-0.35;
        (*points_of_interest + 11) -> y =-0.35707143;
        (*points_of_interest + 12) -> x =-0.25;
        (*points_of_interest + 12) -> y =-0.4330127;
        (*points_of_interest + 13) -> x =-0.15;
        (*points_of_interest + 13) -> y =-0.4769696;
        (*points_of_interest + 14) -> x =-0.049999997;
        (*points_of_interest + 14) -> y =-0.4974937;
        (*points_of_interest + 15) -> x =0.050000004;
        (*points_of_interest + 15) -> y =-0.4974937;
        (*points_of_interest + 16) -> x =0.15;
        (*points_of_interest + 16) -> y =-0.4769696;
        (*points_of_interest + 17) -> x =0.25;
        (*points_of_interest + 17) -> y =-0.4330127;
        (*points_of_interest + 18) -> x =0.35;
        (*points_of_interest + 18) -> y =-0.35707143;
        
        // collocation points
        (*collocation_points + 0) -> x =0.3;
        (*collocation_points + 0) -> y =0.39504206;
        (*collocation_points + 1) -> x =0.2;
        (*collocation_points + 1) -> y =0.45499116;
        (*collocation_points + 2) -> x =0.10000001;
        (*collocation_points + 2) -> y =0.48723167;
        (*collocation_points + 3) -> x =3.7252903E-9;
        (*collocation_points + 3) -> y =0.4974937;
        (*collocation_points + 4) -> x =-0.1;
        (*collocation_points + 4) -> y =0.48723167;
        (*collocation_points + 5) -> x =-0.2;
        (*collocation_points + 5) -> y =0.45499116;
        (*collocation_points + 6) -> x =-0.3;
        (*collocation_points + 6) -> y =0.39504206;
        (*collocation_points + 7) -> x =-0.39999998;
        (*collocation_points + 7) -> y =0.2875082;
        (*collocation_points + 8) -> x =-0.475;
        (*collocation_points + 8) -> y =0.10897249;
        (*collocation_points + 9) -> x =-0.475;
        (*collocation_points + 9) -> y =-0.10897249;
        (*collocation_points + 10) -> x =-0.39999998;
        (*collocation_points + 10) -> y =-0.2875082;
        (*collocation_points + 11) -> x =-0.3;
        (*collocation_points + 11) -> y =-0.39504206;
        (*collocation_points + 12) -> x =-0.2;
        (*collocation_points + 12) -> y =-0.45499116;
        (*collocation_points + 13) -> x =-0.1;
        (*collocation_points + 13) -> y =-0.48723167;
        (*collocation_points + 14) -> x =3.7252903E-9;
        (*collocation_points + 14) -> y =-0.4974937;
        (*collocation_points + 15) -> x =0.10000001;
        (*collocation_points + 15) -> y =-0.48723167;
        (*collocation_points + 16) -> x =0.2;
        (*collocation_points + 16) -> y =-0.45499116;
        (*collocation_points + 17) -> x =0.3;
        (*collocation_points + 17) -> y =-0.39504206;
    }
    
    // collocation points & normal vectors
    for (int i = 0; i < point_number - 1; i++) {
        if (!isTest){
            place_for_point(*points_of_interest + i, *points_of_interest + (i+1), .5, *collocation_points + i);
        }
        normal_to_line(*points_of_interest + i, *points_of_interest + (i+1), *normal_vectors + i);
        //printf("normal[%d] x= %f, y= %f\n", i, (*normal_vectors + i)->x, (*normal_vectors + i)->y);
    }
}

void place_for_point(point* p1, point* p2, double weight, point* result) {
    if (!p1 || !p2 || !result || weight < 0 || weight > 1) {
        return;
    }

    result->x = (1-weight)*p1->x + weight*p2->x;
    result->y = (1-weight)*p1->y + weight*p2->y;
}

void find_Gamma_2(void* callback, double*** gamma_r, point* collocation_points, point* points_of_interest, point* normal_points, int* separation_points_positions, int time, int p, double*** j_n_p, point*** r, int m, double alpha, double gamma_0, double delta, double** delta_t) {
    if (!collocation_points || !points_of_interest || !normal_points || !separation_points_positions || !j_n_p || !r) {
        // Wrong input data
        return;
    }
    double** A = (double**)malloc(sizeof(double*) * m);
    double** A2 = (double**)malloc(sizeof(double*) * m);
    double* B = (double*)malloc(sizeof(double) * m);
    *j_n_p = (double**)malloc(sizeof(double*)*p);
    *r = (point**)malloc(sizeof(point*)*p);
    double** gamma = (double**)malloc(sizeof(double*) * (time+1));
    *gamma_r = gamma;
    *delta_t = (double*)malloc(sizeof(double) * time);
    if (!A || !B || !*j_n_p || !gamma || !*r || !*delta_t) {
        // Low memory
        return;
    }
    for (int i = 0; i < m; i++) {
        A[i] = (double*)malloc(sizeof(double)*m);
        if (!A[i]) {
            // Low memory
            return;
        }
    }
    for (int i = 0; i < m; i++) {
        A2[i] = (double*)malloc(sizeof(double)*m);
        if (!A[i]) {
            // Low memory
            return;
        }
    }
    for (int i = 0; i < p; i++) {
        (*j_n_p)[i] = (double*)malloc(sizeof(double)*(time+1));
        if (!(*j_n_p)[i]) {
            // Low memory
            return;
        }
        (*j_n_p)[i][0] = 0.0f;
    }
    
    for (int i = 0; i < p; i++) {
        (*r)[i] = (point*)malloc(sizeof(point)*(time+1));
        if (!(*r)[i]) {
            // Low memory
            return;
        }
        
        (*r)[i][0].x = points_of_interest[separation_points_positions[i]].x;
        (*r)[i][0].y = points_of_interest[separation_points_positions[i]].y;
    }
    // delta_t is filled in calculations sections below
    
    point* v_inf = V_inf(alpha);
    
    for (int k = 0; k < m - 1; k++) {
        for (int j = 0; j < m; j++) {
            point* temp = V_j(collocation_points + k, points_of_interest + j, delta);
            A[k][j] = dot_product(temp, normal_points + k);
            free(temp);
        }
    }
    
    bool continueCalc = true;
    // START CALCULATIONS
    for (int current_time = 0; current_time < time; current_time++) {
        if (true) {//current_time > 0 && current_time % 5 == 0) {
            continueCalc = drawCurrentTrace(callback, current_time);
            if (!continueCalc) {
                break;
            }
        }
        
        // there is (m-1) point of collocation
        for (int k = 0; k < m - 1; k++) {
            for (int j = 0; j < m; j++) {
                A2[k][j] = A[k][j];
            }
            
            B[k] = -dot_product(v_inf, normal_points + k);
            
            if (current_time > 0) {
                for (int p_i = 0; p_i < p; p_i++) {
                    for (int n_i = 0; n_i < current_time; n_i++) {
                        point* temp = V_j(collocation_points + k, (*r)[p_i] + n_i, delta);
                        B[k] -= dot_product(temp, normal_points + k) * (*j_n_p)[p_i][n_i];
                        free(temp);
                    }
                }
            }
        }

        
        // m-th equation
        for (int k = 0; k < m; k++) {
            A2[m-1][k] = 1.0f;
        }
        B[m-1] = 0;
        if (current_time > 0) {
            for (int p_i = 0; p_i < p; p_i++) {
                for (int n_i = 0; n_i < current_time; n_i++) {
                    B[m-1] -= (*j_n_p)[p_i][n_i];
                }
            }
        }
        
        gamma[current_time] = Gauss(A2, B, m);
        if (!gamma[current_time]) {
            // Error calculating gamma
            return;
        }
        
        for (int i = 0; i < p; i++) {
            (*j_n_p)[i][current_time] = gamma[current_time][separation_points_positions[i]];
        }
        
        double current_delta;
        (*delta_t)[current_time] = MAXFLOAT;
        
        for (int i = 0; i < p; i++) {
            (*r)[i][current_time].x = points_of_interest[separation_points_positions[i]].x;
            (*r)[i][current_time].y = points_of_interest[separation_points_positions[i]].y;
        }
        
        for (int i = 0; i < p; i++) {
            point* temp = V_2((*r)[i]+current_time, &points_of_interest, gamma[current_time], m, alpha, r, j_n_p, current_time, p, delta);
            current_delta = delta/length(temp);
            if (current_delta < (*delta_t)[current_time]) {
                (*delta_t)[current_time] = current_delta;
            }
            free(temp);
        }
        
        for (int j = current_time; j >= 0; j--) {
            for (int i = 0; i < p; i++) {
                point* V_in_cur_point = V_2((*r)[i]+j, &points_of_interest, gamma[current_time], m, alpha, r, j_n_p, current_time, p, delta);
                point* temp = mul_point(V_in_cur_point, (*delta_t)[current_time]);
                point* temp2 = add_points((*r)[i]+j, temp);
                (*r)[i][j].x = temp2->x;
                (*r)[i][j].y = temp2->y;
                free(V_in_cur_point);
                free(temp);
                free(temp2);
            }
        }
    }

    if (A) {
        for (int i = 0; i < m - 1; i++) {
            if (A[i]) {
                free(A[i]);
            }
        }
        free(A);
    }
    if (B) {
        free(B);
    }
    
    if (continueCalc) {
        drawCurrentTrace(callback, time - 1);
    }
}

double* find_Gamma(point* collocation_points, point* points_of_interest, point* normal_points, int m, double alpha, double gamma_0, double delta) {
    double** A = (double**)malloc(sizeof(double*) * m);
    double* B = (double*)malloc(sizeof(double) * m);
    if (!A || !B) {
        printf("Low memory\n");
        return NULL;
    }
    
    // there is (m-1) point of collocation
    for (int i = 0; i < m - 1; i++) {
        A[i] = (double*)malloc(sizeof(double)*m);
        if (!A[i]) {
            printf("Low memory\n");
            return NULL;
        }
        for (int j = 0; j < m; j++) {
            point* temp = V_j(collocation_points + i, points_of_interest + j, delta);
            A[i][j] = dot_product(temp, normal_points + i);
            free(temp);
        }

        B[i] = -dot_product(V_inf(alpha), normal_points + i);
    }

    // m-th equation
    A[m-1] = (double*)malloc(sizeof(double)*m);
    if (!A[m-1]) {
        printf("Low memory\n");
        return NULL;
    }
    for (int j = 0; j < m; j++) {
        A[m-1][j] = 1;
    }
    B[m-1] = gamma_0;
    
    return Gauss(A, B, m);
}

double** phi_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max, point*** r, double*** j_n_p, int n_t, int num_p) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0 || !min || !max) {
        printf("phi_for_rect2: wrong input data\n");
        return NULL;
    }
    
    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("phi_for_rect2: result low memory\n");
        return NULL;
    }
    
    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("phi_for_rect2: result subarray low memory\n");
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            p.y = p_start->y + i * step;
            p.x = p_start->x + j * step;
            result[i][j] = phi_2(&p, p_arr, gamma, m, alpha, r, j_n_p, n_t, num_p);
            if (result[i][j] < *min) {
                *min = result[i][j];
            } else if (result[i][j] > *max) {
                *max = result[i][j];
            }
        }
    }
    
    return result;
}

double** phi_for_rect(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0 || !min || !max) {
        printf("phi_for_rect: wrong input data\n");
        return NULL;
    }

    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("phi_for_rect: result low memory\n");
        return NULL;
    }

    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("phi_for_rect: result subarray low memory\n");
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            p.y = p_start->y + i * step;
            p.x = p_start->x + j * step;
            result[i][j] = phi(&p, p_arr, gamma, m, alpha);
            if (result[i][j] < *min) {
                *min = result[i][j];
            } else if (result[i][j] > *max) {
                *max = result[i][j];
            }
        }
    }

    return result;
}

double** phi_dipol_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, double** J, point** p_col, double* gamma, int m, double alpha, double* min, double* max, point** r, int n_t, int num_p) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0 || !min || !max) {
        printf("phi_for_rect_2: wrong input data\n");
        return NULL;
    }
    
    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("phi_for_rect_2: result low memory\n");
        return NULL;
    }
    
    int number_to_remove = width*height/50;
    double* minimums = (double*)malloc(sizeof(double)*number_to_remove);
    double* maximums = (double*)malloc(sizeof(double)*number_to_remove);
    int cur_min = 0;
    int cur_max = 0;
    minimums[0] = *min;
    maximums[0] = *max;
    
    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("phi_for_rect_2: result subarray low memory\n");
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            p.y = p_start->y + i * step;
            p.x = p_start->x + j * step;
            result[i][j] = phi_dipol_2(&p, p_arr, J, p_col, gamma, m, alpha, r, n_t, num_p);
            // cut too low or too high values
            if (result[i][j] < minimums[cur_min%number_to_remove]) {
                //printf("min: %f %d %d\n", result[i][j], i, j);
                minimums[(++cur_min)%number_to_remove] = result[i][j];
            } else if (result[i][j] > maximums[cur_min%number_to_remove]) {
                //printf("max: %f %d %d\n", result[i][j], i, j);
                maximums[(++cur_max)%number_to_remove] = result[i][j];
            }
        }
    }
    
    if (cur_min <= number_to_remove) {
        *min = minimums[1];
    } else {
        *min = minimums[(++cur_min)%number_to_remove];
    }
    if (cur_max <= number_to_remove) {
        *max = maximums[1];
    } else {
        *max = maximums[(++cur_max)%number_to_remove];
    }
    printf("min: %f max: %f\n", *min, *max);
    
    return result;
}

double** phi_dipol_for_rect(point* p_start, double step, int width, int height, point** p_arr, point** p_col, double* gamma, int m, double alpha, double* min, double* max) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0 || !min || !max) {
        printf("phi_for_rect: wrong input data\n");
        return NULL;
    }

    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("phi_for_rect: result low memory\n");
        return NULL;
    }
    
    int number_to_remove = width*height/50;
    double* minimums = (double*)malloc(sizeof(double)*number_to_remove);
    double* maximums = (double*)malloc(sizeof(double)*number_to_remove);
    int cur_min = 0;
    int cur_max = 0;
    minimums[0] = *min;
    maximums[0] = *max;
    
    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("phi_for_rect: result subarray low memory\n");
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            p.y = p_start->y + i * step;
            p.x = p_start->x + j * step;
            result[i][j] = phi_dipol(&p, p_arr, p_col, gamma, m, alpha);
            // cut too low or too high values
            if (result[i][j] < minimums[cur_min%number_to_remove]) {
                //printf("min: %f %d %d\n", result[i][j], i, j);
                minimums[(++cur_min)%number_to_remove] = result[i][j];
            } else if (result[i][j] > maximums[cur_min%number_to_remove]) {
                //printf("max: %f %d %d\n", result[i][j], i, j);
                maximums[(++cur_max)%number_to_remove] = result[i][j];
            }
        }
    }

    if (cur_min <= number_to_remove) {
        *min = minimums[1];
    } else {
        *min = minimums[(++cur_min)%number_to_remove];
    }
    if (cur_max <= number_to_remove) {
        *max = maximums[1];
    } else {
        *max = maximums[(++cur_max)%number_to_remove];
    }
    printf("min: %f max: %f\n", *min, *max);

    return result;
}

double** ksi_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, point** r, double* gamma, int m, double alpha, double delta, double* min, double* max, double*** j_n_p, int n_t, int num_p) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0) {
        return NULL;
    }
    
    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("Low memory\n");
            return NULL;
        }
        p.y = p_start->y + i * step;
        for (int j = 0; j < width; j++) {
            p.x = p_start->x + j * step;
            result[i][j] = ksi_2(&p, p_arr, r, gamma, m, alpha, delta, j_n_p, n_t, num_p);
            if (result[i][j] < *min) {
                *min = result[i][j];
            } else if (result[i][j] > *max) {
                *max = result[i][j];
            }
        }
    }
    
    return result;
}

double** ksi_for_rect(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double delta, double* min, double* max) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0) {
        return NULL;
    }

    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }

    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("Low memory\n");
            return NULL;
        }
        p.y = p_start->y + i * step;
        for (int j = 0; j < width; j++) {
            p.x = p_start->x + j * step;
            result[i][j] = ksi(&p, p_arr, gamma, m, alpha, delta);
            if (result[i][j] < *min) {
                *min = result[i][j];
            } else if (result[i][j] > *max) {
                *max = result[i][j];
            }
        }
    }

    return result;
}

vect* V_for_rect_2(point* p_start, double step, int width, int height, int square_size, point** p_arr, double* gamma, int m, double alpha, int* result_count, double delta, point*** r, double*** j_n_p, int n_t, int num_p) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0) {
        return NULL;
    }
    
    int totalCount = (height/square_size)*(width/square_size);
    vect* result = (vect*)malloc(sizeof(vect)*totalCount);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    int count = 0;
    
    point p;
    float delta_x;
    float delta_y;
    for (int i = square_size/2; i < height && count < totalCount; i+=square_size) {
        p.y = p_start->y + i * step;
        for (int j = square_size/2; j < width && count < totalCount; j+=square_size) {
            p.x = p_start->x + j * step;
            point* v = V_2(&p, p_arr, gamma, m, alpha, r, j_n_p, n_t, num_p, delta);
            delta_x = v->x/2 * square_size / 3 * 2;
            delta_y = v->y/2 * square_size / 3 * 2;
            if (fabs(delta_x) > square_size/2 || fabs(delta_y) > square_size/2) {
                double k = fabs(delta_x/delta_y);
                if (fabs(delta_x) > fabs(delta_y)) {
                    delta_x = square_size/2 * (delta_x >= 0 ? 1 : -1);
                    delta_y = delta_x/k *  (delta_y >= 0 ? 1 : -1);
                } else {
                    delta_y = square_size/2  * (delta_y >= 0 ? 1 : -1);
                    delta_x = delta_y*k  * (delta_x >= 0 ? 1 : -1);
                }
            }
            result[count].start.x = j - delta_x;
            result[count].start.y = i - delta_y;
            result[count].finish.x = j + delta_x;
            result[count].finish.y = i + delta_y;
            free(v);
            count++;
        }
    }
    
    *result_count = totalCount;
    
    return result;
}

vect* V_for_rect(point* p_start, double step, int width, int height, int square_size, point** p_arr, double* gamma, int m, double alpha, int* result_count, double delta) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0) {
        return NULL;
    }

    int totalCount = (height/square_size)*(width/square_size);
    vect* result = (vect*)malloc(sizeof(vect)*totalCount);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }

    int count = 0;
    
    point p;
    float delta_x;
    float delta_y;
    for (int i = square_size/2; i < height && count < totalCount; i+=square_size) {
        p.y = p_start->y + i * step;
        for (int j = square_size/2; j < width && count < totalCount; j+=square_size) {
            p.x = p_start->x + j * step;
            point* v = V(&p, p_arr, gamma, m, alpha, delta);
            delta_x = v->x/2 * square_size / 3 * 2;
            delta_y = v->y/2 * square_size / 3 * 2;
            if (fabs(delta_x) > square_size/2 || fabs(delta_y) > square_size/2) {
                double k = fabs(delta_x/delta_y);
                if (fabs(delta_x) > fabs(delta_y)) {
                    delta_x = square_size/2 * (delta_x >= 0 ? 1 : -1);
                    delta_y = delta_x/k *  (delta_y >= 0 ? 1 : -1);
                } else {
                    delta_y = square_size/2  * (delta_y >= 0 ? 1 : -1);
                    delta_x = delta_y*k  * (delta_x >= 0 ? 1 : -1);
                }
            }
            result[count].start.x = j - delta_x;
            result[count].start.y = i - delta_y;
            result[count].finish.x = j + delta_x;
            result[count].finish.y = i + delta_y;
            free(v);
            count++;
        }
    }
    
    *result_count = totalCount;

    return result;
}

double** Cp_for_rect(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max, double delta) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0) {
        return NULL;
    }

    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    int number_to_remove = width*height/500;
    double* minimums = (double*)malloc(sizeof(double)*number_to_remove);
    double* maximums = (double*)malloc(sizeof(double)*number_to_remove);
    int cur_min = 0;
    int cur_max = 0;
    minimums[0] = *min;
    maximums[0] = *max;

    point p;
    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("Low memory\n");
            return NULL;
        }
        p.y = p_start->y + i * step;
        for (int j = 0; j < width; j++) {
            p.x = p_start->x + j * step;
            result[i][j] = Cp(&p, p_arr, gamma, m, alpha, delta);
            // cut too low or too high values
            if (result[i][j] < minimums[cur_min%number_to_remove]) {
                //printf("min: %f %d %d\n", result[i][j], i, j);
                minimums[(++cur_min)%number_to_remove] = result[i][j];
            } else if (result[i][j] > maximums[cur_min%number_to_remove]) {
                //printf("max: %f %d %d\n", result[i][j], i, j);
                maximums[(++cur_max)%number_to_remove] = result[i][j];
            }
        }
    }

    if (cur_min <= number_to_remove) {
        *min = minimums[1];
    } else {
        *min = minimums[(++cur_min)%number_to_remove];
    }
    if (cur_max <= number_to_remove) {
        *max = maximums[1];
    } else {
        *max = maximums[(++cur_max)%number_to_remove];
    }
    printf("min: %f max: %f\n", *min, *max);

    return result;
}

double** Cp_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max, double delta, double*** j_n_p, double** gamma_t, int time, point** r, int num_p, double* delta_t, point** collocation_points, int* separation_point_positions, int value_window_size) {
    if (!p_start || step <= 0 || width <= 0 || height <= 0) {
        return NULL;
    }
    
    double** result = (double**)malloc(sizeof(double*)*height);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    int number_to_remove = 1;//width*height/1000000;
    double* minimums = (double*)malloc(sizeof(double)*number_to_remove);
    double* maximums = (double*)malloc(sizeof(double)*number_to_remove);
    int cur_min = 0;
    int cur_max = 0;
    minimums[0] = *min;
    maximums[0] = *max;


    int squares_in_row = width/value_window_size;

    int totalCount = (height/value_window_size + 1) * (squares_in_row + 1);
    double* result_squares = (double*)malloc(sizeof(double)*totalCount);
    if (!result) {
        printf("Low memory\n");
        return NULL;
    }
    
    int count = 0;
    
    point p;
    for (int i = value_window_size/2; i < height + value_window_size && count < totalCount; i+=value_window_size) {
        p.y = p_start->y + i * step;
        for (int j = value_window_size/2; j < width && count < totalCount; j+=value_window_size) {
            p.x = p_start->x + j * step;

            result_squares[count] = Cp_2(&p, p_arr, j_n_p, gamma_t, m, alpha, time, r, num_p, delta, delta_t, collocation_points, separation_point_positions);
            if (result_squares[count] > 2.) {
                printf("found bad big value : %f\n", result_squares[count]);
                result_squares[count] = 1;
            }
            if (result_squares[count] < -7.) {
                printf("found bad small value : %f\n", result_squares[count]);
                result_squares[count] = -5;
            }

            count++;
        }
    }
    // TODO hack
    result_squares[count++] = 0;

    for (int i = 0; i < height; i++) {
        result[i] = (double*)malloc(sizeof(double)*width);
        if (!result[i]) {
            printf("Low memory\n");
            return NULL;
        }
        p.y = p_start->y + i * step;
        for (int j = 0; j < width; j++) {
            p.x = p_start->x + j * step;
            result[i][j] = result_squares[(i/value_window_size) * squares_in_row + j/value_window_size];
            if (result[i][j] < minimums[cur_min%number_to_remove]) {
                minimums[(++cur_min)%number_to_remove] = result[i][j];
            } else if (result[i][j] > maximums[cur_min%number_to_remove]) {
                maximums[(++cur_max)%number_to_remove] = result[i][j];
            }
        }
    }
    
    if (cur_min <= number_to_remove) {
        *min = minimums[1];
    } else {
        *min = minimums[(++cur_min)%number_to_remove];
    }
    if (cur_max <= number_to_remove) {
        *max = maximums[1];
    } else {
        *max = maximums[(++cur_max)%number_to_remove];
    }
    printf("min: %f max: %f\n", *min, *max);
    
    return result;
}