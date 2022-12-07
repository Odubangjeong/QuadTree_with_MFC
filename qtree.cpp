#include "pch.h"
#include "qtree.hpp"
#include "bitset"

//creates a qt_node
qt_node* init_node() {
    qt_node* newQTNode = new qt_node;
    newQTNode->is_leaf = false; //change this?
    newQTNode->r_min = NULL;
    newQTNode->r_max = NULL;
    newQTNode->c_min = NULL;
    newQTNode->r_max = NULL;
    newQTNode->deviation = NULL;
    newQTNode->NW = NULL;
    newQTNode->NE = NULL;
    newQTNode->SW = NULL;
    newQTNode->SE = NULL;
    //    newQTNode->pixel_value = NULL;
    return newQTNode;
}

//adds pixel values, r_min/max, c_min/max
void add_values(cv::Mat* img, qt_node* q, int* p, BGR* value, int num_rows, int num_cols) {
    // BGR 평균값 저장
    // TODO: 픽셀 컬러 데이터 가져오기
    // unsigned char* pixels = new unsigned char[num_rows * num_cols * 3];
    q->pixel_value = value;
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            cv::Vec3b& color = img->at<cv::Vec3b>(r, c);
            //    unsigned char tb = color[0];
            q->pixel_value[r * num_cols + c].B = color[0];
            q->pixel_value[r * num_cols + c].G = color[1];
            q->pixel_value[r * num_cols + c].R = color[2];
        }
    }

    q->p = p;
    q->prows = num_rows;
    q->pcols = num_cols;
    q->r_min = 0;
    q->r_max = num_rows - 1;
    q->c_min = 0;
    q->c_max = num_cols - 1;
}

// get averge value of each pixel's BGR
void get_meanColor(cv::Mat* modified, int* pixels) {
    int rows = modified->rows;
    int cols = modified->cols;
    //int* pixels = new int[rows * cols];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cv::Vec3b& color = modified->at <cv::Vec3b>(r, c);
            pixels[r * cols + c] = color[0];
            pixels[r * cols + c] += color[1];
            pixels[r * cols + c] += color[2];
            pixels[r * cols + c] /= 3;
            //  std::cout << pixels[r * cols + c] << std::endl;
        }
    }
    //return pixels;
}


void split_qt_node(qt_node* q) {

    int qRMin = q->r_min;
    int qRMax = q->r_max;
    int qCMin = q->c_min;
    int qCMax = q->c_max;

    bool noSouth = (qRMin == qRMax);
    bool noEast = (qCMin == qCMax);

    q->NW = init_node();
    q->NW->p = q->p;
    q->NW->pixel_value = q->pixel_value;
    q->NW->prows = q->prows;
    q->NW->pcols = q->pcols;
    q->NW->r_min = qRMin;
    q->NW->r_max = (qRMax + qRMin) / 2;
    q->NW->c_min = qCMin;
    q->NW->c_max = (qCMax + qCMin) / 2;

    if (!noEast) {
        q->NE = init_node();
        q->NE->p = q->p;
        q->NE->pixel_value = q->pixel_value;
        q->NE->prows = q->prows;
        q->NE->pcols = q->pcols;
        q->NE->r_min = qRMin;
        q->NE->r_max = (qRMax + qRMin) / 2;
        q->NE->c_min = (qCMax + qCMin) / 2 + 1;
        q->NE->c_max = qCMax;
    }


    if (!noSouth) {
        q->SW = init_node();
        q->SW->p = q->p;
        q->SW->pixel_value = q->pixel_value;
        q->SW->prows = q->prows;
        q->SW->pcols = q->pcols;
        q->SW->r_min = (qRMax + qRMin) / 2 + 1;
        q->SW->r_max = qRMax;
        q->SW->c_min = qCMin;
        q->SW->c_max = (qCMax + qCMin) / 2;
    }

    if (!noEast && !noSouth) {
        q->SE = init_node();
        q->SE->p = q->p;
        q->SE->pixel_value = q->pixel_value;
        q->SE->prows = q->prows;
        q->SE->pcols = q->pcols;
        q->SE->r_min = (qRMax + qRMin) / 2 + 1;
        q->SE->r_max = qRMax;
        q->SE->c_min = (qCMax + qCMin) / 2 + 1;
        q->SE->c_max = qCMax;
    }


}

// 주어진 픽셀들에게서 가장 평균에 가까운 BGR 값 추출
BGR find_cloestElements(qt_node* q, float avg) {
    // p 배열에서 가장 가까운 값을 찾아 BGR 값으로 반환
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int pcols = q->pcols;
    BGR color = { 0, 0, 0 };
    int cloest_distance = 999;
    unsigned distance = 999;
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            distance = fabs(avg - q->p[r * pcols + c]);
            if (distance < cloest_distance) {
                cloest_distance = distance;
                color.B = q->pixel_value[r * pcols + c].B;
                color.G = q->pixel_value[r * pcols + c].G;
                color.R = q->pixel_value[r * pcols + c].R;
            }
        }
    }
    return color;
}

BGR get_avg_color(qt_node* q) {

    unsigned long B = 0, G = 0, R = 0;
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int pcols = q->pcols;
    int prows = q->prows;
    int pixel_number = (r_max - r_min + 1) * (c_max - c_min + 1);
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            B += q->pixel_value[r * pcols + c].B;
            G += q->pixel_value[r * pcols + c].G;
            R += q->pixel_value[r * pcols + c].R;
        }
    }
    B /= pixel_number;
    G /= pixel_number;
    R /= pixel_number;
    BGR avg = { B, G, R };
    return avg;
}

float get_avg_pxvalue(qt_node* q) {
    float total = 0;
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int total_cells = (r_max - r_min + 1) * (c_max - c_min + 1);
    int pcols = q->pcols;
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            total += q->p[r * pcols + c];
        }
    }
    float average = float(total) / float(total_cells);
    return average;
}

float get_node_deviation(qt_node* q) {
    float average = get_avg_pxvalue(q);

    float total_dev = 0;
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int total_cells = (r_max - r_min + 1) * (c_max - c_min + 1);
    int pcols = q->pcols;
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            total_dev += (average - q->p[r * pcols + c]) * (average - q->p[r * pcols + c]);
        }
    }
    float dev = total_dev / total_cells;
    dev = sqrt(dev);
    return dev;
}

float get_pixel_variance(qt_node* q) {
    float average = get_avg_pxvalue(q);

    float total_dev = 0;
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int total_cells = (r_max - r_min + 1) * (c_max - c_min + 1);
    int pcols = q->pcols;
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            total_dev += (average - q->p[r * pcols + c]) * (average - q->p[r * pcols + c]);
        }
    }
    float dev = total_dev / total_cells;
    return dev;
}

// builds the quad-tree based on the specified Tsigma(standard deviation)
// splits starting node and successive nodes into child nodes
void build_tree(qt_node* start, int dev_th, int min_block_size = 1) {
    if (start == NULL) { //NEW
        return;
    }
    // calculate standard deviation
    float dev = get_node_deviation(start);
    
    unsigned long size = ((unsigned long long int)start->r_max - (unsigned long long int)start->r_min) * ((unsigned long long int)start->c_max - (unsigned long long int)start->c_min);
    // int min_block_size_square = pow(min_block_size, 2);
    // if bigger than standard deviation, split it
    if (dev > dev_th && size >= min_block_size*4) {
        split_qt_node(start);
        build_tree(start->NW, dev_th, min_block_size);
        build_tree(start->NE, dev_th, min_block_size);
        build_tree(start->SW, dev_th, min_block_size);
        build_tree(start->SE, dev_th, min_block_size);
    }
    // else: 대표 BGR 값 설정
    else {
        float avg = get_avg_pxvalue(start);
        //  start->represent = find_cloestElements(start, avg);
        start->represent = get_avg_color(start);
        //   start->pixel_value = avg;
        //   start->represent = avg;
        start->is_leaf = true;
    }
}


//Unpacks the tree data 
void unpack_tree(qt_node* start, cv::Mat& modified, int total_rows, int total_cols) {
    if (start == NULL) { //NEW
        return;
    }

    //base case
    if (start->is_leaf) {
        int r_min = start->r_min;
        int r_max = start->r_max;
        int c_min = start->c_min;
        int c_max = start->c_max;

        BGR pixel_value = start->represent;
        for (int r = r_min; r <= r_max; r++) {
            for (int c = c_min; c <= c_max; c++) {
                //   modified.at<uint8_t>(r, c) = pixel_value;
                cv::Vec3b& intensity = modified.at<cv::Vec3b>(r, c);
                intensity.val[0] = pixel_value.B;
                intensity.val[1] = pixel_value.G;
                intensity.val[2] = pixel_value.R;
            }
        }
    }
    else {
        unpack_tree(start->NW, modified, total_rows, total_cols);
        unpack_tree(start->NE, modified, total_rows, total_cols);
        unpack_tree(start->SW, modified, total_rows, total_cols);
        unpack_tree(start->SE, modified, total_rows, total_cols);
    }
}

//counts leaf nodes of an already built tree
//can be a proxy for the number of pixel representations
int count_tree_nodes(qt_node* start) {
    if (start == NULL) {
        return 0;
    }
    if (start->is_leaf) {
        return 1;
    }
    else {
        return count_tree_nodes(start->NW) + count_tree_nodes(start->NE) + count_tree_nodes(start->SW) + count_tree_nodes(start->SE);
    }
}


//Counts the number of pixels used
//Just for checking, should be equal to the image's rows * cols
int check_num_pixels(qt_node* start) {
    if (start == NULL) {
        return 0;
    }
    if (start->is_leaf) {
        int size = (start->r_max - start->r_min + 1) * (start->c_max - start->c_min + 1);
        return size;
    }
    else {
        return check_num_pixels(start->NW) + check_num_pixels(start->NE) + check_num_pixels(start->SW) + check_num_pixels(start->SE);
    }
}


void make_bitStream(qt_node* start) {

}

double cal_MSE(cv::Mat* original, cv::Mat* modified) {
    int rows = modified->rows;
    int cols = modified->cols;
    unsigned int N = rows * cols;
    double val_true, val_mod;
    double MSE = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cv::Vec3b& color_origin = original->at <cv::Vec3b>(r, c);
            cv::Vec3b& color_mod = modified->at <cv::Vec3b>(r, c);
            val_true = (color_origin[0] + color_origin[1] + color_origin[2]) / 3;
            val_mod = (color_mod[0] + color_mod[1] + color_mod[2]) / 3;
            MSE += pow((val_true - val_mod), 2);
        }
    }
    MSE /= N;
    return MSE;
}

double cal_PSNR(double mse, double MAXi) {
    double PSNR = 0;
    PSNR = 10 * log10(pow(MAXi, 2) / mse);
    return PSNR;
}

void qt_tree::explore_tree(qt_node* start, ofstream& file, int total_rows, int total_cols) {
    if (start == NULL) { //NEW
        return;
    }
    if (start->is_leaf) {
        int r_min = start->r_min;
        int r_max = start->r_max;
        int c_min = start->c_min;
        int c_max = start->c_max;


        // 비트 하나 넣는다
        buffer += '1';

        std::string strB = std::bitset<8>(start->represent.B).to_string();
        std::string strG = std::bitset<8>(start->represent.G).to_string();
        std::string strR = std::bitset<8>(start->represent.R).to_string();
        buffer += strB;
        buffer += strG;
        buffer += strR;
       
    }
    else {
        buffer += '0';
        explore_tree(start->NW, file, total_rows, total_cols);
        explore_tree(start->NE, file, total_rows, total_cols);
        explore_tree(start->SW, file, total_rows, total_cols);
        explore_tree(start->SE, file, total_rows, total_cols);
    }
}

void qt_tree::make_bitStream_file(qt_node* start, string filename, unsigned short total_rows, unsigned short total_cols) {
    if (start == NULL) { //NEW
        return;
    }
    buffer = char("0");

    filename += ".KQ";
    ofstream myfile(filename, ios::out | ios::app | ios::binary);
    // ofstream myfile(filename, ios::out | ios::app);
    if (myfile.is_open() != 1) return;
    myfile << "KQ";
    myfile << total_cols << total_rows;

    // get buffer
    explore_tree(start, myfile, total_rows, total_cols);
    
    // 8개씩 계산
    unsigned long size = buffer.size();
    unsigned char _8bit = 0;
    int modul = size % 8;
    int i = 0;
    int j = 0;
    for (i = 0; i < size / 8; i++) {
        _8bit = 0;
        for (j = 0; j < 8; j++) {
            if (buffer[(unsigned long long int)i * 8 + j] == '0') _8bit = _8bit << 1;
            else {
                _8bit = (_8bit << 1) | 1;
            }
        }
        myfile << _8bit;
    }
    for (i = 0; i < modul; i++) {
        _8bit = 0;
        if (buffer[(unsigned long long int)i * 8 + j] == '0') _8bit = _8bit << 1;
        else {
            _8bit = (_8bit << 1) | 1;
        }
    }
    myfile << _8bit;
    fileByte = buffer.length();
    myfile.close();
}


qt_tree::qt_tree(void) {
    MSE = 0;
    PSNR = 0;
    target_deviation = NULL;
    min_pixel_size = NULL;
    origin_rows = NULL;
    origin_cols = NULL;

    q = NULL;
    pixels = NULL;
    values = NULL;
}

qt_tree::qt_tree(cv::String name, int target, int min_pixel) {
    filename = name;
    target_deviation = target;
    min_pixel_size = min_pixel;
    original = cv::imread(filename);
    modified = original.clone();
    q = init_node();

    origin_rows = original.rows;
    origin_cols = original.cols;

    pixels = new int[(unsigned long long int)origin_rows * (unsigned long long int)origin_cols];
    values = new BGR[(unsigned long long int)origin_rows * (unsigned long long int)origin_cols];

    get_meanColor(&modified, pixels);
    add_values(&original, q, pixels, values, origin_rows, origin_cols);

    build_tree(q, target_deviation, min_pixel_size);
    unpack_tree(q, modified, origin_rows, origin_cols);
    MSE = cal_MSE(&original, &modified);
    PSNR = cal_PSNR(MSE);

    delete[] pixels;
    delete[] values;
    make_bitStream_file(q, filename, origin_rows, origin_cols);
}

void qt_tree::make_quadTree(cv::String name, int target, int min_pixel) {
    filename = name;
    target_deviation = target;
    min_pixel_size = min_pixel;
    original = cv::imread(filename);
    modified = original.clone();
    q = init_node();

    origin_rows = original.rows;
    origin_cols = original.cols;

    pixels = new int[(unsigned long long int)origin_rows * (unsigned long long int)origin_cols];
    values = new BGR[(unsigned long long int)origin_rows * (unsigned long long int)origin_cols];

    get_meanColor(&modified, pixels);
    add_values(&original, q, pixels, values, origin_rows, origin_cols);

    build_tree(q, target_deviation, min_pixel_size);
    unpack_tree(q, modified, origin_rows, origin_cols);
    MSE = cal_MSE(&original, &modified);
    PSNR = cal_PSNR(MSE);

    delete[] pixels;
    delete[] values;
    make_bitStream_file(q, filename, origin_rows, origin_cols);
}

void qt_tree::fileopen(cv::String name) {
    filename = name;
    original = cv::imread(filename);
    origin_rows = original.rows;
    origin_cols = original.cols;
}

