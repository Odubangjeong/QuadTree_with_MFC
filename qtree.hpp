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

// ��� �ʱ�ȭ �� �� ����
void add_values(cv::Mat* img, qt_node* q, int* p, BGR* value, int num_rows, int num_cols);

// get averge value of each pixel's BGR
void get_meanColor(cv::Mat* modified, int* pixels);

// node ������
void split_qt_node(qt_node* q);

// node ǥ������ ���
float get_node_deviation(qt_node* q);

// �־��� ��� �÷��� ���� ����� ��� ���(�̻��)
BGR find_cloestElements(qt_node* q, float avg);

// ����� ��� �÷� ���(BGR)
BGR get_avg_color(qt_node* q);

// ��� �� �ȼ����� ��� �� ���
float get_avg_pxvalue(qt_node* q);

// �ȼ����� �л� ���
float get_pixel_variance(qt_node* q);

// quad tree ����
void build_tree(qt_node* start, int max_var, int min_block_size);

// quad tree Mat���� ����
void unpack_tree(qt_node* start, int* unpacked, int total_rows, int total_cols);

// quad tree Mat���� ����
void unpack_tree(qt_node* start, cv::Mat& modified, int total_rows, int total_cols);

// node �� ī��Ʈ
int count_tree_nodes(qt_node* start);

// �ȼ� �� ī��Ʈ
int check_num_pixels(qt_node* start);

// MSE ���
double cal_MSE(cv::Mat* original, cv::Mat* modified);

// PSNR ���
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