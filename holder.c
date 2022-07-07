// // Michael Gamston - edit 6/07/22************************************************************************************************************************** 
// /*motion dectection */ 
// #define CAMERA_MODEL_AI_THINKER
// /* includes */
// #include "esp_camera.h"
// #include "camera_pins.h"
// #include "sensor.h"
// #include "math.h"

// #define FRAME_SIZE FRAMESIZE_HVGA
// #define WIDTH 480
// #define HEIGHT 320
// #define BLOCK_SIZE 5
// #define W (WIDTH / BLOCK_SIZE)
// #define H (HEIGHT / BLOCK_SIZE)
// #define BLOCK_DIFF_THRESHOLD 0.2
// #define IMAGE_DIFF_THRESHOLD 0.1


// uint16_t prev_frame[H][W] = { 0 };
// uint16_t current_frame[H][W] = { 0 };


// bool setup_camera() {
//     camera_config_t config;

//     config.ledc_channel = LEDC_CHANNEL_0;
//     config.ledc_timer = LEDC_TIMER_0;
//     config.pin_d0 = Y2_GPIO_NUM;
//     config.pin_d1 = Y3_GPIO_NUM;
//     config.pin_d2 = Y4_GPIO_NUM;
//     config.pin_d3 = Y5_GPIO_NUM;
//     config.pin_d4 = Y6_GPIO_NUM;
//     config.pin_d5 = Y7_GPIO_NUM;
//     config.pin_d6 = Y8_GPIO_NUM;
//     config.pin_d7 = Y9_GPIO_NUM;
//     config.pin_xclk = XCLK_GPIO_NUM;
//     config.pin_pclk = PCLK_GPIO_NUM;
//     config.pin_vsync = VSYNC_GPIO_NUM;
//     config.pin_href = HREF_GPIO_NUM;
//     config.pin_sscb_sda = SIOD_GPIO_NUM;
//     config.pin_sscb_scl = SIOC_GPIO_NUM;
//     config.pin_pwdn = PWDN_GPIO_NUM;
//     config.pin_reset = RESET_GPIO_NUM;
//     config.xclk_freq_hz = 20000000;
//     config.pixel_format = PIXFORMAT_GRAYSCALE;
//     config.frame_size = FRAMESIZE_HVGA;
//     config.jpeg_quality = 12;
//     config.fb_count = 1;

//     bool ok = esp_camera_init(&config) == ESP_OK;

//     sensor_t *sensor = esp_camera_sensor_get();
//     sensor->set_framesize(sensor, FRAMESIZE_HVGA);

//     return ok;
// }


// bool capture_still() {
//     camera_fb_t *frame_buffer = esp_camera_fb_get();

//     if (!frame_buffer){
//         return false;
//     }

//     // set all 0s in current frame
//     for (int y = 0; y < H; y++){
//         for (int x = 0; x < W; x++){
//             current_frame[y][x] = 0;
//         }
//     }

//     // down-sample image in blocks
//     for (uint32_t i = 0; i < WIDTH * HEIGHT; i++) {
//         const uint16_t x = i % WIDTH;
//         const uint16_t y = floor(i / WIDTH);
//         const uint8_t block_x = floor(x / BLOCK_SIZE);
//         const uint8_t block_y = floor(y / BLOCK_SIZE);
//         const uint8_t pixel = frame_buffer->buf[i];
//         const uint16_t current = current_frame[block_y][block_x];

//         // average pixels in block (accumulate)
//         current_frame[block_y][block_x] += pixel;
//     }

//     // average pixels in block (rescale)
//     for (int y = 0; y < H; y++)
//         for (int x = 0; x < W; x++)
//             current_frame[y][x] /= BLOCK_SIZE * BLOCK_SIZE;

//     esp_camera_fb_return(frame_buffer);

//     return true;
// }

// bool motion_detect() {
//     uint16_t changes = 0;
//     const uint16_t blocks = (WIDTH * HEIGHT) / (BLOCK_SIZE * BLOCK_SIZE);

//     for (int y = 0; y < H; y++) {
//         for (int x = 0; x < W; x++) {
//             float current = current_frame[y][x];
//             float prev = prev_frame[y][x];
//             float delta = abs(current - prev) / prev;

//             if (delta >= BLOCK_DIFF_THRESHOLD) {
//                 changes += 1;
//             }
//         }
//     }

//     return (1.0 * changes / blocks) > IMAGE_DIFF_THRESHOLD;
// }

// void update_frame() {
//     for (int y = 0; y < H; y++) {
//         for (int x = 0; x < W; x++) {
//             prev_frame[y][x] = current_frame[y][x];
//         }
//     }
// }

// bool run_montion_detec(){

//     bool clause = false;
//     u8CubikControl_GPIO_Pin_ValueSet(12, CA_PIN_SET_ON);
//     if (!capture_still()) {
//         printf("capture_still failed");
//         SMT_Cubik_delay_function(3000);

//         return clause;
//     }

//     if (motion_detect()) {
//         printf("motion detected");
//         clause = true;
//     }
    
//     update_frame();
//     SMT_Cubik_delay_function(3000);
//     u8CubikControl_GPIO_Pin_ValueSet(12, CA_PIN_SET_OFF);
//     return clause;

// }



// /* Functions for motions dectection*/
// bool setup_camera(void);
// void cameraUpdate(void);
// bool capture_still(void);
// bool motion_detect(void);
// void update_frame(void);
// bool run_motion_detec(void);
