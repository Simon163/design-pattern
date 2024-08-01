/*
 *  transposeTest.cpp
 *
 *  Author: Simon (dewen.wu@gmail.com)
 *
 */

#include "transposeTest.h"

int transposeTest::run() {
  bool ret = SUCCESS;

  {
    int nrow       = 256;
    int ncol       = 256;
    int repeatTime = 1000;
    int warmup     = 100;
    int tileSize   = 128;

    LOGI("===naive transposition===");
    if (testBaselineTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write "
        "consecutively===");
    if (testWriteConsecutiveTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict===");
    if (testWriteConsecutiveRestrictTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile===");
    tileSize = 128;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile + openMP===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileOmpTranspose(nrow, ncol, repeatTime,
                                                     warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");
  }

  {
    int nrow       = 1024;
    int ncol       = 1024;
    int repeatTime = 1000;
    int warmup     = 100;
    int tileSize   = 128;

    LOGI("===naive transposition===");
    if (testBaselineTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write "
        "consecutively===");
    if (testWriteConsecutiveTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict===");
    if (testWriteConsecutiveRestrictTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile===");
    tileSize = 128;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile + openMP===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileOmpTranspose(nrow, ncol, repeatTime,
                                                     warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");
  }

  {
    int nrow       = 2048;
    int ncol       = 2048;
    int repeatTime = 1000;
    int warmup     = 100;
    int tileSize   = 128;

    LOGI("===naive transposition===");
    if (testBaselineTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write "
        "consecutively===");
    if (testWriteConsecutiveTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict===");
    if (testWriteConsecutiveRestrictTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile===");
    tileSize = 128;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + tile by tile + openMP===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileOmpTranspose(nrow, ncol, repeatTime,
                                                     warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");
  }

  return ret;
}

TESTREGISTER(transposeTest, "TRANSPOSETEST");
