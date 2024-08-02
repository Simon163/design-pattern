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
    int threadNum  = 3;

    LOGI("===naive transpose===");
    if (testBaselineTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + restrict===");
    if (testRestrictTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 32;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 128;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 256;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 1;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 2;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 3;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 4;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
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
        "restrict + loop tiling===");
    tileSize = 32;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + loop tiling + openMP===");
    tileSize  = 32;
    threadNum = 4;
    LOGI("tileSize = %d", tileSize);
    LOGI("threadNum = %d", threadNum);
    if (testWriteConsecutiveRestrictTileOmpTranspose(
            nrow, ncol, repeatTime, warmup, tileSize, threadNum)) {
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
    int threadNum  = 3;

    LOGI("===naive transpose===");
    if (testBaselineTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + restrict===");
    if (testRestrictTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 32;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 128;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 256;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 1;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 2;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 3;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 4;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
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
        "restrict + loop tiling===");
    tileSize = 32;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + loop tiling + openMP===");
    tileSize  = 32;
    threadNum = 4;
    LOGI("tileSize = %d", tileSize);
    LOGI("threadNum = %d", threadNum);
    if (testWriteConsecutiveRestrictTileOmpTranspose(
            nrow, ncol, repeatTime, warmup, tileSize, threadNum)) {
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
    int threadNum  = 3;

    LOGI("===naive transpose===");
    if (testBaselineTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + restrict===");
    if (testRestrictTranspose(nrow, ncol, repeatTime, warmup)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 32;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 64;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 128;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + loop tiling===");
    tileSize = 256;
    LOGI("tileSize = %d", tileSize);
    if (testTitleTranspose(nrow, ncol, repeatTime, warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 1;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 2;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 3;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI("===naive transpose + openMP===");
    threadNum = 4;
    LOGI("threadNum = %d", threadNum);
    if (testOmpTranspose(nrow, ncol, repeatTime, warmup, threadNum)) {
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
        "restrict + loop tiling===");
    tileSize = 32;
    LOGI("tileSize = %d", tileSize);
    if (testWriteConsecutiveRestrictTileTranspose(nrow, ncol, repeatTime,
                                                  warmup, tileSize)) {
      ret = FAILURE;
    }
    LOGI("done\n");

    LOGI(
        "===optimization method, read non-consecutively, write consecutively + "
        "restrict + loop tiling + openMP===");
    tileSize  = 32;
    threadNum = 4;
    LOGI("tileSize = %d", tileSize);
    LOGI("threadNum = %d", threadNum);
    if (testWriteConsecutiveRestrictTileOmpTranspose(
            nrow, ncol, repeatTime, warmup, tileSize, threadNum)) {
      ret = FAILURE;
    }
    LOGI("done\n");
  }

  return ret;
}

TESTREGISTER(transposeTest, "TRANSPOSETEST");
