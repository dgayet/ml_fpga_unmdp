#include <iostream>

#include "myproject.h"
#include "parameters.h"

void myproject(
    input_t flatten_22_input[N_INPUT_1_1*N_INPUT_2_1],
    result_t layer8_out[N_LAYER_6]
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS ARRAY_RESHAPE variable=flatten_22_input complete dim=0
    #pragma HLS ARRAY_PARTITION variable=layer8_out complete dim=0
    #pragma HLS INTERFACE ap_vld port=flatten_22_input,layer8_out 
    #pragma HLS PIPELINE 

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        // hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<weight3_t, 3920>(w3, "w3.txt");
        nnet::load_weights_from_txt<bias3_t, 5>(b3, "b3.txt");
        nnet::load_weights_from_txt<weight6_t, 10>(w6, "w6.txt");
        nnet::load_weights_from_txt<bias6_t, 2>(b6, "b6.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    auto& layer2_out = flatten_22_input;
    layer3_t layer3_out[N_LAYER_3];
    #pragma HLS ARRAY_PARTITION variable=layer3_out complete dim=0
    nnet::dense<input_t, layer3_t, config3>(layer2_out, layer3_out, w3, b3); // fc3

    layer5_t layer5_out[N_LAYER_3];
    #pragma HLS ARRAY_PARTITION variable=layer5_out complete dim=0
    nnet::linear<layer3_t, layer5_t, linear_config5>(layer3_out, layer5_out); // relu3

    layer6_t layer6_out[N_LAYER_6];
    #pragma HLS ARRAY_PARTITION variable=layer6_out complete dim=0
    nnet::dense<layer5_t, layer6_t, config6>(layer5_out, layer6_out, w6, b6); // output

    nnet::softmax<layer6_t, result_t, softmax_config8>(layer6_out, layer8_out); // softmax

}
