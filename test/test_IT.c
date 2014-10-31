#include "unity.h"
#include "Common.h"
#include "DCT.h"
#include "IDCT.h"
#include "Normalization.h"
#include "Stream.h"
#include "ArrayIO.h"

#define TEST_ASSERT_EQUAL_MATRIX(expected, actual) \
  assert8by8Matrix(expected, actual, __LINE__);

void assert8by8Matrix(float expectedMatrix[][8], float actualMatrix[0][8], int line){
  int i, j;
  
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      TEST_ASSERT_FLOAT_WITHIN(0.5, expectedMatrix[i][j], actualMatrix[i][j]);
    }
  }
}

void setUp(void){}

void tearDown(void){}

void test_DCT_transform_array_of_3_elements_and_should_invert_back_to_original_by_IDCT(){
  float imageMatrix[3] = {1, 2, 3};
  
  oneD_DCT_row(imageMatrix, sizeof(imageMatrix)/sizeof(float));
  
  TEST_ASSERT_FLOAT_WITHIN(0.001, 3.464, imageMatrix[0]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, -1.414, imageMatrix[1]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[2]);
  
  oneD_IDCT_row(imageMatrix, 3);
  round_float(imageMatrix, 3);
  
  TEST_ASSERT_EQUAL(1,imageMatrix[0]);
  TEST_ASSERT_EQUAL(2,imageMatrix[1]);
  TEST_ASSERT_EQUAL(3,imageMatrix[2]);
}

void test_DCT_transform_array_of_8_elements_and_should_invert_back_to_original_by_IDCT(){
  float imageMatrix[8] = {1,2,3,4,5,6,7,8};

  oneD_DCT_row(imageMatrix, sizeof(imageMatrix)/sizeof(float));
  
  TEST_ASSERT_FLOAT_WITHIN(0.001, 12.727, imageMatrix[0]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, -6.442, imageMatrix[1]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[2]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, -0.673, imageMatrix[3]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[4]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, -0.200, imageMatrix[5]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[6]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, -0.050, imageMatrix[7]);
  
  oneD_IDCT_row(imageMatrix, 8);
  round_float(imageMatrix, 8);
  
  TEST_ASSERT_EQUAL(1,imageMatrix[0]);
  TEST_ASSERT_EQUAL(2,imageMatrix[1]);
  TEST_ASSERT_EQUAL(3,imageMatrix[2]);
  TEST_ASSERT_EQUAL(4,imageMatrix[3]);
  TEST_ASSERT_EQUAL(5,imageMatrix[4]);
  TEST_ASSERT_EQUAL(6,imageMatrix[5]);
  TEST_ASSERT_EQUAL(7,imageMatrix[6]);
  TEST_ASSERT_EQUAL(8,imageMatrix[7]);
}

void test_two_D_DCT_transform_array_of_3_elements_and_should_invert_back_to_original_by_IDCT(){
  float imageMatrix[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  int size = 3;
  
  twoD_DCT(size, imageMatrix);
  
  TEST_ASSERT_FLOAT_WITHIN(0.001, 5.999, imageMatrix[0][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, -2.449, imageMatrix[0][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[0][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[1][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[1][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[1][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[2][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[2][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, 0, imageMatrix[2][2]);
  
  twoD_IDCT(size, imageMatrix);
  
  TEST_ASSERT_EQUAL(1,imageMatrix[0][0]);
  TEST_ASSERT_EQUAL(1,imageMatrix[1][0]);
  TEST_ASSERT_EQUAL(1,imageMatrix[2][0]);
  TEST_ASSERT_EQUAL(2,imageMatrix[0][1]);
  TEST_ASSERT_EQUAL(2,imageMatrix[1][1]);
  TEST_ASSERT_EQUAL(2,imageMatrix[2][1]);
  TEST_ASSERT_EQUAL(3,imageMatrix[0][2]);
  TEST_ASSERT_EQUAL(3,imageMatrix[1][2]);
  TEST_ASSERT_EQUAL(3,imageMatrix[2][2]);
}

void test_two_D_DCT_transform_array_of_8_elements_and_should_invert_back_to_original_by_IDCT(){
  float imageMatrix[8][8] = {{1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8},
                             {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8},
                             {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}};
                             
  float expectMatrix[8][8] ={{1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8},
                             {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8},
                             {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}};
  
  int size = 8;
  int i, j;
  twoD_DCT(size, imageMatrix);
  
  twoD_IDCT(size, imageMatrix);
  
  TEST_ASSERT_EQUAL_MATRIX(expectMatrix, imageMatrix);
}

void test_two_D_DCT_transform_array_of_8_elements_and_should_invert_back_to_original_by_IDCT_case2(){
  float imageMatrix[8][8] = {{10, 22, 53, 44, 81, 53, 35, 102}, 
                             {35, 43, 11, 48, 0, 110, 120, 90}, 
                             {12, 68, 35, 44, 5, 64, 79, 88},
                             {11, 24, 35, 74, 59, 65, 47, 88}, 
                             {71, 52, 83, 54, 59, 61, 78, 88}, 
                             {31, 29, 73, 44, 51, 46, 7, 8},
                             {12, 23, 36, 48, 50, 16, 78, 98}, 
                             {17, 92, 33, 74, 95, 96, 97, 81}};

  float expectMatrix[8][8] ={{10, 22, 53, 44, 81, 53, 35, 102}, 
                             {35, 43, 11, 48, 0, 110, 120, 90}, 
                             {12, 68, 35, 44, 5, 64, 79, 88},
                             {11, 24, 35, 74, 59, 65, 47, 88}, 
                             {71, 52, 83, 54, 59, 61, 78, 88}, 
                             {31, 29, 73, 44, 51, 46, 7, 8},
                             {12, 23, 36, 48, 50, 16, 78, 98}, 
                             {17, 92, 33, 74, 95, 96, 97, 81}};
                             
  int size = 8;
  int i, j;
  
  twoD_DCT(size, imageMatrix);
  
  // dumpMatrix(size,imageMatrix);
  
  twoD_IDCT(size, imageMatrix);
  
  // dumpMatrix(size,imageMatrix);
  
  TEST_ASSERT_EQUAL_MATRIX(expectMatrix, imageMatrix);
}

void test_two_D_DCT_transform_array_of_8_elements_and_should_invert_back_to_original_by_IDCT_with_normalization(){
  float imageMatrix[8][8] = {{154, 123, 123, 123, 123, 123, 123, 136}, 
                             {192, 180, 136, 154, 154, 154, 136, 110}, 
                             {254, 198, 154, 154, 180, 154, 123, 123},
                             {239, 180, 136, 180, 180, 166, 123, 123}, 
                             {180, 154, 136, 167, 166, 149, 136, 136}, 
                             {128, 136, 123, 136, 154, 180, 198, 154},
                             {123, 105, 110, 149, 136, 136, 180, 166}, 
                             {110, 136, 123, 123, 123, 136, 154, 136}};
                             
  float expectMatrix[8][8] ={{154, 123, 123, 123, 123, 123, 123, 136}, 
                             {192, 180, 136, 154, 154, 154, 136, 110}, 
                             {254, 198, 154, 154, 180, 154, 123, 123},
                             {239, 180, 136, 180, 180, 166, 123, 123}, 
                             {180, 154, 136, 167, 166, 149, 136, 136}, 
                             {128, 136, 123, 136, 154, 180, 198, 154},
                             {123, 105, 110, 149, 136, 136, 180, 166}, 
                             {110, 136, 123, 123, 123, 136, 154, 136}};                            
                             
  int size = 8;
  int i, j;

  normalizeMatrix(size, imageMatrix);
  
  twoD_DCT(size, imageMatrix);
  
  // dumpMatrix(size,imageMatrix);
  // printf("\n");
  
  twoD_IDCT(size, imageMatrix);
  
  denormalizeMatrix(size, imageMatrix);
  
  // dumpMatrix(size, imageMatrix);
  
  TEST_ASSERT_EQUAL_MATRIX(expectMatrix, imageMatrix);
}

void test_release1_given_file_should_output_DCTed_matrix_into_output_file(){
  CEXCEPTION_T error;
  Stream *inStream = NULL;
  Stream *outStream = NULL;
  float inputMatrix[8][8];
  int size = 8, count = 0;
  
  Try{
    inStream = openStream("test/Data/Water lilies.7z.010", "rb");
    outStream = openStream("test/Data/Water lilies_RE1.7z.010", "wb");
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE, error);
  }
  
  while(count < 1){
    readBlock(inStream, size, inputMatrix);
    //printf("%.3f", inputMatrix[0][0]);
    normalizeMatrix(size, inputMatrix);
    twoD_DCT(size, inputMatrix);
    // printf("%.3f", inputMatrix[0][0]);
    // dumpMatrix(size, inputMatrix);
    writeBlock(outStream, size, inputMatrix);
    
    count++;
  }
  closeStream(inStream);
  closeStream(outStream);
  // printf("\n");
  Stream *inStream2 = NULL;
  Stream *outStream2 = NULL;
  count = 0;
  
  Try{
    inStream2 = openStream("test/Data/Water lilies_RE1.7z.010", "rb");
    outStream2 = openStream("test/Data/Water lilies_RE1Out.7z.010", "wb");
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE, error);
  }
  while(count < 1){
    readBlockWithConvert(inStream2, size, inputMatrix);
    // dumpMatrix(size, inputMatrix);
    
    twoD_IDCT(size, inputMatrix);
    denormalizeMatrix(size, inputMatrix);
    // dumpMatrix(size, inputMatrix);
    
    writeBlock(outStream2, size, inputMatrix);
    
    count++;
  }
  closeStream(inStream2);
  closeStream(outStream2);
}
