//
//  lab1.h
//  NumMethods
//
//  Created by Andrii Kulian on 11/27/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#include "tools.h"

#ifndef NumMethods_lab1_h
#define NumMethods_lab1_h

void get_points_from_simple_figure(figure* fig, int point_number, point** points_of_interest, point** collocation_points, point** normal_vectors, int isTest);
double figure_length(figure* fig);
void place_for_point(point* p1, point* p2, double weight, point* result);
double part_length(figure* fig, int part_start);
double** find_Gamma_2(point* collocation_points, point* points_of_interest, point* normal_points, int* separation_points_positions, int time, int p, double*** j_n_p, point*** r, int m, double alpha, double gamma_0, double delta, double** delta_t);
double* find_Gamma(point* collocation_points, point* points_of_interest, point* normal_points, int m, double alpha, double gamma_0, double delta);
double** phi_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max, point*** r, double*** j_n_p, int n_t, int num_p);
double** phi_for_rect(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max);
double** phi_dipol_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, double** J, point** p_col, double* gamma, int m, double alpha, double* min, double* max, point** r, int n_t, int num_p);
double** phi_dipol_for_rect(point* p_start, double step, int width, int height, point** p_arr, point** p_col, double* gamma, int m, double alpha, double* min, double* max);
double** ksi_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, point** r, double* gamma, int m, double alpha, double delta, double* min, double* max, double*** j_n_p, int n_t, int num_p);
double** ksi_for_rect(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double delta, double* min, double* max);
vect* V_for_rect_2(point* p_start, double step, int width, int height, int square_size, point** p_arr, double* gamma, int m, double alpha, int* result_count, double delta, point*** r, double*** j_n_p, int n_t, int num_p);
vect* V_for_rect(point* p_start, double step, int width, int height, int square_size, point** p_arr, double* gamma, int m, double alpha, int* result_count, double delta);
double** Cp_for_rect(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max, double delta);
double** Cp_for_rect_2(point* p_start, double step, int width, int height, point** p_arr, double* gamma, int m, double alpha, double* min, double* max, double delta, double*** j_n_p, double** gamma_t, int time, point** r, int num_p, double* delta_t, point** collocation_points, int* separation_point_positions, int value_window_size);

#endif
