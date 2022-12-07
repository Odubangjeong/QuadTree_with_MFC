#pragma once
#ifndef qtree_hpp
#define qtree_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <opencv2/opencv.hpp>
#include <fstream>

#endif /* qtree_hpp */

#ifndef MAX_DIM
#define MAX_DIM 8192 


using namespace std;

typedef struct BGR {
    unsigned char B;
    unsigned char G;
    unsigned char R;
};


struct qt_node {
    bool is_leaf;
    // int pixel_value;
     // BGR : color info
    BGR* pixel_value;

    // represent color of this node
    BGR represent;

    // average of BGR
    int* p;

    // number of rows / cols of this node
    int prows;
    int pcols;



    //what parts of the image this node represents
    int r_min;
    int r_max;
    int c_min;
    int c_max;

    //pixel value deviation in the node
    int deviation;

    qt_node* NW;
    qt_node* NE;
    qt_node* SE;
    qt_node* SW;


};


// creates a qt_node
qt_node* init_node();

// 노드 초기화 후 값 저장
void add_values(cv::Mat* img, qt_node* q, int* p, BGR* value, int num_rows, int num_cols);

// get averge value of each pixel's BGR
void get_meanColor(cv::Mat* modified, int* pixels);

// node 나누기
void split_qt_node(qt_node* q);

// node 표준편차 계산
float get_node_deviation(qt_node* q);

// 주어진 평균 컬러에 제일 가까운 노드 계산(미사용)
BGR find_cloestElements(qt_node* q, float avg);

// 노드의 평균 컬러 계산(BGR)
BGR get_avg_color(qt_node* q);

// 노드 내 픽셀들의 평균 값 계산
float get_avg_pxvalue(qt_node* q);

// 픽셀들의 분산 계산
float get_pixel_variance(qt_node* q);

// quad tree 생성
void build_tree(qt_node* start, int max_var, int min_block_size);

// quad tree Mat으로 복원
void unpack_tree(qt_node* start, int* unpacked, int total_rows, int total_cols);

// quad tree Mat으로 복원
void unpack_tree(qt_node* start, cv::Mat& modified, int total_rows, int total_cols);

// node 수 카운트
int count_tree_nodes(qt_node* start);

// 픽셀 수 카운트
int check_num_pixels(qt_node* start);

// MSE 계산
double cal_MSE(cv::Mat* original, cv::Mat* modified);

// PSNR 계산
double cal_PSNR(double mse, double MAXi = 255);


class qt_tree {
public:
    cv::String filename;
    cv::Mat original;
    cv::Mat modified;

    qt_node* q;

    double MSE;
    double PSNR;

    int target_deviation;
    int min_pixel_size;

    int origin_rows;
    int origin_cols;

    int* pixels;
    BGR* values;

    string buffer;
    unsigned long fileByte;
public:
    qt_tree();

    qt_tree(cv::String name, int target, int min_pixel);

public:
    void explore_tree(qt_node* start, ofstream& file, int total_rows, int total_cols);
    void make_quadTree(cv::String name, int target, int min_pixel);
    void fileopen(cv::String name);
    void make_bitStream_file(qt_node* start, string filename, unsigned short total_rows, unsigned short total_cols);
};
#endif