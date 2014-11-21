#include "unity.h"
#include "HuffmanCoding.h"
#include "Scan.h"
#include "dataType.h"
void setUp(void){}

void tearDown(void){}

void test_runLengthEncoding_to_encode_lengthy_value(void){
	int size = 10;
	int input[10] = {5,5,66,21,1,0,0,0,0,2};
	int output[20] = {0};
	runLengthEncoding(input,output,size);
	TEST_ASSERT_EQUAL(2,output[0]);
	TEST_ASSERT_EQUAL(5,output[1]);
	TEST_ASSERT_EQUAL(1,output[2]);
	TEST_ASSERT_EQUAL(66,output[3]);
	TEST_ASSERT_EQUAL(1,output[4]);
	TEST_ASSERT_EQUAL(21,output[5]);
	TEST_ASSERT_EQUAL(1,output[6]);
	TEST_ASSERT_EQUAL(1,output[7]);
	TEST_ASSERT_EQUAL(4,output[8]);
	TEST_ASSERT_EQUAL(0,output[9]);
	TEST_ASSERT_EQUAL(1,output[10]);
	TEST_ASSERT_EQUAL(2,output[11]);
}

void test_runLengthEncoding_to_encode_lengthy_value_case_2(void){
	int size = 10;
	int input[10] = {5,3,66,21,1,4,6,7,8,2};
	int output[20] = {0};
	runLengthEncoding(input,output,size);
	TEST_ASSERT_EQUAL(1,output[0]);
	TEST_ASSERT_EQUAL(5,output[1]);
	TEST_ASSERT_EQUAL(1,output[2]);
	TEST_ASSERT_EQUAL(3,output[3]);
	TEST_ASSERT_EQUAL(1,output[4]);
	TEST_ASSERT_EQUAL(66,output[5]);
	TEST_ASSERT_EQUAL(1,output[6]);
	TEST_ASSERT_EQUAL(21,output[7]);
	TEST_ASSERT_EQUAL(1,output[8]);
	TEST_ASSERT_EQUAL(1,output[9]);
	TEST_ASSERT_EQUAL(1,output[10]);
	TEST_ASSERT_EQUAL(4,output[11]);
	TEST_ASSERT_EQUAL(1,output[12]);
	TEST_ASSERT_EQUAL(6,output[13]);
	TEST_ASSERT_EQUAL(1,output[14]);
	TEST_ASSERT_EQUAL(7,output[15]);
	TEST_ASSERT_EQUAL(1,output[16]);
	TEST_ASSERT_EQUAL(8,output[17]);
	TEST_ASSERT_EQUAL(1,output[18]);
	TEST_ASSERT_EQUAL(2,output[19]);
}

void test_runLengthEncoding_to_encode_lengthy_value_case_3(void){
	int size = 10;
	int input[10] = {5,3,0,21,5,4,0,7,8,2};
	int output[20] = {0};
	runLengthEncoding(input,output,size);
	TEST_ASSERT_EQUAL(1,output[0]);
	TEST_ASSERT_EQUAL(5,output[1]);
	TEST_ASSERT_EQUAL(1,output[2]);
	TEST_ASSERT_EQUAL(3,output[3]);
	TEST_ASSERT_EQUAL(1,output[4]);
	TEST_ASSERT_EQUAL(0,output[5]);
	TEST_ASSERT_EQUAL(1,output[6]);
	TEST_ASSERT_EQUAL(21,output[7]);
	TEST_ASSERT_EQUAL(1,output[8]);
	TEST_ASSERT_EQUAL(5,output[9]);
	TEST_ASSERT_EQUAL(1,output[10]);
	TEST_ASSERT_EQUAL(4,output[11]);
	TEST_ASSERT_EQUAL(1,output[12]);
	TEST_ASSERT_EQUAL(0,output[13]);
	TEST_ASSERT_EQUAL(1,output[14]);
	TEST_ASSERT_EQUAL(7,output[15]);
	TEST_ASSERT_EQUAL(1,output[16]);
	TEST_ASSERT_EQUAL(8,output[17]);
	TEST_ASSERT_EQUAL(1,output[18]);
	TEST_ASSERT_EQUAL(2,output[19]);
}

void test_runLengthDecoding_to_decode_encode_value_into_original_value_and_sequence(void){
	int size = 12;
	int input[12] = {2,5,1,66,1,21,1,1,4,0,1,2};
	int output[20] = {0};
	runLengthDecoding(input,output,size);
	TEST_ASSERT_EQUAL(5,output[0]);
	TEST_ASSERT_EQUAL(5,output[1]);
	TEST_ASSERT_EQUAL(66,output[2]);
	TEST_ASSERT_EQUAL(21,output[3]);
	TEST_ASSERT_EQUAL(1,output[4]);
	TEST_ASSERT_EQUAL(0,output[5]);
	TEST_ASSERT_EQUAL(0,output[6]);
	TEST_ASSERT_EQUAL(0,output[7]);
	TEST_ASSERT_EQUAL(0,output[8]);
	TEST_ASSERT_EQUAL(2,output[9]);
}

void test_runLengthEncoder_should_return(){
	State progress = {.state = 1, .index = 0};
	int size = 8;
	short int dataIn[8][8] = {{160,  44,  20,  80,  24,   0,   0,   0},
							{ 36, 108,  14,  38,  26,   0,   0,   0},
							{-98, -65,  16, -48, -40,   0,   0,   0},
							{-42, -85,   0, -29,   0,   0,   0,   0},
							{-36,  22,   0,   0,   0,   0,   0,   0}, 
							{  0,   0,   0,   0,   0,   0,   0,   0},
							{  0,   0,   0,   5,   0,   0,   0,   0},
							{  1,   0,   0,   0,   0,   0,   0,   1}};
	
	runLengthEncode(size, dataIn, &progress);
}

/* 
void test_runLengthEncoding2(){
	scanTable table = {.row = 0, .column = 0, .col_limit = 2, .stage = 0};
	int size = 8;
	int dataOut[128];
	int dataIn[8][8] = {{160,  44,  20,  80,  24,   0,   0,   0},
                        { 36, 108,  14,  38,  26,   0,   0,   0},
                        {-98, -65,  16, -48, -40,   0,   0,   0},
                        {-42, -85,   0, -29,   0,   0,   0,   0},
                        {-36,  22,   0,   0,   0,   0,   0,   0}, 
                        {  0,   0,   0,   0,   0,   0,   0,   0},
                        {  0,   0,   0,   5,   0,   0,   0,   0},
                        {  1,   0,   0,   0,   0,   0,   0,   1}};
						
	runLengthEncoding2(size, dataOut, dataIn, &table);
}

void test_runLengthDecoding2(){
	scanTable table = {.row = 0, .column = 0, .col_limit = 2, .firstStage = 0, .secondStage = 0, .thirdStage = 0, .finalStage = 0};
	int size = 8;
	int dataIn[24] = {1,2,3,4,0,5,0,6,0,99,0,11,0,12,0,13,0,87,0,15,19,56,29,5};
	int dataOut[8][8];
	runLengthDecoding2(size, dataIn, dataOut, &table);
}
*/