//
//  tools.h
//  NumMethods
//
//  Created by Andrii Kulian on 9/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#import "data_types.h"

#ifndef NumMethods_tools_h
#define NumMethods_tools_h

void coordinates_to_figure(figure** fig, double *coordinates, int point_num);
void figure_to_coordinates(double **coordinates, int *point_num, figure *fig);
void normal_to_line(point* p1, point* p2, point* result);

double phi_2(point* p, point** p_arr, double* gamma, int m, double alpha, point*** r, double*** j_n_p, int n_t, int num_p);
double phi(point* p, point** p_arr, double* gamma, int m, double alpha);
double phi_j(point* p, point* p_j);
double phi_dipol_2(point* p, point** p_arr, double** J, point** p_col, double* gamma, int m, double alpha, point** r, int n_t, int num_p);
double phi_dipol(point* p, point** p_arr, point** p_col, double* gamma, int m, double alpha);

point** V_2_init(point* p, point** p_arr, double* gamma_t, int m, double alpha, int n_t, double delta);
void V_2_cons(point* result, point* p, point** p_arr, double* gamma_t, int m, double alpha, point*** r, double*** j_n_p, int n_t, int num_p, double delta);

point* V_2(point* p, point** p_arr, double* gamma_t, int m, double alpha, point*** r, double*** j_n_p, int n_t, int num_p, double delta);
point* V(point* p, point** p_arr, double* gamma, int m, double alpha, double delta);
point* V_inf(double alpha);
point* V_j(point* p, point* p_j, double delta);
double u_j(point* p, point* p_j, double delta);
double v_j(point* p, point* p_j, double delta);

// pressure
double Cp(point* p, point** p_arr, double* gamma, int m, double alpha, double delta);
double Cp_2(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta, double* delta_t, point** collocation_points, int* separation_point_positions);
double d_phi(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta, double* delta_t, point** collocation_points, int* separation_point_positions);
double d_phi_dip(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta, double* delta_t, point** collocation_points, int* separation_point_positions);
double func_WTF(point* p1, point* p2, point* p3, point* p4, double gamma_0);
point* mid_point(point* p1, point* p2);
bool is_separation_point(int check_point, int* separation_point_positions, int sep_point_num);
double d_phi_konv(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta);
// end of pressure

double ksi_2(point* p, point** p_arr, point** r, double* gamma, int m, double alpha, double delta, double*** j_n_p, int n_t, int num_p);
double ksi(point* p, point** p_arr, double* gamma, int m, double alpha, double delta);
double R(point* p, point* p_j, double delta);

double* Gauss(double** A, double* B, int n);

double degreeToRad(double degree);
double dist_from_point_to_line(point* p, point* p1, point* p2);
double dist_from_point_to_segment(point* p, point* p0, point* p1);
int side_of_line(point* p, point* p1, point* p2);
void square_eq(double a, double b, double c, double* x1, double* x2);
void points_on_line_with_radius(double A, double B, double C, double a, double b, double R, point* p1, point* p2);
point* point_of_perp_root_on_line(point* p, point* p1, point* p2);
void points_on_normal_line_with_point(point* p, point* p1, point* p2, double R, point* p_res_1, point* p_res_2);

#endif
