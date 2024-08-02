/*
 *  transposeTest.h
 *
 *  Copyright (C) 2024
 *  Author: Simon (dewen.wu@gmail.com)
 *
 */

#pragma once

#include <stdint.h>
#include <string.h>
#include <time.h>

#include <chrono>
#include <iostream>

#include "testSuite.h"

class transposeTest : public TestCase {
 private:
  // the row size of matrix
  int _nrow = 0;
  // the column size of matrix
  int _ncol = 0;
  // source data before transpose
  uint8_t* _pSrc = nullptr;
  // real destination data after transpose
  uint8_t* _pDst = nullptr;
  // expected destination data after transpose
  uint8_t* _pDstExpect = nullptr;
  // how many rounds of test for correctness verification
  int _repeatCorrect = 10;
  // how many rounds of test for time performance statistics
  int _repeatTime = 1000;
  // how many rounds of test for warmup before time performance test
  int _warmup = 100;

 public:
  transposeTest() = default;

  transposeTest(int nrow, int ncol, int repeatTime = 1000, int warmup = 100) {
    init(nrow, ncol, repeatTime, warmup);
  };

  // initialize configuration parameters
  void init(int nrow, int ncol, int repeatTime = 1000, int warmup = 100) {
    _nrow       = nrow;
    _ncol       = ncol;
    _repeatTime = repeatTime;
    _warmup     = warmup;
    _pSrc       = new uint8_t[_nrow * _ncol];
    _pDst       = new uint8_t[_nrow * _ncol];
    _pDstExpect = new uint8_t[_nrow * _ncol];
    srand((unsigned)time(NULL));

    print();
    return;
  }

  // print configuration parameters
  void print() const {
    LOGI(
        "nrow = %d, ncol = %d, repeatCorrect = %d, repeatTime = %d, warmup = "
        "%d",
        _nrow, _ncol, _repeatCorrect, _repeatTime, _warmup);
  }

  // generate random source data
  void genRandomSrcData(int min, int max) {
    for (int irow = 0; irow < _nrow; ++irow) {
      for (int icol = 0; icol < _ncol; ++icol) {
        *(_pSrc + irow * _ncol + icol) =
            (uint8_t)(rand() % (max - min + 1) + min);
      }
    }
    return;
  }

  /* naive transpose, baseline
   * dst[icol][irow] = src[irow][icol],
   * source data is read consecutively,
   * destination data is written non-consecutively */
  inline void naiveTranspose() {
    for (int irow = 0; irow < _nrow; ++irow) {
      for (int icol = 0; icol < _ncol; ++icol) {
        *(_pDstExpect + icol * _nrow + irow) = *(_pSrc + irow * _ncol + icol);
      }
    }
    return;
  }

  /* naive transpose + restirct */
  inline void restricTranspose() {
    const uint8_t* const __restrict pSrc = _pSrc;
    uint8_t* const __restrict pDst       = _pDst;

    for (int irow = 0; irow < _nrow; ++irow) {
      for (int icol = 0; icol < _ncol; ++icol) {
        *(pDst + icol * _nrow + irow) = *(pSrc + irow * _ncol + icol);
      }
    }
    return;
  }

  /* naive transpose + loop tiling */
  inline void tileTranspose(int tilesize) {
    int nbR = _nrow / tilesize;
    int nbC = _ncol / tilesize;
    // LOGI("tilesize = %d, nbR = %d, nbC = %d", tilesize, nbR, nbC);

    for (int ibr = 0; ibr < nbR; ++ibr) {
      for (int ibc = 0; ibc < nbC; ++ibc) {
        for (int irow = 0; irow < tilesize; ++irow) {
          for (int icol = 0; icol < tilesize; ++icol) {
            *(_pDst + (ibc * tilesize + icol) * _nrow + ibr * tilesize + irow) =
                *(_pSrc + (ibr * tilesize + irow) * _ncol + ibc * tilesize +
                  icol);
          }
        }
      }
    }
    return;
  }

  /* naive transpose + openmp */
  inline void ompTranspose(int threadNum) {
#pragma omp parallel for num_threads(threadNum) schedule(dynamic)
    for (int irow = 0; irow < _nrow; ++irow) {
      for (int icol = 0; icol < _ncol; ++icol) {
        *(_pDst + icol * _nrow + irow) = *(_pSrc + irow * _ncol + icol);
      }
    }
    return;
  }

  /* optimize by changing the pattern of read and write,
   * dst[irow][icol] = src[icol][irow],
   * source data is read non-consecutively,
   * destination data is written consecutively */
  inline void writeConsecutiveTranspose() {
    for (int irow = 0; irow < _nrow; ++irow) {
      for (int icol = 0; icol < _ncol; ++icol) {
        *(_pDst + irow * _ncol + icol) = *(_pSrc + icol * _nrow + irow);
      }
    }
    return;
  }

  /* optimize by using restrict keyword,
   * source data is read non-consecutively,
   * destination data is written consecutively */
  inline void writeConsecutiveRestrictTranspose() {
    const uint8_t* const __restrict pSrc = _pSrc;
    uint8_t* const __restrict pDst       = _pDst;

    for (int irow = 0; irow < _nrow; ++irow) {
      for (int icol = 0; icol < _ncol; ++icol) {
        *(pDst + irow * _ncol + icol) = *(pSrc + icol * _nrow + irow);
      }
    }
    return;
  }

  /* optimize by using loop tiling and restrict keyword,
   * source data is read non-consecutively,
   * destination data is written consecutively */
  inline void writeConsecutiveRestrictTileTranspose(int tilesize) {
    const uint8_t* const __restrict pSrc = _pSrc;
    uint8_t* const __restrict pDst       = _pDst;

    int nbR                              = _nrow / tilesize;
    int nbC                              = _ncol / tilesize;
    // LOGI("tilesize = %d, nbR = %d, nbC = %d", tilesize, nbR, nbC);

    for (int ibr = 0; ibr < nbR; ++ibr) {
      for (int ibc = 0; ibc < nbC; ++ibc) {
        for (int irow = 0; irow < tilesize; ++irow) {
          for (int icol = 0; icol < tilesize; ++icol) {
            *(pDst + (ibr * tilesize + irow) * _ncol + ibc * tilesize + icol) =
                *(pSrc + (ibc * tilesize + icol) * _nrow + ibr * tilesize +
                  irow);
          }
        }
      }
    }
    return;
  }

  /* optimize by using multithreading, loop tiling and restrict keyword,
   * source data is read non-consecutively,
   * destination data is written consecutively */
  inline void writeConsecutiveRestrictTileOmpTranspose(int tilesize,
                                                       int threadnum) {
    const uint8_t* const __restrict pSrc = _pSrc;
    uint8_t* const __restrict pDst       = _pDst;

    int nbR                              = _nrow / tilesize;
    int nbC                              = _ncol / tilesize;
    // LOGI("tilesize = %d, nbR = %d, nbC = %d", tilesize, nbR, nbC);

#pragma omp parallel for num_threads(threadnum) schedule(dynamic)
    for (int ibr = 0; ibr < nbR; ++ibr) {
      for (int ibc = 0; ibc < nbC; ++ibc) {
        for (int irow = 0; irow < tilesize; ++irow) {
          for (int icol = 0; icol < tilesize; ++icol) {
            *(pDst + (ibr * tilesize + irow) * _ncol + ibc * tilesize + icol) =
                *(pSrc + (ibc * tilesize + icol) * _nrow + ibr * tilesize +
                  irow);
          }
        }
      }
    }
    return;
  }

  // compare real data with expected data
  // return: true indicates match, false indicates mismatch
  bool compare() const {
    if (memcmp(_pDst, _pDstExpect, _nrow * _ncol)) {
      return false;
    }

    return true;
  }

  // baseline test as a reference, naive transpose
  bool testBaselineTranspose(int nrow, int ncol, int repeatTime = 1000,
                             int warmup = 100) {
    init(nrow, ncol, repeatTime, warmup);
    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      naiveTranspose();
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      naiveTranspose();
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, restrict */
  bool testRestrictTranspose(int nrow, int ncol, int repeatTime = 1000,
                             int warmup = 100) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      restricTranspose();
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      restricTranspose();
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      restricTranspose();
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, loop tiling */
  bool testTitleTranspose(int nrow, int ncol, int repeatTime = 1000,
                          int warmup = 100, int tilesize = 64) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      tileTranspose(tilesize);
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
        break;
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      tileTranspose(tilesize);
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      tileTranspose(tilesize);
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, openmp */
  bool testOmpTranspose(int nrow, int ncol, int repeatTime = 1000,
                        int warmup = 100, int threadNum = 3) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      ompTranspose(threadNum);
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
        break;
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      ompTranspose(threadNum);
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      ompTranspose(threadNum);
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, read non-consecutively, write consecutively */
  bool testWriteConsecutiveTranspose(int nrow, int ncol, int repeatTime = 1000,
                                     int warmup = 100) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      writeConsecutiveTranspose();
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
        break;
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      writeConsecutiveTranspose();
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      writeConsecutiveTranspose();
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, read non-consecutively, write consecutively +
   * restrict
   */
  bool testWriteConsecutiveRestrictTranspose(int nrow, int ncol,
                                             int repeatTime = 1000,
                                             int warmup     = 100) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      writeConsecutiveRestrictTranspose();
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
        break;
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      writeConsecutiveRestrictTranspose();
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      writeConsecutiveRestrictTranspose();
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, read non-consecutively, write consecutively +
   * restrict
   * + tile by tile */
  bool testWriteConsecutiveRestrictTileTranspose(int nrow, int ncol,
                                                 int repeatTime = 1000,
                                                 int warmup     = 100,
                                                 int tilesize   = 64) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      writeConsecutiveRestrictTileTranspose(tilesize);
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
        break;
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      writeConsecutiveRestrictTileTranspose(tilesize);
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      writeConsecutiveRestrictTileTranspose(tilesize);
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  /* optimization method, read non-consecutively, write consecutively +
   * restrict
   * + tile by tile + openMP */
  bool testWriteConsecutiveRestrictTileOmpTranspose(int nrow, int ncol,
                                                    int repeatTime = 1000,
                                                    int warmup     = 100,
                                                    int tilesize   = 128,
                                                    int threadNum  = 1) {
    init(nrow, ncol, repeatTime, warmup);

    /*=============
      correctness verfication
    =============*/
    int k;
    LOGI("test correctness...");
    for (k = 0; k < _repeatCorrect; ++k) {
      // generate random source data
      genRandomSrcData(0, 255);
      // calculate expected destination data
      naiveTranspose();
      // calculate real destination data
      writeConsecutiveRestrictTileOmpTranspose(tilesize, threadNum);
      // compare real data with expected data
      if (!compare()) {
        LOGE("test correctness, %d-th test failed", k);
        break;
      }
    }
    if (k == _repeatCorrect) {
      LOGI("test correctness, succeeded");
    } else {
      LOGE("test correctness, failed");
      return FAILURE;
    }

    /*=============
      time performance measurement
    =============*/
    // warmup
    for (int i = 0; i < _warmup; ++i) {
      writeConsecutiveRestrictTileOmpTranspose(tilesize, threadNum);
    }

    std::chrono::steady_clock::time_point time_begin =
        std::chrono::steady_clock::now();

    for (int i = 0; i < _repeatTime; ++i) {
      writeConsecutiveRestrictTileOmpTranspose(tilesize, threadNum);
    }
    std::chrono::steady_clock::time_point time_end =
        std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    LOGI("time elapsed on average: %f ms", (float)duration / _repeatTime);

    deinit();

    return SUCCESS;
  }

  ~transposeTest() { deinit(); };

  void deinit() {
    if (_pSrc) {
      delete[] _pSrc;
      _pSrc = nullptr;
    }
    if (_pDst) {
      delete[] _pDst;
      _pDst = nullptr;
    }
    if (_pDstExpect) {
      delete[] _pDstExpect;
      _pDstExpect = nullptr;
    }

    return;
  };

  virtual int run();
};
