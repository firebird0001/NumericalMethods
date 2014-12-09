//
//  tools.c
//  NumMethods
//
//  Created by Andrii Kulian on 9/10/13.
//  Copyright (c) 2013 Andrii Kulian. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#import "tools.h"

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

#define ANOMAL_THRESHOLD (2.)

void coordinates_to_figure(figure **fig, double *coordinates, int point_num) {
    if (point_num <= 0 || !coordinates) {
        return;
    }

    *fig = (figure*)malloc(sizeof(figure));
    point *points = (point*)malloc(sizeof(point)*point_num);
    if (!*fig || !points) {
        // Low memory
        return;
    }

    for (int i = 0; i < point_num; i++) {
        point p1;
        p1.x = coordinates[2*i];
        p1.y = coordinates[2*i+1];
        points[i] = p1;
    }

    (*fig)->point_number = point_num;
    (*fig)->points = points;
}

void figure_to_coordinates(double **coordinates, int *point_num, figure *fig) {
    if (!fig) {
        return;
    }
    
    *coordinates = (double*)malloc(sizeof(double)*fig->point_number*2);
    point_num = (int*)malloc(sizeof(int));
    if (!*coordinates || !point_num) {
        // Low memory
        return;
    }
    
    for (int i = 0; i < fig->point_number; i++) {
        *coordinates[i*2] = fig->points[i].x;
        *coordinates[i*2+1] = fig->points[i].y;
    }
}

void normal_to_line(point* p1, point* p2, point* result) {
    if (!p1 || !p2 || !result) {
        return;
    }
    
    double distance = dist(p1, p2);

    result->y = (p2->x-p1->x)/distance;
    result->x = -(p2->y-p1->y)/distance;
}

double phi_2(point* p, point** p_arr, double* gamma, int m, double alpha, point*** r, double*** j_n_p, int n_t, int num_p) {
    if (!p || !p_arr || !gamma || m == 0) {
        printf("phi2: wrong input data\n");
        return 0;
    }
    
    double result;
    double temp = 0;
    
    result = p->x * cos(alpha) + p->x * sin(alpha);
    for (int j = 0; j < m; j++) {
        temp += phi_j(p, *p_arr+j) * gamma[j];
    }
    for (int k = 0; k < num_p; k++) {
        for (int j = 0; j < n_t; j++) {
            temp += phi_j(p, (*r)[k]+j) * (*j_n_p)[k][j];
        }
    }
    
    temp /= 2*M_PI;
    result += temp;
    
    return result;
}

double phi(point* p, point** p_arr, double* gamma, int m, double alpha) {
    if (!p || !p_arr || !gamma || m == 0) {
        printf("phi: wrong input data\n");
        return 0;
    }

    double result;
    double temp = 0;

    result = p->x * cos(alpha) + p->x * sin(alpha);
    for (int j = 0; j < m; j++) {
        temp += phi_j(p, *p_arr+j) * gamma[j];
    }
    temp /= 2*M_PI;
    result += temp;

    return result;
}

double phi_j(point* p, point* p_j) {
    if (!p || !p_j) {
        printf("phi_j: wrong input data\n");
        return 0;
    }
    
    return atan2((p->y-p_j->y), (p->x-p_j->x));
}

point* V_2(point* p, point** p_arr, double* gamma_t, int m, double alpha, point*** r, double*** j_n_p, int n_t, int num_p, double delta) {
    if (!p || !p_arr || m == 0 || !gamma_t) {
        return NULL;
    }
    
    point* result = V_inf(alpha);
    
    for (int j = 0; j < m; j++) {
        point* temp2 = V_j(p, *p_arr+j, delta);
        point* temp = mul_point(temp2, gamma_t[j]);
        result->x += temp->x;
        result->y += temp->y;
        free(temp);
        free(temp2);
    }
    
    for (int k = 0; k < num_p; k++) {
        for (int j = 0; j < n_t; j++) {
            point* temp = V_j(p, (*r)[k]+j, delta);

            point* temp2 = mul_point(temp, (*j_n_p)[k][j]);
            result->x += temp2->x;
            result->y += temp2->y;
            free(temp);
            free(temp2);
        }
    }
    
    return result;
}

point* V(point* p, point** p_arr, double* gamma, int m, double alpha, double delta) {
    if (!p || !p_arr || m == 0) {
        return NULL;
    }
    
    point* result = malloc(sizeof(point));
    point* temp1 = V_inf(alpha);
    result->x = temp1->x;
    result->y = temp1->y;
    free(temp1);
    for (int j = 0; j < m; j++) {
        point* temp2 = V_j(p, *p_arr+j, delta);
        point* temp = mul_point(temp2, gamma[j]);
        result->x += temp->x;
        result->y += temp->y;
        free(temp);
        free(temp2);
    }

    result->y = result->y;
    
    return result;
}

point* V_inf(double alpha) {
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        // Low memory
        return NULL;
    }

    result->x = cos(alpha);
    result->y = sin(alpha);

    return result;
}

point* V_j(point* p, point* p_j, double delta) {
    if (!p || !p_j) {
        return NULL;
    }
    
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        // Low memory
        return NULL;
    }
    
    result->x = u_j(p, p_j, delta);
    result->y = v_j(p, p_j, delta);
    
    return result;
}

double u_j(point* p, point* p_j, double delta) {
    if (!p || !p_j) {
        return 0;
    }

    double dst = R(p, p_j, delta);
    
    double res = (p_j->y-p->y)/(dst*dst*2*M_PI);
    
    return res;
}

double v_j(point* p, point* p_j, double delta) {
    if (!p || !p_j) {
        return 0;
    }

    double dst = R(p, p_j, delta);
    
    return (p->x-p_j->x)/(dst*dst*2*M_PI);
}

/* ############### START OF PRESSURE CALCULATION ############## */

double Cp(point* p, point** p_arr, double* gamma, int m, double alpha, double delta) {
    if (!p) {
        return 0;
    }

    point* v = V(p, p_arr, gamma, m, alpha, delta);
    point* v_inf = V_inf(alpha);

    double result =  1. - dot_product(v, v)/dot_product(v_inf, v_inf);

    free(v);
    free(v_inf);

    return result;
}

double Cp_2(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta, double* delta_t, point** collocation_points, int* separation_point_positions) {
    if (!p) {
        return 0;
    }
    
    point* temp1 = V_2(p, p_arr, gamma_t[time-1], m, alpha, &r, j_n_p, time, num_p, delta);
    
    double res = - dot_product(temp1, temp1);
    res -= 2 * d_phi(p, p_arr, j_n_p, gamma_t, m, alpha, time, r, num_p, delta, delta_t, collocation_points, separation_point_positions);
    res += 1;
    
    free(temp1);

    return res;
}

double d_phi(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta, double* delta_t, point** collocation_points, int* separation_point_positions) {
    return d_phi_dip(p, p_arr, j_n_p, gamma_t, m, alpha, time, r, num_p, delta, delta_t, collocation_points, separation_point_positions) + d_phi_konv(p, p_arr, j_n_p, gamma_t, m, alpha, time, r, num_p, delta);
}

double d_phi_dip(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta, double* delta_t, point** collocation_points, int* separation_point_positions) {
    int currentTime = time - 1;
    double res = 0;
    double gamma0 = 0;
    int p_i = 0;
        
    for (int i = 0; i < m - 1; i++) {
        // check if is separation point
        if (is_separation_point(i, separation_point_positions, num_p)) {
            gamma0 += (*j_n_p)[p_i][currentTime] / delta_t[currentTime];

            point* temp_mid_p = mid_point(r[p_i] + currentTime, *p_arr + i);
            
            res += func_WTF(*p_arr + i, r[p_i] + currentTime, p, temp_mid_p, gamma0);
            free(temp_mid_p);

            p_i++;
        }

        gamma0 += (gamma_t[currentTime][i] - gamma_t[currentTime - 1][i]) / delta_t[currentTime];
        
        res += func_WTF(*p_arr + (i + 1), *p_arr + i, p, * collocation_points + i, gamma0);
    }
    
    // check if last one is also a separation point
    if (is_separation_point(m-1, separation_point_positions, num_p)) {
        gamma0 += (*j_n_p)[p_i][currentTime] / delta_t[currentTime];
        
        point* temp_mid_p = mid_point(r[p_i] + currentTime, *p_arr + (m-1));
        
        res += func_WTF(*p_arr + (m-1), r[p_i] + currentTime, p, temp_mid_p, gamma0);
        free(temp_mid_p);
    }
    
    res /= 2 * M_PI;
    return res;
}
        
inline double func_WTF(point* p1, point* p2, point* p3, point* p4, double gamma_0) {
    double x1 = p1->x - p2->x;
    double x2 = p1->y - p2->y;
    double x3 = p3->x - p4->x;
    double x4 = p3->y - p4->y;
    
    return gamma_0 * (-x1*x4 + x2*x3) / (x3*x3 + x4*x4);
}

point* mid_point(point* p1, point* p2) {
    point* res = (point*)malloc(sizeof(point));
    
    res->x = (p1->x + p2->x) / 2;
    res->y = (p1->y + p2->y) / 2;
    
    return res;
}
        
bool is_separation_point(int check_point, int* separation_point_positions, int sep_point_num) {
    for (int i = 0; i < sep_point_num; i++) {
        if (check_point == separation_point_positions[i]) {
            return true;
        }
    }
    return false;
}

double d_phi_konv(point* p, point** p_arr, double*** j_n_p, double** gamma_t, int m, double alpha, int time, point** r, int num_p, double delta) {
    double res = 0;
    int current_time = time - 1;
    if (current_time != 0) {
        for(int p_i = 0; p_i < num_p; p_i++){
            for(int n_i = 0 ; n_i < current_time; n_i++){
                res += (*j_n_p)[p_i][n_i] * dot_product(V_j(p, r[p_i] + n_i, delta),
                                                   V_2(r[p_i] + n_i, p_arr, gamma_t[n_i], m, alpha, &r, j_n_p, n_i, num_p, delta));
            }
        }
    }
    return -res;
}


/*float d_Phi_dip(Point point){
 int currentTime = time - 1;
 float res = 0;
 if(point != null && currentTime != 0){
 float d_G, Y_n;
 Point temp;
 for(int j = 0 ; j < specialPoint.size(); j++){
 temp = specialPoint.get(j);
 d_G = (gamma[currentTime][j] - gamma[currentTime - 1][j])/deltaT[currentTime];
 res += d_G * Math.atan2((point.getY() - temp.getY()), (point.getX() - temp.getX()));
 }
 
 for(int p_i = 0; p_i < p ; p_i++){
 temp = r[p_i][currentTime];
 Y_n = J_p[p_i][currentTime]/deltaT[currentTime];
 res += Y_n * Math.atan2((point.getY() - temp.getY()), (point.getX() - temp.getX()));
 }
 }
 return (float) (res/(2*Math.PI));
 }*/

/* ##################### END OF PRESSURE CALCULATION ################# */

double ksi_2(point* p, point** p_arr, point** r, double* gamma, int m, double alpha, double delta, double*** j_n_p, int n_t, int num_p) {
    if (!p || !p_arr || !gamma || m == 0) {
        return 0;
    }
    
    double result = 0.;
    
    for (int j = 0; j < m; j++) {
        result -= gamma[j]*log(R(p, *p_arr+j, delta));
    }
    for (int k = 0; k < num_p; k++) {
        for (int i = 0; i < n_t; i++) {
            result -= (*j_n_p)[k][i]*log(R(p, r[k] + i, delta));
        }
    }
    result /= (2*M_PI);
    
    result += - p->x * sin(alpha) + p->y * cos(alpha);
    
    return result;
}

double ksi(point* p, point** p_arr, double* gamma, int m, double alpha, double delta) {
    if (!p || !p_arr || !gamma || m == 0) {
        return 0;
    }

    double result = 0.;

    for (int j = 0; j < m; j++) {
        result -= gamma[j]*log(R(p, *p_arr+j, delta));
    }
    result /= (2*M_PI);

    result += - p->x * sin(alpha) + p->y * cos(alpha);

    return result;
}

double phi_dipol_2(point* p, point** p_arr, double** J, point** p_col, double* gamma, int m, double alpha, point** r, int n_t, int num_p) {
    if (!p || !p_arr || !gamma || m == 0) {
        printf("phi_dipol_2: wrong input data\n");
        if (!p) {
            printf("WRONG P\n");
        }
        if (!p_arr) {
            printf("WRONG P_ARR\n");
        }
        if (!gamma) {
            printf("WRONG GAMMA\n");
        }
        return 0;
    }
    
    double result;
    double temp = 0;
    
    result = p->x * cos(alpha) + p->y * sin(alpha);
    double gamma_0 = 0;
    for (int j = 0; j < m - 1; j++) {
        gamma_0 += gamma[j];
        
        double x1 = (*p_arr)[j+1].x - (*p_arr)[j].x;
        double x2 = (*p_arr)[j+1].y - (*p_arr)[j].y;
        double x3 = p->x - (*p_col)[j].x;
        double x4 = p->y - (*p_col)[j].y;
        
        temp += gamma_0 * (-x1*x4 + x2*x3) / (x3*x3 + x4*x4);
    }

    for (int k = 0; k < num_p; k++) {
        gamma_0 = 0;
        for (int j = 0; j < n_t - 1; j++) {
            gamma_0 += J[k][j];
            
            //temp += phi_j(p, (*r)[k]+j);
            
            double x1 = r[k][j+1].x - r[k][j].x;
            double x2 = r[k][j+1].y - r[k][j].y;
            double x3 = p->x - (r[k][j+1].x + r[k][j].x) / 2;
            double x4 = p->y - (r[k][j+1].y + r[k][j].y) / 2;
            
            temp += gamma_0 * (-x1*x4 + x2*x3) / (x3*x3 + x4*x4);
        }
    }
    temp /= 2*M_PI;
    result += temp;
    
    return result;
}

double phi_dipol(point* p, point** p_arr, point** p_col, double* gamma, int m, double alpha) {
    if (!p || !p_arr || !gamma || m == 0) {
        printf("phi_dipol: wrong input data\n");
        return 0;
    }
    
    double result;
    double temp = 0;
    
    result = p->x * cos(alpha) + p->y * sin(alpha);
    for (int j = 0; j < m - 1; j++) {
        double gamma_temp = 0;
        for (int i = 0; i < j; i++) {
            gamma_temp += gamma[i];
        }
        //gamma_temp /= 2*M_PI;
        double x1 = (*p_arr)[j+1].x - (*p_arr)[j].x;
        double x2 = (*p_arr)[j+1].y - (*p_arr)[j].y;
        double x3 = p->x - (*p_col)[j].x;
        double x4 = p->y - (*p_col)[j].y;
        
        temp += gamma_temp * (-x1*x4 + x2*x3) / (x3*x3 + x4*x4);
    }
    temp /= 2*M_PI;
    result += temp;
    
    return result;
}

double R(point* p, point* p_j, double delta) {
    if (!p || !p_j) {
        return 0;
    }

    return max(delta, dist(p, p_j));
}

double* Gauss(double** A, double* B, int n) {
    if (!A || !B || n <= 0) {
        return NULL;
    }
    
    double* result = (double*)malloc(sizeof(double) * n);
    
    for (int i = 0; i < n; i++) {
        double main_elem = A[i][i];
        if (fabs(main_elem) < 0.00001) {
            // need to find another element
            for (int k = i+1; k < n; k++) {
                if (fabs(A[k][i]) >= 0.00001) {
                    double temp;
                    for (int j = i; j < n; j++) {
                        temp = A[k][j];
                        A[k][j] = A[i][j];
                        A[i][j] = temp;
                    }
                    temp = B[k];
                    B[i] = temp;
                    B[k] = B[i];
                    
                    main_elem = A[i][i];
                    break;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            A[i][j] /= main_elem;
        }
        
        B[i] /= main_elem;
        
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double multiplier = A[k][i];
                for (int j = i; j < n; j++) {
                    A[k][j] -= A[i][j]*multiplier;
                }
                B[k] -= B[i]*multiplier;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        result[i] = B[i];
    }
    
    return result;
}

double degreeToRad(double degree) {
    return - degree * M_PI / 180;
}

double dist_from_point_to_segment(point* p, point* p0, point* p1) {
    point* v = (point*)malloc(sizeof(point));
    point* w = (point*)malloc(sizeof(point));
    v->y = p1->y - p0->y;
    v->x = p1->x - p0->x;
    w->y = p->y - p0->y;
    w->x = p->x - p0->x;
    double c1 = w->y * v->y + w->x * v->x;
    if ( c1 <= 0 ) {
        free(v);
        free(w);
        return dist(p, p0);
    }
    double c2 = v->y * v->y + v->x * v->x;
    if ( c2 <= c1 ) {
        free(v);
        free(w);
        return dist(p, p1);
    }
    double b = c1 / c2;
    w->y = p0->y + b * v->y;
    w->x = p0->x + b * v->x;
    return dist(p, w);
}

double dist_from_point_to_line(point* p, point* p1, point* p2) {
    double A = p2->y - p1->y;
    double B = p1->x - p2->x;
    double C = p1->x * (p1->y - p2->y) + p1->y * (p2->x - p1->x);
    
    return (A*p->x + B*p->y + C) / sqrt(A*A + B*B);
}

int side_of_line(point* p, point* p1, point* p2) {
    double A = p2->y - p1->y;
    double B = p1->x - p2->x;
    double C = p1->x * (p1->y - p2->y) + p1->y * (p2->x - p1->x);
    
    double result = A*p->x + B*p->y + C;
    
    if (result > 0.000001) {
        return 1;
    } else if (result < -0.000001) {
        return -1;
    } else {
        return 0;
    }
}

void square_eq(double a, double b, double c, double* x1, double* x2) {
    if (!x1 || !x2) {
        return;
    }
    
    if (fabs(a) < 0.000001) {
        printf("Error in square equation");
        return;
    }
    double D = b*b - 4*a*c;
    *x1 = (-b+D)/(2*a);
    *x2 = (-b-D)/(2*a);
}

void points_on_line_with_radius(double A, double B, double C, double a, double b, double R, point* p1, point* p2) {
    if (!p1 || !p2) {
        return;
    }
    
    double y_1 = 0;
    double y_2 = 0;
    
    square_eq(B*B/(A*A) + 1, 2*B*C/(A*A) + 2*B*a/A - 2*b, C*C/(A*A) + a*a + 2*C*a/A + b*b - R*R, &y_1, &y_2);
    
    p1->y = y_1;
    p1->x = (-C-B*y_1)/A;
    p2->y = y_2;
    p2->x = (-C-B*y_2)/A;
}

point* point_of_perp_root_on_line(point* p, point* p1, point* p2) {
    point* result = (point*)malloc(sizeof(point));
    if (!result) {
        // Low memory
        return NULL;
    }
    
    result->x = (p1->x*(p2->y-p1->y)*(p2->y-p1->y) + p->x*(p2->x-p1->x)*(p2->x-p1->x) + (p2->x-p1->x)*(p2->y-p1->y)*(p->y-p1->y))/((p2->y-p1->y)*(p2->y-p1->y) + (p2->x-p1->x)*(p2->x-p1->x));
    result->y = (p2->x-p1->x)*(p->x-result->x)/(p2->y-p1->y) + p->y;
    
    return result;
}

void points_on_normal_line_with_point(point* p, point* p1, point* p2, double R, point* p_res_1, point* p_res_2) {
    /*double A = (p2->x - p1->x)/((p2->y - p1->y));
    double B = 1;
    double C = -p->y - A * p->x;*/
    point* perp_root = point_of_perp_root_on_line(p, p1, p2);
    
    double k = (p2->y-p1->y)/(p2->x-p1->x);
    double A = 1/k;
    double B = 1;
    double C = -perp_root->y - perp_root->x/k;
    
    points_on_line_with_radius(A, B, C, perp_root->x, perp_root->y, R, p_res_1, p_res_2);
}
