#ifndef IMAGE_OPENCV_H
#define IMAGE_OPENCV_H

#include "image.h"
#include "matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OPENCV

// declaration
typedef struct mat_cv mat_cv;
typedef struct cap_cv cap_cv;
typedef struct write_cv write_cv;

// cv::Mat / IplImage
image load_image_cv(char *filename, int channels);
mat_cv *load_image_mat_cv(const char *filename, int flag);
image load_image_resize(char *filename, int w, int h, int c, image *im);
int get_width_cv(mat_cv *ipl);
int get_height_cv(mat_cv *ipl);
void release_ipl(mat_cv **ipl);

// image-to-ipl, ipl-to-image
mat_cv *image_to_ipl(image im);
image ipl_to_image_custom(mat_cv* src);
// Mat image_to_mat(image im);
// image mat_to_image(Mat m)

// Window
void create_window_cv(char const* window_name, int full_screen, int width, int height);
void destroy_all_windows_cv();
int wait_key_cv(int delay);
int wait_until_press_key_cv();
void make_window(char *name, int w, int h, int fullscreen);
void show_image_cv(image p, const char *name);
void show_image_cv_ipl(mat_cv *disp, const char *name);

// Video Writer
write_cv *create_video_writer(char *out_filename, char c1, char c2, char c3, char c4, int fps, int width, int height, int is_color);
int write_frame_cv(write_cv *output_video_writer, mat_cv *show_img);
void release_video_writer(write_cv **output_video_writer);


//void *open_video_stream(const char *f, int c, int w, int h, int fps);
//image get_image_from_stream(void *p);
//image load_image_cv(char *filename, int channels);
//int show_image_cv(image im, const char* name, int ms);

// Video Capture
cap_cv* get_capture_video_stream(const char *path);
cap_cv* get_capture_webcam(int index);
void release_capture(cap_cv* cap);

mat_cv* get_capture_frame_cv(cap_cv *cap);
int get_stream_fps_cpp_cv(cap_cv *cap);
double get_capture_property_cv(cap_cv *cap, int property_id);
double get_capture_frame_count_cv(cap_cv *cap);
int set_capture_property_cv(cap_cv *cap, int property_id, double value);
int set_capture_position_frame_cv(cap_cv *cap, int index);

// ... Video Capture
image get_image_from_stream(cap_cv *cap);
image get_image_from_stream_cpp(cap_cv *cap);
image get_image_from_stream_resize(cap_cv *cap, int w, int h, int c, mat_cv** in_img, int cpp_video_capture, int dont_close);
image get_image_from_stream_letterbox(cap_cv *cap, int w, int h, int c, mat_cv** in_img, int cpp_video_capture, int dont_close);
int get_stream_fps(cap_cv *cap, int cpp_video_capture);


// Image Saving
void save_cv_png(mat_cv *img, const char *name);
void save_cv_jpg(mat_cv *img, const char *name);

// Draw Detection
void draw_detections_cv_v3(mat_cv* show_img, detection *dets, int num, float thresh, char **names, image **alphabet, int classes, int ext_output);
void draw_detections_cv(mat_cv* show_img, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes);

// Draw Loss & Accuracy chart
mat_cv* draw_train_chart(float max_img_loss, int max_batches, int number_of_lines, int img_size, int dont_show);
void draw_train_loss(mat_cv* img, int img_size, float avg_loss, float max_img_loss, int current_batch, int max_batches,
    float precision, int draw_precision, char *accuracy_name, int dont_show, int mjpeg_port);

// Data augmentation
image image_data_augmentation(mat_cv* ipl, int w, int h,
    int pleft, int ptop, int swidth, int sheight, int flip,
    float jitter, float dhue, float dsat, float dexp);

// Show Anchors
void show_acnhors(int number_of_boxes, int num_of_clusters, float *rel_width_height_array, model anchors_data, int width, int height);

#else

static int wait_key_cv(int delay) { return 0; }
static int wait_until_press_key_cv() { return 0; }
static void destroy_all_windows_cv() {}

#endif  // OPENCV

#ifdef __cplusplus
}
#endif

#endif // IMAGE_OPENCV_H